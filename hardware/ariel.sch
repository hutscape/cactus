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
P 8850 1600
F 0 "U4" H 8650 2150 50  0000 C CNN
F 1 "74HC595" H 8650 950 50  0000 C CNN
F 2 "" H 8850 1600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 8850 1600 50  0001 C CNN
	1    8850 1600
	-1   0    0    -1  
$EndComp
$Comp
L wemos_mini:WeMos_D1_mini U3
U 1 1 5C77373A
P 5300 1600
F 0 "U3" H 5300 1050 60  0000 C CNN
F 1 "WeMos_D1_mini" H 5300 2181 60  0000 C CNN
F 2 "" H 5700 900 60  0000 C CNN
F 3 "https://wiki.wemos.cc/products:d1_mini_shields:battery_shield" H 5300 2181 60  0001 C CNN
	1    5300 1600
	1    0    0    1   
$EndComp
$Comp
L Device:R_Small R3
U 1 1 5C7739E8
P 1600 3250
F 0 "R3" H 1450 3250 50  0000 L CNN
F 1 "470" H 1650 3250 50  0000 L CNN
F 2 "" H 1600 3250 50  0001 C CNN
F 3 "~" H 1600 3250 50  0001 C CNN
	1    1600 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 5C773C60
P 1450 3550
F 0 "R1" V 1350 3500 50  0000 L CNN
F 1 "1k" V 1550 3500 50  0000 L CNN
F 2 "" H 1450 3550 50  0001 C CNN
F 3 "~" H 1450 3550 50  0001 C CNN
	1    1450 3550
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5C773D83
P 1450 3850
F 0 "R2" V 1350 3850 50  0000 C CNN
F 1 "10k" V 1550 3850 50  0000 C CNN
F 2 "" H 1450 3850 50  0001 C CNN
F 3 "~" H 1450 3850 50  0001 C CNN
	1    1450 3850
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5C773EE5
P 1900 3850
F 0 "C1" V 1800 3800 50  0000 L CNN
F 1 "10u" V 2000 3800 50  0000 L CNN
F 2 "" H 1900 3850 50  0001 C CNN
F 3 "~" H 1900 3850 50  0001 C CNN
	1    1900 3850
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5C85EE0D
P 2200 3550
F 0 "SW1" H 2200 3700 50  0000 C CNN
F 1 "SW_Push" H 2200 3500 50  0000 C CNN
F 2 "" H 2200 3750 50  0001 C CNN
F 3 "" H 2200 3750 50  0001 C CNN
	1    2200 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 3550 1650 3550
Wire Wire Line
	1550 3850 1650 3850
Wire Wire Line
	1650 3550 1650 3850
Connection ~ 1650 3550
Wire Wire Line
	1650 3550 2000 3550
Connection ~ 1650 3850
Wire Wire Line
	1650 3850 1800 3850
$Comp
L power:GND #PWR03
U 1 1 5C8607DD
P 2450 3600
F 0 "#PWR03" H 2450 3350 50  0001 C CNN
F 1 "GND" H 2455 3427 50  0000 C CNN
F 2 "" H 2450 3600 50  0001 C CNN
F 3 "" H 2450 3600 50  0001 C CNN
	1    2450 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 3550 2450 3550
Wire Wire Line
	2450 3550 2450 3600
Wire Wire Line
	1600 3150 2600 3150
Wire Wire Line
	2600 3150 2600 3850
Wire Wire Line
	2600 3850 2000 3850
$Comp
L power:GND #PWR05
U 1 1 5C8612CC
P 4400 2050
F 0 "#PWR05" H 4400 1800 50  0001 C CNN
F 1 "GND" H 4405 1877 50  0000 C CNN
F 2 "" H 4400 2050 50  0001 C CNN
F 3 "" H 4400 2050 50  0001 C CNN
	1    4400 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 1900 4400 1900
Wire Wire Line
	4400 1900 4400 2050
$Comp
L power:GND #PWR07
U 1 1 5C8625CA
P 8850 2300
F 0 "#PWR07" H 8850 2050 50  0001 C CNN
F 1 "GND" H 9000 2250 50  0000 C CNN
F 2 "" H 8850 2300 50  0001 C CNN
F 3 "" H 8850 2300 50  0001 C CNN
	1    8850 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5C862AA3
P 7350 1100
F 0 "D1" H 7350 1200 50  0000 C CNN
F 1 "LED" H 7350 1000 50  0000 C CNN
F 2 "" H 7350 1100 50  0001 C CNN
F 3 "~" H 7350 1100 50  0001 C CNN
	1    7350 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 5C862B20
