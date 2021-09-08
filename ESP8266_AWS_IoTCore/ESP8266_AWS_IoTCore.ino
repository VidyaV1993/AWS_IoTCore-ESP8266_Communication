/*
  This example needs https://github.com/esp8266/arduino-esp8266fs-plugin

  This program connects to AWS IoT server:
  * Publishes "Hello from esp8266" to the topic "outTopic" every three seconds.
  * Subscribes to the topic "inTopic", printing out any messages. 
  * Controls the on board LED present in esp8266 board from AWS IoT console.
*/

#include <FS.h>
#include <LittleFS.h> 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Update these with values suitable for your network.

const char* ssid = "my_ssid"; //WiFi ssid
const char* password = "my_password"; //WiFi password

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

const char* AWS_endpoint = "my_mqtt_broker_ip.amazonaws.com"; //MQTT endpoint url

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]); // Pring payload content
  }
  char led = (char)payload[62]; // Extracting the controlling command from the Payload to Controlling LED from AWS
  Serial.print("led command=");
  Serial.println(led);
  if (led == 49) // 49 is the ASCI value of 1
  {
    //digitalWrite(D5, HIGH);
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level) 
    Serial.println("LED_State changed to HIGH");
  }
  else if (led == 48) // 48 is the ASCI value of 0
  {
    //digitalWrite(D5, LOW);
    digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW 
    Serial.println("LED_State changed to LOW");
  }
  Serial.println();
}

WiFiClientSecure espClient;
PubSubClient client(AWS_endpoint, 8883, callback, espClient); //set MQTT port number to 8883 as per //standard
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() 
{
  delay(10);
  // We start by connecting to a WiFi network
  espClient.setBufferSizes(512, 512);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  while (!timeClient.update()) 
  {
    timeClient.forceUpdate();
  }

  espClient.setX509Time(timeClient.getEpochTime());

}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESPthing")) 
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "Hello from esp8266");
      // ... and resubscribe
      client.subscribe("inTopic");
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      char buf[256];
      espClient.getLastSSLError(buf, 256);
      Serial.print("WiFiClientSecure SSL error: ");
      Serial.println(buf);

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {

  Serial.begin(9600);
  Serial.setDebugOutput(true);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  setup_wifi();
  delay(1000);
  if (!LittleFS.begin()) 
  {
    Serial.println("Failed to mount file system");
    return;
  }

  Serial.print("Heap: "); Serial.println(ESP.getFreeHeap());

  // Load certificate file
  File cert = LittleFS.open("/cert.der", "r"); //certificate file name
  if (!cert) 
  {
    Serial.println("Failed to open cert file");
  }
  else
    Serial.println("Successfully opened cert file");

  delay(1000);

  if (espClient.loadCertificate(cert))
    Serial.println("cert loaded");
  else
    Serial.println("cert not loaded");

  // Load private key file
  File private_key = LittleFS.open("/private.der", "r"); //private file name
  if (!private_key) 
  {
    Serial.println("Failed to open private cert file");
  }
  else
    Serial.println("Successfully opened private cert file");

  delay(1000);

  if (espClient.loadPrivateKey(private_key))
    Serial.println("private key loaded");
  else
    Serial.println("private key not loaded");

  // Load CA file
  File ca = LittleFS.open("/ca.der", "r"); //ca file name
  if (!ca) 
  {
    Serial.println("Failed to open ca ");
  }
  else
    Serial.println("Successfully opened ca");

  delay(1000);

  if (espClient.loadCACert(ca))
    Serial.println("ca loaded");
  else
    Serial.println("ca failed");

  Serial.print("Heap: "); Serial.println(ESP.getFreeHeap());
}

void loop() 
{

  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 3000) 
  {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "{\"message\": \"Hello from esp8266 #%ld\"}", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
    Serial.print("Heap: "); Serial.println(ESP.getFreeHeap()); //Low heap can cause problems
  }
}
