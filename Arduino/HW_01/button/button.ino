int buttonState = 0;
uint8_t pin = 2;
int cnt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(12, OUTPUT);
}


void loop() {
 buttonState = digitalRead(pin);
 
 if (buttonState == LOW) {
    digitalWrite(13, HIGH);
    ++cnt;
 }
 else {
  if(cnt){
     Serial.print("\n");
     Serial.print(cnt);
  }
  digitalWrite(13, LOW);
  cnt = 0;
 }
  delay(1);
}

/*
enum { button_read_period = 10 }; /* опрашивать состояние будем каждые 10 мс 
void loop()
{
	static uint8_t  button_state = 0; //* Состояние кнопки; каждый бит соответствует состоянию входа в очередной момент времени 
	{
    	static uint32_t ts = 0; //* здесь храним момент последнего отсчёта 
    	if ( millis() - ts > button_read_period ) //* Если с момента последнего отсчёта прошло более button_read_period миллисекунд 
    	{
        	ts = millis();  	//* Запоминам этот момент 
        	button_state <<= 1; //* сдвигаем текущее состояние на один бит влево, «забывая» самое старое значение
        	button_state  |=  digitalRead(pin); //* И в крайний правый бит записываем текущий отсчёт
    	}
	}
 
	switch(button_state)
	{
    	case  0xff:  //*то есть все биты «1» — последние 8 отсчётов кнопка была отпущена
        	//*Кнопка отпущена в течение минимум (button_read_period * 8) миллисекунд
          Serial.print("RELEASED\n");
          digitalWrite(12, LOW);
        	break;
    	case 0: 	// то есть все биты «0» — последние 8 отсчётов кнопка была нажата
          	//*Кнопка нажата в течение минимум (button_read_period * 8) миллисекунд
          Serial.print(" PRESSED\n");
          digitalWrite(12, HIGH);
        	break;
    	default:
        	//*Кнопка в процессе переключения;
          Serial.print("SWITCHING\n");
          digitalWrite(12, HIGH);
        	break;
	}
}

*/