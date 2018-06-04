EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
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
LIBS:LED
LIBS:modules
LIBS:battery_management
LIBS:74xgxx
LIBS:ac-dc
LIBS:actel
LIBS:allegro
LIBS:Altera
LIBS:analog_devices
LIBS:bbd
LIBS:bosch
LIBS:brooktre
LIBS:cmos_ieee
LIBS:dc-dc
LIBS:diode
LIBS:elec-unifil
LIBS:ESD_Protection
LIBS:ftdi
LIBS:gennum
LIBS:graphic_symbols
LIBS:hc11
LIBS:infineon
LIBS:intersil
LIBS:ir
LIBS:Lattice
LIBS:leds
LIBS:LEM
LIBS:logic_programmable
LIBS:maxim
LIBS:mechanical
LIBS:microchip_dspic33dsc
LIBS:microchip_pic10mcu
LIBS:microchip_pic12mcu
LIBS:microchip_pic16mcu
LIBS:microchip_pic18mcu
LIBS:microchip_pic24mcu
LIBS:microchip_pic32mcu
LIBS:motor_drivers
LIBS:msp430
LIBS:nordicsemi
LIBS:nxp
LIBS:nxp_armmcu
LIBS:onsemi
LIBS:Oscillators
LIBS:Power_Management
LIBS:powerint
LIBS:pspice
LIBS:references
LIBS:rfcom
LIBS:RFSolutions
LIBS:sensors
LIBS:silabs
LIBS:stm8
LIBS:stm32
LIBS:supertex
LIBS:transf
LIBS:triac_thyristor
LIBS:ttl_ieee
LIBS:video
LIBS:wiznet
LIBS:Worldsemi
LIBS:Xicor
LIBS:zetex
LIBS:Zilog
LIBS:skoro_sensors
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L SK6812 D1
U 1 1 5B0161C6
P 1300 1200
F 0 "D1" H 1500 1425 50  0000 R BNN
F 1 "SK6812" H 1350 975 50  0000 L TNN
F 2 "LED_SMD:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 1350 900 50  0001 L TNN
F 3 "" H 1400 825 50  0001 L TNN
	1    1300 1200
	1    0    0    -1  
$EndComp
$Comp
L SK6812 D2
U 1 1 5B01625D
P 2200 1200
F 0 "D2" H 2400 1425 50  0000 R BNN
F 1 "SK6812" H 2250 975 50  0000 L TNN
F 2 "LED_SMD:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 2250 900 50  0001 L TNN
F 3 "" H 2300 825 50  0001 L TNN
	1    2200 1200
	1    0    0    -1  
$EndComp
$Comp
L SK6812 D3
U 1 1 5B016368
P 3100 1200
F 0 "D3" H 3300 1425 50  0000 R BNN
F 1 "SK6812" H 3150 975 50  0000 L TNN
F 2 "LED_SMD:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 3150 900 50  0001 L TNN
F 3 "" H 3200 825 50  0001 L TNN
	1    3100 1200
	1    0    0    -1  
$EndComp
$Comp
L SK6812 D4
U 1 1 5B0163C5
P 4000 1200
F 0 "D4" H 4200 1425 50  0000 R BNN
F 1 "SK6812" H 4050 975 50  0000 L TNN
F 2 "LED_SMD:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 4050 900 50  0001 L TNN
F 3 "" H 4100 825 50  0001 L TNN
	1    4000 1200
	1    0    0    -1  
$EndComp
$Comp
L SK6812 D5
U 1 1 5B0163F2
P 4950 1200
F 0 "D5" H 5150 1425 50  0000 R BNN
F 1 "SK6812" H 5000 975 50  0000 L TNN
F 2 "LED_SMD:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 5000 900 50  0001 L TNN
F 3 "" H 5050 825 50  0001 L TNN
	1    4950 1200
	1    0    0    -1  
