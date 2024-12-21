#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <TimerOne.h>
#include <Encod_er.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>

// пин LED+ дисплея подключаем к +5V через резистор 150 ом
#define TFT_CS 10       // пин 10 подключаем к CS дисплея
#define TFT_RST 8       // пин 8 подключаем к RST дисплея
#define TFT_DC 9        // пин 9 подключаем к DS дисплея
#define TFT_BL 7        // пин 7 подсветка
#define pin_DT 4        // пин 4 подключаем к DT энкодера
#define pin_CLK 2       // пин 2 подключаем к CLK энкодера
#define pin_SW 3        // пин 3 подключаем к SW энкодера
#define pin_Speaker 5   // пин 5 подключаем к + пищалки ( - пищалки на землю)
#define pin_battery A3  // аналоговы пин 3 - делитель батареи

#define NotPush 0
#define ShortPush 1
#define LongPush 2
#define DurationOfLongPush 350  // длительность длинного нажатия

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define MaxX 13
#define MaxY 22
//#define MaxX 8
//#define MaxY 17
#define SmeX 3
#define SmeY 5
//#define LL 97
#define LL 198
#define BB 270
#define interval 250
#define puzzle_size 15  // размер квадратика
//#define puzzle_size 18     // размер квадратика
#define NumCol 6      // количество цветов квадратиков
#define MaxLevel 8    // макс. кол-во уровней
#define NextLevel 80  // через сколько столбиков повышать уровень

