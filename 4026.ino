/*
  Author: Kidus Berihun
  Date: October 15, 2024
  Description: This Arduino code simulates the behavior of a CD4026 IC 
               driving a 7-segment display. It increments the number displayed 
               on the 7-segment every time a clock pulse (button press) is detected 
               and resets to 0 when the reset button is pressed.

  Pin Configuration:
    - Pins 3-9: Connected to the segments (a-g) of the 7-segment display.
    - Pin 10: Connected to a push button (simulating the clock input).
    - Pin 11: Connected to a reset button.
*/

int clockPin = 11;  // Pin to simulate the clock input
int resetPin = 12; // Pin to simulate the reset input
int inital_number = 0;  // Start at 0

// Pin mapping for the 7-segment display segments
const int segmentPins[] = {3, 4, 5, 6, 7, 8, 9, 10};  // a, b, c, d, e, f, g , dot(.)

// Define the seven-segment patterns for digits 0-9 and dot(.)
const byte digitPatterns[11][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1, 0},  // 2
  {1, 1, 1, 1, 0, 0, 1, 0},  // 3
  {0, 1, 1, 0, 0, 1, 1, 0},  // 4
  {1, 0, 1, 1, 0, 1, 1, 0},  // 5
  {1, 0, 1, 1, 1, 1, 1, 0},  // 6
  {1, 1, 1, 0, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1, 0},  // 8
  {1, 1, 1, 1, 0, 1, 1, 0},   // 9
  {0, 0, 0, 0, 0, 0, 0, 1} // .
};



void setup() {
  // Set the segment pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  
  pinMode(clockPin, INPUT_PULLUP);  // Button to increment the counter (clock)  with internal pull up resistor
  pinMode(resetPin, INPUT_PULLUP);  // Button to reset the counter with internal pull up resistor
  
  
  displayNumber(inital_number); // Initialize by displaying the number 0
}

void loop() {
  // Check if the clock button is pressed 
  if (digitalRead(clockPin) == LOW) {
    delay(50);  // Debounce delay
    if (digitalRead(clockPin) == LOW) {  // Check again after debounce
      incrementCounter();
      while (digitalRead(clockPin) == LOW);  // Wait until button is released
    }
  }

  // Check if the reset button is pressed
  if (digitalRead(resetPin) == LOW) {
    delay(50);  // Debounce delay
    if (digitalRead(resetPin) == LOW) {  // Check again after debounce
      resetCounter();
      while (digitalRead(resetPin) == LOW);  // Wait until button is released
    }
  }
  
  delay(100);  // Short delay to prevent rapid counting
}

void incrementCounter() {
  inital_number++;  // Increment the count
  if (inital_number > 9) {
    inital_number = 0;  // Roll over to 0 after 9
  }
  displayNumber(inital_number);  // Update the display
}

void resetCounter() {
  inital_number = 0;  // Reset to 0
  displayNumber(initial_number);  // Update the display
}

void displayNumber(int number) {
  // Display the corresponding segments for the given number
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digitPatterns[number][i]);
  }
}