P 7350 1400
F 0 "D2" H 7350 1500 50  0000 C CNN
F 1 "LED" H 7350 1300 50  0000 C CNN
F 2 "" H 7350 1400 50  0001 C CNN
F 3 "~" H 7350 1400 50  0001 C CNN
	1    7350 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 5C862C14
P 7350 1700
F 0 "D3" H 7350 1800 50  0000 C CNN
F 1 "LED" H 7350 1600 50  0000 C CNN
F 2 "" H 7350 1700 50  0001 C CNN
F 3 "~" H 7350 1700 50  0001 C CNN
	1    7350 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D4
U 1 1 5C862C76
P 7350 2000
F 0 "D4" H 7350 2100 50  0000 C CNN
F 1 "LED" H 7350 1900 50  0000 C CNN
F 2 "" H 7350 2000 50  0001 C CNN
F 3 "~" H 7350 2000 50  0001 C CNN
	1    7350 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D5
U 1 1 5C862CE0
P 7350 2300
F 0 "D5" H 7350 2400 50  0000 C CNN
F 1 "LED" H 7350 2200 50  0000 C CNN
F 2 "" H 7350 2300 50  0001 C CNN
F 3 "~" H 7350 2300 50  0001 C CNN
	1    7350 2300
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Humidity:Si7020-A20 U2
U 1 1 5C86A90D
P 3750 3900
F 0 "U2" V 3300 3900 50  0000 C CNN
F 1 "Si7020-A20" V 4250 3900 50  0000 C CNN
F 2 "Package_DFN_QFN:DFN-6-1EP_3x3mm_P1mm_EP1.5x2.4mm" H 3750 3500 50  0001 C CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/Si7020-A20.pdf" H 3550 4200 50  0001 C CNN
	1    3750 3900
	0    1    1    0   
$EndComp
NoConn ~ 3450 4000
$Comp
L Device:R_Small R4
U 1 1 5C871A82
P 7600 1100
F 0 "R4" V 7500 1050 50  0000 L CNN
F 1 "1k" V 7700 1050 50  0000 L CNN
F 2 "" H 7600 1100 50  0001 C CNN
F 3 "~" H 7600 1100 50  0001 C CNN
	1    7600 1100
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R5
U 1 1 5C871CA9
P 7600 1400
F 0 "R5" V 7500 1350 50  0000 L CNN
F 1 "1k" V 7700 1350 50  0000 L CNN
F 2 "" H 7600 1400 50  0001 C CNN
F 3 "~" H 7600 1400 50  0001 C CNN
	1    7600 1400
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R6
U 1 1 5C871E05
P 7600 1700
F 0 "R6" V 7500 1650 50  0000 L CNN
F 1 "1k" V 7700 1650 50  0000 L CNN
F 2 "" H 7600 1700 50  0001 C CNN
F 3 "~" H 7600 1700 50  0001 C CNN
	1    7600 1700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R7
U 1 1 5C871EB9
P 7600 2000
F 0 "R7" V 7500 1950 50  0000 L CNN
F 1 "1k" V 7700 1950 50  0000 L CNN
F 2 "" H 7600 2000 50  0001 C CNN
F 3 "~" H 7600 2000 50  0001 C CNN
	1    7600 2000
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R8
U 1 1 5C871F77
P 7600 2300
F 0 "R8" V 7500 2250 50  0000 L CNN
F 1 "1k" V 7700 2250 50  0000 L CNN
F 2 "" H 7600 2300 50  0001 C CNN
F 3 "~" H 7600 2300 50  0001 C CNN
	1    7600 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	6850 1100 6850 1400
Connection ~ 6850 2000
Wire Wire Line
	6850 2000 6850 2300
Connection ~ 6850 1700
Wire Wire Line
	6850 1700 6850 2000
Connection ~ 6850 1400
Wire Wire Line
	6850 1400 6850 1700
$Comp
L power:GND #PWR06
U 1 1 5C88238D
P 6850 2300
F 0 "#PWR06" H 6850 2050 50  0001 C CNN
F 1 "GND" H 6855 2127 50  0000 C CNN
F 2 "" H 6850 2300 50  0001 C CNN
F 3 "" H 6850 2300 50  0001 C CNN
	1    6850 2300
	1    0    0    -1  
$EndComp
NoConn ~ 9250 1500
NoConn ~ 8450 1700
NoConn ~ 8450 1800
NoConn ~ 8450 1900
NoConn ~ 8450 2100
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
Wire Wire Line
	2100 1950 2100 2250
Wire Wire Line
	2100 2250 1450 2250
