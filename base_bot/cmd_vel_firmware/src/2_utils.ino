

#define backward_right_wheel 180
#define forward_right_wheel 0
#define backward_left_wheel 0
#define forward_left_wheel 180

int get_forward_val_right_wheel(){
  return map_to_spd(r_spd,forward_right_wheel);
}

int get_forward_val_left_wheel(){
  return map_to_spd(l_spd,forward_left_wheel);
}

int get_backward_val_right_wheel(){
  return map_to_spd(r_spd,backward_right_wheel);
}

int get_backward_val_left_wheel(){
  return map_to_spd(l_spd,backward_left_wheel);
}

int moveRight_wheel(){
  if (r_spd>0){ //postive forward
    right.write(get_forward_val_right_wheel());
  }else{
    right.write(get_backward_val_right_wheel());
  }
}

int moveLeft_wheel(){
  if (l_spd>0){ //postive forward
    left.write(get_forward_val_left_wheel());
  }else{
    left.write(get_backward_val_left_wheel());
  }
}


void StartWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("SSID:");
  Serial.println(ssid);

  Serial.print("Password:");
  Serial.println(password);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}
