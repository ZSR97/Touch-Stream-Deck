#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"
#include "Keyboard.h"
//#include <iostream>

//-------------------------Pins Pro Micro----------------------------------
//-------------------------------------------------------------------------
// MOSI=16, MISO=14, SCK=15
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


//------------For the Adafruit shield, these are the default.--------------
//-------------------------------------------------------------------------
#define TS_CS 7
#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


//-------------------------Touch Calibration-------------------------------
//-------------------------------------------------------------------------

/*
#define TS_MINX 3800
#define TS_MAXX 100
#define TS_MINY 100
#define TS_MAXY 3750
*/

#define TS_MINX 100
#define TS_MAXX 3800
#define TS_MINY 100
#define TS_MAXY 3750

 /*
 #define TS_MINX 150
 #define TS_MINY 130
 #define TS_MAXX 3800
 #define TS_MAXY 4000 
*/

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


//------------------------------Keyboard-----------------------------------
//-------------------------------------------------------------------------	
// Note: Uncomment only the keys that you are using to take as less memory
// as possible.
//-------------------------------------------------------------------------

//#define KEY_LEFT_CTRL		0x80
//#define KEY_LEFT_SHIFT		0x81
//#define KEY_LEFT_ALT		0x82
//#define KEY_LEFT_GUI		0x83
//#define KEY_RIGHT_CTRL		0x84
//#define KEY_RIGHT_SHIFT		0x85
//#define KEY_RIGHT_ALT		0x86
//#define KEY_RIGHT_GUI		0x87

//#define KEY_UP_ARROW		0xDA
//#define KEY_DOWN_ARROW		0xD9
//#define KEY_LEFT_ARROW		0xD8
//#define KEY_RIGHT_ARROW		0xD7
//#define KEY_BACKSPACE		0xB2
//#define KEY_TAB				0xB3
//#define KEY_RETURN			0xB0
//#define KEY_ESC				0xB1
//#define KEY_INSERT			0xD1
//#define KEY_DELETE			0xD4
//#define KEY_PAGE_UP			0xD3
//#define KEY_PAGE_DOWN		0xD6
//#define KEY_HOME			0xD2
//#define KEY_END				0xD5
//#define KEY_CAPS_LOCK		0xC1


//----------------------------Function Keys--------------------------------

//#define KEY_F1				0xC2
//#define KEY_F2				0xC3
//#define KEY_F3				0xC4
//#define KEY_F4				0xC5
#define KEY_F5				0xC6
#define KEY_F6				0xC7
#define KEY_F7				0xC8
#define KEY_F8				0xC9
#define KEY_F9				0xCA
#define KEY_F10				0xCB
#define KEY_F11				0xCC
#define KEY_F12				0xCD
//#define KEY_F13				0x68
//#define KEY_F14				0x69
//#define KEY_F15				0x6A
//#define KEY_F16				0x6B
//#define KEY_F17				0x6C
//#define KEY_F18				0x6D
//#define KEY_F19				0x6E
//#define KEY_F20				0x6F
//#define KEY_F21				0x70
//#define KEY_F22				0x71
//#define KEY_F23				0x72
//#define KEY_F24				0x73
//#define KEY_F24				0x73

//-----------------------Missing sound control keys------------------------

#define KEY_MUTE				0x7F
#define KEY_VOLUMEUP			0x80
#define KEY_VOLUMEDOWN		0x81

//------------------------------Numeric keypad-----------------------------

//#define KEY_KEYPAD_0			0x62
//define KEY_KEYPAD_1			0x59
//#define KEY_KEYPAD_2			0x5A
//#define KEY_KEYPAD_3			0x5B
//#define KEY_KEYPAD_4			0x5C
//#define KEY_KEYPAD_5			0x5D
//#define KEY_KEYPAD_6			0x5E
//#define KEY_KEYPAD_7			0x5F
//#define KEY_KEYPAD_8			0x60
//#define KEY_KEYPAD_9			0x61
//#define KEY_KEYPAD_DECIMAL		0x63
//#define KEY_KEYPAD_ENTER		0x58
//#define KEY_KEYPAD_PLUS		0x57
//#define KEY_KEYPAD_MINUS		0x56
//#define KEY_KEYPAD_MULTIPLY		0x55
//#define KEY_KEYPAD_DIVIDE		0x54
//#define KEY_KEYPAD_NUMLOCK		0x53
//#define KEY_KEYPAD_EQUALS		0x67

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------



// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC

XPT2046_Touchscreen ts(TS_CS);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
Adafruit_GFX_Button btn, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9, btn10, btn11, btn12;

// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setup() {
  Serial.begin(38400);
  Serial.setTimeout(10);

//-----------------------Deselect all SPI Devices--------------------------
//-------------------------------------------------------------------------

  pinMode(TFT_CS, OUTPUT);
  pinMode(TS_CS, OUTPUT);
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(TS_CS, HIGH);


//--------------------------Start the devices------------------------------
//-------------------------------------------------------------------------
  
  //Start the keyboard
  Keyboard.begin();

  //Start the TFT Screen
  tft.begin();

  //Start the touch Screen
  ts.begin();

  //Set TFT and Touch Screen rotation
  ts.setRotation(-1);
  tft.setRotation(1);
  
  //Set the TFT Screen background color to black
  tft.fillScreen(ILI9341_BLACK);


//---------------------Screen Layout and Settings--------------------------
//-------------------------------------------------------------------------

  //Colors
  #define BLACK 0x0000
  #define WHITE 0xFFFF
  
  #define YELLOW 0xCDE0
  #define AMBER 0x9384
  #define ORANGE 0xE360
  #define VERMELLON 0xF9E7
  #define RED 0xF800
  #define MAGENTA 0xF81F
  #define PURPLE 0x4070
  #define VIOLET 0xBB9F
  #define BLUE 0x001F
  #define TEAL 0x4E11
  #define GREEN 0x0620
  #define PINK 0xC116

  //If you want to use personalized color you can use this color picker http://www.barth-dev.de/online/rgb565-color-picker/

  //Button width
  int btnWidth = 60;

  // Font settings
  uint8_t fontSize = 1;
  uint16_t fontColor = BLACK;

  // Button Border colors
  uint16_t btnBorderColor[3][4] = {
                    {YELLOW, AMBER, ORANGE, VERMELLON},
                    {RED, MAGENTA, PURPLE, VIOLET},
                    {BLUE, TEAL, GREEN, PINK}
                  };


  // Button Background colors
  uint16_t btnBackgroundColor[3][4] = {
                    {YELLOW, AMBER, ORANGE, VERMELLON},
                    {RED, MAGENTA, PURPLE, VIOLET},
                    {BLUE, TEAL, GREEN, PINK}
                  };
                  
  // Button Labels
  const char *btnLabel[3][4] = {
                    {"YELLOW", "AMBER"," ORANGE", "VERMELLON"},
                    {"RED", "MAGENTA", "PURPLE", "VIOLET"},
                    {"BLUE", "TEAL", "GREEN", "PINK"}
                  };


//----------------------------First row------------------------------------

  btn.initButton(&tft, 40, 40, btnWidth, btnWidth, btnBorderColor[0][0], btnBackgroundColor[0][0], fontColor, btnLabel[0][0], fontSize);
  btn.drawButton();
  btn2.initButton(&tft, 120, 40, btnWidth, btnWidth, btnBorderColor[0][1], btnBackgroundColor[0][1], fontColor, btnLabel[0][1], fontSize);
  btn2.drawButton();  
  btn3.initButton(&tft, 200, 40, btnWidth, btnWidth, btnBorderColor[0][2], btnBackgroundColor[0][2], fontColor, btnLabel[0][2], fontSize);
  btn3.drawButton();  
  btn4.initButton(&tft, 280, 40, btnWidth, btnWidth, btnBorderColor[0][3], btnBackgroundColor[0][3], fontColor, btnLabel[0][3], fontSize);
  btn4.drawButton();  