uint8_t MasSt[MaxX][MaxY], MasTmp[MaxX][MaxY], MasOld[MaxX][MaxY], fignext[3];
int dx, dy;
uint8_t Level = 1, OldLevel;
uint16_t MasCol[] = { WHITE, BLACK, RED, BLUE, GREEN, YELLOW, MAGENTA, CYAN };
uint32_t TimeOfPush, Counter, Score = 0, TScore = 0, Record = 0, OldRecord, OldScore, last_activity, battery_time;
word tempspeed;
struct eeprom_data {
  uint32_t myrecord;
  uint32_t total_games;
  uint8_t max_level;
} game_data;
bool fl, Demo = true, myfl = false, gaming = false, FlNew, FlZ = false, debug = false, first_run, reset_flag = true;  // reset_flag 0-обнулить, 1-не обнулять
int8_t VAL, Mp, x, y;
int8_t mmm[4][2] = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };
uint16_t MasSpeed[MaxLevel] = { 500, 450, 400, 350, 300, 250, 200, 100 };  // задержки уровней

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
Encod_er encoder(pin_CLK, pin_DT, pin_SW);
//==================================================
void setup() {
  randomSeed(analogRead(0));
  analogReference(INTERNAL);
  init_tft();
  FlNew = true;
  ViewStacan();
  GetNext();

  Timer1.initialize(interval);                       // инициализация таймера 1, период interval мкс
  Timer1.attachInterrupt(timerInterrupt, interval);  // задаем обработчик прерываний
  pinMode(pin_DT, INPUT);
  pinMode(pin_CLK, INPUT);
  pinMode(pin_battery, INPUT);
  pinMode(pin_SW, INPUT_PULLUP);
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(pin_SW, HIGH);  // подтягиваем к 5V
  delay(100);
  encoder.timeLeft = 0;
  encoder.timeRight = 0;
  if_debug();
  eeprom_enable();

  last_activity = millis();
}
//==================================================
// обработчик прерывания
void timerInterrupt() {
  encoder.scanState();
}
//==================================================first_run
void eeprom_enable() {
  //first_run = EEPROM.read(0);
  first_run = eeprom_read_byte(0);
  if (debug) {
    Serial.println((String) "first_run = " + first_run);
  }
  if (first_run == reset_flag) {
    //EEPROM.get(1, game_data);
    eeprom_read_block((void *)&game_data, 1, sizeof(game_data));
  } else {
    game_data.myrecord = 0;
    game_data.max_level = 0;
    game_data.total_games = 0;
    eeprom_write_block((void *)&game_data, 1, sizeof(game_data));
    eeprom_write_byte(0, reset_flag);
    //EEPROM.put(1, game_data);
    //  EEPROM.put(0, reset_flag);
    if (debug) {
      Serial.println((String) "reset_flag = " + reset_flag);
    }
  }
  if (debug) {
    Serial.println((String) "myrecord = " + game_data.myrecord);
  }
}
//==================================================
void if_debug() {
  if (!digitalRead(pin_SW)) {
    debug = true;
  } else {
    debug = false;
  }
  if (debug) {
    Serial.begin(9600);
    tft.setTextSize(1);
    tft.setCursor(5, BB + 5);
    tft.print("X = ");
    tft.setCursor(55, BB + 5);
    tft.print("Y = ");
  } else {
    tft.setTextSize(1);
    tft.setCursor(5, BB + 5);
    tft.print("HOLD SW DURING BOOT FOR DEBUG");
  }
}
//==================================================
void init_tft() {
  tft.init(240, 320);  // initialize a ST7739S chip, black tab
  digitalWrite(TFT_BL, HIGH);
  tft.fillScreen(WHITE);
  tft.setCursor(LL, 65);
  tft.setTextColor(BLACK);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  tft.print("LEVEL");
  tft.setCursor(LL, SmeY);
  tft.print("NEXT");
  tft.setCursor(LL, 100);
  tft.print("SCORE");
  tft.setCursor(LL + 5, 135);
  tft.print("TOP");
  tft.setCursor(LL, 145);
  tft.print("SCORE");

  tft.setCursor(LL + 5, 170);
  tft.print("MAX");
  tft.setCursor(LL, 180);
  tft.print("LEVEL");

  tft.setCursor(LL, 205);
  tft.print("TOTAL");
  tft.setCursor(LL, 215);
  tft.print("GAMES");

  tft.drawFastVLine(1, 2, BB - 1, BLACK);
  tft.drawFastVLine(puzzle_size * MaxX + 5 - MaxX, 2, BB - 1, BLACK);
  tft.drawFastHLine(1, BB, puzzle_size * MaxX + 5 - MaxX, BLACK);

  /// Battery Frame
   tft.setCursor(45, 290);
  tft.print("===== BATTERY LEVEL =====");
  tft.drawFastHLine(3, 300, 234, BLACK);
  tft.drawFastHLine(3, 315, 234, BLACK);
  tft.drawFastVLine(3, 300, 15, BLACK);
  tft.drawFastVLine(236, 300, 15, BLACK);
}
//================================================
void ViewStacan() {
  if (millis() - battery_time > 1000) {
    show_battery_level();
  }

  char myStr2[5];
  tft.setTextColor(BLUE);
  tft.setTextSize(1);
  if (OldScore != Score || FlNew) {
    tft.fillRect(LL, 113, 30, 8, WHITE);
    tft.setCursor(LL, 113);
    sprintf(myStr2, "%05d", Score);
    tft.print(myStr2);
    OldScore = Score;
  }

  if (OldRecord != Record || FlNew) {
    tft.setCursor(LL, 154);
    sprintf(myStr2, "%05d", Record);
    tft.fillRect(LL, 154, 30, 8, WHITE);
    tft.print(myStr2);
    OldRecord = Record;
  }
  if (OldLevel != Level || FlNew) {
    tft.fillRect(LL + 8, 75, 30, 20, WHITE);
    tft.setCursor(LL + 8, 75);
    tft.setTextSize(2);
    tft.print(Level);
    OldLevel = Level;
  }
  tft.fillRect(LL + 8, 190, 30, 10, WHITE);
  tft.setCursor(LL + 8, 190);
  tft.setTextSize(1);
  tft.print(game_data.max_level);

  tft.fillRect(LL, 224, 30, 10, WHITE);
  tft.setCursor(LL, 224);
  tft.setTextSize(1);
  tft.print(game_data.total_games);

  FlNew = false;

  for (byte j = 3; j < MaxY; j++)
    for (byte i = 0; i < MaxX; i++)
      if (MasSt[i][j] != MasOld[i][j]) ViewQuad(i, j, MasSt[i][j]);
  tft.drawFastHLine(3, BB - 2, (puzzle_size - 1) * MaxX, BLACK);

  for (byte j = 3; j < MaxY; j++)
    for (byte i = 0; i < MaxX; i++)
      MasOld[i][j] = MasSt[i][j];
}
//==================================================
void show_battery_level() {
  int b_level  = analogRead(A3), diff;
  static int prev_batt = 2000;
  
    if (debug) {
      Serial.println(b_level);
      Serial.println(prev_batt);
      tft.setCursor(6, 305);
      tft.setTextSize(1);
      tft.print("Battery level ADC: ");
      tft.fillRect(120, 305, 30, 10, WHITE);
      tft.setCursor(120, 305);
      tft.setTextSize(1);
      tft.print(b_level);
    }
 diff = prev_batt - b_level;
 if (diff > 5 || diff < -5 ){
    prev_batt = b_level;

    
    if (b_level > 444) {  //5.1v
      draw_battery_bars(19, CYAN);
    } else if (b_level > 434) {  //5v
      draw_battery_bars(19, GREEN);
    } else if (b_level > 386) {  //4.5v
      draw_battery_bars(18, GREEN);
    } else if (b_level > 377) {  //4.4v
      draw_battery_bars(17, GREEN);
    } else if (b_level > 367) {  //4.3v
      draw_battery_bars(16, GREEN);
    } else if (b_level > 359) {  //4.2v
      draw_battery_bars(15, GREEN);
    } else if (b_level > 348) {  //4.1v
      draw_battery_bars(14, GREEN);
    } else if (b_level > 340) {  //4.0v
      draw_battery_bars(13, YELLOW);
    } else if (b_level > 329) {  //3.9v
      draw_battery_bars(12, YELLOW);
    } else if (b_level > 322) {  //3.8v
      draw_battery_bars(11, YELLOW);
    } else if (b_level > 312) {  //3.7v
      draw_battery_bars(10, YELLOW);
    } else if (b_level > 304) {  //3.6v
      draw_battery_bars(9, YELLOW);
    } else if (b_level > 295) {  //3.4v
      draw_battery_bars(8, ST77XX_ORANGE);
    } else if (b_level > 285) {  //3.3v
      draw_battery_bars(7, ST77XX_ORANGE);
    } else if (b_level > 278) {  //3.2v
      draw_battery_bars(6, ST77XX_ORANGE);
    } else if (b_level > 268) {  //3.1v
      draw_battery_bars(5, ST77XX_ORANGE);
    } else if (b_level > 261) {  //3.0v
      draw_battery_bars(4, RED);
    } else if (b_level > 251) {  //2.9v
      draw_battery_bars(3, RED);
    } else if (b_level > 367) {  //2.8v
      draw_battery_bars(2, RED);
    } else if (b_level > 244) {  //4.4v
      draw_battery_bars(1, RED);
    } else if (b_level > 235) {  //4.4v
      draw_battery_bars(0, RED);
    } else {
      // draw_battery_bars(19, RED);
   }
  }
  /*
  5.0 - 434
  4.5 - 386
  4.4 - 377
  4.3 - 367
  4.2 - 359
  4.1 - 348
  4.0 - 340
  3.9 - 329
  3.8 - 322
  3.7 - 312
  3.6 - 304
  3.5 - 295
  3.4 - 285
  3.3 - 278
  3.2 - 268
  3.1 - 261
  3.0 - 251
  2.9 - 244
  2.8 - 235
  */
}
//==================================================
void draw_battery_bars(uint8_t num, uint16_t color) {
  tft.fillRect(7, 302, 228, 12, WHITE);
  for (uint8_t i = 0; i < num; i++) {
    tft.fillRect(7 + 12 * i, 302, 10, 12, color);
  }
}
//==================================================
byte mypush()  // возвращает длинное-2, короткое-1 или осутствие нажатия-0
{
  unsigned long tpr = millis();
  byte res = NotPush;
  if (!digitalRead(pin_SW)) {
    if (TimeOfPush == 0) TimeOfPush = tpr;
    else if (tpr - TimeOfPush > DurationOfLongPush && !myfl) {
      TimeOfPush = 0;
      myfl = true;
      //Serial.println("Long Press");
      return (LongPush);
    }
  } else {
    if (TimeOfPush > 0 && !myfl) res = ShortPush;
    TimeOfPush = 0;
    myfl = false;
  }
  return (res);
}
//==================================================
void ViewQuad(byte i, byte j, byte mycolor)  // отрисовка 1-го квадрата
{
  if (j < 3) return;
  byte wy = SmeY + (j - 3) * puzzle_size - j;
  byte wx = SmeX + i * puzzle_size - i;
  if (mycolor != 0) {
    tft.drawRect(wx, wy, puzzle_size, puzzle_size, BLACK);
    tft.fillRect(wx + 1, wy + 1, puzzle_size - 2, puzzle_size - 2, MasCol[mycolor]);
  } else
    tft.fillRect(wx + 1, wy - 1, puzzle_size - 2, puzzle_size, WHITE);
}
//==================================================

