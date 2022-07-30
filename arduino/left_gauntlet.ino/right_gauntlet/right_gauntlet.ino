#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//I2C
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//software SPI:
//#define OLED_CLK    8
//#define OLED_MOSI  9
//#define OLED_RESET 10
//#define OLED_DC    11
//#define OLED_CS    12
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);



int radius = 25;
int degree = 0;
int x = cos(degree/360)*radius;
int y = sin(degree/360)*radius;

int xold;
int yold;

int faktor;
int show;
int led_mod_counter = 0;
int led_loop_counter = 0;

void setup() {
  // LED SET
  // quartet 1
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  // quartet 2
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  Serial.begin(9600);
  display.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  display.clearDisplay();

  

  display.fillCircle(63, 31, 31, WHITE);
  display.fillCircle(63, 31, 29, BLACK);
  
  display.fillTriangle(53, 31, 31, 4, 31, 58, BLACK);
  display.fillTriangle(73, 31, 95, 4, 95, 58, BLACK);
  
  display.drawCircle(63, 31, 29, WHITE);

  display.fillRect(55, 0, 17, 64, BLACK);

  display.drawLine(32, 0, 94, 62, WHITE);
  display.drawLine(32, 62, 94, 0, WHITE);

  display.fillCircle(63, 31, 24, BLACK);

  display.drawRoundRect(0, 0, 127, 63, 4, WHITE);
  
  display.drawLine(36, 31, 45, 31, WHITE);
  display.drawLine(90, 31, 81, 31, WHITE);
  display.drawLine(63, 4, 63, 13, WHITE);
  display.drawLine(63, 58, 63, 49, WHITE);

  display.display();

  delay(1000);


}

void loop() {
  led_loop_counter++;
  
  if (led_loop_counter > 32000){
    led_loop_counter=0;
  }

  if(led_loop_counter % 10 == 0){
    led_mod_counter++;
    if (led_mod_counter > 32000){
      led_mod_counter=0;
    }
    for (int i = 1; i <= 9; i++) {
      if (led_mod_counter%i){
        digitalWrite(i, HIGH); 
      } else {
        digitalWrite(i, LOW); 
      }
      
    }
  }
  
  if(show == 1)
  {
    display.drawPixel(63+xold*faktor/25, 31+yold*faktor/25, WHITE);
  }

  faktor = random(25);
  show = random(2);
  
  int x = radius * cos((degree * PI /180));
  int y = radius * sin((degree * PI /180));

  int xb = radius * cos((degree+45) * PI /180);
  int yb = radius * sin((degree+45) * PI /180);

  int xc = 14 * cos((degree-25) * PI /180);
  int yc = 14 * sin((degree-25) * PI /180);

  int xd = 14 * cos((degree+25) * PI /180);
  int yd = 14 * sin((degree+25) * PI /180);

  int xe = 44 * cos((-degree) * PI /180);
  int ye = 44 * sin((-degree) * PI /180);

  display.fillTriangle(63, 31, 63+xb, 31+yb, 63+x, 31+y, BLACK);
  
  display.drawLine(36, 31, 45, 31, WHITE);
  display.drawLine(90, 31, 81, 31, WHITE);
  display.drawLine(63, 4, 63, 13, WHITE);
  display.drawLine(63, 58, 63, 49, WHITE);

  display.drawCircle(63, 31, 11, WHITE);
  display.drawCircle(63, 31, 25, WHITE);
  display.drawCircle(63, 31, 44, WHITE);

  display.drawPixel(63-xe, 31-ye, BLACK);
  display.drawPixel(63-xe, 31-ye+1, BLACK);
  display.drawPixel(63-xe, 31-ye-1, BLACK);
  display.drawPixel(63-xe+1, 31-ye, BLACK);
  display.drawPixel(63-xe+1, 31-ye+1, BLACK);
  display.drawPixel(63-xe+1, 31-ye-1, BLACK);
  display.drawPixel(63-xe-1, 31-ye, BLACK);
  display.drawPixel(63-xe-1, 31-ye+1, BLACK);
  display.drawPixel(63-xe-1, 31-ye-1, BLACK);

  display.drawLine(32, 0, 35, 3, WHITE);
  display.drawLine(32, 62, 35, 59, WHITE);
  display.drawLine(94, 0, 91, 3, WHITE);
  display.drawLine(94, 62, 91, 59, WHITE);
    
  display.drawRoundRect(0, 0, 127, 63, 4, WHITE);
  
  display.drawLine(0, 63, 127, 63, BLACK);

  display.fillTriangle(63, 31, 63+xd, 31+yd, 63+xc, 31+yc, BLACK);
  display.fillTriangle(63, 31, 63-xd, 31-yd, 63-xc, 31-yc, BLACK);
  
  display.drawLine(63, 31, 63+x, 31+y, WHITE);

  display.display();
 
  display.drawLine(63, 31, 63+x, 31+y, BLACK);
  

  if(degree == 360)
  {
    degree = 0;
  }

  degree = degree + 5;

  xold = x;
  yold = y;

  delay(30);

}
