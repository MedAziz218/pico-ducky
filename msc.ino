

#include "SPI.h"
#include "SdFat.h"
#include "Adafruit_SPIFlash.h"
#include "Adafruit_TinyUSB.h"

#include "flash_config.h"

Adafruit_SPIFlash flash(&flashTransport);
// file system object from SdFat
FatVolume fatfs;
FatFile root;
FatFile file;

// USB Mass Storage object
Adafruit_USBD_MSC usb_msc;

// Check if flash is formatted
bool fs_formatted = false;

// Set to true when PC write to flash
bool fs_changed = true;

void toggle_msc_mode() {

  if (file.open(".state", O_WRITE)) {
    Serial.println("[important]- " + msc_state);
    String new_state;
    if (msc_state == "on") {
      new_state = "msc_state: off  ";
    } else if (msc_state == "off") {
      new_state = "msc_state: on   ";
    }
    int res = file.write(new_state.c_str());
    // file.write('c')

    if (res >= 0)
      Serial.println("[saved]- " + new_state);
    else Serial.println("[error] could not write " + String(res));
    Serial.flush();
    delay(50);
    file.close();
  } else {
    Serial.println("[error] could not open");
  }
}

void fs_setup() {
  if (fs_formatted) return;
  flash.begin();
  fs_formatted = fatfs.begin(&flash);
}
void load_msc_state() {
  bool x = file.open(".state");
  if (x) Serial.println("loading .state --> " + String(x));
  else Serial.println("[error] could not open .state ");

  while (file.available()) {
    String line = "";
    readline(file, line);
    Serial.println("[logging] \n" + line);
    if (line.startsWith("msc_state:")) {
      String temp_msc_state = line.substring(10);
      temp_msc_state.trim();
      temp_msc_state.toLowerCase();

      Serial.println("[read] msc_state: " + temp_msc_state);
      if (temp_msc_state == "on" || temp_msc_state == "off") {
        Serial.println("[loaded] msc_state: " + temp_msc_state);
        msc_state = temp_msc_state;
      }
    }
  }
  file.close();
}
// the setup function runs once when you press reset or power the board
void setup_msc() {
  fs_setup();
  // Set disk vendor id, product id and revision with string up to 8, 16, 4 characters respectively
  usb_msc.setID("Adafruit", "External Flash", "1.0");
  // Set callback
  usb_msc.setReadWriteCallback(msc_read_cb, msc_write_cb, msc_flush_cb);
  // Set disk size, block size should be 512 regardless of spi flash page size
  usb_msc.setCapacity(flash.size() / 512, 512);
  // MSC is ready for read/write
  usb_msc.setUnitReady(true);
  usb_msc.begin();
  


  // Init file system on the flash
}


void msc_loop() {

  // check if formatted
  if (!fs_formatted) {
    fs_formatted = fatfs.begin(&flash);

    if (!fs_formatted) {
      Serial.println("Failed to init files system, flash may not be formatted");
      Serial.println();
      delay(1000);
      return;
    }
  }
  if (fs_changed) {
    fs_changed = false;
    Serial.println("File System Changed");

    load_config();
  }
}

// Callback invoked when received READ10 command.
// Copy disk's data to buffer (up to bufsize) and
// return number of copied bytes (must be multiple of block size)
int32_t msc_read_cb(uint32_t lba, void* buffer, uint32_t bufsize) {
  // Note: SPIFLash Block API: readBlocks/writeBlocks/syncBlocks
  // already include 4K sector caching internally. We don't need to cache it, yahhhh!!
  return flash.readBlocks(lba, (uint8_t*)buffer, bufsize / 512) ? bufsize : -1;
}

// Callback invoked when received WRITE10 command.
// Process data in buffer to disk's storage and
// return number of written bytes (must be multiple of block size)
int32_t msc_write_cb(uint32_t lba, uint8_t* buffer, uint32_t bufsize) {
  digitalWrite(LED_BUILTIN, HIGH);

  // Note: SPIFLash Block API: readBlocks/writeBlocks/syncBlocks
  // already include 4K sector caching internally. We don't need to cache it, yahhhh!!
  return flash.writeBlocks(lba, buffer, bufsize / 512) ? bufsize : -1;
}

// Callback invoked when WRITE10 command is completed (status received and accepted by host).
// used to flush any pending cache.
void msc_flush_cb(void) {
  // sync with flash
  flash.syncBlocks();

  // clear file system's cache to force refresh
  fatfs.cacheClear();

  fs_changed = true;

  digitalWrite(LED_BUILTIN, LOW);
}

void readline(FatFile& file, String& buffer) {

  while (file.available()) {
    char c = file.read();
    if (c == '\n') {
      return;
    } else {
      buffer += c;
    }
  }
}

void save_language_config() {
  bool res = file.open("config.txt", O_RDWR);
  if (res) {
    
    String s = "language: " + selected_language+"\n";
    file.write(s.c_str());
    file.rewind();
    String tt;
    readline(file,tt);
    Serial.println("[logging]- "+tt);

    file.close();
    Serial.println("[saved] saved language ->"+selected_language);
  } else Serial.println("[error] could not open config.txt ");
}
void load_config() {
  if (! file.open("config.txt")){
    Serial.println("[error] could not open file");
    return;
  }
  Serial.println("[info] loading config -"+String(file.available()));
  while (file.available()) {
    String line = "";
    readline(file, line);
    line.trim();
    if (line.startsWith("language:")) {
      String temp_language = line.substring(9);
      temp_language.trim();
      setLanguage(temp_language);
      Serial.println("[loaded] Language: " + temp_language);
      Serial.flush();

    } else if (line.startsWith("payload1:")) {
      String temp_payload1 = line.substring(9);
      temp_payload1.trim();
      payload1 = temp_payload1;
      Serial.println("[loaded] Payload1: " + temp_payload1);
      Serial.flush();

    } else if (line.startsWith("payload2:")) {
      String temp_payload2 = line.substring(9);
      temp_payload2.trim();
      payload2 = temp_payload2;

      Serial.println("[loaded] Payload2: " + temp_payload2);
      Serial.flush();
    } else if (line.startsWith("payload3:")) {
      String temp_payload3 = line.substring(9);
      temp_payload3.trim();
      payload3 = temp_payload3;
      Serial.println("[loaded] Payload3: " + temp_payload3);
      Serial.flush();

    }
  }
  file.close();
}
