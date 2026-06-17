// Smart Navigation for Blind Kids
// Pins definition
const int trigPin = 9;   // Ultrasonic Sensor Trig Pin
const int echoPin = 10;  // Ultrasonic Sensor Echo Pin
const int buzzerPin = 11; // Buzzer/Vibration Motor Pin

// Variables for distance calculation
long duration;
int distance;

void setup() {
  // Initialize pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Start Serial Communication for debugging
  Serial.begin(9600);
  Serial.println("Smart Navigation System Initialized.");
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor by sending a 10-microsecond pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters
  // Speed of sound wave divided by 2 (go and back)
  distance = duration * 0.034 / 2;
  
  // Print distance to Serial Monitor for tracking
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Logic for Obstacle Alerts
  if (distance > 0 && distance <= 20) {
    // Critical Distance: Dangerously close! Continuous beep.
    digitalWrite(buzzerPin, HIGH);
    delay(50); 
  } 
  else if (distance > 20 && distance <= 50) {
    // Warning Distance: Obstacle ahead. Fast intermittent beeping.
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  } 
  else if (distance > 50 && distance <= 100) {
    // Safe Alert: Distance closing. Slow intermittent beeping.
    digitalWrite(buzzerPin, HIGH);
    delay(300);
    digitalWrite(buzzerPin, LOW);
    delay(300);
  } 
  else {
    // No obstacle nearby
    digitalWrite(buzzerPin, LOW);
  }

  delay(60); // Small delay for stability
}