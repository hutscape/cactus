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
L 74xx:74HC595 U4
U 1 1 5C77296E
P 9250 1650
F 0 "U4" H 9050 2200 50  0000 C CNN
F 1 "74HC595" H 9050 1000 50  0000 C CNN
F 2 "" H 9250 1650 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 9250 1650 50  0001 C CNN
	1    9250 1650
	-1   0    0    -1  
$EndComp
$Comp
L wemos_mini:WeMos_D1_mini U3
U 1 1 5C77373A
P 5400 1600
F 0 "U3" H 5400 1050 60  0000 C CNN
F 1 "WeMos_D1_mini" H 5400 2181 60  0000 C CNN
F 2 "" H 5800 900 60  0000 C CNN
F 3 "https://wiki.wemos.cc/products:d1_mini_shields:battery_shield" H 5400 2181 60  0001 C CNN
	1    5400 1600
	1    0    0    1   
$EndComp
$Comp
L Device:R_Small R3
U 1 1 5C7739E8
P 3400 3250
F 0 "R3" H 3250 3250 50  0000 L CNN
F 1 "470" H 3450 3250 50  0000 L CNN
F 2 "" H 3400 3250 50  0001 C CNN
F 3 "~" H 3400 3250 50  0001 C CNN
	1    3400 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 5C773C60
P 3250 3550
F 0 "R1" V 3150 3500 50  0000 L CNN
F 1 "1k" V 3350 3500 50  0000 L CNN
F 2 "" H 3250 3550 50  0001 C CNN
F 3 "~" H 3250 3550 50  0001 C CNN
	1    3250 3550
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5C773D83
P 3250 3850
F 0 "R2" V 3150 3850 50  0000 C CNN
F 1 "10k" V 3350 3850 50  0000 C CNN
F 2 "" H 3250 3850 50  0001 C CNN
F 3 "~" H 3250 3850 50  0001 C CNN
	1    3250 3850
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5C773EE5
P 3700 3850
F 0 "C1" V 3600 3800 50  0000 L CNN
F 1 "10u" V 3800 3800 50  0000 L CNN
F 2 "" H 3700 3850 50  0001 C CNN
F 3 "~" H 3700 3850 50  0001 C CNN
	1    3700 3850
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5C85EE0D
P 4000 3550
F 0 "SW1" H 4000 3700 50  0000 C CNN
F 1 "SW_Push" H 4000 3500 50  0000 C CNN
F 2 "" H 4000 3750 50  0001 C CNN
F 3 "" H 4000 3750 50  0001 C CNN
	1    4000 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3550 3450 3550
Wire Wire Line
	3350 3850 3450 3850
Wire Wire Line
	3450 3550 3450 3850
Connection ~ 3450 3550
Wire Wire Line
	3450 3550 3800 3550
Connection ~ 3450 3850
Wire Wire Line
	3450 3850 3600 3850
$Comp
L power:GND #PWR03
U 1 1 5C8607DD
P 4250 3600
F 0 "#PWR03" H 4250 3350 50  0001 C CNN
F 1 "GND" H 4255 3427 50  0000 C CNN
F 2 "" H 4250 3600 50  0001 C CNN
F 3 "" H 4250 3600 50  0001 C CNN
	1    4250 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3550 4250 3550
Wire Wire Line
	4250 3550 4250 3600
Wire Wire Line
	3400 3150 4400 3150
Wire Wire Line
	4400 3150 4400 3850
Wire Wire Line
	4400 3850 3800 3850
$Comp
L power:GND #PWR05
U 1 1 5C8612CC
P 4500 2050
F 0 "#PWR05" H 4500 1800 50  0001 C CNN
F 1 "GND" H 4505 1877 50  0000 C CNN
F 2 "" H 4500 2050 50  0001 C CNN
F 3 "" H 4500 2050 50  0001 C CNN
	1    4500 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 1900 4500 1900
Wire Wire Line
	4500 1900 4500 2050
