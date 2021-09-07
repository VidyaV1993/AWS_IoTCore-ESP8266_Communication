# Control devices using AWS IoT Core - ESP8266 Communication

This project illustrates how to set up a simple communication between AWS IoT Core and the NodeMCU ESP8266 board via WiFi and control the built in LED on the ESP8266 board from AWS IoT Core. I used Arduino IDE and MQTT Protocol for this purpose.

This program connects to AWS IoT server:
* Publishes "Hello from esp8266" to the topic "outTopic" every three seconds.
* Subscribes to the topic "inTopic", printing out any messages. 
* Controls the built-in LED present in the esp8266 board from AWS IoT console.

### General Overview on AWS IoT Core ###
AWS IoT Core lets you connect IoT devices to the AWS cloud without the need to provision or manage servers. AWS IoT Core can support billions of devices and trillions of messages, and can process and route those messages to AWS endpoints and to other devices reliably and securely.

### Procedure ###
* Create an AWS account and go to AWS IoT Core service.
* Create a 'Thing' in the AWS, generate a certificate and attach a policy to it.
* Convert AWS IoT Core credential (Certificate, Private Key, Root CA) from .pem to .der format using OpenSSL. You can install OpenSSL from this link: https://slproweb.com/products/Win32OpenSSL.html 
* The following commands will convert the downloaded device certificate to the correct format. xxx indicates the input file name and yy indicates the output filename. You may change the filename as per your convenience.
	* openssl x509 -in xxxxxxxxxx-certificate.pem.crt -out yy.der -outform DER 
	* openssl rsa -in xxxxxxxxxx-private.pem.key -out yy.der -outform DER
	* openssl x509 -in xxxxxxxxxCA1.pem -out yy.der -outform DER
* Install ESP8266 NodeMCU LittleFS Filesystem Uploader in Arduino IDE. Refer this link: https://randomnerdtutorials.com/install-esp8266-nodemcu-littlefs-arduino/ 
* Do modifications to the ESP8266_AWS_IoTCore.ino file as per your WiFi credentials
	* const char* ssid = "my_ssid"; // Give your ssid name
	* const char* password = "my_password"; //Give your password
* Change the AWS end point (MQTT broker address) as per your AWS account. This can be found in the Custom Endpoint section under Seetings menu.
	* const char* AWS_endpoint = "xxxxxxxxxxxxxx.amazonaws.com"; //Give your end point url in place of 'xxxx'. 
* Upload AWS certificates to the NodeMCU ESP8266 via 'ESP8266 LittleFS Data Upload' option under Tools menu in Arduino IDE. Then upload the sketch using the 'Upload' button in Arduino IDE.

### Results ###

#### Part 1: Illustration of simple communication ####

* Go to 'Test' menu of AWS IoT column, under 'Subscription to a topic', type 'outTopic' and click subscribe button. The results in the AWS IoT Console window and the serial monitor in the arduino IDE is shown below:
![AWS serial Output1](https://github.com/VidyaV1993/AWS_IoTCore-ESP8266_Communication/blob/main/ESP8266_AWS_IoTCore/screenshots/aws_serial1.JPG?raw=true)
	
* Go to 'Test' menu of AWS IoT column, under 'Publish to a topic', type 'inTopic' and type the message you want to publish from AWS IoTcore. The results in the AWS IoT Console window and the serial monitor in the arduino IDE is shown below:
![AWS serial Output2](https://github.com/VidyaV1993/AWS_IoTCore-ESP8266_Communication/blob/main/ESP8266_AWS_IoTCore/screenshots/aws_serial2.JPG?raw=true)

#### Part 2: Control the on board LED from AWS IoT Console ####

* Send the LED ON command from AWS IoT Console. The command in the AWS IoT Console window, the serial monitor in the arduino IDE and the on board LED is shown below:
![LED ON](https://github.com/VidyaV1993/AWS_IoTCore-ESP8266_Communication/blob/main/ESP8266_AWS_IoTCore/screenshots/LED_ON1.JPG?raw=true)
	
* Send the LED OFF command from AWS IoT Console. The command in the AWS IoT Console window, the serial monitor in the arduino IDE and the on board LED is shown below:
![LED ON](https://github.com/VidyaV1993/AWS_IoTCore-ESP8266_Communication/blob/main/ESP8266_AWS_IoTCore/screenshots/LED_OFF1.JPG?raw=true)

### Conclusion ###
* Successfully established a communication between AWS IoT Core and the NodeMCU ESP8266 board.
* Illustrated how to control the the built-in LED present in the esp8266 board from AWS IoT console.
* In the same way, it is possible to control other devices and AC appliances for home automation using AWS IoT Core.

https://user-images.githubusercontent.com/50157188/132419452-2479df92-1668-48d6-8277-da78ea248c66.mp4
