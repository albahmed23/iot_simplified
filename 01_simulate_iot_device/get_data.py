'''
IoT Simplified
MIT License

Save the incoming data from the subsribed topic in a csv file.
'''
import csv
import paho.mqtt.client as mqtt
import json

#Callback function for when a connection occurs to ensure we are connected
def on_connect(client,userdata,flags,rc):
    print("Connected with result code: "+ str(rc))

    client.subscribe("sensor/sound")

#Callback for when a message is recieved in the subscribed topic 
def on_message(client,userdata,msg):
    print(msg.topic+" "+str(msg.payload))
    decoded_message = json.loads(msg.payload)

    #Save message as a new row in sounddata.csv
    with open('sounddata.csv','a') as appendFile:
        appendFileWriter = csv.writer(appendFile)
        appendFileWriter.writerow([decoded_message["timestamp"],decoded_message["soundlevel"]])


#MQTT Client functions
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("mqtt.eclipse.org")

#Make a new file to save incoming messages
with open('sounddata.csv','w') as newFile:
    newFileWriter = csv.writer(newFile)
    newFileWriter.writerow(['timestamp','sound_level'])


#Function by the client to loop forever
client.loop_forever()