$Comp
L power:GND #PWR07
U 1 1 5C8625CA
P 9250 2350
F 0 "#PWR07" H 9250 2100 50  0001 C CNN
F 1 "GND" H 9400 2300 50  0000 C CNN
F 2 "" H 9250 2350 50  0001 C CNN
F 3 "" H 9250 2350 50  0001 C CNN
	1    9250 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5C862AA3
P 7550 1100
F 0 "D1" H 7550 1200 50  0000 C CNN
F 1 "LED" H 7550 1000 50  0000 C CNN
F 2 "" H 7550 1100 50  0001 C CNN
F 3 "~" H 7550 1100 50  0001 C CNN
	1    7550 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 5C862B20
P 7550 1400
F 0 "D2" H 7550 1500 50  0000 C CNN
F 1 "LED" H 7550 1300 50  0000 C CNN
F 2 "" H 7550 1400 50  0001 C CNN
F 3 "~" H 7550 1400 50  0001 C CNN
	1    7550 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 5C862C14
P 7550 1700
F 0 "D3" H 7550 1800 50  0000 C CNN
F 1 "LED" H 7550 1600 50  0000 C CNN
F 2 "" H 7550 1700 50  0001 C CNN
F 3 "~" H 7550 1700 50  0001 C CNN
	1    7550 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D4
U 1 1 5C862C76
P 7550 2000
F 0 "D4" H 7550 2100 50  0000 C CNN
F 1 "LED" H 7550 1900 50  0000 C CNN
F 2 "" H 7550 2000 50  0001 C CNN
F 3 "~" H 7550 2000 50  0001 C CNN
	1    7550 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D5
U 1 1 5C862CE0
P 7550 2300
F 0 "D5" H 7550 2400 50  0000 C CNN
F 1 "LED" H 7550 2200 50  0000 C CNN
F 2 "" H 7550 2300 50  0001 C CNN
F 3 "~" H 7550 2300 50  0001 C CNN
	1    7550 2300
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Humidity:Si7020-A20 U2
U 1 1 5C86A90D
P 1600 3900
F 0 "U2" V 1150 3900 50  0000 C CNN
F 1 "Si7020-A20" V 2100 3900 50  0000 C CNN
F 2 "Package_DFN_QFN:DFN-6-1EP_3x3mm_P1mm_EP1.5x2.4mm" H 1600 3500 50  0001 C CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/Si7020-A20.pdf" H 1400 4200 50  0001 C CNN
	1    1600 3900
	0    1    1    0   
$EndComp
NoConn ~ 1300 4000
$Comp
L Device:R_Small R4
U 1 1 5C871A82
P 7800 1100
F 0 "R4" V 7700 1050 50  0000 L CNN
F 1 "1k" V 7900 1050 50  0000 L CNN
F 2 "" H 7800 1100 50  0001 C CNN
F 3 "~" H 7800 1100 50  0001 C CNN
	1    7800 1100
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R5
U 1 1 5C871CA9
P 7800 1400
F 0 "R5" V 7700 1350 50  0000 L CNN
F 1 "1k" V 7900 1350 50  0000 L CNN
F 2 "" H 7800 1400 50  0001 C CNN
F 3 "~" H 7800 1400 50  0001 C CNN
	1    7800 1400
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R6
U 1 1 5C871E05
P 7800 1700
F 0 "R6" V 7700 1650 50  0000 L CNN
F 1 "1k" V 7900 1650 50  0000 L CNN
F 2 "" H 7800 1700 50  0001 C CNN
F 3 "~" H 7800 1700 50  0001 C CNN
	1    7800 1700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R7
U 1 1 5C871EB9
P 7800 2000
F 0 "R7" V 7700 1950 50  0000 L CNN
F 1 "1k" V 7900 1950 50  0000 L CNN
F 2 "" H 7800 2000 50  0001 C CNN
F 3 "~" H 7800 2000 50  0001 C CNN
	1    7800 2000
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R8
U 1 1 5C871F77
P 7800 2300
F 0 "R8" V 7700 2250 50  0000 L CNN
F 1 "1k" V 7900 2250 50  0000 L CNN
F 2 "" H 7800 2300 50  0001 C CNN
F 3 "~" H 7800 2300 50  0001 C CNN
	1    7800 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	7050 1100 7050 1400
