# AWS IoT-ESP8266 Communication

AWS IoT Core lets you connect IoT devices to the AWS cloud without the need to provision or manage servers. AWS IoT Core can support billions of devices and trillions of messages, and can process and route those messages to AWS endpoints and to other devices reliably and securely.

This project illustrates a simple communication between AWS IoT Core and the NodeMCU ESP8266 board via WiFi. I used Arduino IDE and MQTT Protocol for this purpose.

### Steps ###
* Create an AWS account and go to AWS IoT Core service
* Create a 'Thing' in the AWS, generate a certificate and attach a policy to it.
* Convert AWS IoT Core credential(Certificate, Private Key, Root CA) from .pem to .der format using OpenSSL. You can install OpenSSL from this link: https://slproweb.com/products/Win32OpenSSL.html 
* The following commands will convert the downloaded device certificate to the correct format. xxx indicates the input file name and yy indicates the output filename. You may change the filename as per your convenience.
> openssl x509 -in xxxxxxxxxx-certificate.pem.crt -out yy.der -outform DER 
> openssl rsa -in xxxxxxxxxx-private.pem.key -out yy.der -outform DER
> openssl x509 -in xxxxxxxxxCA1.pem -out yy.der -outform DER
* Install ESP8266 LittleFS data upload tool in Arduino IDE