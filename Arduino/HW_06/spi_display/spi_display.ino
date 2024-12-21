#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789
#include <SPI.h>
#define cs 10
#define dc 9
#define rst 8

Adafruit_ST7789 TFTscreen = Adafruit_ST7789(cs, dc, rst);

int paddleX = 0;
int paddleY = 0;
int oldPaddleX, oldPaddleY;
int ballDirectionX = 1;
int ballDirectionY = 1;
int ballSpeed = 11;  // скорость шара - уменьшение этого значения делает его быстрее
int ballX, ballY, oldBallX, oldBallY;

void setup() {
  Ser
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  TFTscreen.init(240, 320);
  TFTscreen.fillScreen(ST77XX_WHITE);
}

int myWidth = TFTscreen.width();
int myHeight = TFTscreen.height();

void loop() {
  // сохраняем в переменные высоту и ширину экрана

  // масштабируем значения с потенциометров к размерам нашего экрана
  paddleX = map(filterX(analogRead(A0)), 0, 1023, 0, myWidth) - 10;
  paddleY = map(filterY(analogRead(A1)), 0, 1023, myHeight, 0) - 3;

  if (oldPaddleX != paddleX || oldPaddleY != paddleY) {
    TFTscreen.fillRect(oldPaddleX, oldPaddleY, 20, 6, ST77XX_WHITE);
    TFTscreen.drawRect(oldPaddleX, oldPaddleY, 20, 6, ST77XX_WHITE);
    TFTscreen.fillRect(paddleX, paddleY, 20, 6, ST77XX_BLACK);
    TFTscreen.drawRect(paddleX, paddleY, 20, 6, ST77XX_BLACK);
  }

  // рисуем платформу и сохраняем ее позицию
  oldPaddleX = paddleX;
  oldPaddleY = paddleY;

  // обновляем позицию шара
  if (millis() % ballSpeed < 2) {
    moveBall();
  }
}

// функция, регистрирующая положение шара на экране
void moveBall() {
  // if the ball goes offscreen, reverse the direction:
  if (ballX > myWidth || ballX < 0) {
    ballDirectionX = -ballDirectionX;
  }

  if (ballY > myHeight || ballY < 0) {
    ballDirectionY = -ballDirectionY;
  }

  if (inPaddle(ballX, ballY, paddleX, paddleY, 20, 6)) {
    ballDirectionX = -ballDirectionX;
    ballDirectionY = -ballDirectionY;
  }

  ballX += ballDirectionX;
  ballY += ballDirectionY;

  if (oldBallX != ballX || oldBallY != ballY) {
    TFTscreen.fillRect(oldBallX, oldBallY, 5, 5, ST77XX_WHITE);
    TFTscreen.drawRect(oldBallX, oldBallY, 5, 5, ST77XX_WHITE);
    TFTscreen.fillRect(ballX, ballY, 5, 5, ST77XX_BLACK);
    TFTscreen.drawRect(ballX, ballY, 5, 5, ST77XX_BLACK);
  }
  oldBallX = ballX;
  oldBallY = ballY;
}

boolean inPaddle(int x, int y, int rectX, int rectY, int rectWidth, int rectHeight) {
  boolean result = false;
  if ((x >= rectX && x <= (rectX + rectWidth)) && (y >= rectY && y <= (rectY + rectHeight))) {
    result = true;
  }
  return result;
}

int filterX(int newval) {
  float static val = 0;
  val += (newval - val) * 0.1;
  return val;
}

int filterY(int newval) {
  float static val = 0;
  val += (newval - val) * 0.1;
  return val;
}