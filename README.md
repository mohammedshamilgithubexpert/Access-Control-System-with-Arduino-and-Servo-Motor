# Access-Control-System-with-Arduino-and-Servo-Motor

The Access Control System utilizes an Arduino and servo motor for secure entry via keypad or RFID authentication. It includes LED feedback and is designed for easy installation. Future upgrades may include mobile app integration. Contributions are welcome under the MIT License.
# Access Control System with Arduino and Servo Motor

****************************************************************************************************************************************************************************
## Historical Context and IoT Relevance

Arduino was created in 2003 by a group of students at the Interaction Design Institute Ivrea (IDII) in Ivrea, Italy, to simplify electronics for non-experts. A group of students, including Massimo Banzi and David Cuartielles, aimed to create an accessible platform for rapid prototyping of electronic projects. Its open-source philosophy and user-friendly programming language and IDE made it accessible to a wide audience. Arduino's modularity, strong community, and global reach have had a significant impact on the maker and IoT communities. It continues to evolve and inspire both open-source and commercial products, supporting a wide range of applications and projects worldwide.

In the context of the Internet of Things (IoT), Arduino has emerged as a foundational tool for developing and prototyping connected devices. By simplifying hardware and software development, Arduino has empowered creators worldwide to craft smart, interconnected solutions that are transforming our modern world.

****************************************************************************************************************************************************************************

## Introduction

The "Access Control System with Arduino and Servo Motor" is a sophisticated project that showcases the integration of various electronic components to create a secure access control solution. This project employs an Arduino microcontroller, a 16x2 LCD display, a 4x4 Matrix Keypad, a servo motor, a buzzer, and LEDs to grant or deny access based on a pre-defined 4-digit password. When access is granted, the servo motor moves to a specific angle, visually indicating authorized entry. In the event of unauthorized access, the servo returns to its initial position, and an alarm sounds. This system is designed to enhance security and provide a user-friendly interface for both educational and practical applications.

****************************************************************************************************************************************************************************
## Components

The following components are integral to the success of this project:

- **Arduino Board**: The project is built on an Arduino platform, such as the Arduino Uno, serving as the central control unit.
- **16x2 LCD Display**: An LCD display with an I2C module is utilized for displaying system messages and feedback to the user.
- **4x4 Matrix Keypad**: A keypad enables users to input a 4-digit password for access control.
- **Servo Motor**:A servo motor is responsible for physically controlling access.
   It rotates to a specified angle when access is granted and returns to its initial position when denied.
- **Buzzer**: A buzzer provides audible feedback to indicate access status.
- **Green and Red LEDs**: These LEDs are used to signal access granted and access denied, respectively.
- **Jumper Wires**: These wires are crucial for connecting the components and facilitating communication between them.
- **Power Source for Servo**: In some cases, an external power source may be necessary to ensure the servo receives sufficient power.

****************************************************************************************************************************************************************************
-----------------------
## Procedure
-----------------------
### Components Needed:

- Arduino Uno
- S90 Servo Motor
- I2C 16x2 LCD
- Keypad
- Buzzer
- Green and Red LEDs
- Small Breadboard
- Jumper Wires

**************************************************************************************************************************************************************************
### Step 1: Set Up the Circuit

1. Connect the I2C LCD to the Arduino.
2. Connect the servo motor to the Arduino.
3. Connect the keypad, buzzer, green LED, and red LED to the Arduino.
4. Ensure all components are powered appropriately.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Step 2: Install Required Libraries

- To use the I2C LCD, install the "LiquidCrystal_I2C" library from the Arduino Library Manager.
- To control the servo, no additional libraries are required.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Step 3: Check the LCD

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address may vary; use an I2C scanner to find the correct one.

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("LCD is working!");
}

