#include <LiquidCrystal.h>
#include <Servo.h>

const int rs = 4, en = 5, d4 = 0, d5 = 1, d6 = 2, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int resetSignalPin = A5;   // Signal from Arduino2 to enable user input
const int startSignalPin = A4;  // Signal to Arduino2 to start countdown

const int rows[] = {7, 8, 9, 10};
const int cols[] = {13, 12, 11};
const int redPin = A0;
const int greenPin = A1;
const int bluePin = A2;

Servo myServo; // Create a servo object
bool isCorrect = false;
String hashPass = "";
int wrongTimes = 0;
int passD0 = 0, passD1 = 0, passD2 = 0, passD3 = 0;
int pass = -1;
int i = 0;
bool blocked = false;  // Indicates whether input is blocked

unsigned long lastDebounceTime = 0; // To track debounce timing
unsigned long debounceDelay = 200; // Debounce delay in milliseconds
char lastKey = '\0';               // To track the last pressed key

// Keypad layout
char keypad[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

void alertSound() {
    tone(6, 1000, 500);
}

char scanKey() {
    char key = -1;
    for (int r = 0; r < 4; r++) {
        digitalWrite(rows[r], LOW);
        for (int c = 0; c < 3; c++) {
            if (digitalRead(cols[c]) == LOW) {
                key = keypad[r][c];
            }
        }
        digitalWrite(rows[r], HIGH);
    }
    return key;
}

void lightLcd(int mode) {
    if (mode == 1) {
        analogWrite(redPin, 0);
        analogWrite(greenPin, 255);
        analogWrite(bluePin, 0);
    } else if (mode == 0) {
        analogWrite(redPin, 255);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 0);
    }
}

void SavePassword(int d0, int d1, int d2, int d3) {
    pass = (d0 * 1000) + (d1 * 100) + (d2 * 10) + d3;
    lcd.clear();
    lcd.print("Password Saved");
    delay(1000);
    lcd.clear();
}

bool checkPassword(int d0, int d1, int d2, int d3) {
    int newPass = (d0 * 1000) + (d1 * 100) + (d2 * 10) + d3;
    return (newPass == pass);
}

void clearVariables() {
    passD0 = passD1 = passD2 = passD3 = 0;
    i = 0;
    hashPass = "";
}

void setup() {
    pinMode(startSignalPin, OUTPUT);
    pinMode(resetSignalPin, INPUT);

    for (int r = 0; r < 4; r++) 
     pinMode(rows[r], OUTPUT);
    for (int c = 0; c < 3; c++) 
    pinMode(cols[c], INPUT_PULLUP);

    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);


    myServo.attach(A3); // Attach the servo to pin A3
    myServo.write(0);   // Initially close the servo

    lcd.begin(16, 2);
    lcd.print("Set Password");
}

void loop() {

    // Handle keypad input with debounce
    char key = scanKey();
    unsigned long currentTime = millis();
    if (key != '\0' && key != lastKey && (currentTime - lastDebounceTime > debounceDelay)) {
        lastDebounceTime = currentTime;
        lastKey = key;

        if (key >= '0' && key <= '9') {
            if (i == 0)
             passD0 = key - '0';
            else if (i == 1) 
             passD1 = key - '0';
            else if (i == 2) 
             passD2 = key - '0';
            else if (i == 3) 
             passD3 = key - '0';

            hashPass += "*";
            lcd.setCursor(0, 1);
            lcd.print(hashPass);

            i++;
        } else if (key == '*') {
            clearVariables();
            lcd.clear();
            lcd.print((pass == -1) ? "Set Password" : "Enter Password");
        } else if (key == '#') {
            if (i == 4) {
                if (pass == -1) {
                    SavePassword(passD0, passD1, passD2, passD3);
                } else {
                    isCorrect = checkPassword(passD0, passD1, passD2, passD3);
                    lcd.clear();
                    if (isCorrect) {
                        lightLcd(1);
                        lcd.print("Correct!");
                        myServo.write(90); // Open the servo
                        wrongTimes = 0;
                    } else {
                        lightLcd(0);
                        lcd.print("Wrong!");
                        myServo.write(0); // Close the servo
                        wrongTimes++;
                        alertSound();
                        if (wrongTimes >= 3) {
                            lcd.clear();
                            lcd.print("Blocked!");
                            digitalWrite(startSignalPin, HIGH); // Notify Arduino2
                            delay(100);
                            digitalWrite(startSignalPin, LOW);
                            wrongTimes = 0;
                            delay(30000);
                        }
                    }
                }
                clearVariables();
                delay(700);
                lcd.clear();
                lcd.print("Enter Password");
            } else {
                lcd.clear();
                lcd.print("Enter 4 digits!");
                clearVariables();
            }
        }
    } else if (key == '\0') {
        lastKey = '\0'; // Reset lastKey when no key is pressed
    }
}
