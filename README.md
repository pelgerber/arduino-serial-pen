# arduino-serial-pen

Arduino sketch to use keybord for painting on Arduino Uno R4 WiFi LED matrix via serial input.
A serial terminal like PuTTY or picocom can be used to interact with the Arduino.

LED matrix status can also be dumped to Serial terminal, with this kind of output: 

```c
uint8_t frame[8][12] = {
	{0,0,0,1,1,1,1,1,1,0,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,1,1,1,1,1,1,0,0,0},
	{0,0,1,0,0,0,0,0,0,1,0,0},
	{0,1,0,0,0,0,0,0,0,0,1,0},
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0},
};
```
