// This is how many color levels the display shows - the more the slower the update
//#define PxMATRIX_COLOR_DEPTH 8

// Defines the buffer height / the maximum height of the matrix
//#define PxMATRIX_MAX_HEIGHT 64

// Defines the buffer width / the maximum width of the matrix
//#define PxMATRIX_MAX_WIDTH 64

// Defines how long we display things by default
//#define PxMATRIX_DEFAULT_SHOWTIME 30

// Defines the speed of the SPI bus (reducing this may help if you experience noisy images)
//#define PxMATRIX_SPI_FREQEUNCY 20000000

// Creates a second buffer for backround drawing (doubles the required RAM)
//#define PxMATRIX_double_buffer true

#include <PxMatrix.h>

// Pins for LED MATRIX

#include <Ticker.h>
Ticker display_ticker;
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_E 0
#define P_OE 2

#define matrix_width 32
#define matrix_height 16

// This defines the 'on' time of the display is us. The larger this number,
// the brighter the display. If too large the ESP will crash
uint8_t display_draw_time=20; //10-50 is usually fine

PxMATRIX display(32,16,P_LAT, P_OE,P_A,P_B,P_C);
//PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);
//PxMATRIX display(64,64,P_LAT, P_OE,P_A,P_B,P_C,P_D,P_E);

// Some standard colors
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(0, 255, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);

uint16_t myCOLORS[8]={myRED,myGREEN,myBLUE,myWHITE,myYELLOW,myCYAN,myMAGENTA,myBLACK};

// ISR for display refresh
void display_updater()
{
  display.display(display_draw_time);
}

void display_update_enable(bool is_enable)
{

 if (is_enable)
   display_ticker.attach(0.002, display_updater);
 else
   display_ticker.detach();

}

void setup() {

 Serial.begin(9600);
  // Define your display layout here, e.g. 1/8 step, and optional SPI pins begin(row_pattern, CLK, MOSI, MISO, SS)
  display.begin(8);
  //display.begin(8, 14, 13, 12, 4);

  // Define multiplex implemention here {BINARY, STRAIGHT} (default is BINARY)
  //display.setMuxPattern(BINARY);

  // Set the multiplex pattern {LINE, ZIGZAG,ZZAGG, ZAGGIZ, WZAGZIG, VZAG, ZAGZIG} (default is LINE)
  //display.setScanPattern(LINE);

  // Rotate display
  //display.setRotate(true);

  // Flip display
  //display.setFlip(true);

  // Helps to reduce display update latency on larger displays
  //display.setFastUpdate(true);

  // Control the minimum color values that result in an active pixel
  //display.setColorOffset(5, 5,5);

  // Set the multiplex implemention {BINARY, STRAIGHT} (default is BINARY)
  //display.setMuxPattern(BINARY);

  // Set the color order {RRGGBB, RRBBGG, GGRRBB, GGBBRR, BBRRGG, BBGGRR} (default is RRGGBB)
  //display.setColorOrder(RRGGBB);

  // Set the time in microseconds that we pause after selecting each mux channel
  // (May help if some rows are missing / the mux chip is too slow)
  //display.setMuxDelay(0,1,0,0,0);

  // Set the number of panels that make up the display area width (default is 1)
  //display.setPanelsWidth(2);

  // Set the brightness of the panels (default is 255)
  //display.setBrightness(50);

  // Set driver chip type
  //display.setDriverChip(FM6124);

  //display.setFastUpdate(true);
  display.clearDisplay();
  display_update_enable(true);

}

unsigned long last_draw=0;
void scroll_text(uint8_t ypos, unsigned long scroll_delay, String text, uint8_t colorR, uint8_t colorG, uint8_t colorB)
{
    uint16_t text_length = text.length();
    display.setTextWrap(false);  // we don't wrap text so it scrolls nicely
    display.setTextSize(1);
    display.setRotation(0);
    display.setTextColor(display.color565(colorR,colorG,colorB));

    // Asuming 5 pixel average character width
    for (int xpos=matrix_width; xpos>-(matrix_width+text_length*5); xpos--)
    {
      display.setTextColor(display.color565(colorR,colorG,colorB));
      display.clearDisplay();
      display.setCursor(xpos,ypos);
      display.println(text);
      delay(scroll_delay);
      yield();

      // This might smooth the transition a bit if we go slow
      // display.setTextColor(display.color565(colorR/4,colorG/4,colorB/4));
      // display.setCursor(xpos-1,ypos);
      // display.println(text);

      delay(scroll_delay/5);
      yield();

    }
}

void loop() {
  scroll_text(1,50,"Hello World!",96,96,250);
  display.clearDisplay();
}
