#include "RotaryEncoder.h"          // библиотека для энкодера
int buttonState = 0;
uint8_t pin = 2;
int cnt = 0;
static int pos = 0;  // задаем начальное положение энкодера
int newPos;
RotaryEncoder encoder(2, 3, RotaryEncoder::LatchMode::TWO03);  // пины подключение энкодера (DT, CLK)
void setup() {
  pinMode(4, INPUT_PULLUP); // режим работы цифрового вывода для кнопки
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  Serial.println(pos);  // выводим на монитор начальное значение
}

void loop() {
   // проверяем положение ручки энкодера
   encoder.tick();
   newPos = encoder.getPosition();
   
   // если положение изменилось - выводим на монитор
   if (pos != newPos) {
      Serial.println(newPos);
      pos = newPos; 
   }
   if (!digitalRead(4) == HIGH) { 
    digitalWrite(5, HIGH);
   } else {
    digitalWrite(5, LOW);
   }  
}
 
