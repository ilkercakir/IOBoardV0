cd /home/pi/Desktop/C/GPIO/IOBoard
gcc -shared -o libIOBoardV0.so ControllerConsole_Controller.o iochannels.o gpio.o /usr/lib/libwiringPi.so
/cd /usr/lib
/sudo ln -s /home/pi/Desktop/C/GPIO/IOBoard/libIOBoardV0.so libIOBoardV0.so
/cd /home/pi/Desktop/C/GPIO/IOBoard