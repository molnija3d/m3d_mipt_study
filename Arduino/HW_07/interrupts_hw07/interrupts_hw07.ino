#include <GyverTimers.h>
#define BT1 2
#define BT2 4
#define LED1 11
#define LED2 12
//флаги разрешения на запуск диодов
bool led1_on = 0;
bool led2_on = 0;

//счетчик для втрого светодиода
uint32_t cnt_2 = 0;

void setup() {
  // подключаем последовательный порт
  Serial.begin(9600);
  
  //подключение кнопок
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);

  //подключение диодов
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  //запускаем таймер 1
  Timer1.setFrequency(4);  // таймер для первого прерывания, частота 4 Гц
  Timer1.enableISR();
 
  //добавляем обработчики прерываний на кнопки
  attachInterrupt(0, bt1_interrupt, FALLING);
  attachInterrupt(1, bt2_interrupt, FALLING);
}

void loop() {
  //мигание диодом по программному таймеру
  if (led2_on && millis() - cnt_2 > 600) {
    cnt_2 = millis();
    digitalWrite(LED2, !digitalRead(LED2));
  }
  
}

//обработка прерывания по нажатию кнопки 1 с выводом статуса в терминал
void bt1_interrupt() {
  led1_on = !led1_on;
  Serial.println((String) "led1_on = " + led1_on);
};

//обработка прерывания по нажатию кнопки 2 с выводом статуса в терминал
void bt2_interrupt() {
  led2_on = !led2_on;
  Serial.println((String) "led2_on = " + led2_on);
};

//обработчик прерывания таймера
ISR(TIMER1_A) { 
  //моргаем светодиодом, если флаг взведен
  if (led1_on) {
    digitalWrite(LED1, !digitalRead(LED1));
  }
}


