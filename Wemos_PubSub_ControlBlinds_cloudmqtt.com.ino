/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/
//Im using Wemos D1 R1 - set this settings when compiling
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <dht.h>

// Update these with values suitable for your network.

const char* ssid = "JioFiber-24_EXT";
const char* password = "welcome2ibm";  


const char* mqtt_server = "m12.cloudmqtt.com";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
#define CONTROL_BLINDS_IN_1   16 // 
#define CONTROL_BLINDS_IN_2   14 // 
#define CONTROL_BLINDS_EN_A   12 // 

#define DHT11_PIN 12
dht DHT;



void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  // don't touch as there is no relay here ! 
  // shashi - Sep 21st 2022 digitalWrite(CONTROL_BLINDS, HIGH); // turn off the Control lights to begin with, HIGH is off !!
  //Serial.println ("Close off ");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    Serial.println("Setting CONTROL_BLINDS_IN1 Pin 12 to HIGH, 14 to LOW, in function callback, Raise blinds ");
    digitalWrite(CONTROL_BLINDS_EN_A, HIGH);  // lower the blinds, 

    digitalWrite(CONTROL_BLINDS_IN_1, HIGH);   // Motor CW
    digitalWrite(CONTROL_BLINDS_IN_2, LOW);    // 
    
    // it is actually HIGH
    // 
  } else if ((char)payload[0] == '0') { // ccw
    Serial.println("Set blinds to lower, CONTROL_BLINDS Pin 12 and 14 to LOW, in function callback ");
    digitalWrite(CONTROL_BLINDS_EN_A, HIGH);  // lower the blinds, 

    digitalWrite(CONTROL_BLINDS_IN_1, LOW);   // Motor CCW 
    digitalWrite(CONTROL_BLINDS_IN_2, HIGH);  //  
    
  } else if ((char)payload[0] == '2') {  // off
    Serial.println("Set blinds to lower, CONTROL_BLINDS Pin 12 and 14 to LOW, in function callback ");
    digitalWrite(CONTROL_BLINDS_EN_A, LOW);  // Disable the ENABLE PIN, 

  }


}

void reconnect() {
  // Loop until we're reconnected
  int flag = 0;
  
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), "oxefqvkn", "uTM7RdarxTPA" )) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      if ( flag ) {
         flag =0;
         Serial.println("sending a 1");
         client.publish("outTopic", "1");
      } else {
        Serial.println("sending a 0");
        client.publish("outTopic", "0");
      }
      // ... and resubscribe
      client.subscribe("inBlindsControl");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED OFF to indicate that the connection is not done.

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED OFF - to indicate connection not done yet.
  
  // Initialize pin 12,14 and 16 for turning lights on and off.
  pinMode (CONTROL_BLINDS_IN_1, OUTPUT);
  pinMode (CONTROL_BLINDS_IN_2, OUTPUT);
  pinMode (CONTROL_BLINDS_EN_A, OUTPUT);
  
  Serial.begin(115200);
  //Serial.println ("turning CONTROL LIGHTS/Pin 14 off i.e HIGH ");
  setup_wifi();
  client.setServer(mqtt_server, 19757);
  client.setCallback(callback);
}

void loop() {

//  char publish_str [20];
  
  if (!client.connected()) {
    digitalWrite(LED_BUILTIN, HIGH);   // Got disconnected, so turn the wifi indicator off.  
    reconnect();
  }
  client.loop();
  digitalWrite(LED_BUILTIN, LOW);   // Got connected, enable wifi indicator on.

}
