#include <IRremote.hpp>


#define IR_RECEIVE_PIN 2


const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;

const int IN3 = 6;
const int IN4 = 5;
const int ENB = 10;


const int SPEED = 200;


#define FORWARD  0x18
#define BACKWARD 0x52
#define LEFT     0x08
#define RIGHT    0x5A
#define STOP     0x1C

void setup() {

  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  stopCar();

  Serial.println("Car ready!");
}

void loop() {

  if (IrReceiver.decode()) {

    unsigned long command = IrReceiver.decodedIRData.command;

    Serial.print("Command: 0x");
    Serial.println(command, HEX);

    switch (command) {

      case FORWARD:
        forward();
        break;

      case BACKWARD:
        backward();
        break;

      case LEFT:
        left();
        break;

      case RIGHT:
        right();
        break;

      case STOP:
        stopCar();
        break;

      default:
        Serial.println("Unknown button");
        break;
    }
    IrReceiver.resume();
  }
}



void forward() {
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  // Right motor
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Left motor
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}



void backward() {
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  // Right motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Left motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}



void left() {
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  // Right motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Left motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}



void right() {
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  // Right motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Left motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void stopCar() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}