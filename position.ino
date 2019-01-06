// Grid position setup
int outOfBounds = 150;
int errorMargin = 20;
int x;
int y;

void setupPosition() {
  // Get the current robot position and rotate it to the x axis;
  determinePosition();
  rotateToPosition(x);
}


/**
   Determines the current position of the moving robot in the grid
*/
void determinePosition() {
  x = getSmallestPosition();
  updateValue(0, 0, "Found x: ");
  updateValue(54, 0, String(x));

  moveToNextWall();

  y = getSmallestPosition();
  updateValue(0, 14, "Found Y: ");
  updateValue(54, 14, String(y));
}

/**
   Move the robot to the new position in the grid

   @param int newX
     The new X value to move to

   @param int newY
     The new Y value to move to
*/
void moveToPosInGrid(int newX, int newY) {
  if (newX > x) {
    x = moveToNewBackwardPos(newX);
  } else {
    x = moveToNewForwardPos(newX);
  }

  rotateToPosition(y);

  if (newY > y) {
    y = moveToNewBackwardPos(newY);
  } else {
    y = moveToNewForwardPos(newY);
  }

  sendNewPosition(x, y);
}

/**
   Move the robot to the next wall
*/
int moveToNextWall() {
  int largest;
  int errorCounter = 0;
  turnAroundRight(TURN_SPEED);
  while (true) {
    distanceCm = calculateDistance();
    if ((largest == NULL) || (largest < distanceCm)) {
      largest = distanceCm;
    }

    if (distanceCm < (largest - 1)) {
      errorCounter++;
    }

    if (errorCounter > errorMargin) {
      break;
    }
  }
  delay(300);
  stopAll();
}

/**
   Get the smallest distance from the robot

   @returns int smallest
     The smallest distance mesured
*/
int getSmallestPosition() {
  int smallest;
  int errorCounter = 0;
  turnAroundRight(TURN_SPEED);
  while (true) {
    distanceCm = calculateDistance();
    if ((smallest == NULL) || (smallest > distanceCm)) {
      smallest = distanceCm;
    }

    if (distanceCm > (smallest + 1)) {
      errorCounter++;
    }

    if (errorCounter > errorMargin) {
      break;
    }
  }
  stopAll();
  return smallest;
}

/**
   Rotate to the new position

   @param int posToMoveTo
     The new location to rotate to
*/
void rotateToPosition(int posToMoveTo) {
  if ((posToMoveTo + 1) > distanceCm && distanceCm < (posToMoveTo + 1)) {
    return;
  }

  turnAroundRight(TURN_SPEED);
  while ((posToMoveTo + 1) < distanceCm && distanceCm > (posToMoveTo + 1)) {
    distanceCm = calculateDistance();
  }
  stopAll();
}

/**
   Let the robot move to its new forward position

   @param int newPos
     New location to move to

   @returns int newPos
     The new location the robot moved to
*/
int moveToNewForwardPos(int newPos) {
  if (distanceCm == newPos) {
    return;
  }

  runStraight(FORWARD, FORWARD_SPEED);
  while ( (int) distanceCm > newPos)
  {
    distanceCm = calculateDistance();
  }
  stopAll();

  return newPos;
}

/**
   Let the robot move to its new backward position

   @param int newPos
     New location to move to

   @returns int newPos
     The new location the robot moved to
*/
int moveToNewBackwardPos(int newPos) {
  if (distanceCm == newPos) {
    return;
  }

  runStraight(BACKWARD, FORWARD_SPEED);
  while ( (int) distanceCm < newPos)
  {
    distanceCm = calculateDistance();
  }
  stopAll();

  return newPos;
}

