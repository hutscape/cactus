EESchema Schematic File Version 4
LIBS:ariel-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Ariel"
Date "2019-03-13"
Rev "V1"
Comp ""
Comment1 "Kitchen cupboard humidity sensor"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74xx:74HC595 U3
U 1 1 5C77296E
P 8650 1650
F 0 "U3" H 8450 2200 50  0000 C CNN
F 1 "74HC595" H 8450 1000 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 8650 1650 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 8650 1650 50  0001 C CNN
	1    8650 1650
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R6
U 1 1 5C7739E8
P 4200 3600
F 0 "R6" H 4050 3600 50  0000 L CNN
F 1 "470" H 4250 3600 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4200 3600 50  0001 C CNN
F 3 "~" H 4200 3600 50  0001 C CNN
	1    4200 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R7
U 1 1 5C773C60
P 4050 3900
F 0 "R7" V 3950 3850 50  0000 L CNN
F 1 "1k" V 4150 3850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4050 3900 50  0001 C CNN
F 3 "~" H 4050 3900 50  0001 C CNN
	1    4050 3900
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R8
U 1 1 5C773D83
P 4050 4200
F 0 "R8" V 3950 4200 50  0000 C CNN
F 1 "10k" V 4150 4200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4050 4200 50  0001 C CNN
F 3 "~" H 4050 4200 50  0001 C CNN
	1    4050 4200
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5C773EE5
P 4500 4200
F 0 "C1" V 4400 4150 50  0000 L CNN
F 1 "10u" V 4600 4150 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4500 4200 50  0001 C CNN
F 3 "~" H 4500 4200 50  0001 C CNN
	1    4500 4200
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5C85EE0D
P 4800 3900
F 0 "SW1" H 4800 4050 50  0000 C CNN
F 1 "SW_Push" H 4800 3850 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_EVPBF" H 4800 4100 50  0001 C CNN
F 3 "" H 4800 4100 50  0001 C CNN
	1    4800 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3900 4250 3900
Wire Wire Line
	4150 4200 4250 4200
Wire Wire Line
	4250 3900 4250 4200
Connection ~ 4250 3900
Wire Wire Line
	4250 3900 4600 3900
Connection ~ 4250 4200
Wire Wire Line
	4250 4200 4400 4200
$Comp
L power:GND #PWR04
U 1 1 5C8607DD
P 5050 3950
F 0 "#PWR04" H 5050 3700 50  0001 C CNN
F 1 "GND" H 5055 3777 50  0000 C CNN
F 2 "" H 5050 3950 50  0001 C CNN
F 3 "" H 5050 3950 50  0001 C CNN
	1    5050 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3900 5050 3900
Wire Wire Line
	5050 3900 5050 3950
Wire Wire Line
	4200 3500 5200 3500
Wire Wire Line
	5200 3500 5200 4200
Wire Wire Line
	5200 4200 4600 4200
$Comp
L power:GND #PWR05
U 1 1 5C8612CC
P 4800 2400
F 0 "#PWR05" H 4800 2150 50  0001 C CNN
F 1 "GND" H 4805 2227 50  0000 C CNN
F 2 "" H 4800 2400 50  0001 C CNN
F 3 "" H 4800 2400 50  0001 C CNN
	1    4800 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5C8625CA
P 8650 2550
F 0 "#PWR07" H 8650 2300 50  0001 C CNN
F 1 "GND" H 8800 2500 50  0000 C CNN
F 2 "" H 8650 2550 50  0001 C CNN
F 3 "" H 8650 2550 50  0001 C CNN
	1    8650 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5C862AA3
P 6950 1100
F 0 "D1" H 6950 1200 50  0000 C CNN
F 1 "LED" H 6950 1000 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6950 1100 50  0001 C CNN
F 3 "~" H 6950 1100 50  0001 C CNN
	1    6950 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 5C862B20
P 6950 1400
F 0 "D2" H 6950 1500 50  0000 C CNN
F 1 "LED" H 6950 1300 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6950 1400 50  0001 C CNN
F 3 "~" H 6950 1400 50  0001 C CNN
	1    6950 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 5C862C14
