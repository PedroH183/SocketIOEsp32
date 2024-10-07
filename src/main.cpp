#include <WiFi.h>
#include <Arduino.h>

#define SSID    "######"
#define PASSWD  "######"
#define MONITOR_SPEED 115200

WiFiClient clientSockt;
WiFiServer serverSockt(23);

void hello_exec_first(void);
void hello_exec_second(void);

void setup() {
    Serial.begin(MONITOR_SPEED);
    delay(100);
    WiFi.begin(SSID, PASSWD);

    while (WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.println("...");
    };

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    serverSockt.begin();
}

void loop() {
    WiFiClient client = serverSockt.available();

    if (client) {
        Serial.print("Um novo cliente se conectou IP :: ");
        Serial.println(client.remoteIP());

        while (client.connected()) {

            if(client.available()) {
                String data = client.readStringUntil('\n');
                Serial.println(data);

                if(data.equals("start")){
                    hello_exec_first();
                }
                if(data.equals("stop")){
                    hello_exec_second();
                }
            }
            delay(100);
        }
        client.stop();
        Serial.println("Logout Client");
    }
}

void hello_exec_first(){
    // send a connection to other external socket

    while (!clientSockt.connected()) {
        Serial.println("trying connect ...");
        clientSockt.connect("10.0.1.11", 1027);
        delay(100);
    }

    if (clientSockt.connected()) {
        Serial.println("Sending message to external server");
        clientSockt.print("Helllow word");
    }else{
        Serial.println("Don't connected");
    }

    clientSockt.stop();
}

void hello_exec_second(){
    Serial.println("EXTERNAL SECOND");
}