Connection ~ 7050 2000
Wire Wire Line
	7050 2000 7050 2300
Connection ~ 7050 1700
Wire Wire Line
	7050 1700 7050 2000
Connection ~ 7050 1400
Wire Wire Line
	7050 1400 7050 1700
$Comp
L power:GND #PWR06
U 1 1 5C88238D
P 7050 2300
F 0 "#PWR06" H 7050 2050 50  0001 C CNN
F 1 "GND" H 7055 2127 50  0000 C CNN
F 2 "" H 7050 2300 50  0001 C CNN
F 3 "" H 7050 2300 50  0001 C CNN
	1    7050 2300
	1    0    0    -1  
$EndComp
NoConn ~ 9650 1550
NoConn ~ 8850 1750
NoConn ~ 8850 1850
NoConn ~ 8850 1950
NoConn ~ 8850 2150
$Comp
L wemos_mini:WeMos_Battery_Shield U1
U 1 1 5C885570
P 2800 1550
F 0 "U1" H 2800 1000 60  0000 C CNN
F 1 "WeMos_Battery_Shield" H 2800 2100 60  0000 C CNN
F 2 "" H 3200 850 60  0000 C CNN
F 3 "http://www.wemos.cc/Products/d1_mini.html" H 2800 2131 60  0001 C CNN
	1    2800 1550
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5C893BFC
P 1800 1950
F 0 "#PWR02" H 1800 1700 50  0001 C CNN
F 1 "GND" H 1805 1777 50  0000 C CNN
F 2 "" H 1800 1950 50  0001 C CNN
F 3 "" H 1800 1950 50  0001 C CNN
	1    1800 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 1850 1800 1850
Wire Wire Line
	1800 1850 1800 1950
NoConn ~ 3500 1550
NoConn ~ 3500 1650
NoConn ~ 3500 1750
NoConn ~ 3500 1850
$Comp
L power:VCC #PWR01
U 1 1 5C8A5397
P 1450 2050
F 0 "#PWR01" H 1450 1900 50  0001 C CNN
F 1 "VCC" H 1450 2200 50  0000 C CNN
F 2 "" H 1450 2050 50  0001 C CNN
F 3 "" H 1450 2050 50  0001 C CNN
	1    1450 2050
	1    0    0    -1  
$EndComp
Text Label 4550 1600 2    50   ~ 0
I2C_SDA
Text Label 4550 1800 2    50   ~ 0
D4
Text Label 6250 1300 0    50   ~ 0
RST
Text Label 3650 1350 0    50   ~ 0
A0
Text Label 6250 1400 0    50   ~ 0
A0
Text Label 6250 1500 0    50   ~ 0
D0
Wire Wire Line
	1450 2150 1450 2250
Wire Wire Line
	1450 2050 1450 2150
Connection ~ 1450 2150
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5C86A0B5
P 1450 2150
F 0 "#FLG01" H 1450 2225 50  0001 C CNN
F 1 "PWR_FLAG" V 1450 2450 50  0000 C CNN
F 2 "" H 1450 2150 50  0001 C CNN
F 3 "~" H 1450 2150 50  0001 C CNN
	1    1450 2150
	0    -1   -1   0   
$EndComp
Wire Notes Line
	900  2600 900  900 
Text Notes 900  850  0    79   ~ 0
WeMos Battery Shield 
Text Label 2050 3250 0    50   ~ 0
I2C_SCL
Text Label 2050 3400 0    50   ~ 0
I2C_SDA
$Comp
L power:GND #PWR04
U 1 1 5C89C91B
P 1100 3850
F 0 "#PWR04" H 1100 3600 50  0001 C CNN
F 1 "GND" H 1105 3677 50  0000 C CNN
F 2 "" H 1100 3850 50  0001 C CNN
F 3 "" H 1100 3850 50  0001 C CNN
	1    1100 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 3800 1100 3800
Wire Wire Line
	1100 3800 1100 3850