P 6950 1700
F 0 "D3" H 6950 1800 50  0000 C CNN
F 1 "LED" H 6950 1600 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6950 1700 50  0001 C CNN
F 3 "~" H 6950 1700 50  0001 C CNN
	1    6950 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D4
U 1 1 5C862C76
P 6950 2000
F 0 "D4" H 6950 2100 50  0000 C CNN
F 1 "LED" H 6950 1900 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6950 2000 50  0001 C CNN
F 3 "~" H 6950 2000 50  0001 C CNN
	1    6950 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D5
U 1 1 5C862CE0
P 6950 2300
F 0 "D5" H 6950 2400 50  0000 C CNN
F 1 "LED" H 6950 2200 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6950 2300 50  0001 C CNN
F 3 "~" H 6950 2300 50  0001 C CNN
	1    6950 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 5C871A82
P 7200 1100
F 0 "R1" V 7100 1050 50  0000 L CNN
F 1 "1k" V 7300 1050 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7200 1100 50  0001 C CNN
F 3 "~" H 7200 1100 50  0001 C CNN
	1    7200 1100
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5C871CA9
P 7200 1400
F 0 "R2" V 7100 1350 50  0000 L CNN
F 1 "1k" V 7300 1350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7200 1400 50  0001 C CNN
F 3 "~" H 7200 1400 50  0001 C CNN
	1    7200 1400
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R3
U 1 1 5C871E05
P 7200 1700
F 0 "R3" V 7100 1650 50  0000 L CNN
F 1 "1k" V 7300 1650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7200 1700 50  0001 C CNN
F 3 "~" H 7200 1700 50  0001 C CNN
	1    7200 1700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R4
U 1 1 5C871EB9
P 7200 2000
F 0 "R4" V 7100 1950 50  0000 L CNN
F 1 "1k" V 7300 1950 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7200 2000 50  0001 C CNN
F 3 "~" H 7200 2000 50  0001 C CNN
	1    7200 2000
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R5
U 1 1 5C871F77
P 7200 2300
F 0 "R5" V 7100 2250 50  0000 L CNN
F 1 "1k" V 7300 2250 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7200 2300 50  0001 C CNN
F 3 "~" H 7200 2300 50  0001 C CNN
	1    7200 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	6450 1100 6450 1400
Connection ~ 6450 2000
Wire Wire Line
	6450 2000 6450 2300
Connection ~ 6450 1700
Wire Wire Line
	6450 1700 6450 2000
Connection ~ 6450 1400
Wire Wire Line
	6450 1400 6450 1700
$Comp
L power:GND #PWR06
U 1 1 5C88238D
P 6450 2300
F 0 "#PWR06" H 6450 2050 50  0001 C CNN
F 1 "GND" H 6455 2127 50  0000 C CNN
F 2 "" H 6450 2300 50  0001 C CNN
F 3 "" H 6450 2300 50  0001 C CNN
	1    6450 2300
	1    0    0    -1  
$EndComp
NoConn ~ 8250 1750
NoConn ~ 8250 1850
NoConn ~ 8250 1950
NoConn ~ 8250 2150
$Comp
L power:GND #PWR03
U 1 1 5C893BFC
P 1800 2700
F 0 "#PWR03" H 1800 2450 50  0001 C CNN
F 1 "GND" H 1805 2527 50  0000 C CNN
F 2 "" H 1800 2700 50  0001 C CNN
F 3 "" H 1800 2700 50  0001 C CNN
	1    1800 2700
	1    0    0    -1  
$EndComp
NoConn ~ 2500 1950
NoConn ~ 2500 2050
NoConn ~ 2500 2150
NoConn ~ 2500 2250
$Comp
L power:VCC #PWR02
U 1 1 5C8A5397
P 1800 1200
F 0 "#PWR02" H 1800 1050 50  0001 C CNN
F 1 "VCC" H 1800 1350 50  0000 C CNN
F 2 "" H 1800 1200 50  0001 C CNN
F 3 "" H 1800 1200 50  0001 C CNN
	1    1800 1200
	1    0    0    -1  
