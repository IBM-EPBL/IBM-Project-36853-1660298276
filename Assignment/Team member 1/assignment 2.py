import device_info
from boltiot import Bolt, Sms

import json,time
max_temp = 55
min_temp = 25

response = mybolt.isOnline()
power = json.loads(response)
if power['value']== "online":
        while True:
                print ("Reading sensor data...")
                data = json.loads(mybolt.analogRead('A0'))
                try:
                        temp = int(data['value'])*100/1024
                        print ("Sensor reading is "+str(temp)+" degree celsius")
                        if temp > max_temp:
                                print ("Contacting Twilio servers...")
                                response = sms.send_sms("HIGH TEMPERATURE ALERT! CURRENT TEMPERATURE IS "+str(temp))
                                print ("SMS status: "+str(response.status))
                                response2 = mybolt.analogWrite('1','250')
                                for i in range(1,8):
                                        response3 = mybolt.digitalWrite('2','HIGH')
                                        time.sleep(0.5)
                                        response3 = mybolt.digitalWrite('2','LOW')
                        elif temp < min_temp:
                                print ("Contacting Twilio servers...")
                                response = sms.send_sms("LOW TEMPERATURE ALERT! CURRENT TEMPERATURE IS: "+str(temp))
                                print ("SMS status: "+str(response.status))
                                response2 = mybolt.analogWrite('1','50')
                                for i in range(1,8):
                                        response3 = mybolt.digitalWrite('3','HIGH')
                                        time.sleep(0.5)
                                        response3 = mybolt.digitalWrite('3','LOW')
                        else:
                                print ("Temperature alright.")
                                response2 = mybolt.digitalWrite('1','LOW')
                                response3 = mybolt.digitalWrite('2','LOW')
                                response3 = mybolt.digitalWrite('3','LOW')
                except Exception as e:
                        print ("Error!")
                        print (e)
                time.sleep(10)
else:
        print ("DEVICE OFFLINE..")
        print ("MAKE SURE THE IOT MODULE HAS BEEN PLUGGED IN")
