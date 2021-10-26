EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ArduSyth - Kiin Synthesizer PCB"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Switch:SW_Push SW1
U 1 1 5FFC80AA
P 5650 2850
F 0 "SW1" H 5650 3135 50  0000 C CNN
F 1 "SW_Push" H 5650 3044 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH-12mm_Wuerth-430476085716" H 5650 3050 50  0001 C CNN
F 3 "~" H 5650 3050 50  0001 C CNN
	1    5650 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5FFC80B0
P 5550 3650
F 0 "C1" H 5435 3696 50  0000 R CNN
F 1 "4.7n" H 5435 3605 50  0000 R CNN
F 2 "Capacitors_THT:C_Rect_L4.6mm_W2.0mm_P2.50mm_MKS02_FKP02" H 5588 3500 50  0001 C CNN
F 3 "~" H 5550 3650 50  0001 C CNN
	1    5550 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5FFC80B6
P 6750 4450
F 0 "#PWR0101" H 6750 4200 50  0001 C CNN
F 1 "GND" H 6755 4277 50  0000 C CNN
F 2 "" H 6750 4450 50  0001 C CNN
F 3 "" H 6750 4450 50  0001 C CNN
	1    6750 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5FFC80BC
P 6650 4450
F 0 "#PWR0102" H 6650 4200 50  0001 C CNN
F 1 "GND" H 6655 4277 50  0000 C CNN
F 2 "" H 6650 4450 50  0001 C CNN
F 3 "" H 6650 4450 50  0001 C CNN
	1    6650 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5FFC80C8
P 9650 950
F 0 "#PWR0104" H 9650 800 50  0001 C CNN
F 1 "+5V" H 9665 1123 50  0000 C CNN
F 2 "" H 9650 950 50  0001 C CNN
F 3 "" H 9650 950 50  0001 C CNN
	1    9650 950 
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_US RV3
U 1 1 5FFC80E0
P 10250 2400
F 0 "RV3" H 10182 2354 50  0000 R CNN
F 1 "100K" H 10182 2445 50  0000 R CNN
F 2 "test:Potentiometer_Alps_RK09K_Single_Vertical_modified" H 10250 2400 50  0001 C CNN
F 3 "~" H 10250 2400 50  0001 C CNN
	1    10250 2400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5FFC80E6
P 10250 2550
F 0 "#PWR0107" H 10250 2300 50  0001 C CNN
F 1 "GND" H 10255 2377 50  0000 C CNN
F 2 "" H 10250 2550 50  0001 C CNN
F 3 "" H 10250 2550 50  0001 C CNN
	1    10250 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 5FFC80EC
P 10250 2250
F 0 "#PWR0108" H 10250 2100 50  0001 C CNN
F 1 "+5V" H 10265 2423 50  0000 C CNN
F 2 "" H 10250 2250 50  0001 C CNN
F 3 "" H 10250 2250 50  0001 C CNN
	1    10250 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_US RV4
U 1 1 5FFC80F2
P 10500 3050
F 0 "RV4" H 10432 3004 50  0000 R CNN
F 1 "100K" H 10432 3095 50  0000 R CNN
F 2 "test:Potentiometer_Alps_RK09K_Single_Vertical_modified" H 10500 3050 50  0001 C CNN
F 3 "~" H 10500 3050 50  0001 C CNN
	1    10500 3050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5FFC80F8
P 10500 3200
F 0 "#PWR0109" H 10500 2950 50  0001 C CNN
F 1 "GND" H 10505 3027 50  0000 C CNN
F 2 "" H 10500 3200 50  0001 C CNN
F 3 "" H 10500 3200 50  0001 C CNN
	1    10500 3200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0110
U 1 1 5FFC80FE
P 10500 2900
F 0 "#PWR0110" H 10500 2750 50  0001 C CNN
F 1 "+5V" H 10515 3073 50  0000 C CNN
F 2 "" H 10500 2900 50  0001 C CNN
F 3 "" H 10500 2900 50  0001 C CNN
	1    10500 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_US RV5
U 1 1 5FFC8104
P 10500 3900
F 0 "RV5" H 10432 3854 50  0000 R CNN
F 1 "100K" H 10432 3945 50  0000 R CNN
F 2 "test:Potentiometer_Alps_RK09K_Single_Vertical_modified" H 10500 3900 50  0001 C CNN
F 3 "~" H 10500 3900 50  0001 C CNN
	1    10500 3900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5FFC810A
