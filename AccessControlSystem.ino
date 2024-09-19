#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16x2 LCD
const byte ROWS = 4;                  // Four rows
const byte COLS = 4;                  // Four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};     // Connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3};        // Connect to the column pinouts of the keypad

int greenLED = 10;                     // Digital pin for the green LED
int redLED = 11;                       // Digital pin for the red LED
int buzzerPin = 12;                    // Digital pin for the buzzer
Servo servo;                            // Create a servo object

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char password[] = "1234";              // Set your 4-digit password here
boolean accessGranted = false;

void setup() {
  lcd.init();                          // Initialize the LCD
  lcd.backlight();                     // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Enter code:");

  pinMode(greenLED, OUTPUT);           // Set green LED pin as an output
  pinMode(redLED, OUTPUT);              // Set red LED pin as an output
  pinMode(buzzerPin, OUTPUT);           // Set buzzer pin as an output

  servo.attach(13);                    // Attach the servo to digital pin 13
  servo.write(0);                      // Initialize the servo at 0 degrees

  Serial.begin(9600);
}

void loop() {
  char inputPassword[5] = "    ";       // Initialize an empty input password
  int digitCount = 0;

  while (digitCount < 4) {
    char key = keypad.getKey();
    if (key) {
      lcd.setCursor(digitCount, 1);
      lcd.print('*');                   // Display an asterisk for each digit entered
      inputPassword[digitCount] = key;
      digitCount++;
      delay(100);                       // Debounce
    }
  }

  if (strcmp(inputPassword, password) == 0) {
    lcd.clear();
    lcd.print("Access Granted");
    digitalWrite(greenLED, HIGH);      // Turn on the green LED
    accessGranted = true;

    // Slowly rotate the servo to 90 degrees (or any desired angle)
    for (int pos = 0; pos <= 90; pos++) {
      servo.write(pos);
      delay(15);                        // Adjust the delay to control the speed
    }
    delay(3000);                        // Additional delay
    lcd.clear();
    lcd.print("Enter code:");
    digitCount = 0;                    // Reset the digit count for the next attempt
    memset(inputPassword, ' ', sizeof(inputPassword)); // Clear the input password
    digitalWrite(greenLED, LOW);       // Turn off the green LED
  } else {
    if (accessGranted) {
      // Slowly rotate the servo back to 0 degrees
      for (int pos = 90; pos >= 0; pos--) {
        servo.write(pos);
        delay(15);                       // Adjust the delay to control the speed
      }
      accessGranted = false;
    }
    lcd.clear();
    lcd.print("Access Denied");
    digitalWrite(redLED, HIGH);         // Turn on the red LED
    digitalWrite(buzzerPin, HIGH);      // Turn on the buzzer
    delay(3000);                        // Buzzer duration
    digitalWrite(buzzerPin, LOW);       // Turn off the buzzer
    delay(5000);                        // Additional delay
    lcd.clear();
    lcd.print("Enter code:");
    digitCount = 0;                    // Reset the digit count for the next attempt
    memset(inputPassword, ' ', sizeof(inputPassword)); // Clear the input password
    digitalWrite(redLED, LOW);          // Turn off the red LED
  }
}
