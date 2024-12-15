# Security Keypad Embedded System

## Overview
This project is an **Embedded System** implementation for a Security Keypad. It features a password-protected system that authenticates users and allows access based on predefined logic. The project is designed to work on a microcontroller, with hardware and software components integrated to achieve a secure and functional setup.

---

## Features
- **User Authentication:** Users must input the correct password to gain access.
- **Password Change Option:** Users can update the password securely.
- **Alert System:** Triggers alerts upon incorrect password attempts.
- **Hardware Integration:** Includes keypad input and output display on an LCD.
- **Embedded Software:** Developed in C using AVR microcontroller libraries.

---

## Components
### Hardware:
1. **Microcontroller:** AVR (e.g., ATmega32 or equivalent).
2. **Keypad:** 4x4 matrix keypad for user input.
3. **LCD:** 16x2 LCD for displaying messages.
4. **Buzzer:** Used for alerts or error indications.
5. **Power Supply:** Standard 5V DC.
6. **Wires and Resistors:** For proper connections.

### Software:
1. Embedded C code, developed using:
   - AVR-GCC Compiler.
   - Atmel Studio or equivalent IDE.
2. Libraries:
   - LCD control library.
   - Keypad scanning library.
   - EEPROM library for password storage.

---

## How to Use
### Setup:
1. Connect the hardware components as per the circuit diagram provided in the repository.
2. Flash the microcontroller with the provided firmware.
3. Power on the system.

### Default Password:
The default password is `1234`. This can be changed after initial setup.

### Operation:
1. Enter the password on the keypad.
   - If correct, access is granted, and a success message is displayed.
   - If incorrect, an error message is displayed, and the buzzer will sound.
2. To change the password, follow the instructions on the LCD.
3. After 3 incorrect attempts, the system locks and triggers an alert.

---

## Repository Structure
```
Security-Keypad-Embedded-System/
├── Documentation/
│   ├── CircuitDiagram.pdf   # Circuit schematic for hardware setup
│   ├── Flowchart.png        # System flowchart
│   └── ProjectDescription.txt
├── SourceCode/
│   ├── main.c               # Main application logic
│   ├── lcd.c                # LCD driver
│   ├── keypad.c             # Keypad driver
│   └── eeprom.c             # EEPROM driver for password handling
├── README.md                # Project documentation (this file)
└── LICENSE                  # License information
```

---

## Installation and Compilation
1. Clone the repository:
   ```bash
   git clone https://github.com/Eman288/Security-Keypad-Embedded-System.git
   ```
2. Open the project in Atmel Studio or another AVR development environment.
3. Connect your microcontroller to the programmer.
4. Compile and flash the code to the microcontroller.

---

## How It Works
1. The system initializes and displays a welcome message on the LCD.
2. The user inputs a password using the keypad.
3. The password is checked against the stored value in the EEPROM:
   - **Correct Password:** Grants access.
   - **Incorrect Password:** Increments the failed attempt counter and triggers an alert after 3 consecutive failures.
4. The user can update the password through a secure procedure.

---

## Future Enhancements
- Add support for an RTC (Real-Time Clock) module for logging failed attempts.
- Introduce a mobile app interface via Bluetooth for remote password management.
- Implement a fingerprint scanner for multi-factor authentication.

---

## Contributing
Contributions are welcome! If you have suggestions or enhancements, feel free to submit a pull request or open an issue in the repository.

---

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---

## Contact
For questions or support, please reach out to the repository owner:
- **Name:** Eman288
- **Email:** [Your Email Here]
- **GitHub Profile:** [https://github.com/Eman288](https://github.com/Eman288)

---

Thank you for checking out this project! Your feedback and contributions are greatly appreciated.