$EndComp
Text GLabel 2200 800  1    60   Input ~ 0
VCC
$Comp
L GNDREF #PWR01
U 1 1 5B016875
P 1300 1500
F 0 "#PWR01" H 1300 1250 50  0001 C CNN
F 1 "GNDREF" H 1300 1350 50  0000 C CNN
F 2 "" H 1300 1500 50  0001 C CNN
F 3 "" H 1300 1500 50  0001 C CNN
	1    1300 1500
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR02
U 1 1 5B016893
P 2200 1500
F 0 "#PWR02" H 2200 1250 50  0001 C CNN
F 1 "GNDREF" H 2200 1350 50  0000 C CNN
F 2 "" H 2200 1500 50  0001 C CNN
F 3 "" H 2200 1500 50  0001 C CNN
	1    2200 1500
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR03
U 1 1 5B016988
P 3100 1500
F 0 "#PWR03" H 3100 1250 50  0001 C CNN
F 1 "GNDREF" H 3100 1350 50  0000 C CNN
F 2 "" H 3100 1500 50  0001 C CNN
F 3 "" H 3100 1500 50  0001 C CNN
	1    3100 1500
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR04
U 1 1 5B016A28
P 4000 1500
F 0 "#PWR04" H 4000 1250 50  0001 C CNN
F 1 "GNDREF" H 4000 1350 50  0000 C CNN
F 2 "" H 4000 1500 50  0001 C CNN
F 3 "" H 4000 1500 50  0001 C CNN
	1    4000 1500
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR05
U 1 1 5B016A4B
P 4950 1500
F 0 "#PWR05" H 4950 1250 50  0001 C CNN
F 1 "GNDREF" H 4950 1350 50  0000 C CNN
F 2 "" H 4950 1500 50  0001 C CNN
F 3 "" H 4950 1500 50  0001 C CNN
	1    4950 1500
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5B016C9E
P 1950 850
F 0 "C2" H 1975 950 50  0000 L CNN
F 1 "104" H 1975 750 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1988 700 50  0001 C CNN
F 3 "" H 1950 850 50  0001 C CNN
	1    1950 850 
	0    1    1    0   
$EndComp
$Comp
L GNDREF #PWR06
U 1 1 5B0170CF
P 1800 850
F 0 "#PWR06" H 1800 600 50  0001 C CNN
F 1 "GNDREF" H 1800 700 50  0000 C CNN
F 2 "" H 1800 850 50  0001 C CNN
F 3 "" H 1800 850 50  0001 C CNN
	1    1800 850 
	0    1    1    0   
$EndComp
Text GLabel 1300 800  1    60   Input ~ 0
VCC
$Comp
L C C1
U 1 1 5B0175A9
P 1050 850
F 0 "C1" H 1075 950 50  0000 L CNN
F 1 "104" H 1075 750 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1088 700 50  0001 C CNN
F 3 "" H 1050 850 50  0001 C CNN
	1    1050 850 
	0    1    1    0   
$EndComp
$Comp
L GNDREF #PWR07
U 1 1 5B0175AF
P 900 850
F 0 "#PWR07" H 900 600 50  0001 C CNN
F 1 "GNDREF" H 900 700 50  0000 C CNN
F 2 "" H 900 850 50  0001 C CNN
F 3 "" H 900 850 50  0001 C CNN
	1    900  850 
	0    1    1    0   
$EndComp
Text GLabel 3100 800  1    60   Input ~ 0
VCC
$Comp
L C C3
U 1 1 5B0179AD
P 2850 850
F 0 "C3" H 2875 950 50  0000 L CNN
F 1 "104" H 2875 750 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2888 700 50  0001 C CNN
F 3 "" H 2850 850 50  0001 C CNN
	1    2850 850 
	0    1    1    0   
$EndComp
$Comp
L GNDREF #PWR08
U 1 1 5B0179B3
P 2700 850
F 0 "#PWR08" H 2700 600 50  0001 C CNN
F 1 "GNDREF" H 2700 700 50  0000 C CNN
F 2 "" H 2700 850 50  0001 C CNN
F 3 "" H 2700 850 50  0001 C CNN
	1    2700 850 
	0    1    1    0   
$EndComp
Text GLabel 4000 800  1    60   Input ~ 0
VCC
$Comp
L C C4
U 1 1 5B017A8C
P 3750 850
F 0 "C4" H 3775 950 50  0000 L CNN
F 1 "104" H 3775 750 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3788 700 50  0001 C CNN
F 3 "" H 3750 850 50  0001 C CNN
	1    3750 850 
	0    1    1    0   
