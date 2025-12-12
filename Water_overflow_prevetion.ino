const int trigPin = 9;
const int echoPin = 10;
const int relayPin = 7;

const int lowerThreshold = 2;
const int upperThreshold = 15;
const int resetThreshold = 10;

bool pumpState = false;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, HIGH);
  Serial.println("System Initialized");
}

void loop() {
  long duration, distance;

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= lowerThreshold) {
    digitalWrite(relayPin, HIGH);
    pumpState = false;
    Serial.println("Pump OFF");
  } else if (distance >= resetThreshold && !pumpState) {
    digitalWrite(relayPin, LOW);
    pumpState = true;
    Serial.println("Pump ON");
  } else if (distance > upperThreshold && pumpState) {
    digitalWrite(relayPin, HIGH);
    pumpState = false;
    Serial.println("Pump OFF");
  }

  delay(100);
}