P 10500 4050
F 0 "#PWR0111" H 10500 3800 50  0001 C CNN
F 1 "GND" H 10505 3877 50  0000 C CNN
F 2 "" H 10500 4050 50  0001 C CNN
F 3 "" H 10500 4050 50  0001 C CNN
	1    10500 4050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0112
U 1 1 5FFC8110
P 10500 3750
F 0 "#PWR0112" H 10500 3600 50  0001 C CNN
F 1 "+5V" H 10515 3923 50  0000 C CNN
F 2 "" H 10500 3750 50  0001 C CNN
F 3 "" H 10500 3750 50  0001 C CNN
	1    10500 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5FFC811C
P 10150 4700
F 0 "#PWR0113" H 10150 4450 50  0001 C CNN
F 1 "GND" H 10155 4527 50  0000 C CNN
F 2 "" H 10150 4700 50  0001 C CNN
F 3 "" H 10150 4700 50  0001 C CNN
	1    10150 4700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0114
U 1 1 5FFC8122
P 10150 4400
F 0 "#PWR0114" H 10150 4250 50  0001 C CNN
F 1 "+5V" H 10165 4573 50  0000 C CNN
F 2 "" H 10150 4400 50  0001 C CNN
F 3 "" H 10150 4400 50  0001 C CNN
	1    10150 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_US RV7
U 1 1 5FFC8128
P 9850 5150
F 0 "RV7" H 9782 5104 50  0000 R CNN
F 1 "100K" H 9782 5195 50  0000 R CNN
F 2 "test:Potentiometer_Alps_RK09K_Single_Vertical_modified" H 9850 5150 50  0001 C CNN
F 3 "~" H 9850 5150 50  0001 C CNN
	1    9850 5150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5FFC812E
P 9850 5300
F 0 "#PWR0115" H 9850 5050 50  0001 C CNN
F 1 "GND" H 9855 5127 50  0000 C CNN
F 2 "" H 9850 5300 50  0001 C CNN
F 3 "" H 9850 5300 50  0001 C CNN
	1    9850 5300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0116
U 1 1 5FFC8134
P 9850 5000
F 0 "#PWR0116" H 9850 4850 50  0001 C CNN
F 1 "+5V" H 9865 5173 50  0000 C CNN
F 2 "" H 9850 5000 50  0001 C CNN
F 3 "" H 9850 5000 50  0001 C CNN
	1    9850 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_US RV8
U 1 1 5FFC813A
P 9550 5800
F 0 "RV8" H 9482 5754 50  0000 R CNN
F 1 "100K" H 9482 5845 50  0000 R CNN
F 2 "test:Potentiometer_Alps_RK09K_Single_Vertical_modified" H 9550 5800 50  0001 C CNN
F 3 "~" H 9550 5800 50  0001 C CNN
	1    9550 5800
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 5FFC8140
P 9550 5950
F 0 "#PWR0117" H 9550 5700 50  0001 C CNN
F 1 "GND" H 9555 5777 50  0000 C CNN
F 2 "" H 9550 5950 50  0001 C CNN
F 3 "" H 9550 5950 50  0001 C CNN
	1    9550 5950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0118
U 1 1 5FFC8146
P 9550 5650
F 0 "#PWR0118" H 9550 5500 50  0001 C CNN
F 1 "+5V" H 9565 5823 50  0000 C CNN
F 2 "" H 9550 5650 50  0001 C CNN
F 3 "" H 9550 5650 50  0001 C CNN
	1    9550 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 3450 7150 3450
Wire Wire Line
	8100 3650 7150 3650
Wire Wire Line
	7900 3750 7150 3750
Wire Wire Line
	7950 3050 7550 3050
Wire Wire Line
	7550 3050 7550 3350
Wire Wire Line
	7550 3350 7150 3350
Wire Wire Line
	7150 3250 7500 3250
Wire Wire Line
	7500 3250 7500 3000
Wire Wire Line
	7500 3000 7750 3000
Wire Wire Line
	7500 2950 7450 2950