$EndComp
$Comp
L GNDREF #PWR09
U 1 1 5B017A92
P 3600 850
F 0 "#PWR09" H 3600 600 50  0001 C CNN
F 1 "GNDREF" H 3600 700 50  0000 C CNN
F 2 "" H 3600 850 50  0001 C CNN
F 3 "" H 3600 850 50  0001 C CNN
	1    3600 850 
	0    1    1    0   
$EndComp
Text GLabel 4950 800  1    60   Input ~ 0
VCC
$Comp
L C C5
U 1 1 5B017ADF
P 4700 850
F 0 "C5" H 4725 950 50  0000 L CNN
F 1 "104" H 4725 750 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 4738 700 50  0001 C CNN
F 3 "" H 4700 850 50  0001 C CNN
	1    4700 850 
	0    1    1    0   
$EndComp
$Comp
L GNDREF #PWR010
U 1 1 5B017AE5
P 4550 850
F 0 "#PWR010" H 4550 600 50  0001 C CNN
F 1 "GNDREF" H 4550 700 50  0000 C CNN
F 2 "" H 4550 850 50  0001 C CNN
F 3 "" H 4550 850 50  0001 C CNN
	1    4550 850 
	0    1    1    0   
$EndComp
Text GLabel 1000 1200 0    60   Input ~ 0
LEDS_IN
Text GLabel 5250 1200 2    60   Output ~ 0
LEDS_OUT
$Comp
L Arduino_Nano_v3.x A1
U 1 1 5B018CAF
P 9400 5050
F 0 "A1" H 9200 6075 50  0000 R CNN
F 1 "Arduino_Nano_v3.x" H 9200 6000 50  0000 R CNN
F 2 "Modules:Arduino_Nano" H 9550 4100 50  0001 L CNN
F 3 "" H 9400 4050 50  0001 C CNN
	1    9400 5050
	1    0    0    -1  
$EndComp
$Comp
L Buzzer BZ1
U 1 1 5B01D686
P 1000 6350
F 0 "BZ1" H 1150 6400 50  0000 L CNN
F 1 "Buzzer" H 1150 6300 50  0000 L CNN
F 2 "Buzzers_Beepers:MagneticBuzzer_ProSignal_ABT-410-RC" V 975 6450 50  0001 C CNN
F 3 "" V 975 6450 50  0001 C CNN
	1    1000 6350
	-1   0    0    1   
$EndComp
$Comp
L Buzzer BZ2
U 1 1 5B01DC35
P 1000 6800
F 0 "BZ2" H 1150 6850 50  0000 L CNN
F 1 "Buzzer" H 1150 6750 50  0000 L CNN
F 2 "Buzzers_Beepers:MagneticBuzzer_ProSignal_ABT-410-RC" V 975 6900 50  0001 C CNN
F 3 "" V 975 6900 50  0001 C CNN
	1    1000 6800
	-1   0    0    1   
$EndComp
$Comp
L GNDREF #PWR011
U 1 1 5B01DF4E
P 1250 6250
F 0 "#PWR011" H 1250 6000 50  0001 C CNN
F 1 "GNDREF" H 1250 6100 50  0000 C CNN
F 2 "" H 1250 6250 50  0001 C CNN
F 3 "" H 1250 6250 50  0001 C CNN
	1    1250 6250
	0    -1   -1   0   
$EndComp
$Comp
L GNDREF #PWR012
U 1 1 5B01DFBD
P 1250 6700
F 0 "#PWR012" H 1250 6450 50  0001 C CNN
F 1 "GNDREF" H 1250 6550 50  0000 C CNN
F 2 "" H 1250 6700 50  0001 C CNN
F 3 "" H 1250 6700 50  0001 C CNN
	1    1250 6700
	0    -1   -1   0   
$EndComp
Text GLabel 1250 6450 2    60   Input ~ 0
BUZZ1
Text GLabel 1250 6900 2    60   Input ~ 0
BUZZ2
Text GLabel 8600 5000 0    60   Output ~ 0
BUZZ1
Text GLabel 8600 5400 0    60   Output ~ 0
BUZZ2
Text GLabel 9600 3900 1    60   Input ~ 0
VCC
Wire Wire Line
	4300 1200 4650 1200
