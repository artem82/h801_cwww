# h801_cwww
## (h801 coolwhite+warmwhite)
#### Версия 0.2
<br>Данный скетч управляет по MQTT двуцветной led лентой на основе h801rgbww (esp8266+5 мосфетов)
<br>Поддержка OTA
<br>Поддержка MQTT
### Подключение
W2 - это CW (Cool White) холодный цвет 6000 кельвинов 
W1 - это WW (Warm White) желтый цвет 2700 кельвинов 
GND - земля
VCC - 12 вольт

### Описание GPIO
<br>Red Gpio: 15
<br>Green Gpio: 13
<br>Blue Gpio:  12
<br>WW Gpio:  14
<br>WW Color Temp (Kelvin): 2000 //This depends on your leds but 2000 should be fine for warm white
<br>CW Gpio:  4
<br>CW Color Temp (Kelvin): 6000 //This depends on your leds but 6000 should be fine for cold white

<br>Red is on GPIO15
<br>Green is on GPIO13
<br>Blue is on GPIO12
<br>White 1 (W1) is on GPIO14 is WW
<br>White 2 (W2) is on GPIO4  is CW
<br>There are two on board LEDs, a red one on GPIO5 and a green on GPIO 1.

![alt text](https://image.prntscr.com/image/KlCG0ljaTKiAzxOmHpeoLQ.jpeg)
