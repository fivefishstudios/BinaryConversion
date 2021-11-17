// Binary Conversion
using namespace std;
#include <FastLED.h>
#include <bitset>  

#define FASTLED_INTERNAL
#define LED_PIN     3
#define NUM_LEDS    288
#define BRIGHTNESS  32
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_ROWS    18
#define NUM_COLS    16
#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))
#define NUM_BITS 16

CRGB leds[NUM_LEDS];
int led_pos=0;
int i=0;  // for loop 

// convert X,Y position to a linear array, with zigzag wiring
// position 1,1 is lower-left corner, first row
// first row wiring is left-to-right
// second row wiring is right-to-left
int LEDArrayPosition(int x, int y){
  // do some bounds checking 
  if (x>NUM_COLS) x=NUM_COLS;
  if (x<1) x=1;
  if (y>NUM_ROWS) y = NUM_ROWS;
  if (y<1) y=1;

  if (y%2==0){
    led_pos = ((y) * NUM_COLS) - x;  // even row
  } else {
    led_pos = x + ((y-1) * NUM_COLS) -1;  // odd row 
  }
  return led_pos;
}

// draw a single pixel on the matrix screen at specified color
void DrawPixel(uint8_t x, uint8_t y, CRGB pixelcolor){
  leds[LEDArrayPosition(x, y)] = pixelcolor;
}


// convert decimal N to binary & display on LED Matrix row
void DisplayBinaryOnMatrixLED(byte row, int N){
  bitset<NUM_BITS> B = N;
  for (int i=0;i<NUM_BITS;i++){
    if (B[i])
      DrawPixel(16-i, row, CRGB::Green);
    else
      DrawPixel(16-i, row, CRGB::DarkRed);
  } 
}

void loop() {
  i++;
  for (int r=1;r<=18;r++){ // 18 rows on LED Matrix Display
    DisplayBinaryOnMatrixLED(r, i);  
  }
  FastLED.show(); 
}

void setup() {
  Serial.begin(115200);
  delay( 500 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>
      (leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );  

  // clear whole display
  FastLED.clear(); 
  FastLED.show(); 
}
