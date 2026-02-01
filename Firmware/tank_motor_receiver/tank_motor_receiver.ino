#include <GyverMotor.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <Servo.h>



// уапавление моторами
byte motor_r_dig_pin = 4; //2
byte motor_r_PWM_pin = 5; //3

byte motor_l_dig_pin = 2; //4
byte motor_l_PWM_pin = 3; //5

GMotor motor_R(DRIVER2WIRE, motor_r_dig_pin, motor_r_PWM_pin);
GMotor motor_L(DRIVER2WIRE, motor_l_dig_pin, motor_l_PWM_pin);

// Создаём приёмник
RF24 radio(9, 10);  // "создать" модуль на пинах 9 и 10 Для Уно
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

// создаём servo 
Servo servo;

byte SERV_PIN = 6;

short recieved_data[3];  // массив принятых данных


void setup() {
  Serial.begin(9600);
  // Настройки приёмника
  radio.begin(); //активировать модуль
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);   // размер пакета, в байтах

  radio.openReadingPipe(1, address[0]);     // хотим слушать трубу 0 
  radio.setChannel(0x6e);  // выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX);   // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_1MBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp();          // начать работу
  radio.startListening();   // начинаем слушать эфир, мы приёмный модуль

  // настройки моторов
  // установка скорости изменения скорости (ускорения) мотора
  motor_R.setSmoothSpeed(20);
  motor_L.setSmoothSpeed(20);
  motor_R.setMode(AUTO);
  motor_L.setMode(AUTO);

  // настройка servo
  servo.attach(SERV_PIN);
  Serial.println("recieved_data[2]");


}

void loop() {
  byte pipeNo;
  while ( radio.available(&pipeNo)) { // есть входящие данные
    // чиатем входящий сигнал
    radio.read(&recieved_data, sizeof(recieved_data));

    // управляем моторами
    motor_R.setSpeed(recieved_data[0]);
    motor_L.setSpeed(recieved_data[1]);

    //управляем servo
 
    int new_pos = recieved_data[2];
    servo.write(new_pos);


    Serial.println(recieved_data[2]);
    //Serial.println(recieved_data[1]);
    //Serial.println(recieved_data[0]);
  }
  
}
