// Pins connected to the BCD decoders for tens and ones displays
int bcdPins1[] = {2, 3, 4, 5}; // Pins for tens display
int bcdPins2[] = {6, 7, 8, 9}; // Pins for ones display

int startPin = 1;     // Pin connected to Arduino1's signal
int endSignalPin = 0; // Pin to send the "finished" signal to Arduino1

void setup() {
    // Set up BCD pins as outputs
    for (int i = 0; i < 4; i++) {
        pinMode(bcdPins1[i], OUTPUT);
        pinMode(bcdPins2[i], OUTPUT);
    }

    pinMode(startPin, INPUT);       // Start signal pin as input
    pinMode(endSignalPin, OUTPUT); // End signal pin as output
    digitalWrite(endSignalPin, LOW); // Initialize end signal to LOW
}

void loop() {
    if (digitalRead(startPin) == HIGH) {
        delay(50); // Debounce signal
        if (digitalRead(startPin) == HIGH) {
            // Countdown from 30 to 0
            for (int num = 30; num >= 0; num--) {
                int tens = num / 10;  // Tens digit
                int ones = num % 10; // Ones digit

                // Display the digits on the 7-segment displays
                displayNumber(tens, bcdPins1);
                displayNumber(ones, bcdPins2);

                delay(1000); // 1-second delay
            }

            // Clear the displays after countdown
            clearDisplay(bcdPins1);
            clearDisplay(bcdPins2);

            // Send a signal back to Arduino1
            digitalWrite(endSignalPin, HIGH);
            delay(200); // Hold the signal for a short period
            digitalWrite(endSignalPin, LOW);
        }
    }
}

// Function to display a number on a BCD decoder
void displayNumber(int num, int bcdPins[]) {
    for (int i = 0; i < 4; i++) {
        digitalWrite(bcdPins[i], bitRead(num, i)); // Set each bit
    }
}

// Function to clear the display
void clearDisplay(int bcdPins[]) {
    for (int i = 0; i < 4; i++) {
        digitalWrite(bcdPins[i], LOW); // Clear all bits
    }
}
