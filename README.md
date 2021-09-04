# AWS IoT-ESP8266 Communication

AWS IoT Core lets you connect IoT devices to the AWS cloud without the need to provision or manage servers. AWS IoT Core can support billions of devices and trillions of messages, and can process and route those messages to AWS endpoints and to other devices reliably and securely.

This project illustrates a simple communication between AWS IoT Core and the NodeMCU ESP8266 board via WiFi. I used Arduino IDE and MQTT Protocol for this purpose.

This program connects to AWS IoT server:
* Publishes "Hello from esp8266" to the topic "outTopic" every three seconds
* Subscribes to the topic "inTopic", printing out any messages. In this case I am sending the message "Hello, this is Vidya from AWS IoT console"

### Steps ###
* Create an AWS account and go to AWS IoT Core service
* Create a 'Thing' in the AWS, generate a certificate and attach a policy to it.
* Convert AWS IoT Core credential(Certificate, Private Key, Root CA) from .pem to .der format using OpenSSL. You can install OpenSSL from this link: https://slproweb.com/products/Win32OpenSSL.html 
* The following commands will convert the downloaded device certificate to the correct format. xxx indicates the input file name and yy indicates the output filename. You may change the filename as per your convenience.
	* openssl x509 -in xxxxxxxxxx-certificate.pem.crt -out yy.der -outform DER 
	* openssl rsa -in xxxxxxxxxx-private.pem.key -out yy.der -outform DER
	* openssl x509 -in xxxxxxxxxCA1.pem -out yy.der -outform DER
* Install ESP8266 NodeMCU LittleFS Filesystem Uploader in Arduino IDE. Refer this link: https://randomnerdtutorials.com/install-esp8266-nodemcu-littlefs-arduino/ 
* Do modifications to the ESP8266_AWS_IoTCore.ino file as per your WiFi credentials
	* const char* ssid = "my_ssid"; // Give your ssid name
	* const char* password = "my_password"; //Give your password
* Change the AWS end point (MQTT broker address) as per your AWS account	
	* const char* AWS_endpoint = "xxxxxxxxxxxxxx.amazonaws.com"; //Give your end point url in place of 'xxxx'. This can be found in the Custom Endpoint section under Seetings menu.
* Uploading AWS certificates & code to the NodeMCU ESP8266 via 'ESP8266 LittleFS Data Upload' option under Tools menu in Arduino IDE. Then upload the sketch using the 'Upload' button in Arduino IDE.
* Results
	* Go to 'Test' menu of AWS IoT column, under Subscription topic, type 'outTopic' and click subscribe button. You will see the results as shown below:
	![AWS IoT Console Output](https://github.com/VidyaV1993/AWS_IoTCore-ESP8266_Communication/blob/main/ESP8266_AWS_IoTCore/screenshots/aws_console1.PNG?raw=true)
	ESP8266_AWS_IoTCore/screenshots/aws_console.PNG) 