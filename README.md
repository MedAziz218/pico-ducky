# Pico Ducky: Raspberry Pi Pico based RubberDucky
<div style="display: flex; flex-wrap: wrap;">
    <img src="https://github.com/MedAziz218/pico-ducky/assets/118969900/eadd0037-6a4c-4794-b8d9-46cc107d04eb" alt="picoducky" width="30%" />
    <img src="https://github.com/MedAziz218/pico-ducky/assets/118969900/6e7ede7c-d1a4-4986-bdf4-2d9121e4b3bc" alt="Animated GIF" style="width: min(62%, 400px);" />
</div>

## Description
This code allows the Raspberry Pi Pico to function as a USB HID keyboard, capable of executing predefined payloads (commands) on Windows machines through the "Run Command" window (Win+R).

## Features
- Stores up to 3 payloads simultaneously.
- Supports both QWERTY and AZERTY keyboard layouts.
- Easy payload customization without re-uploading the code.

## Usage Instructions
The functionality of the Pico Ducky is controlled using the built-in bootsel button on the Raspberry Pi Pico:
- **Short Press:** Injects payload 1.
- **Double Short Press:** Injects payload 2.
- **Triple Short Press:** Injects payload 3.
- **Long Press:** Switches between QWERTY and AZERTY layouts.
- **Short Press followed by Long Press:** Enters setup mode, allowing the Pico to appear as a flash drive with a "config.txt" file. Edit and save payloads directly on the Pico. Repeat button strokes to exit setup mode.

## Installation Instructions
1. Set up the Earle F. Philhower III Arduino-Pico environment in ArduinoIDE. Details can be found [here](https://github.com/earlephilhower/arduino-pico?tab=readme).
2. Clone this repository and open it in ArduinoIDE.
3. Navigate to `Tools` > `Boards` > `Raspberry Pi Pico/RP2040`, then select your Pico.
4. Choose an appropriate flash size under `Tools` > `Flash Size` (ensure it has FS for filesystem support).
5. Select `Adafruit Tiny USB` as the USB stack under `Tools`.
6. Upload the sketch to the Pico.
7. Upon the first upload, a new USB flash drive will be mounted on your PC (if prompted to format, do so).
8. Copy the `.state` and `config.txt` files from the `data` folder in this repository to the Pico's USB drive.
9. [Optional] Rename your Pico USB flash drive if desired.
10. Unplug and replug the device to complete the setup.

You're now ready to use your Pico Ducky! Refer to the usage instructions above and have fun experimenting with your new tool.

## Project Background
This project was developed as part of my cybersecurity class project in my second year of computer science engineering degree at ENSI (National School of Computer Science) in Tunisia. The full report of the project, detailing its objectives, methodology, and outcomes, can be found [here](docs/pico-ducky_project_report.md)

This project served as the foundation for a broader cybersecurity project, utilizing the BadUSB functionality to launch a reverse shell attack on any Windows victim machine.

## Disclaimer
This project was created for educational and learning purposes only. The creators do not condone or support any illegal or unethical use of the information or tools provided. The use of this project to execute unauthorized actions on any system without explicit permission is strictly prohibited. The creators shall not be held responsible for any misuse or consequences resulting from the use of this project.
