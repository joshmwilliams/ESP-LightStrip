#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ElegantOTA.h>
#include "FastLED.h"
#include <stdlib.h>

const char* ssid = "SSID";
const char* password = "SSID_PW";

ESP8266WebServer server(80);

int currentR = 255;
int currentG = 255;
int currentB = 255;
String currentColor; 
int currentBrightness;

#define NUM_LEDS 200
CRGB leds[NUM_LEDS];

//Function for converting provided hex string into RGB values
long hstol(String recv){
  char c[recv.length() + 1];
  recv.toCharArray(c, recv.length() + 1);
  return strtol(c, NULL, 16);
}

//Since server.on() doesn't support wildcards, I am using server.uri() to get the path.
void handleNotFound() {
  String path = server.uri();
  int index = path.indexOf('/');
  String truePath = path.substring(index, path.length());
  if(truePath == "/status"){
      String status;  
      int currentBrightness = FastLED.getBrightness();
      if(currentBrightness == 0){
        status = "0";
      }else{
        status = "1" ;
      }
      server.send(200, "text/plain", status);
  }else if(truePath == "/on"){
    FastLED.setBrightness(255);
    FastLED.show();
    server.send(200, "text/plain", "1");

  }else if(truePath == "/off"){
    FastLED.setBrightness(0);
    FastLED.show();
    server.send(200, "text/plain", "0");

  }else if(truePath == "/brightness"){
      int currentBrightnessPercent = (int) currentBrightness / 2.55;-
      server.send(200, "text/plain", String(currentBrightnessPercent));

  }else if(truePath.startsWith("/brightness/")){
    float lastIndex = path.lastIndexOf('/');
    int endPath = path.substring(lastIndex + 1, path.length()).toInt();
    int newBrightness = endPath * 2.55;
    FastLED.setBrightness(newBrightness);
    currentBrightness = newBrightness;
    FastLED.show();
    server.send(200, "text/plain", String(endPath));

  }else if(truePath == "/set"){
    server.send(200, "text/plain", currentColor);
    
  }else if(truePath.startsWith("/set/")){
    //ex http://192.168.0.X/set/FF00FF
    int lastIndex = path.lastIndexOf('/');
    String endPath = path.substring(lastIndex + 1, path.length());

    //Set global currentColor for future calls to /set...I need to add some functionality here, but it works for now
    currentColor = endPath;
    int newR = hstol(endPath.substring(0,2));
    int newG = hstol(endPath.substring(2,4));
    int newB = hstol(endPath.substring(4,6));

    //Set all leds to the provided color
    for(int dot = 0; dot < NUM_LEDS; dot++) {
      leds[dot].setRGB( newR, newG, newB);
    }

    FastLED.show();
    currentR = newR;
    currentG = newG;
    currentB = newB;

    server.send(200, "text/plain", endPath);
  }
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  FastLED.addLeds<WS2812, 2, GRB>(leds, NUM_LEDS);

  //Sample URL for testing
  server.on("/red",[](){
    for(int dot = 0; dot < NUM_LEDS; dot++) {
      leds[dot] = CRGB::Red;
    }
    FastLED.show();
    server.send(200, "text/plain", "red");
  });
  
  server.onNotFound(handleNotFound);
  ElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
}

void loop(void) {
   server.handleClient();
}

