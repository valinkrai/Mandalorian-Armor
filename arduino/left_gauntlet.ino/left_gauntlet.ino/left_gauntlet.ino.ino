#include SPI.h
#include Wire.h
#include Adafruit_GFX.h
#include Adafruit_SSD1306.h
#include mandalor10pt7b.h
#include Aurebesh8pt7b.h

#define SCREEN_WIDTH 128  OLED display width, in pixels
#define SCREEN_HEIGHT 64  OLED display height, in pixels
#define FONT_WIDTH 7  OLED display height, in pixels

I2C
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);;  SDA to Pin A4, SCK to Pin A5

software SPI
#define OLED_CLK    8       SCL
#define OLED_MOSI  9        SDA
#define OLED_RESET 10       RES
#define OLED_DC    11       DC
#define OLED_CS    12       CS
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define SSD1306_LCDHEIGHT 64
#if (SSD1306_LCDHEIGHT != 64)
#error(Height incorrect, please fix Adafruit_SSD1306.h!);
#endif

void setup()   {                
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  randomSeed(analogRead(0));


}

long readVcc() {
  long result;
   Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0)  _BV(MUX3)  _BV(MUX2)  _BV(MUX1);
  delay(2);  Wait for Vref to settle
  ADCSRA = _BV(ADSC);  Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result = ADCH8;
  result = 1126400L  result;  Back-calculate AVcc in mV
  return result;
}


void loop() {
    String scroll = birov solus haat mirshe'adate beskar'gam tolase tsikala. ;
    char buffer[80];
    int scroll_start_x = SCREEN_WIDTH;
    int scroll_len= scroll.length(); 
    int scroll_width=(FONT_WIDTH(scroll_len+1));
    int scroll_x_pos = scroll_start_x;

     square meters setup
    int meter_width=8;
    int meter_y_top=16;
    int meter_x_start=100;
    int spacing = 2;
    int meter_height=SCREEN_HEIGHT-meter_y_top;
    int meter_val_height=meter_height-4;
    int val1;
    int val2;
    int val3;
    while(true){
      display.clearDisplay();
      int width = 17;
      display.fillCircle(13, 28, 8, WHITE);
      display.drawCircle(13, 28, 10, WHITE);
      display.drawRect(0,16,27,26, WHITE);
  
      
      display.setCursor(scroll_x_pos, 63);
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.setTextWrap(false);
      display.setFont(&mandalor10pt7b);
      display.print(scroll);
      
      scroll_x_pos--;
      if (scroll_x_pos == (scroll_width-1)) {
        scroll_x_pos = scroll_start_x;
      }
       print voltage
      display.setCursor(0, 12);
      display.setFont(&Aurebesh8pt7b);
      display.print(readVcc()1000.0);
      display.setCursor(44, 12);
      display.print('v');
      
      print idk
      display.setCursor(65, 12);
      display.setFont(&Aurebesh8pt7b);
      display.print(valin);
      
      print idk
      display.setCursor(90, 36);
      display.setFont(&mandalor10pt7b);
      display.print(krai);

       square meters

       Meter 1
      val1 = (int)(analogRead(A0)  50.01023.0);
      
      display.drawRect(
        30,
        16,
        54  ,
        12, 
        WHITE
      );
      display.fillRect(
        32,
        18,
        val1,
        8, 
        WHITE
      );
      
   
       Meter 2
      val2 = 20 + random(-5,5);
      
      
      display.drawRect(
        30,
        16 + 14,
        54,
        12, 
        WHITE
      );

      display.fillRect(
        32,
        32,
        val2,
        8, 
        WHITE
      );
     
      
      display.display();
      delay(5);
    }
}
