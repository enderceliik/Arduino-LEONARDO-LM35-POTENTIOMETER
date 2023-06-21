![](https://img.shields.io/badge/Arduino-blue?style=for-the-badge&logo=arduino&logoColor=%2300979D&labelColor=white&color=white)  ![](https://img.shields.io/badge/C_%2B_%2B-white?style=for-the-badge&logo=c%2B%2B&logoColor=%2300589d&color=%23c4d8ea)
# Arduino-LEONARDO-LM35-POTENTIOMETER
Arduino Leonardo project, which evaluates the data received from the potentiometer and LM35 temperature sensor with timer and simulates incubator with leds.

> ## Circuit View
![Circuit View Png](https://github.com/enderceliik/Arduino-LEONARDO-LM35-POTENTIOMETER/blob/main/assets/gs_incubation_bb.png)

> ## Schema View
![Schema View Png](https://github.com/enderceliik/Arduino-LEONARDO-LM35-POTENTIOMETER/blob/main/assets/gs_incubation_schema.png)

To simply summarize:
The whole system (value reading from lm35, reading potentiometer value, values ​​to be given to leds) works with interruption at 1 second intervals.
- The white led is flashing to check the operating status of the system.
- Yellow led that is on if the control is in the potentiometer (ie user control) and off if it is not.
- If the temperature from the LM35 is in the range of -10 45 degrees and the value from the potentiometer is different than 255, the red and green leds whose brightness is adjusted according to the value from the potentiometer, or according to the intervals written in the EEPROM.
