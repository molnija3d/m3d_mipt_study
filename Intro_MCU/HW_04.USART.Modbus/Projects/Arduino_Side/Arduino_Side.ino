#include <ModbusRtu.h>
#define LED 13
#define BTN 2
#define QUERY_CNT 2
#define REG_SZ 64

uint16_t reg_buff[REG_SZ] = {
  0,
};

uint32_t refresh;
bool toggle = false;

/**
 *  Modbus object declaration
 *  u8id : node id = 0 for master, = 1..247 for slave
 *  port : serial port
 *  u8txenpin : 0 for RS-232 and USB-FTDI 
 *               or any pin number > 1 for RS-485f
 */
Modbus master(0, Serial, 0);  // this is master and RS-232 or USB-FTDI
modbus_t my_query[QUERY_CNT];
//////////////////////////////////////////////////////////////////
void make_action(uint32_t my_delay);
void init_request();
void send_slave(modbus_t my_query);
void btn_irq();

/////////////////////////////////////////////////////////////////
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  attachInterrupt(0, btn_irq, FALLING);
  // put your setup code here, to run once:
  init_request();
  Serial.begin(115200);
  master.start();
  master.setTimeOut(2000);  // if there is no answer in 2000 ms, roll over
  digitalWrite(LED, LOW);
}
//////////
void loop() {
  send_slave(my_query[0]);  //read registers
  send_slave(my_query[1]);  //write registers
  make_action(200);
}
///////////////////////////////////////////////////////////////////
/**
  * @brief  Makes action corresponding to reg_buff values. 
  * @retval none
  */
void make_action(uint32_t my_delay) {
  if (millis() > refresh + my_delay) {
    //client blinking
    if (toggle) {
      reg_buff[0] = reg_buff[0] == 7 ? 3 : 7;
    }
    //server blinking
    if (reg_buff[1] & 0x1u) {
      digitalWrite(LED, !digitalRead(LED));
    }
    refresh = millis();
  }
}
////////////////////
/**
  * @brief  Sending a specified request to client.
  * @retval none
  */
void send_slave(modbus_t my_query) {
  for (uint8_t i = 0; i < 3; i++) {
    static uint8_t u8state = 0;
    static uint32_t u32wait = 0;
    switch (u8state) {
      case 0:
        if (millis() > u32wait + 10) {
          u8state = 1;
        }
        break;
      case 1:
        master.query(my_query);  // send query (only once)
        u8state = 2;
      case 2:
        master.poll();  // check incoming messages
        if (master.getState() == COM_IDLE) {
          u8state = 0;
          u32wait = millis();
        }
        break;
    }
  }
}
/////////////////////
/**
  * @brief  Request initialization
  * @retval none
  */
void init_request() {
  // query 0: read registers
  uint8_t reg_addr = 1;
  my_query[0].u8id = 17;                      // slave address
  my_query[0].u8fct = 3;                      // function code (this one is registers read)
  my_query[0].u16RegAdd = reg_addr;           // start address in slave
  my_query[0].u16CoilsNo = 1;                 // number of elements (coils or registers) to read
  my_query[0].au16reg = reg_buff + reg_addr;  // pointer to a memory array in the Arduino

  // query 1: write a multiple register
  reg_addr = 0;
  my_query[1].u8id = 17;                      // slave address
  my_query[1].u8fct = 16;                     // function code (this one is write a multiple register)
  my_query[1].u16RegAdd = reg_addr;           // start address in slave
  my_query[1].u16CoilsNo = 1;                 // number of elements (coils or registers) to read
  my_query[1].au16reg = reg_buff + reg_addr;  // pointer to a memory array in the Arduino
}
/////////////////////
void btn_irq() {
  toggle = !toggle;
}