#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define BTN_DEB 50      // тай-маут смены состояния, мс
//bool stop = false;
const int POT = A2;   // Потенциометр для упраления башней
const int BUTTON_PIN = 4;
RF24 radio(9, 10); // "создать" модуль на пинах 9 и 10 Для Уно и нано

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

// Пины с джойстика по осям
const int X_PIN = A0;
const int Y_PIN = A1;

// Для отключения передатчика если данные не изменились и экономии энепгии
short transmit_data[4];  // массив, хранящий передаваемые данные

void button_press();



void setup() {

  Serial.begin(9600);

  radio.begin();              // активировать модуль
  radio.setAutoAck(1);        // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();   // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);   // размер пакета, в байтах

  radio.openWritingPipe(address[0]);  // мы - труба 0, открываем канал для передачи данных
  radio.setChannel(0x6e);     // выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX);   // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_1MBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp();        //начать работу
  radio.stopListening();  //не слушаем радиоэфир, мы передатчик
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {

  //  Переводим Аналоговый 0 -1023 в - 255  +255 ШИМ

  int X = (255 - (analogRead(X_PIN) + 9) / 2) *-1;
  int Y = (255 - (analogRead(Y_PIN) +9) / 2);

  // Преазуем значения в значения для управления
  int m_r = X + Y;
  int m_l = Y - X;
  button_press();
  transmit_data[0] = m_r;
  transmit_data[1] = m_l;
  transmit_data[2] = map(analogRead(POT), 0, 1023, 0, 180);
  radio.write(&transmit_data, sizeof(transmit_data)); // отправить по радио
  Serial.println(transmit_data[3]);
}

void button_press(){
  static bool pState = false;
    static uint32_t tmr;
    bool state = !digitalRead(BUTTON_PIN);

    if (pState != state) {
        if (!tmr) tmr = millis();               // первое изменение
        else if (millis() - tmr >= BTN_DEB) {   // вышел тайм-аут
            pState = state;                     // запомнить состояние

            if (state) transmit_data[3] = true;  // кнопка нажата
            else transmit_data[3] = false;        // кнопка отпущена
        }
    } else tmr = 0;  // сброс
}