Wire Wire Line
	3400 1200 3700 1200
Wire Wire Line
	2500 1200 2800 1200
Wire Wire Line
	1600 1200 1900 1200
Wire Wire Line
	2100 850  2200 850 
Wire Wire Line
	2200 800  2200 900 
Connection ~ 2200 850 
Wire Wire Line
	1200 850  1300 850 
Wire Wire Line
	1300 800  1300 900 
Connection ~ 1300 850 
Wire Wire Line
	3000 850  3100 850 
Wire Wire Line
	3100 800  3100 900 
Connection ~ 3100 850 
Wire Wire Line
	3900 850  4000 850 
Wire Wire Line
	4000 800  4000 900 
Connection ~ 4000 850 
Wire Wire Line
	4850 850  4950 850 
Wire Wire Line
	4950 800  4950 900 
Connection ~ 4950 850 
Wire Wire Line
	9450 6150 9450 6050
Wire Wire Line
	9400 6050 9500 6050
Connection ~ 9450 6050
Wire Wire Line
	1250 6450 1100 6450
Wire Wire Line
	1100 6250 1250 6250
Wire Wire Line
	1250 6700 1100 6700
Wire Wire Line
	1100 6900 1250 6900
Wire Wire Line
	9600 3900 9600 4050
$Comp
L NRF24L01_Breakout U1
U 1 1 5B024791
P 6350 6800
F 0 "U1" H 6000 7300 50  0000 L CNN
F 1 "NRF24L01" H 6500 7300 50  0000 L CNN
F 2 "RF_Modules:nRF24L01_Breakout" H 6500 7400 50  0001 L CIN
F 3 "" H 6350 6700 50  0000 C CNN
	1    6350 6800
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR013
U 1 1 5B024896
P 6350 7400
F 0 "#PWR013" H 6350 7150 50  0001 C CNN
F 1 "GNDREF" H 6350 7250 50  0000 C CNN
F 2 "" H 6350 7400 50  0001 C CNN
F 3 "" H 6350 7400 50  0001 C CNN
	1    6350 7400
	1    0    0    -1  
$EndComp
Text GLabel 6350 6200 1    60   Input ~ 0
3V3
$Comp
L RF_Receiver_433_MHz RF1
U 1 1 5B0249F1
P 2950 6600
F 0 "RF1" H 2950 7250 60  0000 C CNN
F 1 "433MHz Receiver" H 2950 7150 60  0000 C CNN
F 2 "Sensors:RF_Receiver_433_MHz" H 3050 6600 60  0001 C CNN
F 3 "" H 3050 6600 60  0000 C CNN
	1    2950 6600
	-1   0    0    1   
$EndComp
$Comp
L RF_Transmitter_433_MHz RF2
U 1 1 5B024A40
P 4000 6450
F 0 "RF2" H 4000 7250 60  0000 C CNN
F 1 "433MHz Transmitter" H 4000 7150 60  0000 C CNN
F 2 "Sensors:RF_Transmitter_433_MHz" H 4000 6450 60  0001 C CNN
F 3 "" H 4000 6450 60  0000 C CNN
	1    4000 6450
	-1   0    0    1   
$EndComp
Text Notes 7650 1300 0    60   ~ 0
TODO:\n\n- Determine amount of tactile switches and place them (6x6x4.3mm)\n- Add bulk capacitor (10-100uF) over battery terminals
$Comp
L TSOP323xx U2
U 1 1 5B14681B
P 1000 2850
F 0 "U2" H 600 3150 50  0000 L CNN
F 1 "CHQ1838" H 600 2550 50  0000 L CNN
F 2 "Opto-Devices:IRReceiver_Vishay_MOLD-3pin" H 950 2475 50  0001 C CNN
F 3 "" H 1650 3150 50  0001 C CNN
	1    1000 2850
	1    0    0    -1  