$EndComp
Text Label 3950 1800 2    50   ~ 0
I2C_SDA
Text Label 5650 1350 0    50   ~ 0
RST
Text Label 2650 1750 0    50   ~ 0
A0
Text Label 5650 1450 0    50   ~ 0
A0
Text Label 5650 1550 0    50   ~ 0
D0
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5C86A0B5
P 1800 1250
F 0 "#FLG01" H 1800 1325 50  0001 C CNN
F 1 "PWR_FLAG" V 1800 1550 50  0000 C CNN
F 2 "" H 1800 1250 50  0001 C CNN
F 3 "~" H 1800 1250 50  0001 C CNN
	1    1800 1250
	0    -1   -1   0   
$EndComp
Text Notes 900  850  0    79   ~ 0
WeMos Battery Shield 
Text Label 1250 4100 2    50   ~ 0
I2C_SCL
Text Label 1250 4000 2    50   ~ 0
I2C_SDA
$Comp
L power:GND #PWR01
U 1 1 5C89C91B
P 1800 4600
F 0 "#PWR01" H 1800 4350 50  0001 C CNN
F 1 "GND" H 1805 4427 50  0000 C CNN
F 2 "" H 1800 4600 50  0001 C CNN
F 3 "" H 1800 4600 50  0001 C CNN
	1    1800 4600
	1    0    0    -1  
$EndComp
Text Label 5650 2050 0    50   ~ 0
3_3V
Text Label 8800 1050 0    50   ~ 0
5V
Text Label 5650 1950 0    50   ~ 0
D8
Text Label 9200 1750 0    50   ~ 0
D8
Text Label 9200 1250 0    50   ~ 0
D7
Text Label 5650 1850 0    50   ~ 0
D7
Text Label 9200 1450 0    50   ~ 0
D5
Text Label 5650 1650 0    50   ~ 0
D5
Wire Wire Line
	2500 1750 2650 1750
Text Label 3800 3500 2    50   ~ 0
RST
Text Label 3800 3700 2    50   ~ 0
D0
Text Label 5650 1750 0    50   ~ 0
D6
Text Label 3800 3900 2    50   ~ 0
D6
Text Label 3800 4200 2    50   ~ 0
3_3V
Wire Wire Line
	4100 1700 3950 1700
Wire Wire Line
	4100 1800 3950 1800
Wire Wire Line
	5500 1350 5650 1350
Wire Wire Line
	5500 1450 5650 1450
Wire Wire Line
	5500 1550 5650 1550
Wire Wire Line
	5500 1650 5650 1650
Wire Wire Line
	5500 1750 5650 1750
Wire Wire Line
	5500 1850 5650 1850
Wire Wire Line
	5500 1950 5650 1950
Wire Wire Line
	5500 2050 5650 2050
Text Notes 3600 850  0    79   ~ 0
WeMos D1 Mini v3.0.0
Wire Wire Line
	4200 3500 3800 3500
Connection ~ 4200 3500
Wire Wire Line
	4200 3700 3800 3700
Wire Wire Line
	3950 3900 3800 3900
Wire Wire Line
	3950 4200 3800 4200
Wire Notes Line
	3500 5050 5500 5050
Wire Notes Line
	5500 5050 5500 3350
Wire Notes Line
	5500 3350 3500 3350
Wire Notes Line
	3500 3350 3500 5050
Text Notes 3700 3300 0    79   ~ 0
Button circuit
Wire Wire Line
	6450 1100 6800 1100
Wire Wire Line
	6450 1400 6800 1400
Wire Wire Line
	6450 2000 6800 2000
Wire Wire Line
	6450 1700 6800 1700
Wire Wire Line
	9050 1250 9200 1250
Wire Wire Line
	9050 1450 9200 1450
Wire Wire Line
	9050 1750 9200 1750
