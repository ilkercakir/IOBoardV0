EESchema Schematic File Version 2
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
LIBS:kicad_custom_lib
LIBS:Actuator_Relay-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "noname.sch"
Date "28 jun 2020"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RELAY_J9906 K1
U 1 1 5E9D80ED
P 1600 1400
F 0 "K1" H 1600 1700 70  0000 C CNN
F 1 "RELAY_J9906" H 1600 1050 70  0000 C CNN
F 2 "~" H 1600 1550 60  0000 C CNN
F 3 "~" H 1600 1550 60  0000 C CNN
	1    1600 1400
	1    0    0    -1  
$EndComp
$Comp
L RJ45_2 J1
U 1 1 5E9D81A5
P 3800 1200
F 0 "J1" H 4000 1700 60  0000 C CNN
F 1 "RJ45_2" H 3650 1700 60  0000 C CNN
F 2 "~" H 3800 1200 60  0000 C CNN
F 3 "~" H 3800 1200 60  0000 C CNN
	1    3800 1200
	0    1    1    0   
$EndComp
$Comp
L RJ45_2 J2
U 1 1 5E9D81B6
P 3800 2200
F 0 "J2" H 4000 2700 60  0000 C CNN
F 1 "RJ45_2" H 3650 2700 60  0000 C CNN
F 2 "~" H 3800 2200 60  0000 C CNN
F 3 "~" H 3800 2200 60  0000 C CNN
	1    3800 2200
	0    1    1    0   
$EndComp
$Comp
L CONN_8X2 P2
U 1 1 5E9D8291
P 2800 1200
F 0 "P2" H 2800 1650 60  0000 C CNN
F 1 "CONN_8X2" V 2800 1200 50  0000 C CNN
F 2 "" H 2800 1200 60  0000 C CNN
F 3 "" H 2800 1200 60  0000 C CNN
	1    2800 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 850  2400 1650
Connection ~ 2400 950 
Connection ~ 2400 1050
Connection ~ 2400 1150
Connection ~ 2400 1250
Connection ~ 2400 1350
Connection ~ 2400 1450
Wire Wire Line
	3200 850  3350 850 
Wire Wire Line
	3200 950  3350 950 
Wire Wire Line
	3350 1050 3200 1050
Wire Wire Line
	3200 1150 3350 1150
Wire Wire Line
	3350 1250 3200 1250
Wire Wire Line
	3200 1350 3350 1350
Wire Wire Line
	3350 1450 3200 1450
Wire Wire Line
	3200 1550 3350 1550
$Comp
L VCC #PWR01
U 1 1 5E9D83AB
P 3100 1850
F 0 "#PWR01" H 3100 1950 30  0001 C CNN
F 1 "VCC" H 3100 1950 30  0000 C CNN
F 2 "" H 3100 1850 60  0000 C CNN
F 3 "" H 3100 1850 60  0000 C CNN
	1    3100 1850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5E9D83BA
P 3100 1950
F 0 "#PWR02" H 3100 1950 30  0001 C CNN
F 1 "GND" H 3100 1880 30  0001 C CNN
F 2 "" H 3100 1950 60  0000 C CNN
F 3 "" H 3100 1950 60  0000 C CNN
	1    3100 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  1850 3350 1850
Wire Wire Line
	3100 1950 3350 1950
$Comp
L 2N2222A Q2
U 1 1 5E9D83F9
P 1300 2250
F 0 "Q2" H 1300 2102 40  0000 R CNN
F 1 "2N2222A" H 1300 2400 40  0000 R CNN
F 2 "TO92" H 1200 2352 29  0000 C CNN
F 3 "" H 1300 2250 60  0000 C CNN
	1    1300 2250
	-1   0    0    -1  
$EndComp
$Comp
L BC557 Q1
U 1 1 5E9D8408
P 2400 2250
F 0 "Q1" H 2400 2101 40  0000 R CNN
F 1 "BC557" H 2400 2400 40  0000 R CNN
F 2 "TO92" H 2300 2352 29  0000 C CNN
F 3 "" H 2400 2250 60  0000 C CNN
	1    2400 2250
	-1   0    0    1   
