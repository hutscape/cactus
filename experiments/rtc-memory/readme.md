# RTC Memory

Use RTC memory, instead of EEPROM, in ESP8266 because it survives deep sleep mode to reduce power consumption even further

## Firmware [[link](main.ino)]

Write a simple number to RTC Memory, deep sleep it and then wake it up again to read the same number! Use the number of count, when to turn on the radio to process something.

### RTC Memory read
```c
bool	system_rtc_mem_read	(
	uint32	src_addr,
	void	*	des_addr,
	uint32	save_size
)
```

### RTC Memory write
```c
bool	system_rtc_mem_write	(
	uint32	des_addr,
	void	*	src_addr,
	uint32	save_size
)
```

## References

- [Video: How to use the RTC Memory in ESP8266 and reduce power consumption by factor of 10](https://www.youtube.com/watch?v=r-hEOL007nw)
- [ESP8266-RTC-Memory code by SensorsIot](https://github.com/SensorsIot/ESP8266-RTC-Memory)
- [Sample code from ESP8266 Arduino](https://github.com/esp8266/Arduino/blob/master/libraries/esp8266/examples/RTCUserMemory/RTCUserMemory.ino)
