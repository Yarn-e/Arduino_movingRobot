// 433mhz transmitter setup
RH_ASK driver;


void setupComm() {
  // Initialise 433mhz
  if (!driver.init()) {
    Serial.println("init failed");
  }
}

/**
   Decodes the recieved message to the 2 positions to move to.

   @param String message
     The recieved message.
*/
void moveToLocationViaMessage(String message) {
  int firstNumber = message.indexOf(':');
  int secondNumber = message.indexOf(':', firstNumber + 1);

  String xToMoveTo = message.substring((firstNumber) + 1, (firstNumber + 5));
  String yToMoveTo = message.substring((secondNumber) + 1, (secondNumber + 5));

  moveToPosInGrid(xToMoveTo.toInt(), yToMoveTo.toInt());
}

/**
   Send the new position the robot moved to.

   @param int xpos
     The current X position
   @param int ypos
     The current Y position
*/
void sendNewPosition(int xpos, int ypos) {
  for (int i = 0; i < 3; i++) {
    Serial.println("Sending data");
    String message = "Robot moved to its position, X: " + convertPosToRightLength(String(xpos)) + " Y: " + convertPosToRightLength(String(ypos));
    const char *msg = message.c_str();
    Serial.println(message);
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
  }
}

/**
   Convert the current position to a uniform length

   @param String pos
     The position that needs converting

   @return String pos
     The converted position
*/
String convertPosToRightLength(String pos) {
  while (pos.length() != 4) {
    pos = "0" + pos;
  }
  return pos;
}


void checkMessage() {
  uint8_t buf[13];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    //If we get a message, move to the new location
    moveToLocationViaMessage(buf);
  }
}