void ClearMas(byte MasStx[MaxX][MaxY]) {
  for (byte j = 0; j < MaxY; j++)
    for (byte i = 0; i < MaxX; i++)
      (MasStx[i][j] = 0);
}
//==================================================
void Sosed(int i, int j, int dx, int dy, byte mode) {
  int nx = i + dx;
  int ny = j + dy;
  if (nx >= 0 && ny >= 0 && nx < MaxX && ny < MaxY && MasSt[nx][ny] == MasSt[i][j]) {
    if (mode == 1) MasTmp[i][j]++;
    else if (mode == 2 && (MasTmp[nx][ny] > 1 || MasTmp[i][j] > 2)) {
      MasTmp[nx][ny] = 3;
      MasTmp[i][j] = 3;
    } else if (mode == 3 && MasTmp[nx][ny] == 3)
      if (MasTmp[i][j] != 3) {
        MasTmp[i][j] = 3;
        fl = true;
      }
  }
}
//==================================================
void Sos(int i, int j, byte mode) {
  for (byte k = 0; k < 4; k++)
    Sosed(i, j, mmm[k][0], mmm[k][1], mode);
}
//==================================================
bool FindFull()  // ищем одноцветные цепочки
{
  byte i, j, k;
  bool res;
  res = false;

  for (byte k = 2; k < 8; k++)  // по каждому цвету
  {
    ClearMas(MasTmp);
    for (j = 3; j < MaxY; j++)
      for (i = 0; i < MaxX; i++)
        if (MasSt[i][j] == k) Sos(i, j, 1);

    for (j = 3; j < MaxY; j++)
      for (i = 0; i < MaxX; i++)
        if (MasTmp[i][j] > 1) Sos(i, j, 2);
    do {
      fl = false;
      for (j = 3; j < MaxY; j++)

        for (i = 0; i < MaxX; i++)
          if (MasTmp[i][j] > 0) Sos(i, j, 3);
    } while (fl);

    for (j = 3; j < MaxY; j++)
      for (i = 0; i < MaxX; i++)
        if (MasTmp[i][j] == 3) {
          MasSt[i][j] = 1;
          TScore++;
        }
  }

  if (TScore > 0) {
    ViewStacan();
    FlZ = true;
    my_delay(500);
  }

  for (j = 0; j < MaxY; j++)
    for (i = 0; i < MaxX; i++) {
      while (MasSt[i][MaxY - 1 - j] == 1) {
        for (k = 0; k < MaxY - 2 - j; k++) MasSt[i][MaxY - 1 - k - j] = MasSt[i][MaxY - 2 - k - j];
        res = true;
      }
    }
  return (res);
}
//==================================================
void GetNext() {
  int dx = LL + 6;
  int dy = 16;
  x = 3;
  y = 0;
  for (byte i = 0; i < 3; i++) {  //fig[i]=fignext[i];
    if (!Demo) MasSt[x][i] = fignext[i];
    fignext[i] = random(NumCol) + 2;
    tft.drawRect(dx, dy + (puzzle_size - 1) * i, puzzle_size, puzzle_size, BLACK);
    tft.fillRect(dx + 1, dy + (puzzle_size - 1) * i + 1, puzzle_size - 2, puzzle_size - 2, MasCol[fignext[i]]);
  }
  if (!Demo) {
    Counter++;
    if (Counter == NextLevel) {
      Counter = 0;
      Level++;
      if (Level > MaxLevel) Level = MaxLevel;
    }
    tempspeed = MasSpeed[Level - 1];
  }
}
//==================================================
void MyScore() {
  TScore = 0;
  while (FindFull()) {
    if (TScore > 7) Score = Score + TScore + (TScore - 8) * 2;
    else Score = Score + TScore;
    if (!Demo) {
      my_tone(60, 100);
    }

    ViewStacan();

    FlZ = true;
    my_delay(600);
  }
  FlZ = false;
}
//==================================================
void my_tone(uint8_t pwm, uint16_t delay) {
  analogWrite(pin_Speaker, pwm);  // издаем звук
  my_delay(delay);
  analogWrite(pin_Speaker, 0);
}
//==================================================

