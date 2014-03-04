// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define BACKLIGHT_PIN 3
#define BUTTON_PIN 2 

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

void setup(void) {
  Serial.begin(9600);
  pinMode(BACKLIGHT_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.setRotation(2);
  tft.setCursor(0, 0);
  tft.fillScreen(BLACK);
}

String data = ""; //this will hold the data to print to the lcd
void loop(void) {
  bool receivedData = false; //we need to prove data was received
  
  // Light the backlight if the button is held
  if (digitalRead(BUTTON_PIN) == HIGH) {
    digitalWrite(BACKLIGHT_PIN, HIGH);
  } else {
    digitalWrite(BACKLIGHT_PIN, LOW);
  }
  while (Serial.available()) {
    if (!receivedData) {
      // We started receiving data
      receivedData = true;
      data = "";
    }
    char inChar = (char)Serial.read(); 
    data += inChar;
    
    // The control character will be the pound sign. The presence of this will reset and refresh the screen. 
    // Be careful not to be able to include this symbol in your bash script.
    if (data.indexOf('#') >= 0) {
      tft.setCursor(0, 0);
      tft.fillScreen(BLACK);
      data.replace("#", "");
    }
  }
  // Received data, print to LCD
  if (receivedData) {
    tft.print(data);
    receivedData = false;
  }
  delay(15); // Give the serial some time.
}