$EndComp
$Comp
L LD271 D6
U 1 1 5B14689E
P 1100 3600
F 0 "D6" H 1120 3670 50  0000 L CNN
F 1 "940nm" H 1060 3490 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 1100 3775 50  0001 C CNN
F 3 "" H 1050 3600 50  0001 C CNN
	1    1100 3600
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5B14695C
P 1800 2700
F 0 "R1" V 1880 2700 50  0000 C CNN
F 1 "10k" V 1800 2700 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1730 2700 50  0001 C CNN
F 3 "" H 1800 2700 50  0001 C CNN
	1    1800 2700
	-1   0    0    1   
$EndComp
Text GLabel 1600 2650 1    60   Input ~ 0
VCC
Wire Wire Line
	1400 2650 1700 2650
Wire Wire Line
	1800 2550 1700 2550
Wire Wire Line
	1700 2550 1700 2650
Connection ~ 1600 2650
Wire Wire Line
	1400 2850 2000 2850
Text GLabel 2000 2850 2    60   Output ~ 0
IR_RECV
Connection ~ 1800 2850
$Comp
L GNDREF #PWR014
U 1 1 5B147254
P 1600 3050
F 0 "#PWR014" H 1600 2800 50  0001 C CNN
F 1 "GNDREF" H 1600 2900 50  0000 C CNN
F 2 "" H 1600 3050 50  0001 C CNN
F 3 "" H 1600 3050 50  0001 C CNN
	1    1600 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 3050 1400 3050
Text GLabel 1400 3600 2    60   Input ~ 0
IR_SEND
Wire Wire Line
	1400 3600 1200 3600
$Comp
L GNDREF #PWR015
U 1 1 5B147766
P 700 3600
F 0 "#PWR015" H 700 3350 50  0001 C CNN
F 1 "GNDREF" H 700 3450 50  0000 C CNN
F 2 "" H 700 3600 50  0001 C CNN
F 3 "" H 700 3600 50  0001 C CNN
	1    700  3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  3600 900  3600
Text GLabel 8600 5150 0    60   Input ~ 0
IR_RECV
Text GLabel 8600 4750 0    60   Output ~ 0
IR_SEND
Wire Wire Line
	8900 4750 8600 4750
Wire Wire Line
	8900 5150 8600 5150
$Comp
L GNDREF #PWR016
U 1 1 5B148ADE
P 2750 6450
F 0 "#PWR016" H 2750 6200 50  0001 C CNN
F 1 "GNDREF" H 2750 6300 50  0000 C CNN
F 2 "" H 2750 6450 50  0001 C CNN
F 3 "" H 2750 6450 50  0001 C CNN
	1    2750 6450
	0    1    1    0   
$EndComp
$Comp
L GNDREF #PWR017
U 1 1 5B148B31
P 3900 6300
F 0 "#PWR017" H 3900 6050 50  0001 C CNN
F 1 "GNDREF" H 3900 6150 50  0000 C CNN
F 2 "" H 3900 6300 50  0001 C CNN
F 3 "" H 3900 6300 50  0001 C CNN
	1    3900 6300
	0    1    1    0   
$EndComp
Wire Wire Line
	3900 6300 3900 6450
Wire Wire Line
	2750 6450 2750 6600
Text GLabel 3050 6450 2    60   Input ~ 0
VCC
Wire Wire Line
	3050 6450 3050 6600
Text GLabel 4000 6300 1    60   Input ~ 0
VCC
Text GLabel 2850 6300 1    60   Output ~ 0
RF_RECV
Wire Wire Line
	2950 6600 2850 6600
Wire Wire Line
	2850 6600 2850 6300
Text GLabel 4200 6300 2    60   Input ~ 0
RF_SEND
Wire Wire Line
	8900 4950 8650 4950
Wire Wire Line
	8650 5050 8900 5050
Text GLabel 8600 4650 0    60   Input ~ 0
RF_RECV
Wire Wire Line
	8600 4650 8900 4650
Text GLabel 8600 5250 0    60   Input ~ 0
RF_SEND
Wire Wire Line
	8600 5250 8900 5250
Wire Wire Line
	4000 6300 4000 6450
Wire Wire Line
	4200 6300 4100 6300
Wire Wire Line
	4100 6300 4100 6450
Text GLabel 8600 4850 0    60   Output ~ 0
LEDS_IN
Wire Wire Line
	8600 4850 8900 4850
