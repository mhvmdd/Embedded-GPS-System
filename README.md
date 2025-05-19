# Tiva C GPS Tracking System

A GPS-based location tracking system implemented on the Tiva C microcontroller. This project allows real-time tracking, navigation to predefined locations, nearby location detection, and even includes a fun treasure-hunt-style game — all displayed on an LCD using UART-based GPS data.

---

## 📸 Project Preview

> Add an image of your project setup here (e.g., breadboard, Tiva C, LCD, GPS module, etc.)


markdown
Copy
Edit

---

## 🚀 Features

- **Main Menu Navigation**: Choose between three main functionalities:
  - `Go To`: Navigate to predefined locations like halls, library, mosque, etc.
  - `Game`: Play a treasure hunt game based on GPS coordinates.
  - `Nearby`: Detect and display the closest known location.

- **Real-Time GPS Parsing**: Parses GPS messages and calculates real-time distances.

- **Dynamic LCD Interface**: Provides interactive feedback via a 16x2 LCD display.

- **User Interaction**: Controlled via ADC-based selector and digital push buttons for confirming selections.

- **Celebration Effects**: Uses LED patterns to signal success in finding treasure or reaching destinations.

---

## 🧠 System Architecture

The system uses a layered architecture:
- **MCAL**: Direct Tiva C hardware interfaces (`GPIO`, `UART`, `ADC`, `SysTick`)
- **HAL**: High-level modules (`LCD`, `GPS`, `LED`, `Switch`)
- **APP**: Application logic and main program (`MainMenu`, `GoTo`, `Game`, `Nearby`)

---

## 🛠️ Hardware Used

- **Tiva C LaunchPad (TM4C123GH6PM)**
- **GPS Module (UART interface)**
- **16x2 LCD Display**
- **Push Buttons** (ON/OFF and Confirm)
- **LEDs**
- **Potentiometer** (used for menu selection via ADC)

---

## 📁 Project Structure

├── Program.c # Main application logic
├── Program.h # Function declarations
├── MCAL/ # Hardware abstraction for GPIO, UART, ADC, SysTick
├── HAL/ # Higher-level drivers for LCD, GPS, LEDs, Switches
├── Images/ # Add your hardware/project photos here
└── README.md # Project documentation

yaml
Copy
Edit

---

## ⚙️ Setup Instructions

1. Clone this repository and import it into your IDE (e.g., Keil uVision or Code Composer Studio).
2. Connect the hardware components as described.
3. Flash the code to the Tiva C board.
4. Power the board and enjoy the GPS tracking features via LCD and buttons.

---

## 🎮 Game Mode Explanation

- The system randomly selects a hidden treasure location.
- The user has to physically move toward that location.
- Real-time distance updates are shown.
- Upon reaching the correct location, LEDs celebrate the success.

---

## 📌 Notes

- All GPS data is received via UART5 and parsed in NMEA format.
- The system includes debounce handling for button presses.
- Distances are calculated using the Haversine formula.

---

## 📷 Project Photo

//

---
## 🙏 Acknowledgments
- Thanks to all contributors