Wire Wire Line
	7450 2950 7450 3150
Wire Wire Line
	7450 3150 7150 3150
$Comp
L power:+5V #PWR0119
U 1 1 5FFC816F
P 6850 2150
F 0 "#PWR0119" H 6850 2000 50  0001 C CNN
F 1 "+5V" H 6865 2323 50  0000 C CNN
F 2 "" H 6850 2150 50  0001 C CNN
F 3 "" H 6850 2150 50  0001 C CNN
	1    6850 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 5FFC817C
P 5450 2850
F 0 "#PWR0120" H 5450 2600 50  0001 C CNN
F 1 "GND" V 5455 2722 50  0000 R CNN
F 2 "" H 5450 2850 50  0001 C CNN
F 3 "" H 5450 2850 50  0001 C CNN
	1    5450 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 2850 6150 2850
Wire Wire Line
	6750 4150 6750 4450
Wire Wire Line
	6650 4150 6650 4450
$Comp
L Device:R_US R4
U 1 1 5FFC8189
P 6000 3450
F 0 "R4" V 6205 3450 50  0000 C CNN
F 1 "3.9K" V 6114 3450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 6040 3440 50  0001 C CNN
F 3 "~" H 6000 3450 50  0001 C CNN
	1    6000 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5850 3450 5850 3500
$Comp
L power:GND #PWR0121
U 1 1 5FFC8196
P 5550 3800
F 0 "#PWR0121" H 5550 3550 50  0001 C CNN
F 1 "GND" H 5555 3627 50  0000 C CNN
F 2 "" H 5550 3800 50  0001 C CNN
F 3 "" H 5550 3800 50  0001 C CNN
	1    5550 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 3500 5850 3500
Connection ~ 5850 3500
Wire Wire Line
	5850 3500 5850 3550
Wire Wire Line
	4750 3500 5550 3500
Connection ~ 5550 3500
$Comp
L power:GND #PWR0122
U 1 1 60038F0E
P 6500 6400
F 0 "#PWR0122" H 6500 6150 50  0001 C CNN
F 1 "GND" H 6505 6227 50  0000 C CNN
F 2 "" H 6500 6400 50  0001 C CNN
F 3 "" H 6500 6400 50  0001 C CNN
	1    6500 6400
	1    0    0    -1  
$EndComp
$Comp
L arduSynth-rescue:AudioJack3_Ground-Connector-arduSynth-rescue J1
U 1 1 60D5B9AA
P 6500 5900
F 0 "J1" H 6220 5868 50  0000 R CNN
F 1 "AudioJack3_Ground" H 6220 5777 50  0000 R CNN
F 2 "test:FC68125" H 6500 5900 50  0001 C CNN
F 3 "~" H 6500 5900 50  0001 C CNN
	1    6500 5900
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_POT_US RV9
U 1 1 60FCC65B
P 5200 5900
F 0 "RV9" H 5132 5854 50  0000 R CNN
F 1 "100K" H 5132 5945 50  0000 R CNN
F 2 "test:Potentiometer_Alps_RK09K_Single_Vertical_modified" H 5200 5900 50  0001 C CNN
F 3 "~" H 5200 5900 50  0001 C CNN
	1    5200 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 60FD4AA6
P 5200 6150
F 0 "#PWR0123" H 5200 5900 50  0001 C CNN
F 1 "GND" H 5205 5977 50  0000 C CNN
F 2 "" H 5200 6150 50  0001 C CNN
F 3 "" H 5200 6150 50  0001 C CNN
	1    5200 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 3500 4750 5750
Wire Wire Line
	4750 5750 5200 5750
Wire Wire Line
	5200 6050 5200 6150
$Comp
L Switch:SW_Push SW2
U 1 1 60FDB48B
P 4650 2950
F 0 "SW2" H 4650 3235 50  0000 C CNN
F 1 "SW_Push" H 4650 3144 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH-12mm_Wuerth-430476085716" H 4650 3150 50  0001 C CNN
F 3 "~" H 4650 3150 50  0001 C CNN
	1    4650 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0124
