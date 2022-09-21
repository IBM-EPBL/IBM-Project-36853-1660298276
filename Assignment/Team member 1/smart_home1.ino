// C++ code
//
int distance = 0;

int sensorLightValue = 0;

int gas = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(13, INPUT);
  pinMode(6, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(7, OUTPUT);
}

void loop()
{
  // Ultrasonic Distance Sensor
  distance = 0.01723 * readUltrasonicDistance(5, 4);
  if (distance > 200 && distance < 300) {
    analogWrite(11, 0);
    analogWrite(9, 102);
    analogWrite(10, 0);
  }
  if (distance > 100 && distance < 200) {
    analogWrite(11, 255);
    analogWrite(9, 102);
    analogWrite(10, 0);
  }
  if (distance <= 100) {
    analogWrite(11, 255);
    analogWrite(9, 0);
    analogWrite(10, 0);
  }
  // Lights when is dark on
  sensorLightValue = analogRead(A0);
  Serial.print("Sensor Light: ");
  Serial.println(sensorLightValue);
  if (sensorLightValue < 77) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
  // PIR Sensor
  if (digitalRead(13) == 1) {
    tone(6, 523, 1000); // play tone 60 (C5 = 523 Hz)
    digitalWrite(2, HIGH);
  } else {
    noTone(6);
    digitalWrite(2, LOW);
  }
  // Gas detector
  gas = analogRead(A1);
  Serial.print("Gas: ");
  Serial.println(gas);
  if (gas > 120) {
    tone(6, 932, 1000); // play tone 70 (A#5 = 932 Hz)
    digitalWrite(7, HIGH);
  } else {
    noTone(6);
    digitalWrite(7, LOW);
  }
  delay(10); // Delay a little bit to improve simulation performance
}