#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char* ssid = "Alex-FTTH";
const char* password = "@MichaelMichi4848";

// MQTT broker info
const char* mqtt_server = "34.229.181.226";
const int mqtt_port = 1883;
const char* topic = "givemegainz/esp32/test";

// Create WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);


const char* mqtt_user = "givemegainz";
const char* mqtt_pass = "Givemegainz";
// GPIO to control (e.g., LED on pin 2)
const int ledPin = 2;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);
  
  // React to message (turn LED on/off)
  if (message == "on") {
    //digitalWrite(ledPin, HIGH);
    Serial.print("ON");
  } else if (message == "off") {
    //digitalWrite(ledPin, LOW);
    Serial.print("OFF");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client",mqtt_user,mqtt_pass)) {
      Serial.println("connected");
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}