$EndComp
$Comp
L C C1
U 1 1 5E9D8653
P 2100 2250
F 0 "C1" H 2100 2350 40  0000 L CNN
F 1 "10uF" H 2106 2165 40  0000 L CNN
F 2 "~" H 2138 2100 30  0000 C CNN
F 3 "~" H 2100 2250 60  0000 C CNN
	1    2100 2250
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5E9D8662
P 850 2250
F 0 "C2" H 850 2350 40  0000 L CNN
F 1 "100uF" H 856 2165 40  0000 L CNN
F 2 "~" H 888 2100 30  0000 C CNN
F 3 "~" H 850 2250 60  0000 C CNN
	1    850  2250
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5E9D867B
P 1650 2500
F 0 "R3" V 1730 2500 40  0000 C CNN
F 1 "680" V 1657 2501 40  0000 C CNN
F 2 "~" V 1580 2500 30  0000 C CNN
F 3 "~" H 1650 2500 30  0000 C CNN
	1    1650 2500
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5E9D868A
P 1850 2500
F 0 "R4" V 1930 2500 40  0000 C CNN
F 1 "2.2K" V 1857 2501 40  0000 C CNN
F 2 "~" V 1780 2500 30  0000 C CNN
F 3 "~" H 1850 2500 30  0000 C CNN
	1    1850 2500
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5E9D8699
P 2800 2100
F 0 "R1" V 2880 2100 40  0000 C CNN
F 1 "10K" V 2807 2101 40  0000 C CNN
F 2 "~" V 2730 2100 30  0000 C CNN
F 3 "~" H 2800 2100 30  0000 C CNN
	1    2800 2100
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5E9D86BC
P 2600 1900
F 0 "R2" V 2680 1900 40  0000 C CNN
F 1 "22K" V 2607 1901 40  0000 C CNN
F 2 "~" V 2530 1900 30  0000 C CNN
F 3 "~" H 2600 1900 30  0000 C CNN
	1    2600 1900
	1    0    0    -1  
$EndComp
Connection ~ 3100 1850
Wire Wire Line
	2800 2350 2800 2250
Wire Wire Line
	2800 2250 2600 2250
Wire Wire Line
	2400 1650 2600 1650
Connection ~ 2400 1550
Wire Wire Line
	2600 2250 2600 2150
Wire Wire Line
	2100 1650 2100 2050
Connection ~ 2800 1850
Wire Wire Line
	3100 1950 3100 2650
Wire Wire Line
	3100 2650 2100 2650
Wire Wire Line
	2100 2950 2100 2450
Wire Wire Line
	2300 2050 2300 1850
Connection ~ 2300 1850
Wire Wire Line
	2300 2450 2300 2550
Wire Wire Line
	2300 2550 1850 2550
Wire Wire Line
	1850 2550 1850 2750
Wire Wire Line
	1500 2250 1850 2250
Connection ~ 1650 2250
Wire Wire Line
	1650 2950 1650 2750
Wire Wire Line
	850  2950 2100 2950
Connection ~ 2100 2650
Wire Wire Line
	850  2950 850  2450
Connection ~ 1650 2950
Wire Wire Line
	850  1050 850  2050
Connection ~ 2100 1850
Wire Wire Line
	1200 2450 1200 2950
Connection ~ 1200 2950
Wire Wire Line
	1200 1850 1200 1600
Connection ~ 1200 1850
Wire Wire Line
	1200 1500 1050 1500
Wire Wire Line
	1050 1500 1050 2050
Wire Wire Line
	950  2050 1700 2050
$Comp
L R R5
U 1 1 5E9D8947
P 950 1300
F 0 "R5" V 1030 1300 40  0000 C CNN
F 1 "2.2K" V 957 1301 40  0000 C CNN
F 2 "~" V 880 1300 30  0000 C CNN
F 3 "~" H 950 1300 30  0000 C CNN
	1    950  1300
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 5E9D8956
P 950 1850
F 0 "D1" H 950 1950 50  0000 C CNN
F 1 "LED" H 950 1750 50  0000 C CNN
F 2 "~" H 950 1850 60  0000 C CNN
F 3 "~" H 950 1850 60  0000 C CNN
	1    950  1850
	0    1    1    0   
$EndComp
Wire Wire Line
	950  1650 950  1550
Wire Wire Line
	950  1050 850  1050
Connection ~ 850  1850
Connection ~ 1050 2050
$Comp
L KLEMENS_1 P1
U 1 1 5E9D8B3B
P 1300 850
F 0 "P1" V 1250 850 40  0000 C CNN
F 1 "KLEMENS_1" V 1350 850 40  0000 C CNN
F 2 "" H 1300 850 60  0000 C CNN
F 3 "" H 1300 850 60  0000 C CNN
	1    1300 850 
	-1   0    0    1   
$EndComp
Wire Wire Line
	1200 1300 1200 1100
Wire Wire Line
	1200 1100 1650 1100
Wire Wire Line
	1650 750  2200 750 
Wire Wire Line
	2200 750  2200 1400
Wire Wire Line
	2200 1400 2000 1400
Wire Wire Line
	1650 1100 1650 950 
$Comp
L DIODE D2
U 1 1 5EF8356A
P 1900 1650
F 0 "D2" H 1900 1750 40  0000 C CNN
F 1 "DIODE" H 1900 1550 40  0000 C CNN
F 2 "~" H 1900 1650 60  0000 C CNN
F 3 "~" H 1900 1650 60  0000 C CNN
	1    1900 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2050 1700 1650
Connection ~ 1200 2050
$EndSCHEMATC