NoConn ~ 4600 2000
Text Label 1950 1250 2    50   ~ 0
TX
Text Label 4450 1300 2    50   ~ 0
TX
Text Label 1950 1350 2    50   ~ 0
RX
Text Label 4450 1400 2    50   ~ 0
RX
Text Label 1950 1450 2    50   ~ 0
D1
Text Label 4450 1500 2    50   ~ 0
D1
Text Label 1950 1550 2    50   ~ 0
D2
Text Label 4450 1600 2    50   ~ 0
D2
Text Label 1950 1650 2    50   ~ 0
D3
Text Label 4450 1700 2    50   ~ 0
D3
Text Label 1950 1750 2    50   ~ 0
D4
Text Label 4450 1800 2    50   ~ 0
D4
Text Label 3650 1250 0    50   ~ 0
RST
Text Label 6150 1300 0    50   ~ 0
RST
Text Label 3650 1350 0    50   ~ 0
A0
Text Label 6150 1400 0    50   ~ 0
A0
Text Label 3650 1450 0    50   ~ 0
D0
Text Label 6150 1500 0    50   ~ 0
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
Text Label 4200 3250 0    50   ~ 0
D1
Text Label 4200 3400 0    50   ~ 0
D2
$Comp
L power:GND #PWR04
U 1 1 5C89C91B
P 3250 3850
F 0 "#PWR04" H 3250 3600 50  0001 C CNN
F 1 "GND" H 3255 3677 50  0000 C CNN
F 2 "" H 3250 3850 50  0001 C CNN
F 3 "" H 3250 3850 50  0001 C CNN
	1    3250 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3800 3250 3800
Wire Wire Line
	3250 3800 3250 3850
Text Label 6150 2000 0    50   ~ 0
3_3V
Text Label 4200 3900 0    50   ~ 0
3_3V
Text Label 9000 1000 0    50   ~ 0
3_3V
Text Label 6150 1900 0    50   ~ 0
D8
Text Label 9400 1700 0    50   ~ 0
D8
Text Label 9400 1800 0    50   ~ 0
D4
Text Label 9400 1200 0    50   ~ 0
D7
Text Label 6150 1800 0    50   ~ 0
D7
Text Label 9400 1400 0    50   ~ 0
D5
Text Label 6150 1600 0    50   ~ 0
D5
Text Label 3650 1950 0    50   ~ 0
3_3V
Wire Wire Line
	2100 1250 1950 1250
Wire Wire Line
	2100 1350 1950 1350
Wire Wire Line
	2100 1450 1950 1450
Wire Wire Line
	2100 1550 1950 1550
Wire Wire Line
	2100 1650 1950 1650
Wire Wire Line
	2100 1750 1950 1750
Wire Wire Line
	3500 1250 3650 1250
Wire Wire Line
	3500 1350 3650 1350
Wire Wire Line
	3500 1450 3650 1450
Wire Wire Line
	3500 1950 3650 1950
Text Label 1200 3150 2    50   ~ 0
RST
Text Label 1200 3350 2    50   ~ 0
D0
Text Label 6150 1700 0    50   ~ 0
D6
Text Label 1200 3550 2    50   ~ 0
D6
Text Label 1200 3850 2    50   ~ 0
3_3V
Wire Notes Line
	3900 900  3900 2600
Wire Notes Line
	900  900  3900 900 
Wire Notes Line
	900  2600 3900 2600
Wire Notes Line
	4200 900  6400 900 
Wire Notes Line
	6400 900  6400 2600
Wire Notes Line
	6400 2600 4200 2600
Wire Notes Line
	4200 900  4200 2600
Wire Wire Line
	4600 1300 4450 1300
Wire Wire Line
	4600 1400 4450 1400
Wire Wire Line
	4600 1500 4450 1500
Wire Wire Line
	4600 1600 4450 1600
Wire Wire Line
	4600 1700 4450 1700
Wire Wire Line
	4600 1800 4450 1800
Wire Wire Line
	6000 1300 6150 1300
Wire Wire Line
	6000 1400 6150 1400
Wire Wire Line
	6000 1500 6150 1500
Wire Wire Line
	6000 1600 6150 1600
Wire Wire Line
	6000 1700 6150 1700
Wire Wire Line
	6000 1800 6150 1800
Wire Wire Line
	6000 1900 6150 1900
Wire Wire Line
	6000 2000 6150 2000
Text Notes 4200 850  0    79   ~ 0
WeMos D1 Mini v3.0.0
Wire Wire Line
	1600 3150 1200 3150
Connection ~ 1600 3150
Wire Wire Line
	1600 3350 1200 3350
Wire Wire Line
	1350 3550 1200 3550
Wire Wire Line
	1350 3850 1200 3850
Wire Notes Line
	900  4700 2900 4700
Wire Notes Line
	2900 4700 2900 3000
Wire Notes Line
	2900 3000 900  3000
