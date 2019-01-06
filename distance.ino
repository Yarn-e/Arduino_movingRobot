// Distance config
const int dist_trigPin = 9;
const int dist_echoPin = 10;
/**
   Initialise the pins for the distance sensor
*/
void setupDistance() {
  pinMode(dist_trigPin, OUTPUT);
  pinMode(dist_echoPin, INPUT);
}

/**
    Measure the distance

    @returns Float dist
      The calculated distance
*/
float calculateDistance() {
  digitalWrite(dist_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(dist_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(dist_trigPin, LOW);
  const unsigned long duration = pulseIn(dist_echoPin, HIGH);
  int dist = duration / 29 / 2;
  updateValue(0, 21, "dist:");
  updateValue(30, 21, String(dist));
  return dist;
}

