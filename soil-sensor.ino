#include <ESP8266WiFi.h>
#include <PubSubClient.h>         //Get it from here: https://github.com/knolleary/pubsubclient
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          // https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include "secrets.h"

unsigned char certificates_esp8266_bin_crt[] = BIN_CRT;
unsigned int certificates_esp8266_bin_crt_len = BIN_CRT_LEN;

unsigned char certificates_esp8266_bin_key[] = BIN_KEY;
unsigned int certificates_esp8266_bin_key_len = BIN_KEY_LEN;

const char* AWS_endpoint = AWS_ENDPOINT; //MQTT broker ip

WiFiClientSecure espClient;
PubSubClient client(AWS_endpoint, 8883, espClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      ESP.restart();
    }
  }
}

void setup() {
  Serial.begin(115200);

  WiFiManager wifiManager;
  wifiManager.autoConnect();
  Serial.println("connected...yeey :)");

  espClient.setCertificate(certificates_esp8266_bin_crt, certificates_esp8266_bin_crt_len);
  espClient.setPrivateKey(certificates_esp8266_bin_key, certificates_esp8266_bin_key_len);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  char msg[50];
  int value = random(30);

  snprintf (msg, 75, "{\"state\":{\"reported\": {\"moisture\":%ld}}}", value);
  Serial.print("Publish message: ");
  Serial.println(msg);

  if (client.publish(UPDATE_TOPIC, msg)) {
    delay(3000);
    client.disconnect();
    ESP.deepSleep(1e6 * 10, WAKE_RF_DEFAULT);
  }
}


void loop() { }
