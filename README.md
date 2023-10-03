# CardinalSense

CardinalSense is a project designed to enhance your orientation by providing real-time direction sensing using a digital compass. It allows you to determine your heading accurately and conveniently, aiding in navigation and orientation tasks.

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

## Dependencies

- [Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)
- [Adafruit_HMC5883_Unified](https://github.com/adafruit/Adafruit_HMC5883_Unified)
- [Wire library](https://www.arduino.cc/en/reference/wire)

Make sure to install these libraries in your PlatformIO project.

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