U 1 1 60FDB492
P 4450 2950
F 0 "#PWR0124" H 4450 2700 50  0001 C CNN
F 1 "GND" V 4455 2822 50  0000 R CNN
F 2 "" H 4450 2950 50  0001 C CNN
F 3 "" H 4450 2950 50  0001 C CNN
	1    4450 2950
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 60FDD955
P 3900 3050
F 0 "SW3" H 3900 3335 50  0000 C CNN
F 1 "SW_Push" H 3900 3244 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH-12mm_Wuerth-430476085716" H 3900 3250 50  0001 C CNN
F 3 "~" H 3900 3250 50  0001 C CNN
	1    3900 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0125
U 1 1 60FDD95C
P 3700 3050
F 0 "#PWR0125" H 3700 2800 50  0001 C CNN
F 1 "GND" V 3705 2922 50  0000 R CNN
F 2 "" H 3700 3050 50  0001 C CNN
F 3 "" H 3700 3050 50  0001 C CNN
	1    3700 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 2950 6150 2950
Wire Wire Line
	4100 3050 6150 3050
$Comp
L Device:LED D1
U 1 1 60FE0148
P 3550 3450
F 0 "D1" H 3541 3666 50  0000 C CNN
F 1 "LED" H 3541 3575 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 3550 3450 50  0001 C CNN
F 3 "~" H 3550 3450 50  0001 C CNN
	1    3550 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 60FE0C24
P 3950 3450
F 0 "R1" V 4155 3450 50  0000 C CNN
F 1 "470" V 4064 3450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 3990 3440 50  0001 C CNN
F 3 "~" H 3950 3450 50  0001 C CNN
	1    3950 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3700 3450 3800 3450
Wire Wire Line
	4100 3450 4250 3450
Wire Wire Line
	4250 3450 4250 3150
Wire Wire Line
	4250 3150 6150 3150
$Comp
L power:GND #PWR0126
U 1 1 60FE2E8E
P 3000 3450
F 0 "#PWR0126" H 3000 3200 50  0001 C CNN
F 1 "GND" H 3005 3277 50  0000 C CNN
F 2 "" H 3000 3450 50  0001 C CNN
F 3 "" H 3000 3450 50  0001 C CNN
	1    3000 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 3450 3400 3450
$Comp
L Device:LED D2
U 1 1 60FE54EA
P 3550 3850
F 0 "D2" H 3541 4066 50  0000 C CNN
F 1 "LED" H 3541 3975 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 3550 3850 50  0001 C CNN
F 3 "~" H 3550 3850 50  0001 C CNN
	1    3550 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 60FE54F1
P 3950 3850
F 0 "R2" V 4155 3850 50  0000 C CNN
F 1 "470" V 4064 3850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 3990 3840 50  0001 C CNN
F 3 "~" H 3950 3850 50  0001 C CNN
	1    3950 3850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3700 3850 3800 3850
$Comp
L power:GND #PWR0127
U 1 1 60FE54FA
P 3000 3850
F 0 "#PWR0127" H 3000 3600 50  0001 C CNN
F 1 "GND" H 3005 3677 50  0000 C CNN
F 2 "" H 3000 3850 50  0001 C CNN
F 3 "" H 3000 3850 50  0001 C CNN
	1    3000 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 3850 3400 3850
$Comp
L Device:LED D3
U 1 1 60FE6397
P 3550 4350
F 0 "D3" H 3541 4566 50  0000 C CNN
F 1 "LED" H 3541 4475 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 3550 4350 50  0001 C CNN
F 3 "~" H 3550 4350 50  0001 C CNN
	1    3550 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R3
U 1 1 60FE639E
P 3950 4350
F 0 "R3" V 4155 4350 50  0000 C CNN
F 1 "470" V 4064 4350 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 3990 4340 50  0001 C CNN
F 3 "~" H 3950 4350 50  0001 C CNN
	1    3950 4350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3700 4350 3800 4350
$Comp
L power:GND #PWR0128
U 1 1 60FE63A7
P 3000 4350
F 0 "#PWR0128" H 3000 4100 50  0001 C CNN
F 1 "GND" H 3005 4177 50  0000 C CNN
F 2 "" H 3000 4350 50  0001 C CNN
F 3 "" H 3000 4350 50  0001 C CNN
	1    3000 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 4350 3400 4350
Wire Wire Line
	4450 3850 4450 3250
Wire Wire Line
	4450 3250 6150 3250
