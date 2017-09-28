![alt text](https://www.picclickimg.com/00/s/MTAwMVgxMDAx/z/AsYAAOSwWxNY02rS/$/RGB-LED-Strip-Light-WIFI-Controller-Dimmer-Andriod-_1.jpg)
# h801_cwww
(h801 coolwhite+warmwhite)
#### Версия 0.2
Данный скетч управляет по MQTT двуцветной led лентой на основе h801rgbww (esp8266+5 мосфетов)
<br>Поддержка OTA
<br>Поддержка MQTT
### Подключение
W2 - это CW (Cool White) холодный цвет 6000 кельвинов 
<br>W1 - это WW (Warm White) желтый цвет 2700 кельвинов 
<br>GND - земля
<br>VCC - 12 вольт
### MQTT
включение/выключение ленты
<br>**CW** - true/false Холодный цвет
<br>**WW** - true/false Теплый цвет 
<br>диммирование ленты
<br>**CWbrightness** значение  от 0 до 1023 Холодный цвет
<br>**WWbrightness** значение  от 0 до 1023 Теплый цвет 
![alt text](https://image.prntscr.com/image/KlCG0ljaTKiAzxOmHpeoLQ.jpeg)
### Описание GPIO
Red Gpio: 15
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
### Ссылки
[Двуцветная лента с Али](https://ru.aliexpress.com/item/DC12V-SMD-5050-led-strip-double-colour-chip-flexible-light-60LEDs-m-natural-white-warm-white/32299783329.html?spm=a2g0s.9042311.0.0.jrR24m)
<br>[IOBROKER](http://www.iobroker.net/)
<br>https://github.com/instalator/Sonoff_basic_OTA

