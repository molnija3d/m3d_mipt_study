#include "RotaryEncoder.h"
#include <GyverOLED.h>
#include <GyverHTU21D.h>
GyverHTU21D htu;
GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;


int buttonState = 0;
int pos = 0;
RotaryEncoder encoder(2, 7, RotaryEncoder::LatchMode::TWO03);

void setup() {
  oled.init(SDA, SCL);
  //vv RGB LED vv
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  //^^ RGB LED ^^

  pinMode(4, INPUT_PULLUP);  // encoder button
  Serial.begin(9600);
  if (!htu.begin())
    Serial.println(F("HTU21D error"));
}

int filter(int newval);

void loop() {
  uint32_t cur_tm = millis();
  static int prev_pos = 0;
  static int menu = 0;
  static int val = 0;
  static float tmp = 0.0;
  static float hum = 0.0;

  val = analogRead(A0);  // возвращает значение от 0 до 1023
  val = filter(val);
  val = map(val, 0, 1023, 0, 256);
  val = constrain(val, 0, 255);

  encoder.tick();
  pos = encoder.getPosition();

  if (prev_pos != pos) {
    bool GT = 0;
    prev_pos < pos ? GT = 1 : GT = 0;
    GT ? menu++ : menu--;
    switch (menu) {
      case 0:
        break;
      case 1:
        break;
      case 2:
        break;
      default:
        menu > 2 ? menu = 0 : menu = 2;
        break;
    }
    prev_pos = pos;
  }

  switch (menu) {
    case 0:
      analogWrite(3, val);
      break;
    case 1:
      analogWrite(5, val);
      break;
    case 2:
      analogWrite(6, val);
      break;
  }

  static uint32_t prev_msr = 0;
  if (htu.readTick() && cur_tm - prev_msr > 500) {
    prev_msr = cur_tm;
    tmp = htu.getTemperature();
    hum = htu.getHumidity();
  }

  static uint32_t prev_lcd = 0;
  if (cur_tm - prev_lcd > 300) {
    prev_lcd = cur_tm;
    oled.clear();  // очистить дисплей (или буфер)
    oled.home();   // курсор в 0,0
    oled.setScale(1);
    oled.print("LED: ");
    oled.print(menu == 0 ? "BLUE" : menu == 1 ? "GREEN"
                                              : "RED");
    oled.setCursor(0, 1);  // курсор в (пиксель X, строка Y)
    oled.setScale(1);
    oled.print("PWM:");
    oled.print(val);

    oled.setCursor(0, 3);  // курсор в (пиксель X, строка Y)
    oled.setScale(2);
    oled.print("Temp:");
    oled.print(tmp);

    oled.setCursor(0, 6);  // курсор в (пиксель X, строка Y)
    oled.setScale(2);
    oled.print(tmp > 30 ? "    :-)" : "    :-(");

    oled.update();
  }
}

int filter(int newval) {
  float static val = 0;
  val += (newval - val) * 0.1;
  return val;
}