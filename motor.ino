// Motor setup
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motorRight = AFMS.getMotor(1);
Adafruit_DCMotor *motorLeft = AFMS.getMotor(3);

// Motor speed setup
const int SPEED_LEFT = 0;
const int SPEED_RIGHT = 2;
const int FORWARD_SPEED = 100;
const int TURN_SPEED = 100;

void setupMotor() {
  AFMS.begin();  
}


/**
   Stop the left motor.
*/
void stopLeft() {
  //Serial.println("Motor LEFT : STOP");
  motorLeft->run(RELEASE);
}

/**
   Stop the right motor.
*/
void stopRight() {
  //Serial.println("Motor RIGHT : STOP");
  motorRight->run(RELEASE);
}

/**
   Stop all motors.
*/
void stopAll() {
  //Serial.println("STOP ALL");
  stopLeft();
  stopRight();
}

/**
   Run the left motor.

   @param int direction
     The direction to turn.
   @param int speed
     The speed (0-255).
*/
void runLeft(int direction, int speed) {
  //Serial.println("Motor LEFT");
  //Serial.println("  > dir   : " + String(direction));
  //Serial.println("  > speed : " + String(speed));

  speed = speed + SPEED_LEFT;
  if (speed > 255) {
    speed = 255;
  }

  motorLeft->setSpeed(speed);
  motorLeft->run(direction);
}

/**
   Run the right motor.

   @param int direction
     The direction to turn.
   @param int speed
     The speed (0-255).
*/
void runRight(int direction, int speed) {
  //Serial.println("Motor RIGHT");
  //Serial.println("  > dir   : " + String(direction));
  //Serial.println("  > speed : " + String(speed));

  speed = speed + SPEED_RIGHT;
  if (speed > 255) {
    speed = 255;
  }

  motorRight->setSpeed(speed);
  motorRight->run(direction);
}

/**
   Run forward.

   @param int direction
   @param int speed
     The speed (0-255).
*/
void runStraight(int direction, int speed) {
  //Serial.println("Run straight");

  runRight(direction, speed);
  runLeft(direction, speed);
}

/**
   Turn to the left.

   @param direction
   @param int speed
     The speed (0-255).
*/
void turnLeft(int direction, int speed) {
  //Serial.println("Turn to the LEFT");

  stopLeft();
  runRight(direction, speed);
}

/**
   Turn to the right.

   @param int direction
   @param int speed
     The speed (0-255).
*/
void turnRight(int direction, int speed) {
  //Serial.println("Turn to the RIGHT");

  stopRight();
  runLeft(direction, speed);
}

/**
   Turn around to the left.

   @param int speed
     The speed (0-255).
*/
void turnAroundLeft(int speed) {
  //Serial.println("Turn around to the LEFT");

  runLeft(BACKWARD, speed);
  runRight(FORWARD, speed);
}

/**
   Turn around to the right.

   @param int speed
     The speed (0-255).
*/
void turnAroundRight(int speed) {
  //Serial.println("Turn around to the RIGHT");

  runLeft(FORWARD, speed);
  runRight(BACKWARD, speed);
}

