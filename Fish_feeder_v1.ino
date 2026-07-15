#include <ESP32Servo.h>   
// test button disabled for fewer fail points 
// feed time 0900hrs

Servo feederServo;

int servoPin = 5;

// Servo positions
int closedPos = 85;
int openPos = 125;

// Shake range
int shakeLeft = 65;
int shakeRight = 105;

// Timing
unsigned long previousMillis = 0;
const unsigned long interval = 86400000UL; // 24 hours

// Manual testing
const int buttonPin = 7;
int buttonState = 0;

// ====================

void setup() {

  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);

  feederServo.setPeriodHertz(50);

  // Attach servo initially
  feederServo.attach(servoPin, 500, 2400);

  // Move to closed position
  feederServo.write(closedPos);

  Serial.println("Fish feeder started");

  delay(1000);


   feedFish();

  // Start timing from power-on
  previousMillis = millis();

  // Detach to reduce heating
  feederServo.detach();
}

void loop() {

  unsigned long currentMillis = millis();

  // Automatic timed feeding
  if (currentMillis - previousMillis >= interval) {

    previousMillis += interval;

    feedFish();
  }

  // Manual test button
  // testCon();
}

// ===== FEED FUNCTION =====
void feedFish() {

  // Re-attach servo before movement
  feederServo.attach(servoPin, 500, 2400);

  Serial.println("VIOLENT SHAKING");

  // ===== STRONG VIBRATION =====
  for (int i = 0; i < 40; i++) {

    feederServo.write(shakeLeft);
    delay(20);

    feederServo.write(shakeRight);
    delay(20);
  }

  delay(300);

  // ===== OPEN FEEDER =====
  Serial.println("OPENING");

  feederServo.write(openPos);

  // Food dispensing time
  delay(100);

  // ===== CLOSE FEEDER =====
  Serial.println("CLOSING");

  feederServo.write(closedPos);

  // Give servo time to settle
  delay(300);

  // Detach servo to reduce heating
  feederServo.detach();

  Serial.println("Servo detached");
  Serial.println("Cycle complete");
}

// ===== MANUAL TEST BUTTON =====
void testCon() {

  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {

    Serial.println("Manual feed triggered");

    feedFish();

    delay(500);
  }
}