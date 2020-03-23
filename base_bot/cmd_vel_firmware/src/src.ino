#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define ssid "HOME"
#define password  "home2home"

ESP8266WebServer server(80);
Servo right; 
Servo left;  

int r_spd;  //max lin vel of .8m/s
int l_spd;  //max lin vel of .8m/s
#define maxspd 255 // arbitary really
#define stop_val 90

#define right_wheel_pwm_pin D5
#define left_wheel_pwm_pin D6

void setup() {
  right.attach(right_wheel_pwm_pin);
  left.attach(left_wheel_pwm_pin);
  Serial.begin(9600);
  StartWifi();
  SetHTTP();
}

void SetHTTP(){
  server.on("/wheels_spd", []() {
    r_spd=server.arg("rw_spd").toInt();
    l_spd=server.arg("lw_spd").toInt();
    
    Serial.print("SPD R:");
    Serial.println(r_spd);
    
    Serial.print("SPD L:");
    Serial.println(l_spd);
    
    moveRight_wheel();
    moveLeft_wheel();
    
    server.send(200, "text/plain", "ok.");
  });

  server.begin();
  Serial.println("HTTP server started");
}

int map_to_spd(int spd_v,int max_val){
  Serial.print("Max_val: ");
  Serial.println(max_val);

  int rr=map(abs(spd_v),0,maxspd,stop_val,max_val); //constrain()?
  
  Serial.print("Mapped value: ");
  Serial.println(rr);
  return rr;
}

void loop() {
  server.handleClient();
}