Wire Wire Line
	4100 3850 4450 3850
Wire Wire Line
	4600 4350 4600 3350
Wire Wire Line
	4600 3350 6150 3350
Wire Wire Line
	4100 4350 4600 4350
$Comp
L Switch:SW_Push SW4
U 1 1 60FEB475
P 5550 4450
F 0 "SW4" H 5550 4735 50  0000 C CNN
F 1 "SW_Push" H 5550 4644 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH-12mm_Wuerth-430476085716" H 5550 4650 50  0001 C CNN
F 3 "~" H 5550 4650 50  0001 C CNN
	1    5550 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0129
U 1 1 60FEB47C
P 5350 4450
F 0 "#PWR0129" H 5350 4200 50  0001 C CNN
F 1 "GND" V 5355 4322 50  0000 R CNN
F 2 "" H 5350 4450 50  0001 C CNN
F 3 "" H 5350 4450 50  0001 C CNN
	1    5350 4450
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 60FF6E22
P 8800 1200
F 0 "J2" H 8772 1132 50  0000 R CNN
F 1 "Conn_01x03_Male" H 8772 1223 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8800 1200 50  0001 C CNN
F 3 "~" H 8800 1200 50  0001 C CNN
	1    8800 1200
	-1   0    0    1   
$EndComp
$Comp
L Device:R_POT_US RV1
U 1 1 5FFC809E
P 9650 1100
F 0 "RV1" H 9582 1054 50  0000 R CNN
F 1 "100K" H 9582 1145 50  0000 R CNN
F 2 "test:Potentiometer_Alps_RK09K_Single_Vertical_modified" H 9650 1100 50  0001 C CNN
F 3 "~" H 9650 1100 50  0001 C CNN
	1    9650 1100
	-1   0    0    1   
$EndComp
$Comp
L Device:R_POT_US RV2
U 1 1 5FFC80CE
P 9950 1750
F 0 "RV2" H 9882 1704 50  0000 R CNN
F 1 "100K" H 9882 1795 50  0000 R CNN
F 2 "test:Potentiometer_Alps_RK09K_Single_Vertical_modified" H 9950 1750 50  0001 C CNN
F 3 "~" H 9950 1750 50  0001 C CNN
	1    9950 1750
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 5FFC80DA
P 9950 1600
F 0 "#PWR0106" H 9950 1450 50  0001 C CNN
F 1 "+5V" H 9965 1773 50  0000 C CNN
F 2 "" H 9950 1600 50  0001 C CNN
F 3 "" H 9950 1600 50  0001 C CNN
	1    9950 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5FFC80D4
P 9950 1900
F 0 "#PWR0105" H 9950 1650 50  0001 C CNN
F 1 "GND" H 9955 1727 50  0000 C CNN
F 2 "" H 9950 1900 50  0001 C CNN
F 3 "" H 9950 1900 50  0001 C CNN
	1    9950 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5FFC80C2
P 9650 1250
F 0 "#PWR0103" H 9650 1000 50  0001 C CNN
F 1 "GND" H 9655 1077 50  0000 C CNN
F 2 "" H 9650 1250 50  0001 C CNN
F 3 "" H 9650 1250 50  0001 C CNN
	1    9650 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_US RV6