void ProcDemo() {
  Score = 0;
  GetNext();
  for (byte j = 3; j < MaxY; j++)
    for (byte i = 0; i < MaxX; i++)
      MasSt[i][j] = random(6) + 2;
  ViewStacan();
  my_delay(1000);
  if (!Demo) return;
  MyScore();
  if (Record < Score) Record = Score;
}
//================================================
void my_delay(int md) {
  unsigned long starttime = millis();
  while (millis() - starttime < md) {
    VAL = 0;
    Mp = mypush();
    if (encoder.timeRight != 0)  // обрабатываем повороты энкодера
    {
      VAL = 1;
      encoder.timeRight = 0;
    } else if (encoder.timeLeft != 0) {
      VAL = -1;
      encoder.timeLeft = 0;
    }

    if (!digitalRead(pin_SW)) VAL = 0;
    if ((VAL != 0 || Mp != NotPush) && Demo) {
      Demo = false;
      NewGame();
    }
    if (VAL != 0 && figmove(VAL, 0) && !FlZ) {
      for (byte i = 0; i < 3; i++) {
        MasSt[x + VAL][y + i] = MasSt[x][y + i];
        MasSt[x][y + i] = 0;
      }
      ViewStacan();
      if (MasSt[x][y + 3] == 0)
        tft.drawFastHLine(SmeX + x * puzzle_size - x + 1, SmeY + y * puzzle_size - y - 3, puzzle_size - 2, WHITE);
      x = x + VAL;
    }
    if (Mp == ShortPush && !FlZ)  // перемена цветов фигуры
    {
      byte aa = MasSt[x][y];
      MasSt[x][y] = MasSt[x][y + 2];
      MasSt[x][y + 2] = MasSt[x][y + 1];
      MasSt[x][y + 1] = aa;
      ViewStacan();
    }

    if (Mp == LongPush && !FlZ) tempspeed = 50;  // падение
  }
}
//================================================
void NewGame() {
  game_data.total_games++;
  eeprom_write_block((void *)&game_data, 1, sizeof(game_data));

  for (byte i = 0; i < MaxX - 1; i++)
    tft.drawFastVLine(3 + (puzzle_size - 1) * i, 2, 255, BLACK);  // направляющие
  for (byte j = 3; j < MaxY; j++)                                 // заполним буфер сравнения значением, которого нет
    for (byte i = 0; i < MaxX; i++)
      MasOld[i][j] = 255;

  Score = 0;
  FlNew = true;
  OldScore = Score;
  ClearMas(MasSt);
  gaming = true;
  GetNext();
  Counter = 0;
  Level = 1;
  tempspeed = MasSpeed[0];
  Record = game_data.myrecord;
  ViewStacan();
}
//================================================
void gameover() {
  gaming = false;
  tft.drawRect(43, 100, 90, 50, BLACK);
  tft.fillRect(44, 101, 88, 48, WHITE);
  tft.setCursor(52, 107);
  tft.setTextSize(2);
  tft.setTextColor(RED);
  tft.print("GAME");
  tft.setCursor(77, 127);
  tft.print("OVER");
  if (Score > game_data.myrecord) {
    game_data.myrecord = Score;
    game_data.max_level = Level;
  }
  for (uint8_t i = 0; i < 4; i++) {
    my_tone(100, 300);
    my_delay(50);
    my_tone(50, 300);
    my_delay(50);
  }
}
//================================================
bool figmove(int dx, int dy) {

  if (debug) {
    tft.setTextColor(BLACK);
    tft.fillRect(30, BB + 5, 15, 10, WHITE);
    tft.setCursor(30, BB + 5);
    tft.setTextSize(1);
    tft.print(x);
    tft.fillRect(80, BB + 5, 15, 10, WHITE);
    tft.setCursor(80, BB + 5);
    tft.setTextSize(1);
    tft.print(y);
  }

  bool fff = false;
  if (x + dx < 0 || x + dx > MaxX - 1) return (false);  // попытка выйти за стенки стакана
  if (dx != 0)
    if (MasSt[x + dx][y + dy + 2] == 0) return (true);
    else return (false);
  if (dy > 0)  // падение вниз
  {
    if (y + dy + 2 > MaxY - 1 || MasSt[x + dx][y + dy + 2] > 0)  // либо на дне, либо на квадрате
    {
      if (y < 3) gameover();
      else fff = true;
    } else {
      for (byte i = 0; i < 3; i++) MasSt[x][y + 2 - i + dy] = MasSt[x][y + 2 - i];
      MasSt[x][y] = 0;
      y = y + dy;
    }
    if (fff) {
      MyScore();
      GetNext();
    }
    ViewStacan();
    last_activity = millis();
  }
  return (true);
}
//================================================
void go_to_sleep() {
  if (debug) {
    Serial.println("Running sleep mode");
    Serial.println("Going to sleep...");
    delay(100);
  }

  digitalWrite(TFT_BL, LOW);
  tft.sendCommand(ST77XX_SLPIN);
  //tft.enableSleep(true);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  attachInterrupt(1, wakeup, LOW);
  sleep_enable();
  sleep_cpu();
  sleep_disable();
  detachInterrupt(1);

  //tft.enableSleep(false);
  tft.sendCommand(ST77XX_SLPOUT);
  digitalWrite(TFT_BL, HIGH);

  if (debug) {
    Serial.println("Waking...");
  }
  last_activity = millis();
}
//================================================
void wakeup() {
}
//================================================
void loop() {
  if (Demo) ProcDemo();
  else {
    if (gaming) {
      my_delay(tempspeed);
      figmove(0, 1);
    } else if (mypush() == ShortPush) {
      NewGame();
    }
  }
  if (millis() - last_activity > 30000) {
    go_to_sleep();
  }
}
