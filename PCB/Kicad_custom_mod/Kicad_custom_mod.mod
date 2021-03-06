PCBNEW-LibModule-V1  Cts 20 Haz 2020 18:25:19 +03
# encoding utf-8
Units mm
$INDEX
BATTERY_16850_1
JACK_STEREO1
KLEMENS_1
POWER_JACK_1
PUSH_BUTTON1
PWR_SW1
RELAY_J9906
RJ45_8_io0
XS3868_V3
$EndINDEX
$MODULE BATTERY_16850_1
Po 0 0 0 15 5EA5772F 00000000 ~~
Li BATTERY_16850_1
Sc 0
AR 
Op 0 0 0
T0 0 3.81 1 1 0 0.15 N V 21 N "BATTERY_16850_1"
T1 0 0 1 1 0 0.15 N V 21 N "BAT**"
T2 0 33.02 1 1 0 0.15 N V 21 N "(-)"
T2 0 -30.48 1 1 0 0.15 N V 21 N "(+)"
DS -10.16 35.56 10.16 35.56 0.15 21
DS 10.16 35.56 10.16 -33.02 0.15 21
DS 10.16 -33.02 -10.16 -33.02 0.15 21
DS -10.16 -33.02 -10.16 35.56 0.15 21
$PAD
Sh "2" C 2 2 0 0 0
Dr 1 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 0 35.56
$EndPAD
$PAD
Sh "1" C 2 2 0 0 0
Dr 1 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 0 -33.02
$EndPAD
$EndMODULE BATTERY_16850_1
$MODULE JACK_STEREO1
Po 0 0 0 15 5EA56D70 00000000 ~~
Li JACK_STEREO1
Cd DC Barrel Jack
Kw Power Jack
Sc 0
AR PWR-Jack
Op 0 0 0
T0 -8.255 -3.175 1.016 1.016 0 0.2032 N V 21 N "CON"
T1 -3.175 0.635 1.016 1.016 0 0.2032 N I 21 N "JACK_STEREO1"
T2 -3.302 -3.81 1 1 0 0.15 N V 21 N "R"
T2 -3.175 5.08 1 1 0 0.15 N V 21 N "L"
T2 -10.16 3.175 1 1 0 0.15 N V 21 N "GND"
DS -11.43 -5.08 2.54 -5.08 0.15 21
DS 2.54 -5.08 2.54 6.35 0.15 21
DS 2.54 6.35 -11.43 6.35 0.15 21
DS -11.43 6.35 -11.43 -5.08 0.15 21
$PAD
Sh "1" R 2.5 2.5 0 0 0
Dr 1.00076 0 0 O 1.00076 1.99974
At STD N 00E0FFFF
Ne 0 ""
Po -10.16 0.635
$EndPAD
$PAD
Sh "3" R 2.5 2.5 0 0 0
Dr 1.00076 0 0 O 1.00076 1.99974
At STD N 00E0FFFF
Ne 0 ""
Po 1.27 5.08
$EndPAD
$PAD
Sh "4" R 2.5 2 0 0 0
Dr 1.99974 0 0 O 1.99974 1.00076
At STD N 00E0FFFF
Ne 0 ""
Po -1.27 -3.81
$EndPAD
$PAD
Sh "2" R 2.5 2.5 0 0 0
Dr 1.99974 0 0 O 1.99974 1.00076
At STD N 00E0FFFF
Ne 0 ""
Po -5.08 5.08
$EndPAD
$PAD
Sh "3" R 2.5 2 0 0 0
Dr 1.99974 0 0 O 1.99974 1.00076
At STD N 00E0FFFF
Ne 0 ""
Po -2.54 -1.27
$EndPAD
$EndMODULE JACK_STEREO1
$MODULE KLEMENS_1
Po 0 0 0 15 5EEE2A59 00000000 ~~
Li KLEMENS_1
Cd Connecteurs 2 pins
Kw CONN DEV
Sc 0
AR 
Op 0 0 0
T0 0 4.445 0.762 0.762 0 0.1524 N V 21 N "KLEMENS_1"
T1 0 1.27 0.762 0.762 0 0.1524 N I 21 N "K**"
DS -5.08 -5.08 5.08 -5.08 0.15 21
DS 5.08 -5.08 5.08 16.51 0.15 21
DS 5.08 16.51 -5.08 16.51 0.15 21
DS -5.08 16.51 -5.08 -5.08 0.15 21
$PAD
Sh "1" R 2.5 2.5 0 0 0
Dr 2 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -2.54 -3.175
$EndPAD
$PAD
Sh "2" R 2.5 2.5 0 0 0
Dr 2 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 2.54 -3.175
$EndPAD
$SHAPE3D
Na "pin_array/pins_array_2x1.wrl"
Sc 1 1 1
Of 0 0 0
Ro 0 0 0
$EndSHAPE3D
$EndMODULE KLEMENS_1
$MODULE POWER_JACK_1
Po 0 0 0 15 5E9DA6B7 00000000 ~~
Li POWER_JACK_1
Cd Connecteur 3 pins
Kw CONN DEV
Sc 0
AR 
Op 0 0 0
T0 -1.27 -1.27 1.016 1.016 0 0.1524 N V 21 N "PWR_JACK_1"
T1 -1.27 -3.81 1.016 1.016 0 0.1524 N I 21 N "PJ**"
DS -6.35 5.08 5.08 5.08 0.15 21
DS 5.08 5.08 5.08 -6.35 0.15 21
DS 5.08 -6.35 -6.35 -6.35 0.15 21
DS -6.35 -6.35 -6.35 5.08 0.15 21
$PAD
Sh "1" R 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -4.445 2.54
$EndPAD
$PAD
Sh "2" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -0.635 2.54
$EndPAD
$PAD
Sh "3" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 2.54 2.54
$EndPAD
$EndMODULE POWER_JACK_1
$MODULE PUSH_BUTTON1
Po 0 0 0 15 5EA5712D 00000000 ~~
Li PUSH_BUTTON1
Sc 0
AR 
Op 0 0 0
T0 -0.635 1.143 1 1 0 0.15 N V 21 N "PUSH_BUTTON1"
T1 -1.143 -6.096 1 1 0 0.15 N V 21 N "PB**"
DS 0.762 -0.254 -3.556 -0.254 0.15 21
DS -3.556 -0.254 -3.556 -5.08 0.15 21
DS 0.762 -0.381 0.762 -0.254 0.15 21
DS -3.556 -5.08 0.762 -5.08 0.15 21
DS 0.762 -5.08 0.762 -0.381 0.15 21
$PAD
Sh "1" C 1.5 1.5 0 0 0
Dr 0.6 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -2.54 -1.27
$EndPAD
$PAD
Sh "2" C 1.5 1.5 0 0 0
Dr 0.6 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -0.254 -1.27
$EndPAD
$PAD
Sh "1" C 1.5 1.5 0 0 0
Dr 0.6 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -2.54 -3.937
$EndPAD
$PAD
Sh "2" C 1.5 1.5 0 0 0
Dr 0.6 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -0.254 -3.937
$EndPAD
$EndMODULE PUSH_BUTTON1
$MODULE PWR_SW1
Po 0 0 0 15 5EA5727D 00000000 ~~
Li PWR_SW1
Cd Connecteur 3 pins
Kw CONN DEV
Sc 0
AR 
Op 0 0 0
T0 0 2.54 1.016 1.016 0 0.1524 N V 21 N "PWR_SW1"
T1 0 -2.54 1.016 1.016 0 0.1524 N I 21 N "PSW**"
DS -3.81 1.27 -3.81 -1.27 0.1524 21
DS -3.81 -1.27 3.81 -1.27 0.1524 21
DS 3.81 -1.27 3.81 1.27 0.1524 21
DS 3.81 1.27 -3.81 1.27 0.1524 21
DS -1.27 -1.27 -1.27 1.27 0.1524 21
$PAD
Sh "1" R 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -2.54 0
$EndPAD
$PAD
Sh "2" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 0 0
$EndPAD
$PAD
Sh "3" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 2.54 0
$EndPAD
$SHAPE3D
Na "pin_array/pins_array_3x1.wrl"
Sc 1 1 1
Of 0 0 0
Ro 0 0 0
$EndSHAPE3D
$EndMODULE PWR_SW1
$MODULE RELAY_J9906
Po 0 0 0 15 5EEE29FD 00000000 ~~
Li RELAY_J9906
Cd Siemens Relay J9906
Kw RELAY J9906
Sc 0
AR 
Op 0 0 0
T0 -1.27 -2.54 1.016 1.016 0 0.2032 N V 21 N "RELAY_J9906"
T1 -1.27 3.81 1.016 1.016 0 0.2032 N I 21 N "REL**"
DS 6.35 10.16 3.81 10.16 0.15 21
DS 6.35 10.16 6.35 -11.43 0.15 21
DS 6.35 -11.43 -10.16 -11.43 0.15 21
DS -10.16 -11.43 -10.16 10.16 0.15 21
DS -10.16 10.16 3.81 10.16 0.15 21
$PAD
Sh "1" C 3.048 3.048 0 0 0
Dr 1.5 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -7.62 -6.35
$EndPAD
$PAD
Sh "2" R 3.048 3.048 0 0 0
Dr 1.5 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -7.62 5.969
$EndPAD
$PAD
Sh "3" C 3.048 3.048 0 0 0
Dr 1.5 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -1.905 7.874
$EndPAD
$PAD
Sh "4" R 3.048 3.048 0 0 0
Dr 1.5 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 3.81 5.969
$EndPAD
$PAD
Sh "5" C 3.048 3.048 0 0 0
Dr 1.5 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 3.81 -6.35
$EndPAD
$EndMODULE RELAY_J9906
$MODULE RJ45_8_io0
Po 0 0 0 15 5E9D6976 00000000 ~~
Li RJ45_8_io0
Kw RJ45_8_io0
Sc 0
AR 
Op 0 0 0
T0 0 3.81 1.524 1.524 0 0.3048 N V 21 N "RJ45_8_io0"
T1 0.14224 -0.1016 1.00076 1.00076 0 0.2032 N V 21 N "VAL**"
DS 7.62 -10.16 7.62 5.08 0.15 21
DS -7.62 5.08 7.62 5.08 0.15 21
DS -7.62 -10.16 -7.62 5.08 0.15 21
DS 7.62 -10.16 -7.62 -10.16 0.127 21
$PAD
Sh "Hole" C 3.64998 3.64998 0 0 0
Dr 3.2512 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 6.096 0
$EndPAD
$PAD
Sh "Hole" C 3.64998 3.64998 0 0 0
Dr 3.2512 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -6.096 0
$EndPAD
$PAD
Sh "1" R 1.50114 1.50114 0 0 1800
Dr 0.89916 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 3.556 -2.286
$EndPAD
$PAD
Sh "2" C 1.50114 1.50114 0 0 1800
Dr 0.89916 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 2.413 -4.318
$EndPAD
$PAD
Sh "3" C 1.50114 1.50114 0 0 1800
Dr 0.89916 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 1.524 -2.286
$EndPAD
$PAD
Sh "4" C 1.50114 1.50114 0 0 1800
Dr 0.89916 0 0
At STD N 00E0FFFF
Ne 0 ""
Po 0.381 -4.318
$EndPAD
$PAD
Sh "5" C 1.50114 1.50114 0 0 1800
Dr 0.89916 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -0.508 -2.286
$EndPAD
$PAD
Sh "6" C 1.50114 1.50114 0 0 1800
Dr 0.89916 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -1.651 -4.318
$EndPAD
$PAD
Sh "7" C 1.50114 1.50114 0 0 1800
Dr 0.89916 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -2.54 -2.286
$EndPAD
$PAD
Sh "8" C 1.50114 1.50114 0 0 1800
Dr 0.89916 0 0
At STD N 00E0FFFF
Ne 0 ""
Po -3.683 -4.318
$EndPAD
$SHAPE3D
Na "connectors/RJ45_8.wrl"
Sc 0.4 0.4 0.4
Of 0 0 0
Ro 0 0 0
$EndSHAPE3D
$EndMODULE RJ45_8_io0
$MODULE XS3868_V3
Po 0 0 0 15 5EA5750B 00000000 ~~
Li XS3868_V3
Sc 0
AR 
Op 0 0 0
T0 0 12.7 1 1 0 0.15 N V 21 N "XS3868_V3"
T1 0 1.27 1 1 0 0.15 N V 21 N "U?"
DS 6.35 -11.43 6.35 13.97 0.15 21
DS 6.35 13.97 -6.35 13.97 0.15 21
DS -6.35 13.97 -6.35 -11.43 0.15 21
DS -6.35 -11.43 6.35 -11.43 0.15 21
$PAD
Sh "1" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -6.35 -1.27
$EndPAD
$PAD
Sh "2" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -6.35 0
$EndPAD
$PAD
Sh "3" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -6.35 1.27
$EndPAD
$PAD
Sh "4" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -6.35 2.54
$EndPAD
$PAD
Sh "5" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -6.35 3.81
$EndPAD
$PAD
Sh "6" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -6.35 5.08
$EndPAD
$PAD
Sh "7" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -6.35 6.35
$EndPAD
$PAD
Sh "8" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -6.35 7.62
$EndPAD
$PAD
Sh "9" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -6.35 8.89
$EndPAD
$PAD
Sh "10" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -6.35 10.16
$EndPAD
$PAD
Sh "11" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -6.35 11.43
$EndPAD
$PAD
Sh "12" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -6.35 12.7
$EndPAD
$PAD
Sh "13" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.35 11.43
$EndPAD
$PAD
Sh "14" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.35 10.16
$EndPAD
$PAD
Sh "15" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.35 8.89
$EndPAD
$PAD
Sh "16" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.35 7.62
$EndPAD
$PAD
Sh "17" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.35 6.35
$EndPAD
$PAD
Sh "18" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.35 5.08
$EndPAD
$PAD
Sh "19" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.35 3.81
$EndPAD
$PAD
Sh "20" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.35 2.54
$EndPAD
$PAD
Sh "21" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.35 1.27
$EndPAD
$PAD
Sh "22" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.35 0
$EndPAD
$PAD
Sh "23" R 1 0.5 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.35 -1.27
$EndPAD
$EndMODULE XS3868_V3
$EndLIBRARY