Text GLabel 10150 5150 2    60   BiDi ~ 0
NRF_CE
Text GLabel 10150 5050 2    60   BiDi ~ 0
SPI_SS
Text GLabel 8600 5550 0    60   BiDi ~ 0
SPI_MOSI
Text GLabel 8600 5650 0    60   BiDi ~ 0
SPI_MISO
Text GLabel 8600 5750 0    60   BiDi ~ 0
SPI_SCK
Wire Wire Line
	8600 5550 8900 5550
Wire Wire Line
	8600 5650 8900 5650
Wire Wire Line
	8900 5750 8600 5750
NoConn ~ 5850 7100
Text GLabel 5750 6500 0    60   BiDi ~ 0
SPI_MOSI
Text GLabel 5750 6600 0    60   BiDi ~ 0
SPI_MISO
Text GLabel 5750 6700 0    60   BiDi ~ 0
SPI_SCK
Text GLabel 5750 6800 0    60   BiDi ~ 0
SPI_SS
Text GLabel 5750 7000 0    60   BiDi ~ 0
NRF_CE
Wire Wire Line
	5750 7000 5850 7000
Wire Wire Line
	5850 6800 5750 6800
Wire Wire Line
	5750 6700 5850 6700
Wire Wire Line
	5850 6600 5750 6600
Wire Wire Line
	5750 6500 5850 6500
Text GLabel 9500 3900 1    60   Input ~ 0
3V3
Wire Wire Line
	9500 4050 9500 3900
Wire Wire Line
	8650 4950 8650 5050
Wire Wire Line
	8650 5000 8600 5000
Connection ~ 8650 5000
Wire Wire Line
	8650 5350 8900 5350
Text GLabel 9300 3900 1    60   Input ~ 0
VIN
Wire Wire Line
	9300 3900 9300 4050
Wire Wire Line
	8650 5450 8900 5450
Wire Wire Line
	8650 5350 8650 5450
Wire Wire Line
	8650 5400 8600 5400
Connection ~ 8650 5400
$Comp
L Battery BT1
U 1 1 5B1573BE
P 10700 3800
F 0 "BT1" H 10800 3900 50  0000 L CNN
F 1 "Battery" H 10800 3800 50  0000 L CNN
F 2 "Battery_Holders:Keystone_2479_3xAAA" V 10700 3860 50  0001 C CNN
F 3 "" V 10700 3860 50  0001 C CNN
	1    10700 3800
	1    0    0    -1  
$EndComp
Text GLabel 10550 3550 1    60   Input ~ 0
VCC
$Comp
L GNDREF #PWR018
U 1 1 5B157699
P 10850 4000
F 0 "#PWR018" H 10850 3750 50  0001 C CNN
F 1 "GNDREF" H 10850 3850 50  0000 C CNN
F 2 "" H 10850 4000 50  0001 C CNN
F 3 "" H 10850 4000 50  0001 C CNN
	1    10850 4000
	1    0    0    -1  
$EndComp
$Comp
L Conn_02x15_Odd_Even J1
U 1 1 5B158708
P 6200 3300
F 0 "J1" H 6250 4100 50  0000 C CNN
F 1 "Dev breakout" H 6250 2500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x15_Pitch2.54mm" H 6200 3300 50  0001 C CNN
F 3 "" H 6200 3300 50  0001 C CNN
	1    6200 3300
	1    0    0    -1  