Text Label 6250 2000 0    50   ~ 0
3_3V
Text Label 2050 3900 0    50   ~ 0
5V
Text Label 9400 1050 0    50   ~ 0
3_3V
Text Label 6250 1900 0    50   ~ 0
D8
Text Label 9800 1750 0    50   ~ 0
D8
Text Label 9800 1850 0    50   ~ 0
D4
Text Label 9800 1250 0    50   ~ 0
D7
Text Label 6250 1800 0    50   ~ 0
D7
Text Label 9800 1450 0    50   ~ 0
D5
Text Label 6250 1600 0    50   ~ 0
D5
Wire Wire Line
	3500 1350 3650 1350
Text Label 3000 3150 2    50   ~ 0
RST
Text Label 3000 3350 2    50   ~ 0
D0
Text Label 6250 1700 0    50   ~ 0
D6
Text Label 3000 3550 2    50   ~ 0
D6
Text Label 3000 3850 2    50   ~ 0
3_3V
Wire Notes Line
	3900 900  3900 2600
Wire Notes Line
	900  900  3900 900 
Wire Notes Line
	900  2600 3900 2600
Wire Notes Line
	4200 900  4200 2600
Wire Wire Line
	4700 1500 4550 1500
Wire Wire Line
	4700 1600 4550 1600
Wire Wire Line
	4700 1800 4550 1800
Wire Wire Line
	6100 1300 6250 1300
Wire Wire Line
	6100 1400 6250 1400
Wire Wire Line
	6100 1500 6250 1500
Wire Wire Line
	6100 1600 6250 1600
Wire Wire Line
	6100 1700 6250 1700
Wire Wire Line
	6100 1800 6250 1800
Wire Wire Line
	6100 1900 6250 1900
Wire Wire Line
	6100 2000 6250 2000
Text Notes 4200 850  0    79   ~ 0
WeMos D1 Mini v3.0.0
Wire Wire Line
	3400 3150 3000 3150
Connection ~ 3400 3150
Wire Wire Line
	3400 3350 3000 3350
Wire Wire Line
	3150 3550 3000 3550
Wire Wire Line
	3150 3850 3000 3850
Wire Notes Line
	2700 4700 4700 4700
Wire Notes Line
	4700 4700 4700 3000
Wire Notes Line
	4700 3000 2700 3000
Wire Notes Line
	2700 3000 2700 4700
Text Notes 2700 2950 0    79   ~ 0
Button circuit
Wire Wire Line
	7050 1100 7400 1100
Wire Wire Line
	7050 1400 7400 1400
Wire Wire Line
	7050 2000 7400 2000
Wire Wire Line
	7050 1700 7400 1700
Wire Wire Line
	9650 1250 9800 1250
Wire Wire Line
	9650 1450 9800 1450
Wire Wire Line
	9650 1750 9800 1750
Wire Wire Line
	9650 1850 9800 1850
Wire Wire Line
	9250 1050 9400 1050
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5C8B6759
P 9250 2350
F 0 "#FLG02" H 9250 2425 50  0001 C CNN
F 1 "PWR_FLAG" V 9250 2650 50  0000 C CNN
F 2 "" H 9250 2350 50  0001 C CNN
F 3 "~" H 9250 2350 50  0001 C CNN
	1    9250 2350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7900 1100 8050 1100
Text Label 8600 1250 2    50   ~ 0
QA
Text Label 8050 1100 2    50   ~ 0
QA
Entry Wire Line
	8350 1150 8450 1250
Entry Wire Line
	8350 1250 8450 1350
Entry Wire Line
	8350 1350 8450 1450
Entry Wire Line
	8350 1450 8450 1550
Entry Wire Line
	8350 1550 8450 1650
Text Label 8600 1350 2    50   ~ 0
QB
Text Label 8600 1450 2    50   ~ 0
QC
Text Label 8600 1550 2    50   ~ 0
QD
Text Label 8600 1650 2    50   ~ 0
QE
Wire Wire Line
	7900 1400 8050 1400
Wire Wire Line
	7900 1700 8050 1700
