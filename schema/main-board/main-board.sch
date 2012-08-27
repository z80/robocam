EESchema Schematic File Version 2  date Mon 27 Aug 2012 09:38:47 PM MSK
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ncp3063
LIBS:sdc
LIBS:stm
LIBS:usb
LIBS:l293
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "27 aug 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L NCP3063 U?
U 1 1 503BB09B
P 6700 4450
F 0 "U?" H 6600 4750 60  0000 C CNN
F 1 "NCP3063" H 6650 4150 60  0000 C CNN
	1    6700 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 503BB009
P 7300 2200
F 0 "#PWR?" H 7300 2200 30  0001 C CNN
F 1 "GND" H 7300 2130 30  0001 C CNN
	1    7300 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 2200 7300 2150
Connection ~ 7500 2150
Wire Wire Line
	7300 2150 7500 2150
Wire Wire Line
	7600 2500 6900 2500
Connection ~ 7500 2200
Wire Wire Line
	7600 2300 7500 2300
Wire Wire Line
	7500 2300 7500 2000
Wire Wire Line
	7500 2100 7600 2100
Wire Wire Line
	7500 2000 7600 2000
Wire Wire Line
	7600 1800 6900 1800
Wire Wire Line
	8700 2600 9200 2600
Wire Wire Line
	8700 2400 9200 2400
Connection ~ 8800 2200
Wire Wire Line
	8700 2300 8800 2300
Wire Wire Line
	8800 2300 8800 2000
Wire Wire Line
	8800 2100 8700 2100
Wire Wire Line
	8800 2000 8700 2000
Wire Wire Line
	8700 1800 9200 1800
Wire Wire Line
	3800 2100 3400 2100
Wire Wire Line
	3400 1900 3800 1900
Wire Wire Line
	3400 900  3800 900 
Wire Wire Line
	1350 850  1350 1200
Connection ~ 1500 6800
Wire Wire Line
	1500 7400 1500 7600
Connection ~ 1500 5150
Wire Wire Line
	1500 5500 1500 5150
Wire Wire Line
	1650 5150 1350 5150
Wire Wire Line
	2250 5150 2400 5150
Wire Wire Line
	2400 5150 2400 5300
Wire Wire Line
	1500 6200 1500 6000
Wire Wire Line
	1500 6900 1500 6700
Wire Wire Line
	2250 6800 1500 6800
Wire Wire Line
	2100 2500 1350 2500
Wire Wire Line
	1350 2600 1350 2400
Wire Wire Line
	1350 1900 1350 1700
Wire Wire Line
	1350 3100 1350 3300
Connection ~ 1350 2500
Wire Wire Line
	1550 850  1150 850 
Connection ~ 1350 850 
Wire Wire Line
	3400 1100 3600 1100
Wire Wire Line
	3600 1100 3600 1300
Wire Wire Line
	3400 2300 3600 2300
Wire Wire Line
	3600 2300 3600 2500
Wire Wire Line
	8700 1700 8950 1700
Wire Wire Line
	8950 1700 8950 1450
Wire Wire Line
	8700 1900 9200 1900
Wire Wire Line
	8800 2200 8700 2200
Connection ~ 8800 2100
Wire Wire Line
	8800 2150 9200 2150
Connection ~ 8800 2150
Wire Wire Line
	9200 2150 9200 2250
Wire Wire Line
	8700 2500 9200 2500
Wire Wire Line
	7600 1700 6900 1700
Wire Wire Line
	7600 1900 6900 1900
Wire Wire Line
	7500 2200 7600 2200
Connection ~ 7500 2100
Wire Wire Line
	7600 2400 6900 2400
Wire Wire Line
	7600 2600 6900 2600
Text GLabel 6900 2600 0    60   Input ~ 0
3v3
Text Label 6950 2500 0    60   ~ 0
moto-in2
Text Label 6950 2400 0    60   ~ 0
moto-out2
Text Label 6950 1900 0    60   ~ 0
moto-out1
Text Label 6950 1800 0    60   ~ 0
moto-in1
Text Label 6950 1700 0    60   ~ 0
moto-en1
Text Label 8800 2600 0    60   ~ 0
moto-en2
Text Label 8800 2500 0    60   ~ 0
moto-in3
Text Label 8800 2400 0    60   ~ 0
moto-out3
$Comp
L GND #PWR?
U 1 1 503BAC1F
P 9200 2250
F 0 "#PWR?" H 9200 2250 30  0001 C CNN
F 1 "GND" H 9200 2180 30  0001 C CNN
	1    9200 2250
	1    0    0    -1  
$EndComp
Text Label 8800 1900 0    60   ~ 0
moto-out4
Text Label 8800 1800 0    60   ~ 0
moto-in4
Text GLabel 8950 1450 1    60   Input ~ 0
boost-output
$Comp
L L293 U?
U 1 1 503BABB8
P 8150 2100
F 0 "U?" H 8150 2650 60  0000 C CNN
F 1 "L293" H 8150 1450 60  0000 C CNN
	1    8150 2100
	1    0    0    -1  