$EndComp
Text GLabel 8900 4450 0    60   BiDi ~ 0
RX
Text GLabel 8900 4550 0    60   BiDi ~ 0
TX
Text GLabel 8900 4650 0    60   BiDi ~ 0
D2
Text GLabel 8900 4750 0    60   BiDi ~ 0
D3
Text GLabel 8900 4850 0    60   BiDi ~ 0
D4
Text GLabel 8900 4950 0    60   BiDi ~ 0
D5
Text GLabel 8900 5050 0    60   BiDi ~ 0
D6
Text GLabel 8900 5150 0    60   BiDi ~ 0
D7
Text GLabel 8900 5250 0    60   BiDi ~ 0
D8
Text GLabel 8900 5350 0    60   BiDi ~ 0
D9
Text GLabel 8900 5450 0    60   BiDi ~ 0
D10
Text GLabel 8900 5550 0    60   BiDi ~ 0
D11
Text GLabel 8900 5650 0    60   BiDi ~ 0
D12
Text GLabel 8900 5750 0    60   BiDi ~ 0
D13
Text GLabel 6500 3000 2    60   BiDi ~ 0
A7
Text GLabel 6500 3100 2    60   BiDi ~ 0
A6
Text GLabel 6500 3200 2    60   BiDi ~ 0
A5
Text GLabel 6500 3300 2    60   BiDi ~ 0
A4
Text GLabel 6500 3500 2    60   BiDi ~ 0
A2
Text GLabel 6500 3600 2    60   BiDi ~ 0
A1
Text GLabel 6500 3700 2    60   BiDi ~ 0
A0
Text GLabel 9900 4850 2    60   BiDi ~ 0
AREF
Text GLabel 9950 4500 2    60   BiDi ~ 0
RESET
Wire Wire Line
	9950 4500 9900 4500
Wire Wire Line
	9900 4450 9900 4550
Connection ~ 9900 4500
Text GLabel 6000 2700 0    60   BiDi ~ 0
RX
Text GLabel 6000 2600 0    60   BiDi ~ 0
TX
Text GLabel 6000 3000 0    60   BiDi ~ 0
D2
Text GLabel 6000 3100 0    60   BiDi ~ 0
D3
Text GLabel 6000 3200 0    60   BiDi ~ 0
D4
Text GLabel 6000 3300 0    60   BiDi ~ 0
D5
Text GLabel 6000 3400 0    60   BiDi ~ 0
D6
Text GLabel 6000 3500 0    60   BiDi ~ 0
D7
Text GLabel 6000 3600 0    60   BiDi ~ 0
D8
Text GLabel 6000 3700 0    60   BiDi ~ 0
D9
Text GLabel 6000 3800 0    60   BiDi ~ 0
D10
Text GLabel 6000 3900 0    60   BiDi ~ 0
D11
Text GLabel 6000 4000 0    60   BiDi ~ 0
D12
Text GLabel 6500 4000 2    60   BiDi ~ 0
D13
Text GLabel 6000 2800 0    60   BiDi ~ 0
RESET
Text GLabel 6500 3900 2    60   Input ~ 0
3V3
Text GLabel 6500 3800 2    60   BiDi ~ 0
AREF
Text GLabel 6500 3400 2    60   BiDi ~ 0
A3
Text GLabel 6500 2900 2    60   Input ~ 0
VCC
Text GLabel 6500 2800 2    60   BiDi ~ 0
RESET
Text GLabel 9450 6150 3    60   Input ~ 0
GND
$Comp
L VCC #PWR019
U 1 1 5B15CD53
P 10850 3550
F 0 "#PWR019" H 10850 3400 50  0001 C CNN
F 1 "VCC" H 10850 3700 50  0000 C CNN
F 2 "" H 10850 3550 50  0001 C CNN
F 3 "" H 10850 3550 50  0001 C CNN
	1    10850 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10700 3600 10700 3550
Wire Wire Line
	10550 3550 10850 3550
Connection ~ 10700 3550
Text GLabel 10550 4000 3    60   Input ~ 0
GND
Wire Wire Line
	10550 4000 10850 4000
Connection ~ 10700 4000
Text GLabel 9900 5750 2    60   BiDi ~ 0
A7
Text GLabel 9900 5650 2    60   BiDi ~ 0
A6
Text GLabel 9900 5550 2    60   BiDi ~ 0
A5
Text GLabel 9900 5450 2    60   BiDi ~ 0
A4
Text GLabel 9900 5250 2    60   BiDi ~ 0
A2
Text GLabel 9900 5150 2    60   BiDi ~ 0
A1
Text GLabel 9900 5050 2    60   BiDi ~ 0
A0
Text GLabel 9900 5350 2    60   BiDi ~ 0
A3
Wire Wire Line
	10150 5050 9900 5050
Wire Wire Line
	10150 5150 9900 5150
Text GLabel 6000 2900 0    60   Input ~ 0
GND
Text GLabel 6500 2700 2    60   Input ~ 0
GND
Text GLabel 6500 2600 2    60   Input ~ 0
VIN
$EndSCHEMATC
