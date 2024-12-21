
void setup() {
  for(uint8_t i = 2;i < 12; i++){
    pinMode(i, OUTPUT);
  }
  // режим работы цифрового вывода для светодиодов
  Serial.begin(9600);
}
int filter(int newval);
void loop() {

int val = analogRead(A0); // analogRead() возвращает значение от 0 до 1023

Serial.print(val);
Serial.print(" ");

val = filter(val);
Serial.print(val);
Serial.print(" ");

val = map(val, 215, 680, 0, 10);
val = constrain(val, 0, 10);
Serial.println(val);
delay(10);//
val += 2;
for(uint8_t i = 2; i < 12; i++){
  if(i < val){
    digitalWrite(i, HIGH);
  }
  else{
    digitalWrite(i, LOW);
  }
}

}
 
int filter(int newval){
  float static val = 0;
  val += (newval - val)*0.1;
  return val;
}

