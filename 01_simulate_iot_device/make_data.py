'''
IoT Simplified
MIT License

Send random data to the topic sensor/sound.
'''
import paho.mqtt.client as mqtt
import time
import json
import random

#Initilizing mqtt Client
mqtt_client = mqtt.Client()

#MQTT Topic
mqtt_topic = "sensor/sound"

#Func that returns random int between 20 to 80
def read_random():
    return random.randint(20,80)

data_payload = {}

#Set the timezone
time.tzset()

#Send data every 10 seconds
while True:
    time.sleep(10)
    data_payload["soundlevel"] = read_random()
    data_payload["timestamp"] = time.strftime("%m-%d-%Y %H:%M:%S")
    
    #Encode data using json
    encoded_payload = json.dumps(data_payload)

    #MQTT client connect and publish
    mqtt_client.connect("mqtt.eclipse.org")
    mqtt_client.publish(mqtt_topic,encoded_payload)

    print(f"Message Sent:{encoded_payload}")
     