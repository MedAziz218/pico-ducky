
// Struct to represent LED indicators and their states
struct LedIndicators {
  bool numlock;        // Indicates the state of the Num Lock LED
  bool capslock;       // Indicates the state of the Caps Lock LED
  bool scrolllock;     // Indicates the state of the Scroll Lock LED
  bool compose;        // Indicates the state of the Compose LED
  bool kana;           // Indicates the state of the Kana LED
  bool _updated_ = 0;  // Flag to indicate whether any LED state has been updated
} ledIndicators;       // Global instance of the struct for LED indicators

void setup_usb_keyboard() {


  // Set up output report (on control endpoint) for Capslock indicator
  usb_hid.setReportCallback(NULL, hid_report_callback);

  usb_hid.begin();


  // wait until device mounted
  while (!TinyUSBDevice.mounted()) delay(1);
  // start serial
  // turn on built-in led
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // make sure numlock is on
  assure_numlock_and_not_capslock();
  setLanguage(selected_language_n);
}

void deliverPayload(String& payload) {
  int payload_index = 0;
  while (payload_index < payload.length()) {

    uint8_t i = 0;
    uint8_t keycodes[6] = { 0 };
    uint8_t modifier = 0;
    uint8_t const report_id = 0;

    for (int i = 0; i < 6; i++) {
      char chr = payload[payload_index];
      uint8_t temp_modifier = (*conv_table)[chr][0];

      // To send characters in the same frame, they must have the same modifier, and there can't be two consecutive characters that are the same
      if ((temp_modifier != modifier && i > 0) || (payload_index && payload[payload_index - 1] == chr && i > 0)) break;
      else {
        modifier = temp_modifier;
        keycodes[i] = (*conv_table)[chr][1];
        payload_index++;
      }
    }
    if (modifier == RIGHTALT) {
      uint8_t _keycodes[6] = { 0, 0, 0, 0, 0, 0 };
      usb_hid.keyboardReport(report_id, RIGHTALT, _keycodes);
      delay(50);
    }
    sendUSBKeyboardFrame(report_id, modifier, keycodes);
  }
}

void sendUSBKeyboardFrame(uint8_t report_id, uint8_t modifier, uint8_t keycodes[6]) {
  usb_hid.keyboardReport(report_id, modifier, keycodes);

  while (!usb_hid.ready()) {};
  delay(8);

  // usb_hid.keyboardReport(report_id, 0, keycode_empty);
  usb_hid.keyboardRelease(report_id);
  while (!usb_hid.ready()) {};
  delay(4);
}

void sendUSBKeyboardFrame(uint8_t report_id, uint8_t modifier, uint8_t singleKeycode) {
  uint8_t _keycodes[6] = { singleKeycode, 0, 0, 0, 0, 0 };
  sendUSBKeyboardFrame(report_id, modifier, _keycodes);
}


void assure_numlock_and_not_capslock() {
  if (!ledIndicators.numlock) {
    sendUSBKeyboardFrame(0, 0, HID_KEY_NUM_LOCK);
    delay(150);
  }
  // make sure capslock is off
  if (ledIndicators.capslock) {
    sendUSBKeyboardFrame(0, 0, HID_KEY_CAPS_LOCK);
    delay(150);
  }
}
void hid_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
  (void)report_id;
  (void)bufsize;
  // LED indicator is output report with only 1 byte length
  // if (report_type != HID_REPORT_TYPE_OUTPUT) return;

  // The LED bit map is as follows: (also defined by KEYBOARD_LED_* )
  // Kana (4) | Compose (3) | ScrollLock (2) | CapsLock (1) | Numlock (0)
  uint8_t ledIndicatorBits = buffer[0];
  ledIndicators.capslock = ledIndicatorBits & KEYBOARD_LED_CAPSLOCK;
  ledIndicators.numlock = ledIndicatorBits & KEYBOARD_LED_NUMLOCK;
  ledIndicators.scrolllock = ledIndicatorBits & KEYBOARD_LED_SCROLLLOCK;
  ledIndicators.compose = ledIndicatorBits & KEYBOARD_LED_COMPOSE;
  ledIndicators.kana = ledIndicatorBits & KEYBOARD_LED_KANA;

  ledIndicators._updated_ = true;
}
