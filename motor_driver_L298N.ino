#include <Wire.h>
#include "L298N.h"

#define ENA 5
#define IN1 9
#define IN2 10
#define IN3 11
#define IN4 12
#define ENB 3

L298N motor0(ENA, IN1, IN2);
L298N motor1(ENB, IN3, IN4);

void setup() {
  Serial.begin(9600);
  Serial.println("Motor Start");

  i2c_init();
}

void loop() {
  //  Serial.println("Motor0 Forward");
  //  motor0.setSpeed(255);
  //  motor0.forward();
  //  delay(2000);
  //  Serial.println("Motor0 Backward");
  //  motor0.setSpeed(100);
  //  motor0.backward();
  //  delay(2000);
  //  motor0.stop();
  //
  //  Serial.println("Motor1 Forward");
  //  motor1.setSpeed(255);
  //  motor1.forward();
  //  delay(2000);
  //  Serial.println("Motor1 Backward");
  //  motor1.setSpeed(100);
  //  motor1.backward();
  //  delay(2000);
  //  motor1.stop();
}

void i2c_init()
{
  Wire.begin(0x26) ;                // Ｉ２Ｃの初期化、自アドレスを0x26とする
  Wire.onRequest(requestEvent);     // マスタからのデータ取得要求のコールバック関数登録
  Wire.onReceive(receiveEvent);     // マスタからのデータ送信対応のコールバック関数登録
}

void receiveEvent(int howMany) {
  Serial.println("receiveEvent");
  byte cmd = Wire.read();
  Serial.print("cmd:");
  Serial.println(cmd);

  if (cmd == 0x01) {
    if (howMany == 3) {
      byte motor = Wire.read();
      uint8_t buf = Wire.read();
      
      int speed = *(int8_t *)(&buf);
      Serial.print("motor: ");
      Serial.print(motor);
      Serial.print(" speed: ");
      Serial.println(speed);

      speed = map(speed, -100, 100, -255, 255);
      if (motor == 0) {
        if (speed > 0) {
          motor0.setSpeed(speed);
          motor0.forward();
        } else if (speed < 0) {
          motor0.setSpeed(-speed);
          motor0.backward();
        } else {
          motor0.stop();
        }
      } else if (motor == 1) {
        if (speed > 0) {
          motor1.setSpeed(speed);
          motor1.forward();
        } else if (speed < 0) {
          motor1.setSpeed(-speed);
          motor1.backward();
        } else {
          motor1.stop();
        }
      } else {

      }
    }
  }
}

// マスターからのリクエストに対するデータ送信
void requestEvent() {
  Serial.println("requestEvent");
}


