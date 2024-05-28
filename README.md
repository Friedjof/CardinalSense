# CardinalSense

CardinalSense is a project designed to enhance your orientation by providing real-time direction sensing using a digital compass. It allows you to determine your heading accurately and conveniently, aiding in navigation and orientation tasks.

> This is currently a work in progress. The project is still in its early stages of development. Images and additional information will be added soon.

## Features

- Accurate heading information: Utilizes a digital compass (e.g., GY-271) to provide precise direction data.
- Orientation assistance: Helps you find the cardinal directions (North, South, East, West) and everything in between.
- Wearable integration: Ideal for incorporating into a belt or wearable device for hands-free orientation support.

## Getting Started

Follow these steps to get started with CardinalSense:

1. **Hardware Setup**: Connect your digital compass (e.g., GY-271) and vibration sensors (in this case 16) to your ESP32/ESP8266 or compatible microcontroller.

2. **Software Setup**: Upload the Arduino code provided in this repository to your ESP32/ESP8266.

3. **Calibration (if needed)**: Depending on your specific setup, you may need to calibrate your compass for accurate readings.

4. **Usage**: Once everything is set up, CardinalSense will provide you with real-time direction information based on your compass readings.

### Flashing
In the release section, you can find the latest binary files for the microcontrollers. You can use the following commands to flash the binary files to the `ESP32` or `ESP8266` microcontroller.

You need to install the esptool first.
```bash
pip install esptool
```
You can also use the nix-shell to get a shell with all dependencies installed `nix-shell`.

#### *firmware.bin, bootloader.bin and partitions.bin (ESP32)*
```bash
esptool.py --port /dev/ttyUSB0 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 bootloader.bin 0x8000 partitions.bin 0x10000 firmware.bin
```
Change the `--port` parameter to match your system configuration and the path to the binary files.

#### *firmware.bin (ESP8266)*
```bash
esptool.py --port /dev/ttyUSB0 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x10000 firmware.bin
```
Change the `--port` parameter to match your system configuration and the path to the binary files.

## Dependencies

- [Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)
- [Adafruit_HMC5883_Unified](https://github.com/adafruit/Adafruit_HMC5883_Unified)
- [Wire library](https://www.arduino.cc/en/reference/wire)

Make sure to install these libraries in your PlatformIO project.

## The name "CardinalSense"
CardinalSense is a project name that combines two key elements: "Cardinal" and "Sense."

1. **Cardinal**: In the context of navigation and orientation, "Cardinal" refers to the four primary directions on the compass—North, South, East, and West. These cardinal directions serve as fundamental reference points for navigation and provide a basis for understanding one's orientation.

2. **Sense**: "Sense" signifies the ability to perceive or detect something. In this project, it represents the core functionality of enhancing your orientation by providing a real-time "sense" or awareness of your current heading or direction.

Together, "**CardinalSense**" encapsulates the primary goal of the project, which is to provide a sensing mechanism for cardinal directions, helping users gain a better understanding of their orientation, particularly in relation to the cardinal points on the compass.

This project's name emphasizes its capability to detect and convey cardinal directions accurately, contributing to improved navigation and orientation experiences.

## Contributing

If you would like to contribute to CardinalSense, please open an issue or submit a pull request. We welcome contributions and improvements from the community.

## License

This project is licensed under the MIT License.

## Acknowledgments

- Thanks to the Arduino community for providing libraries and resources for compass interfacing.
- Inspiration for this project came from the need for hands-free orientation support in various outdoor activities.

## Contact

For questions or inquiries, feel free to contact the project maintainer:

- [Friedjof Noweck](https://github.com/friedjof)