Wire Wire Line
	7900 2000 8050 2000
Wire Wire Line
	7900 2300 8050 2300
Entry Wire Line
	8050 1400 8150 1500
Entry Wire Line
	8050 1700 8150 1800
Entry Wire Line
	8050 1100 8150 1200
Entry Wire Line
	8050 2000 8150 2100
Entry Wire Line
	8050 2300 8150 2400
Wire Wire Line
	7050 2300 7400 2300
Connection ~ 7050 2300
Text Label 8050 1400 2    50   ~ 0
QB
Text Label 8050 1700 2    50   ~ 0
QC
Text Label 8050 2000 2    50   ~ 0
QD
Text Label 8050 2300 2    50   ~ 0
QE
Wire Notes Line
	6900 900  6900 2600
Text Notes 6900 850  0    79   ~ 0
LED Circuit
Wire Wire Line
	1900 3900 2050 3900
Wire Wire Line
	1500 3400 1500 3250
Wire Wire Line
	1700 3400 2050 3400
Wire Wire Line
	1500 3250 2050 3250
Wire Notes Line
	900  3000 900  4700
Text Notes 900  2950 0    79   ~ 0
Sensor circuit
Text Notes 2800 4350 0    50   ~ 0
On button press, ESP8266 will wake up and \ndisplay the humidity values in the LEDs.
Text Notes 1000 2500 0    50   ~ 0
WeMos Battery shield is connected to a LiPo battery.
Text Notes 4350 2550 0    50   ~ 0
WeMos remains in deep sleep for 6 hours and wakes \nup to sense the humidity value, display it in the LEDs \nand post the value to the cloud.
Text Notes 7650 3250 0    50   Italic 0
Humidity RH% | LED ON\n0 - 20       | D1\n21 - 40      | D1, D2\n41 - 60      | D1, D2, D3\n61 - 80      | D1, D2, D3, D4\n81 - 100     | D1, D2, D3, D4, D5
Wire Notes Line
	7600 2750 9100 2750
Wire Notes Line
	9100 3300 7600 3300
Wire Notes Line
	7600 3300 7600 2750
Wire Notes Line
	9100 2750 9100 3300
Text Notes 8200 2550 0    50   ~ 0
Humidity values are displayed in the LEDs.
Wire Notes Line
	9950 900  9950 2600
Wire Notes Line
	6900 2600 9950 2600
Wire Notes Line
	6900 900  9950 900 
Wire Wire Line
	8450 1250 8850 1250
Wire Wire Line
	8450 1350 8850 1350
Wire Wire Line
	8450 1450 8850 1450
Wire Wire Line
	8450 1550 8850 1550
Wire Wire Line
	8450 1650 8850 1650
NoConn ~ 2100 1250
NoConn ~ 2100 1350
NoConn ~ 2100 1450
NoConn ~ 2100 1550
NoConn ~ 2100 1650
NoConn ~ 2100 1750
NoConn ~ 3500 1250
Wire Wire Line
	2100 1950 1950 1950
Wire Wire Line
	1950 1950 1950 2250
Wire Wire Line
	1950 2250 1450 2250
Text Label 2000 1950 2    50   ~ 0
5V
Text Label 4700 2000 2    50   ~ 0
5V
NoConn ~ 3500 1950
NoConn ~ 3500 1450
Text Label 4550 1500 2    50   ~ 0
I2C_SCL
NoConn ~ 4700 1300
NoConn ~ 4700 1400
NoConn ~ 4700 1700
Wire Bus Line
	8150 1050 8350 1050
Wire Notes Line
	4200 900  6600 900 
Wire Notes Line
	6600 900  6600 2600
Wire Notes Line
	4200 2600 6600 2600
Wire Notes Line
	2450 3000 2450 4700
Wire Notes Line
	900  3000 2450 3000
Wire Notes Line
	900  4700 2450 4700
Connection ~ 9250 2350
Wire Bus Line
	8350 1050 8350 1550
Wire Bus Line
	8150 1050 8150 2400
$EndSCHEMATC
