#include <CTBot.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

CTBot myBot;

#define APSSID "KEL"
#define APPSK  "kelompok7"

String ssid0 = "wifi.id";
String pass = "prima2000";
String token = "5053494308:AAG8wctSIr1EcQ3XYLJjcfDEV3rVxO8ZWX4";
const int id = 1413934651;

long sekarang=0, sebelum=0;
String terima="Belum ada data";

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/

String tersimpan = "<h1>Monitoring Daya</h1> <h2>Data Tersimpan</h2>"; 

void simpan(){
//  myBot.sendMessage(id, terima);
  tersimpan=tersimpan+"<p>"+terima+"</p>";
}

void handleRoot() {
  String web=tersimpan+"<h2>Data Sekarang</h2>"+"<p>"+terima+"</p>";
  server.send(200, "text/html", web);
}

void setup() {
//  myBot.wifiConnect(ssid0, pass);
//  myBot.setTelegramToken(token);
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
//  myBot.sendMessage(id, "Mulai");
}

void loop() {
  sekarang=millis();
  while (Serial.available()>0){
    terima = Serial.readString();
  }
  if(sekarang-sebelum>=1800000){
    sebelum=sekarang;
    simpan();
  }
  server.handleClient();
}
