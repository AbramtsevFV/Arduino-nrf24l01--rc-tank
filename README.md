# Arduino nrf24l01  rc tank
## Проект созданный для развлечения. Состоит из: 
- Двух радиом одулей nRF24L01 с усилителем, а также модули питания. [Подключение ссылка на видео Alex Gyver ](https://www.youtube.com/watch?v=ACVtKDJVXS4)
- Двух Arduino Nano
- Одиного модуль L298N управление двигателями [Подключение](https://alexgyver.ru/wp-content/uploads/2021/07/l298.jpg) . 
- Шеcти АКБ 18650
- Трёх батарейных отсеков для аккумуляторов Li-ion типоразмера 18650 [Можно такие](https://www.ozon.ru/product/batareynyy-otsek-2h-dlya-akkumulyatorov-li-ion-tiporazmera-18650-s-kryshkoy-arduino-slot-930989918/?at=QktJP9pD7c6DR65BF9JgBOfEADoZNc8BjBGXfV2L1qX)
- Гусеничное шасси [Использовал такое](https://www.ozon.ru/product/umnaya-gusenichnaya-platforma-robot-na-shassi-tsisterny-s-dvumya-dvigatelyami-postoyannogo-toka-12-v-2890905784/?at=RltyWQ1KNFNk2zkvFzwG99ZcMynZ8jCD6YpnYULR6P10)
- Джойстика (стика) [Использовал такой](https://www.ozon.ru/product/dvuhkoordinatnyy-modul-dzhoystika-xy-datchik-rychaga-upravleniya-dzhoystikom-ps2-ky-023-dlya-arduino-2153603120/?at=k2toB4jLgFzQPkCWLwroAtorWlqiEWv1A7Iq5vqyj)
- Потенциометр с ручкой.
- Два выключателя [Использовал такие](https://www.ozon.ru/product/knopka-vyklyuchatel-tumbler-on-off-10-15-mm-kcd11-1770572766/?at=28t036Xx7fqQ4j5rtppn78zs5OrZ6kTNg7vRVT95wr6J)
- Проводов. Изначально использовал витую пару — не лучший выбор. Потом просто откусил пины от проводов для макетных плат и использовал их для соединения сигнальных контактов. [Например такие](https://aliexpress.ru/item/32996173648.html?spm=a2g2w.orderdetail.0.0.7d8a4aa6TtlGt3&sku_id=12000031133062779&_ga=2.244899973.1861940804.1769938978-2106523636.1745513850)
- DC-DC преобразователя на 5 вольт.
- Для скручивания — латунные шайбы М3.
- Сервопривода для вращения башни.

 ## Сборка
Важно: контакт 5V на модуле L298N не подключать, так как 4 аккумулятора 18650 в сумме дают около 16 вольт, а этот пин рассчитан только на 12В. Логику модуля (контакт +5V) питаем, как и всё остальное, от DC-DC преобразователя.
Также перед загрузкой прошивки рекомендую проверить радиочасты и выбрать наименее зашумленные. Для проверки я использовал прошивку Алекса Гайвера. [Ссылка](https://github.com/AlexGyver/nRF24L01/blob/master/nRF24L01%20tests/nrf_listen_air/nrf_listen_air.ino)
Прошивки лежат в папке Firmware. 
- Пульт [tank_remote_control_transmitter](https://github.com/AbramtsevFV/Arduino-nrf24l01--rc-tank/tree/main/Firmware/tank_remote_control_transmitter).
- Танк [tank_motor_receiver](https://github.com/AbramtsevFV/Arduino-nrf24l01--rc-tank/tree/main/Firmware/tank_motor_receiver)

 Все 3d модели печатались пластиком PLA.

 ## Фото готового проекта 
 <div align="center">
   <img src="https://github.com/AbramtsevFV/Arduino-nrf24l01--rc-tank/blob/main/Images/Tank.jpeg" width="500" height="auto" alt="Танк">
    <p> Рисунок 1 - Готовый танк </p>
   <img src="https://github.com/AbramtsevFV/Arduino-nrf24l01--rc-tank/blob/main/Images/rc.jpeg" width="500" height="auto" alt="Танк">
    <p> Рисунок 2 - ульт управления в сборе </p>
   <img src="https://github.com/AbramtsevFV/Arduino-nrf24l01--rc-tank/blob/main/Images/open.jpeg" width="500" height="auto" alt="Танк">
    <p> Рисунок 3 - Компановка деталей в танке </p>
 </div>
