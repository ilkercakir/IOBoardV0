cd /var/lib/tomcat8/webapps/IOBoardV0/WEB-INF/classes
sudo javac -cp . ControllerConsole/Device.java
sudo javac -cp ".:/usr/share/tomcat8/lib/sqlite-jdbc-3.7.2.jar" ControllerConsole/User.java
sudo javac -cp ".:/usr/share/tomcat8/lib/sqlite-jdbc-3.7.2.jar" ControllerConsole/UserDevices.java
sudo javac -cp ".:/usr/share/tomcat8/lib/log4j-api-2.13.0.jar:/usr/share/tomcat8/lib/log4j-core-2.13.0.jar" ControllerConsole/Controller.java
sudo javac -cp ".:/usr/share/tomcat8/lib/servlet-api.jar:/usr/share/tomcat8/lib/log4j-api-2.13.0.jar:/usr/share/tomcat8/lib/log4j-core-2.13.0.jar" ControllerConsole/ConsoleServlet.java
javah -jni -cp . ControllerConsole.Controller

cd /home/pi/Desktop/C/GPIO/IOBoard
gcc -shared -o libIOBoardV0.so ControllerConsole_Controller.o iochannels.o gpio.o /usr/lib/wiringPi.so

cd /usr/lib
sudo ln -s /home/pi/Desktop/C/GPIO/IOBoard/libIOBoardV0.so libIOBoardV0.so
