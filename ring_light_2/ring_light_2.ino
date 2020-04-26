// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     2

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  204

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 255 //To change white brightness use value specific to white, do not adjust here

// Analog Brightness Knob
int brightnessKnob = A0; //define the pin for the brightness knob
int inLum = 0; // variable to store data from brightnessKnob
int outLum = 0; //newly mapped value for brightness

//Analog Color Temp Knob
int tempKnob = A1; //define the pin for the color temperature knob
int inTemp = 0; // variable to store data from tempKnob
int outTemp = 0; //newly mapped value for color temperature

//Analog Color Red 
int redKnob = A2;
int inRed = 0; // variable to store the value from hueKnob
int red = 0; // mapped value for color

//Analog Color Green
int greenKnob = A3;
int inGreen = 0; // variable to store the value from hueKnob
int green = 0; // mapped value for color

//Analog Color Blue
int blueKnob = A4;
int inBlue = 0; // variable to store the value from hueKnob
int blue = 0; // mapped value for color


// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  int invertedOutTemp = (outLum - outTemp); 
  inLum = analogRead(brightnessKnob);
  outLum = map(inLum, 1023, 0, 0, 255);
  strip.fill(strip.Color(0, 0, 0, outLum));

  inTemp = analogRead(tempKnob);
  outTemp = map(inTemp, 1023, 0, 0 , outLum); //same as before but now limited to lumOut for brightness control

  strip.fill(strip.Color(red, green, blue, outTemp), 0, 100); // RGB + range of first color temp
  strip.fill(strip.Color(red, green, blue, invertedOutTemp), 100, 204); // RGB + range of second color temp

  //RGB STUFF
  inRed = analogRead(redKnob);
  red = map(inRed, 1023, 0, 0, 255);

  inGreen = analogRead(greenKnob);
  green = map(inGreen, 1023, 0, 0, 255);

  inBlue = analogRead(blueKnob);
  blue = map(inBlue, 1023, 0, 0, 255);

  strip.show(); //this is what makes everything above display.
}