U 1 1 5FFC8116
P 10150 4550
F 0 "RV6" H 10082 4504 50  0000 R CNN
F 1 "100K" H 10082 4595 50  0000 R CNN
F 2 "test:Potentiometer_Alps_RK09K_Single_Vertical_modified" H 10150 4550 50  0001 C CNN
F 3 "~" H 10150 4550 50  0001 C CNN
	1    10150 4550
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 6104D24D
P 8800 1850
F 0 "J3" H 8772 1782 50  0000 R CNN
F 1 "Conn_01x03_Male" H 8772 1873 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8800 1850 50  0001 C CNN
F 3 "~" H 8800 1850 50  0001 C CNN
	1    8800 1850
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 6104E722
P 8800 2500
F 0 "J4" H 8772 2432 50  0000 R CNN
F 1 "Conn_01x03_Male" H 8772 2523 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8800 2500 50  0001 C CNN
F 3 "~" H 8800 2500 50  0001 C CNN
	1    8800 2500
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J5
U 1 1 6104F10E
P 8800 3150
F 0 "J5" H 8772 3082 50  0000 R CNN
F 1 "Conn_01x03_Male" H 8772 3173 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8800 3150 50  0001 C CNN
F 3 "~" H 8800 3150 50  0001 C CNN
	1    8800 3150
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J6
U 1 1 6104F787
P 8800 3950
F 0 "J6" H 8772 3882 50  0000 R CNN
F 1 "Conn_01x03_Male" H 8772 3973 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8800 3950 50  0001 C CNN
F 3 "~" H 8800 3950 50  0001 C CNN
	1    8800 3950
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J7
U 1 1 610500C1
P 8800 4650
F 0 "J7" H 8772 4582 50  0000 R CNN
F 1 "Conn_01x03_Male" H 8772 4673 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8800 4650 50  0001 C CNN
F 3 "~" H 8800 4650 50  0001 C CNN
	1    8800 4650
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J8
U 1 1 6105050E
P 8800 5300
F 0 "J8" H 8772 5232 50  0000 R CNN
F 1 "Conn_01x03_Male" H 8772 5323 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8800 5300 50  0001 C CNN
F 3 "~" H 8800 5300 50  0001 C CNN
	1    8800 5300
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J9
U 1 1 61050A4F
P 8800 5900
F 0 "J9" H 8772 5832 50  0000 R CNN
F 1 "Conn_01x03_Male" H 8772 5923 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8800 5900 50  0001 C CNN
F 3 "~" H 8800 5900 50  0001 C CNN
	1    8800 5900
	-1   0    0    1   
$EndComp
Wire Wire Line
	8600 1200 7500 1200
Wire Wire Line
	7500 1200 7500 2950
Wire Wire Line
	8600 1850 7750 1850
Wire Wire Line
	7750 1850 7750 3000
Wire Wire Line
	8600 2500 7950 2500
Wire Wire Line
	7950 2500 7950 3050
Wire Wire Line
	7600 3450 7600 3150
Wire Wire Line
	7600 3150 8600 3150
Wire Wire Line
	8600 3950 8400 3950
Wire Wire Line
	8400 3950 8400 3550
Wire Wire Line
	7150 3550 8400 3550
Wire Wire Line
	8100 3650 8100 4650
Wire Wire Line
	8100 4650 8600 4650
Wire Wire Line
	7900 3750 7900 5300
Wire Wire Line
	7900 5300 8600 5300
Wire Wire Line
	7150 3850 7750 3850
Wire Wire Line
	7750 3850 7750 5900
Wire Wire Line
	7750 5900 8600 5900
Wire Wire Line
	8600 1100 8600 1000
Wire Wire Line
	8600 1000 9500 1000
Wire Wire Line
	9500 1000 9500 1100
Wire Wire Line
	8600 1750 8600 1650
Wire Wire Line
	8600 1650 9800 1650
Wire Wire Line
	9800 1650 9800 1750
Wire Wire Line
	8600 2400 8600 2300
Wire Wire Line
	8600 2300 10100 2300
Wire Wire Line
	10100 2300 10100 2400
Wire Wire Line
	8600 3050 8600 2950
Wire Wire Line
	8600 2950 10350 2950
Wire Wire Line
	10350 2950 10350 3050
Wire Wire Line
	8600 3850 8600 3750
Wire Wire Line
	8600 3750 10350 3750
Wire Wire Line
	10350 3750 10350 3900
Wire Wire Line
	8600 4550 8600 4400
Wire Wire Line
	8600 4400 10000 4400
Wire Wire Line
	10000 4400 10000 4550
Wire Wire Line
	8600 5200 8600 5050
Wire Wire Line
	8600 5050 9700 5050
Wire Wire Line
	9700 5050 9700 5150
Wire Wire Line
	8600 5800 8600 5700
Wire Wire Line
	8600 5700 9400 5700
Wire Wire Line
	9400 5700 9400 5800
Wire Wire Line
	8600 1300 8600 1200
Connection ~ 8600 1200
Wire Wire Line
	8600 1950 8600 1850
Connection ~ 8600 1850
Wire Wire Line
	8600 2600 8600 2500
Connection ~ 8600 2500
Wire Wire Line
	8600 3250 8600 3150
