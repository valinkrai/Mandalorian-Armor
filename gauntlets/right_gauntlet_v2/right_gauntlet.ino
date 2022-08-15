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
  
  // See the following for targetting computer code:
  // https://mandalorianmercs.org/forum/index.php?topic=187680.0

}