Wire Wire Line
	8650 1050 8800 1050
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5C8B6759
P 8650 2350
F 0 "#FLG02" H 8650 2425 50  0001 C CNN
F 1 "PWR_FLAG" V 8650 2650 50  0000 C CNN
F 2 "" H 8650 2350 50  0001 C CNN
F 3 "~" H 8650 2350 50  0001 C CNN
	1    8650 2350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7300 1100 7450 1100
Text Label 8000 1250 2    50   ~ 0
QA
Text Label 7450 1100 2    50   ~ 0
QA
Entry Wire Line
	7750 1150 7850 1250
Entry Wire Line
	7750 1250 7850 1350
Entry Wire Line
	7750 1350 7850 1450
Entry Wire Line
	7750 1450 7850 1550
Entry Wire Line
	7750 1550 7850 1650
Text Label 8000 1350 2    50   ~ 0
QB
Text Label 8000 1450 2    50   ~ 0
QC
Text Label 8000 1550 2    50   ~ 0
QD
Text Label 8000 1650 2    50   ~ 0
QE
Wire Wire Line
	7300 1400 7450 1400
Wire Wire Line
	7300 1700 7450 1700
Wire Wire Line
	7300 2000 7450 2000
Wire Wire Line
	7300 2300 7450 2300
Entry Wire Line
	7450 1400 7550 1500
Entry Wire Line
	7450 1700 7550 1800
Entry Wire Line
	7450 1100 7550 1200
Entry Wire Line
	7450 2000 7550 2100
Entry Wire Line
	7450 2300 7550 2400
Wire Wire Line
	6450 2300 6800 2300
Connection ~ 6450 2300
Text Label 7450 1400 2    50   ~ 0
QB
Text Label 7450 1700 2    50   ~ 0
QC
Text Label 7450 2000 2    50   ~ 0
QD
Text Label 7450 2300 2    50   ~ 0
QE
Text Notes 6300 850  0    79   ~ 0
LED Circuit
Wire Notes Line
	900  3350 900  5050
Text Notes 900  3300 0    79   ~ 0
Sensor circuit
Text Notes 3600 4700 0    50   ~ 0
On button press, ESP8266 will wake up and \ndisplay the humidity values in the LEDs.
Text Notes 2150 1200 0    50   ~ 0
WeMos Battery shield is \nconnected to a LiPo battery.
Text Notes 3750 2900 0    50   ~ 0
WeMos remains in deep sleep for 6 hours and wakes \nup to sense the humidity value, display it in the LEDs \nand post the value to the cloud.
Text Notes 7100 3650 0    50   Italic 0
Humidity RH% | LED ON\n0 - 20       | D1\n21 - 40      | D1, D2\n41 - 60      | D1, D2, D3\n61 - 80      | D1, D2, D3, D4\n81 - 100     | D1, D2, D3, D4, D5
Wire Notes Line
	7050 3150 8550 3150
Wire Notes Line
	8550 3700 7050 3700
Wire Notes Line
	7050 3700 7050 3150
Wire Notes Line
	8550 3150 8550 3700
Text Notes 6450 2850 0    50   ~ 0
Humidity values are displayed in the LEDs.
Wire Notes Line
	6300 900  9350 900 
Wire Wire Line
	7850 1250 8250 1250
Wire Wire Line
	7850 1350 8250 1350
Wire Wire Line
	7850 1450 8250 1450
Wire Wire Line
	7850 1550 8250 1550
Wire Wire Line
	7850 1650 8250 1650
NoConn ~ 1100 1700
NoConn ~ 1100 1800
NoConn ~ 1100 2000
NoConn ~ 1100 2100
NoConn ~ 1100 2200
NoConn ~ 2500 1650
Text Label 1950 1300 0    50   ~ 0
5V
Text Label 4950 1000 0    50   ~ 0
5V
NoConn ~ 2500 2350
NoConn ~ 2500 1850
Text Label 3950 1700 2    50   ~ 0
I2C_SCL
NoConn ~ 4100 1400
NoConn ~ 4100 1500
NoConn ~ 4100 1900
Wire Bus Line
	7550 1050 7750 1050
Wire Notes Line
	3600 900  6000 900 