void loop() {
  // Nothing to do here for now
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

**###Step 4: Test the Keypad**

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}
void loop() {
  char key = keypad.getKey();
  if (key) {
    lcd.setCursor(0, 1);
    lcd.print(key);   // Store key and check for correct password logic
  }
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

**Step 5: Check the Buzzer**
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int buzzerPin = 10;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  pinMode(buzzerPin, OUTPUT);
}
void loop() {
  tone(buzzerPin, 1000);
  delay(500);
  noTone(buzzerPin);
  delay(500);
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

**Step 6: Check the LEDs**

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int greenLedPin = 11;
int redLedPin = 12;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LEDs Testing");
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
}
void loop() {
  digitalWrite(greenLedPin, HIGH);
  delay(1000);
  digitalWrite(greenLedPin, LOW);
  delay(1000);
  digitalWrite(redLedPin, HIGH);
  delay(1000);
  digitalWrite(redLedPin, LOW);
  delay(1000);
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

**Step 7: Integrate All Components**
Component	                 |  Arduino Pin           	  | Notes
I2C LCD (SDA)                	A4	                      Connect to Breadboard for Power and Ground
I2C LCD (SCL)               	A5	                      Connect to Breadboard for Power and Ground
Keypad Rows	                  6, 7, 8, 9	              Connect to Breadboard for Ground
Keypad Columns	              2, 3, 4	                  Connect to Breadboard for Pull-up Resistors
Green LED	                    10	                      Connect to Breadboard for Resistor and Ground
Red LED	                      11                       	Connect to Breadboard for Resistor and Ground
Buzzer	                      12	                      Connect to Breadboard for Resistor and Ground
Servo Motor	                  13	                      Connect to Breadboard for Power and Ground
Breadboard Power	            5V, GND                   Connect to Arduino for Power

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

These connections should help you set up the keypad lock system with the mentioned components. Make sure to add resistors where needed for the LEDs and set up the servo and other components according to the code and the components' datasheets.

Combine the codes and logic to create your keypad lock system. You'll need to add the password logic and servo control for the door lock/unlock functionality. Use the Servo library to control the servo motor. Make sure to replace "YourPassword" with your desired password.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------
**Code Overview**
-----------------
The Arduino code underpinning this project governs various crucial aspects, including:

**Initialization**: The code initializes the LCD, keypad, servo motor, and relevant pins.
**Password Definition**: A 4-digit password is predefined as a variable.
**User Interaction**: The system awaits user input via the keypad.
**Access Control**: When the correct password is entered, access is granted. The servo motor rotates to 90 degrees, and the green LED illuminates.
**Unauthorized Access**: In the case of an incorrect password, access is denied. The servo reverts to 0 degrees, the red LED signals denial, and the buzzer emits a brief alarm.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
_________________
**Key Benefits**
_________________

**Enhanced Security**: The system bolsters security by enforcing a password-based access control mechanism, effectively preventing unauthorized entry, making it suitable for locking doors, cabinets, or other access points.
**User-Friendly Interface**: The integration of a keypad and LCD display ensures a seamless user experience, allowing individuals to input their passwords and receive clear access status feedback.
**Customization**: The system is highly adaptable, allowing for easy adjustments to the password or the incorporation of advanced features, including remote monitoring or integration into larger IoT projects.
**Learning Opportunity**: Building this project helps you learn and practice electronics, coding, and the integration of different components, enhancing your knowledge and skills.
**Low-Cost Solution**: This project can be implemented with relatively low-cost components, making it accessible for educational purposes or personal projects.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

**Conclusion**

The Access Control System with Arduino and Servo Motor presents an engaging and informative way to explore electronics and programming while delivering practical security benefits. With a simple password-based mechanism and visual feedback, this project highlights the potential of Arduino in creating effective IoT solutions. Whether for educational purposes or personal use, this project is a valuable endeavour for hobbyists and learners alike.

***************************************************************************************************************************************************************************
Feel free to copy and paste this structure into your `README.md` file! Let me know if you need any further adjustments.

