/*
  Modified Arduino Radar Code with LED and Buzzer Alerts
*/

#include <Servo.h>

// Ultrasonic sensor pins
const int trigPin = 10;
const int echoPin = 11;

const int servoPin = 12;
Servo myServo;

// LEDs and buzzer pins
const int redLED = 7;
const int greenLED = 6;
const int buzzerPin = 5;

// Distance threshold in cm
const int threshold = 50;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop() {
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    alertSystem(distance);
    sendData(i, distance);
  }
  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    alertSystem(distance);
    sendData(i, distance);
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58;
  return distance;
}


void alertSystem(int dist) {
  if (dist > 0 && dist <= threshold) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);

    int beepDelay = map(dist, 1, threshold, 50, 300); // Closer = faster beep
    digitalWrite(buzzerPin, HIGH);
    delay(5);
    digitalWrite(buzzerPin, LOW);
    delay(beepDelay);
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzerPin, LOW);
  }
}

void sendData(int angle, int dist) {
  Serial.print(angle);
  Serial.print(",");
  Serial.print(dist);
  Serial.print(".");
}