NoConn ~ 1100 2300
Wire Notes Line
	900  900  3300 900 
$Comp
L wemos_mini:WeMos_D1_mini U2
U 1 1 5C9440E1
P 4800 1700
F 0 "U2" H 5250 2250 60  0000 C CNN
F 1 "WeMos_D1_mini" H 5200 1100 60  0000 C CNN
F 2 "WeMos:D1_mini_board" H 5200 1000 60  0001 C CNN
F 3 "http://www.wemos.cc/Products/d1_mini.html" H 4800 2494 60  0001 C CNN
	1    4800 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1200 1800 1250
Wire Wire Line
	1800 1300 1950 1300
Wire Wire Line
	1800 1250 1800 1300
Connection ~ 1800 1250
Connection ~ 1800 1300
$Comp
L wemos_mini:WeMos_Battery_Shield U1
U 1 1 5C954F32
P 1800 2000
F 0 "U1" H 2200 2550 60  0000 C CNN
F 1 "WeMos_Battery_Shield" H 2300 1400 60  0000 C CNN
F 2 "WeMos:D1_mini_board" H 2200 1300 60  0001 C CNN
F 3 "http://www.wemos.cc/Products/d1_mini.html" H 1800 2794 60  0001 C CNN
	1    1800 2000
	1    0    0    -1  
$EndComp
Wire Notes Line
	900  3000 3300 3000
Wire Notes Line
	3300 900  3300 3000
Wire Notes Line
	900  900  900  3000
Wire Wire Line
	4800 1000 4950 1000
Wire Notes Line
	3600 3000 6000 3000
Wire Notes Line
	3600 900  3600 3000
Wire Notes Line
	6000 900  6000 3000
$Comp
L Si7021_breakout_board:Si7021_breakout U4
U 1 1 5C97D9C5
P 1800 4100
F 0 "U4" H 1500 4550 50  0000 L CNN
F 1 "Si7021_breakout" H 1050 3650 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 1800 3500 50  0001 C CNN
F 3 "https://learn.adafruit.com/adafruit-si7021-temperature-plus-humidity-sensor/downloads" H 1800 3900 50  0001 C CNN
	1    1800 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 4000 1250 4000
Wire Wire Line
	1400 4100 1250 4100
Text Label 2050 3450 0    50   ~ 0
5V
Wire Wire Line
	9050 1850 9150 1850
Connection ~ 8650 2350
Wire Notes Line
	6300 3000 9350 3000
Wire Notes Line
	6300 900  6300 3000
Wire Notes Line
	9350 900  9350 3000
Wire Wire Line
	9050 1550 9200 1550
Text Label 9200 1550 0    50   ~ 0
5V
Wire Wire Line
	4100 2000 3950 2000
Text Label 3950 2000 2    50   ~ 0
EN
Wire Wire Line
	8650 2350 8650 2550
Text Label 9150 1850 0    50   ~ 0
EN
$Comp
L Device:R_Small R9
U 1 1 5C9E0F92
P 2400 4050
F 0 "R9" V 2300 4000 50  0000 L CNN
F 1 "0ohm" V 2500 3950 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2400 4050 50  0001 C CNN
F 3 "~" H 2400 4050 50  0001 C CNN
	1    2400 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	2200 4050 2300 4050
Wire Wire Line
	2050 3600 2050 3450
Wire Wire Line
	1800 3600 2050 3600
Connection ~ 2050 3600
Text Notes 2200 4800 0    50   ~ 0
Do not populate for \nAdafruit 5-pin Si7021 \nbreakout board. \n\nPopulate it for other \n4-pin Si7021 breakout \nboards.
Wire Wire Line
	2550 3600 2550 4050
Wire Wire Line
	2550 4050 2500 4050
Wire Wire Line
	2050 3600 2550 3600
Wire Notes Line
	3200 3350 3200 5050
Wire Notes Line
	900  5050 3200 5050
Wire Notes Line
	900  3350 3200 3350
Wire Bus Line
	7550 1050 7550 2400
Wire Bus Line
	7750 1050 7750 1550
$EndSCHEMATC