Wire Notes Line
	900  3000 900  4700
Text Notes 900  2950 0    79   ~ 0
Button circuit
Wire Wire Line
	6850 1100 7200 1100
Wire Wire Line
	6850 1400 7200 1400
Wire Wire Line
	6850 2000 7200 2000
Wire Wire Line
	6850 1700 7200 1700
Wire Wire Line
	9250 1200 9400 1200
Wire Wire Line
	9250 1400 9400 1400
Wire Wire Line
	9250 1700 9400 1700
Wire Wire Line
	9250 1800 9400 1800
Wire Wire Line
	8850 1000 9000 1000
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5C8B6759
P 8850 2300
F 0 "#FLG02" H 8850 2375 50  0001 C CNN
F 1 "PWR_FLAG" V 8850 2600 50  0000 C CNN
F 2 "" H 8850 2300 50  0001 C CNN
F 3 "~" H 8850 2300 50  0001 C CNN
	1    8850 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7700 1100 7850 1100
Text Label 8200 1200 2    50   ~ 0
QA
Text Label 7850 1100 2    50   ~ 0
QA
Entry Wire Line
	7950 1100 8050 1200
Entry Wire Line
	7950 1200 8050 1300
Entry Wire Line
	7950 1300 8050 1400
Entry Wire Line
	7950 1400 8050 1500
Entry Wire Line
	7950 1500 8050 1600
Text Label 8200 1300 2    50   ~ 0
QB
Text Label 8200 1400 2    50   ~ 0
QC
Text Label 8200 1500 2    50   ~ 0
QD
Text Label 8200 1600 2    50   ~ 0
QE
Wire Wire Line
	7700 1400 7850 1400
Wire Wire Line
	7700 1700 7850 1700
Wire Wire Line
	7700 2000 7850 2000
Wire Wire Line
	7700 2300 7850 2300
Entry Wire Line
	7850 1400 7950 1500
Entry Wire Line
	7850 1700 7950 1800
Entry Wire Line
	7850 1100 7950 1200
Entry Wire Line
	7850 2000 7950 2100
Entry Wire Line
	7850 2300 7950 2400
Wire Wire Line
	6850 2300 7200 2300
Connection ~ 6850 2300
Text Label 7850 1400 2    50   ~ 0
QB
Text Label 7850 1700 2    50   ~ 0
QC
Text Label 7850 2000 2    50   ~ 0
QD
Text Label 7850 2300 2    50   ~ 0
QE
Wire Notes Line
	6700 900  6700 2600
Connection ~ 8850 2300
Text Notes 6700 850  0    79   ~ 0
LED Circuit
Wire Wire Line
	4050 3900 4200 3900
Wire Wire Line
	3650 3400 3650 3250
Wire Wire Line
	3850 3400 4200 3400
Wire Wire Line
	3650 3250 4200 3250
Wire Notes Line
	3050 3000 4450 3000
Wire Notes Line
	4450 3000 4450 4700
Wire Notes Line
	4450 4700 3050 4700
Wire Notes Line
	3050 3000 3050 4700
Text Notes 3050 2950 0    79   ~ 0
Sensor circuit
Text Notes 1000 4350 0    50   ~ 0
On button press, ESP8266 will wake up and \ndisplay the humidity values in the LEDs.
Text Notes 1000 2500 0    50   ~ 0
Battery shield is connected to a LiPo battery.
Text Notes 4250 2550 0    50   ~ 0
WeMos remains in deep sleep for 6 hours and wakes \nup to sense the humidity value, display it in the LEDs \nand post the value to the cloud.
Text Notes 7450 3250 0    50   Italic 0
Humidity RH% | LED ON\n0 - 20       | D1\n21 - 40      | D1, D2\n41 - 60      | D1, D2, D3\n61 - 80      | D1, D2, D3, D4\n81 - 100     | D1, D2, D3, D4, D5
Wire Notes Line
	7400 2750 8900 2750
Wire Notes Line
	8900 3300 7400 3300
Wire Notes Line
	7400 3300 7400 2750
Wire Notes Line
	8900 2750 8900 3300
Text Notes 8000 2550 0    50   ~ 0
Humidity values are displayed in the LEDs.
Wire Notes Line
	9750 900  9750 2600
Wire Notes Line
	6700 2600 9750 2600
Wire Notes Line
	6700 900  9750 900 
Wire Wire Line
	8050 1200 8450 1200
Wire Wire Line
	8050 1300 8450 1300
Wire Wire Line
	8050 1400 8450 1400
Wire Wire Line
	8050 1500 8450 1500
Wire Wire Line
	8050 1600 8450 1600
Wire Bus Line
	7950 950  7950 2600
$EndSCHEMATC