//----------------------------Second Row-----------------------------------

  btn5.initButton(&tft, 40, 120, btnWidth, btnWidth, btnBorderColor[1][0], btnBackgroundColor[1][0], fontColor, btnLabel[1][0], fontSize);
  btn5.drawButton();  
  btn6.initButton(&tft, 120, 120, btnWidth, btnWidth, btnBorderColor[1][1], btnBackgroundColor[1][1], fontColor, btnLabel[1][1], fontSize);
  btn6.drawButton();  
  btn7.initButton(&tft, 200, 120, btnWidth, btnWidth, btnBorderColor[1][2], btnBackgroundColor[1][2], fontColor, btnLabel[1][2], fontSize);
  btn7.drawButton();  
  btn8.initButton(&tft, 280, 120, btnWidth, btnWidth, btnBorderColor[1][3], btnBackgroundColor[1][3], fontColor, btnLabel[1][3], fontSize);
  btn8.drawButton();

//-----------------------------Third Row-----------------------------------

  btn9.initButton(&tft, 40, 200, btnWidth, btnWidth, btnBorderColor[2][0], btnBackgroundColor[2][0], fontColor, btnLabel[2][0], fontSize);
  btn9.drawButton();  
  btn10.initButton(&tft, 120, 200, btnWidth, btnWidth, btnBorderColor[2][1], btnBackgroundColor[2][1], fontColor, btnLabel[2][1], fontSize);
  btn10.drawButton();  
  btn11.initButton(&tft, 200, 200, btnWidth, btnWidth, btnBorderColor[2][2], btnBackgroundColor[2][2], fontColor, btnLabel[2][2], fontSize);
  btn11.drawButton();  
  btn12.initButton(&tft, 280, 200, btnWidth, btnWidth, btnBorderColor[2][3], btnBackgroundColor[2][3], fontColor, btnLabel[2][3], fontSize);
  btn12.drawButton();

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
}


void loop(void) {

if (ts.touched()) {
    TS_Point p = ts.getPoint();

    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    Serial.print("Pressure = ");
    Serial.print(p.z);
    Serial.print(", x = ");
    Serial.print(p.x);
    Serial.print(", y = ");
    Serial.print(p.y);
    delay(30);
    Serial.println();

    btn.press(btn.contains(p.x, p.y));
    btn2.press(btn2.contains(p.x, p.y));
    btn3.press(btn3.contains(p.x, p.y)); 
    btn4.press(btn4.contains(p.x, p.y));
    btn5.press(btn5.contains(p.x, p.y));
    btn6.press(btn6.contains(p.x, p.y));
    btn7.press(btn7.contains(p.x, p.y));
    btn8.press(btn8.contains(p.x, p.y));
    btn9.press(btn9.contains(p.x, p.y));
    btn10.press(btn10.contains(p.x, p.y));
    btn11.press(btn11.contains(p.x, p.y));
    btn12.press(btn12.contains(p.x, p.y));
    

   if (btn.isPressed()) {
     Keyboard.press(KEY_F5);
     delay(300);
     Keyboard.releaseAll();
  }
     if (btn2.isPressed()) {
     Keyboard.press(KEY_F6);
     delay(300);
     Keyboard.releaseAll();
  }
     if (btn3.isPressed()) {
     Keyboard.press(KEY_F7);
     delay(300);
     Keyboard.releaseAll();
  }
     if (btn4.isPressed()) {
     Keyboard.press(KEY_F8);
     delay(300);
     Keyboard.releaseAll();
  }
     if (btn5.isPressed()) {
     Keyboard.press(KEY_VOLUMEUP);
  }
     if (btn6.isPressed()) {
     Serial.print("Boton 6 tocado");
     Keyboard.write('F');
  }
     if (btn7.isPressed()) {
     Serial.print("Boton 7 tocado");
     Keyboard.write('G');
  }
     if (btn8.isPressed()) {
     Serial.print("Boton 8 tocado");
     Keyboard.write('H');
  }
     if (btn9.isPressed()) {
     Serial.print("Boton 9 tocado");
     Keyboard.write('I');
  }
     if (btn10.isPressed()) {
     Serial.print("Boton 10 tocado");
     Keyboard.write('J');
  }
     if (btn11.isPressed()) {
     Serial.print("Boton 11 tocado");
     Keyboard.write('K');
  }
     if (btn12.isPressed()) {
     Serial.print("Boton 12 tocado");
     Keyboard.write('L');
  }
}
}