$EndComp
$Comp
L TST P?
U 1 1 503B9E65
P 3400 2100
F 0 "P?" H 3400 2400 40  0000 C CNN
F 1 "TST" H 3400 2350 30  0000 C CNN
	1    3400 2100
	0    -1   -1   0   
$EndComp
Text GLabel 3800 2100 2    60   Input ~ 0
boost-output
$Comp
L GND #PWR?
U 1 1 503B9E38
P 3600 2500
F 0 "#PWR?" H 3600 2500 30  0001 C CNN
F 1 "GND" H 3600 2430 30  0001 C CNN
	1    3600 2500
	1    0    0    -1  
$EndComp
$Comp
L TST P?
U 1 1 503B9E2C
P 3400 2300
F 0 "P?" H 3400 2600 40  0000 C CNN
F 1 "TST" H 3400 2550 30  0000 C CNN
	1    3400 2300
	0    -1   -1   0   
$EndComp
Text GLabel 3800 1900 2    60   Input ~ 0
boost-input
$Comp
L TST P?
U 1 1 503B9E1B
P 3400 1900
F 0 "P?" H 3400 2200 40  0000 C CNN
F 1 "TST" H 3400 2150 30  0000 C CNN
	1    3400 1900
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 503B9E00
P 3600 1300
F 0 "#PWR?" H 3600 1300 30  0001 C CNN
F 1 "GND" H 3600 1230 30  0001 C CNN
	1    3600 1300
	1    0    0    -1  
$EndComp
$Comp
L TST P?
U 1 1 503B9DF4
P 3400 1100
F 0 "P?" H 3400 1400 40  0000 C CNN
F 1 "TST" H 3400 1350 30  0000 C CNN
	1    3400 1100
	0    -1   -1   0   
$EndComp
Text GLabel 3800 900  2    60   Input ~ 0
solar
$Comp
L TST P?
U 1 1 503B9DDB
P 3400 900
F 0 "P?" H 3400 1200 40  0000 C CNN
F 1 "TST" H 3400 1150 30  0000 C CNN
	1    3400 900 
	0    -1   -1   0   
$EndComp
Text GLabel 1550 850  2    60   Input ~ 0
boost-input
$Comp
L R R?
U 1 1 503B90E8
P 1350 1450
F 0 "R?" V 1430 1450 50  0000 C CNN
F 1 "10k" V 1350 1450 50  0000 C CNN
	1    1350 1450
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 503B90E7
P 1350 2150
F 0 "R?" V 1430 2150 50  0000 C CNN
F 1 "10k" V 1350 2150 50  0000 C CNN
	1    1350 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 503B90E6
P 1350 3300
F 0 "#PWR?" H 1350 3300 30  0001 C CNN
F 1 "GND" H 1350 3230 30  0001 C CNN
	1    1350 3300
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 503B90E5
P 1350 2850
F 0 "R?" V 1430 2850 50  0000 C CNN
F 1 "10k" V 1350 2850 50  0000 C CNN
	1    1350 2850
	1    0    0    -1  
$EndComp
Text Label 1500 2500 0    60   ~ 0
solar-tst
Text GLabel 1150 850  0    60   Input ~ 0
solar
Text Label 1650 6800 0    60   ~ 0
battery-tst
$Comp
L R R?
U 1 1 503B904F
P 1500 7150
F 0 "R?" V 1580 7150 50  0000 C CNN
F 1 "10k" V 1500 7150 50  0000 C CNN
	1    1500 7150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 503B9039
P 1500 7600
F 0 "#PWR?" H 1500 7600 30  0001 C CNN
F 1 "GND" H 1500 7530 30  0001 C CNN
	1    1500 7600
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 503B9029
P 1500 6450
F 0 "R?" V 1580 6450 50  0000 C CNN
F 1 "10k" V 1500 6450 50  0000 C CNN
	1    1500 6450
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 503B9021
P 1500 5750
F 0 "R?" V 1580 5750 50  0000 C CNN
F 1 "10k" V 1500 5750 50  0000 C CNN
	1    1500 5750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 503B9016
P 2400 5300
F 0 "#PWR?" H 2400 5300 30  0001 C CNN
F 1 "GND" H 2400 5230 30  0001 C CNN
	1    2400 5300
	1    0    0    -1  
$EndComp
$Comp
L BATTERY BT?
U 1 1 503B8FEB
P 1950 5150
F 0 "BT?" H 1950 5350 50  0000 C CNN
F 1 "BATTERY" H 1950 4960 50  0000 C CNN
	1    1950 5150
	1    0    0    -1  
$EndComp
Text GLabel 1350 5150 0    60   Input ~ 0
boost-output
$EndSCHEMATC
