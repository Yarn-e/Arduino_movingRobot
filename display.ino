// Screen setup
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupDisplay() {
  // Check if the display library works
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  
  // Initialise display
  initDisplay();
}



/**
   Init the display with the fixed text parts.
*/
void initDisplay() {
  Serial.println("Init display");

  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text

  // Measured distance.
  display.setCursor(0, 0);
  display.println("Dist");
  display.setCursor(30, 0);
  display.println("X:");
  display.setCursor(78, 0);
  display.println("Y:");

  // Target.
  display.setCursor(0, 14);
  display.println("Targ");
  display.setCursor(30, 14);
  display.println("X:");
  display.setCursor(78, 14);
  display.println("Y:");

  // Distance.
  display.setCursor(0, 21);
  display.println("Dist");

  display.display();
}

/**
   Print the X-Y position to the screen.

   @param int x
   @param int y
*/
void displayDistance(int x, int y) {
  String distX = String(x);
  String distY = String(y);
  Serial.println("Distance X:" + distX + " Y:" + distY);

  updateValue(42, 0, distX);
  updateValue(90, 0, distY);
}

void displayDistance2(int distance) {
  String dist = String(distance);
  Serial.println("Distance: " + dist);
  updateValue(0, 0, dist);
}

/**
   Print the requested target position.

   @param int x
   @param int y
*/
void displayTarget(String x, String y) {
  Serial.println("Target X:" + x + " Y:" + y);

  updateValue(42, 14, x);
  updateValue(90, 14, y);
}

/**
   Update a value on the given location.

   @param int x
     The x position of the value.
   @param int y
     The y position of the value.
   @param String value
     The value to write to the display.
*/
void updateValue(int x, int y, String value) {
  // Clear first the existing text.
  display.fillRect(x, y, 30, 7, BLACK); // (x, y, w, h)

  // Print the new text.
  display.setCursor(x, y);
  display.println(value);
  display.display();
}

