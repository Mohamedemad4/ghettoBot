# Some notes
 - the platform works by using 360 Servos so I have no idea about movement and you can't use it to extract odom.

### params
 -  max_lin_spd = .22 #arbitrary it works well with the turtlebot teleop
 -  max_ang_spd = 2.84 
 - nodemcu_ip the ip of the NodeMcu
  
# Setup
 - change SSID and Password in cmd_vel_servo360/cmd_vel_firmware/src/src.ino to your Wifi's SSID and Password
 - change rpi3 ip and password in assemble.launch so it can ssh to it
 - first time sshing into the Pi use -oHostKeyAlgorithms='ssh-rsa' option so <machine> works