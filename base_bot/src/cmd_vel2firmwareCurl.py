#!/usr/bin/env python
import rospy
import numpy as np
import requests as req
from geometry_msgs.msg import Twist

max_lin_spd = .22 #arbitrary
max_ang_spd = 2.84 #arbitrary
max_whl_spd=255

rospy.init_node('cmd_vel_servo360', anonymous=True,log_level=rospy.WARN)
node_ip=rospy.get_param("nodemcu_ip",'192.168.1.11')


def angz_to_spd(spd):
    return translate(abs(spd),0,max_ang_spd,0,max_whl_spd)

def linx_to_spd(spd):
    return translate(abs(spd),0,max_lin_spd,0,max_whl_spd)



def translate(value, leftMin, leftMax, rightMin, rightMax):
    # Figure out how 'wide' each range is
    # https://stackoverflow.com/questions/1969240/
    leftSpan = leftMax - leftMin
    rightSpan = rightMax - rightMin

    # Convert the left range into a 0-1 range (float)
    valueScaled = float(value - leftMin) / float(leftSpan)

    # Convert the 0-1 range into a value in the right range.
    return rightMin + (valueScaled * rightSpan)

def callback(twist):
    angz=twist.angular.z
    linx=twist.linear.x
    #set a praiority for angular cmds
    if angz!=0:

        spd=angz_to_spd(angz)
        if angz>0:
            rospy.logdebug("angz is postive,heading right")
            _send(-spd,spd)
        if angz<0:
            rospy.logdebug("angz is negative,heading left")
            _send(spd,-spd)

    if linx!=0:

        spd=linx_to_spd(linx)
        if linx>0:
            rospy.logdebug("linx if postive ,heading forward")
            _send(spd,spd)
        else:
            rospy.logdebug("linx is negative")
            _send(-spd,-spd)

    if linx==0 and angz==0:
        _send(0,0)
    return

def _send(r,l):
    rospy.logdebug("Right Wheel: {0} Left Wheel: {1}".format(r,l))
    req.get("http://{0}/wheels_spd?rw_spd={1}&lw_spd={2}".format(node_ip,int(r),int(l)))


def shutdown():
    _send(0,0)
    return

if __name__=="__main__":
    rospy.on_shutdown(shutdown)
    rospy.Subscriber("cmd_vel", Twist, callback,queue_size=10)
    rospy.loginfo("Connecting to {0}".format(node_ip))
    rospy.spin()