Connection ~ 8600 3150
Wire Wire Line
	8600 4050 8600 3950
Connection ~ 8600 3950
Wire Wire Line
	8600 4750 8600 4650
Connection ~ 8600 4650
Wire Wire Line
	8600 5400 8600 5300
Connection ~ 8600 5300
Wire Wire Line
	8600 6000 8600 5900
Connection ~ 8600 5900
$Comp
L Connector:Screw_Terminal_01x02 J14
U 1 1 61228DB8
P 6550 1200
F 0 "J14" V 6850 1200 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 6750 1550 50  0000 R CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 6550 1200 50  0001 C CNN
F 3 "~" H 6550 1200 50  0001 C CNN
	1    6550 1200
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J11
U 1 1 612296C7
P 4150 1200
F 0 "J11" V 4400 1250 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 4300 1550 50  0000 R CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 4150 1200 50  0001 C CNN
F 3 "~" H 4150 1200 50  0001 C CNN
	1    4150 1200
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J12
U 1 1 6122BFF0
P 5800 6250
F 0 "J12" V 5700 6250 50  0000 R CNN
F 1 "Conn_01x02_Male" V 5600 6500 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5800 6250 50  0001 C CNN
F 3 "~" H 5800 6250 50  0001 C CNN
	1    5800 6250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5350 5900 5800 5900
Wire Wire Line
	5800 5900 5800 6050
$Comp
L Connector:Conn_01x02_Male J13
U 1 1 6122AC4E
P 5900 5500
F 0 "J13" V 5962 5544 50  0000 L CNN
F 1 "Conn_01x02_Male" V 6053 5544 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5900 5500 50  0001 C CNN
F 3 "~" H 5900 5500 50  0001 C CNN
	1    5900 5500
	0    1    1    0   
$EndComp
Wire Wire Line
	5800 5700 5800 5900
Connection ~ 5800 5900
Wire Wire Line
	6550 1400 6550 2150
$Comp
L power:GND #PWR0130
U 1 1 612467D9
P 6650 1600
F 0 "#PWR0130" H 6650 1350 50  0001 C CNN
F 1 "GND" H 6655 1427 50  0000 C CNN
F 2 "" H 6650 1600 50  0001 C CNN
F 3 "" H 6650 1600 50  0001 C CNN
	1    6650 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 1400 6650 1600
$Comp
L power:GND #PWR0131
U 1 1 6124BDD7
P 4250 1650
F 0 "#PWR0131" H 4250 1400 50  0001 C CNN
F 1 "GND" H 4255 1477 50  0000 C CNN
F 2 "" H 4250 1650 50  0001 C CNN
F 3 "" H 4250 1650 50  0001 C CNN
	1    4250 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1400 4250 1650
$Comp
L Connector:Conn_01x03_Male J10
U 1 1 6124F294
P 3950 1900
F 0 "J10" V 4100 2450 50  0000 R CNN
F 1 "Conn_01x03_Male" V 4000 2800 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3950 1900 50  0001 C CNN
F 3 "~" H 3950 1900 50  0001 C CNN
	1    3950 1900
	0    -1   -1   0   
$EndComp
$Comp
L arduSynth-rescue:Arduino_Nano_v3.x-MCU_Module-arduSynth-rescue A1
U 1 1 5FFC8098
P 6650 3150
F 0 "A1" H 6350 2200 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 6250 2100 50  0000 C CNN
F 2 "Modules:Arduino_Nano" H 6650 3150 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 6650 3150 50  0001 C CNN
	1    6650 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4450 5850 4450
Wire Wire Line
	5850 4450 5850 3650
Wire Wire Line
	5850 3650 6150 3650
Wire Wire Line
	4150 1400 4150 1700
Wire Wire Line
	4150 1700 4050 1700
Wire Wire Line
	3950 1700 4050 1700
Connection ~ 4050 1700
Wire Wire Line
	3850 1700 3950 1700
Connection ~ 3950 1700
Wire Wire Line
	6500 6200 6500 6400
Wire Wire Line
	6300 6000 5900 6000
Wire Wire Line
	5900 6000 5900 6050
Wire Wire Line
	6300 5900 5900 5900
Wire Wire Line
	5900 5700 5900 5900
$EndSCHEMATC
