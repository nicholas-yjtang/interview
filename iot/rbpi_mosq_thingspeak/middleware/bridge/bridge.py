import paho.mqtt.client as mqtt
import requests
from dotenv import load_dotenv
import os

# Load the environment variables from the .env file
load_dotenv()

# MQTT broker details from .env file
mqtt_broker_address = os.getenv("MQTT_BROKER_ADDRESS")
mqtt_broker_port = int(os.getenv("MQTT_BROKER_PORT"))
mqtt_topic = os.getenv("TOPIC", "sensors/sensehat")

# ThingSpeak API key from .env file
thingspeak_api_key = os.getenv("THINGSPEAK_API_KEY")
thingspeak_channel_id = "your_thingspeak_channel_id"  # Replace with your ThingSpeak channel ID


def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc), flush=True)
    client.subscribe(mqtt_topic)


def on_message(client, userdata, msg):
    payload = msg.payload.decode()
    print("Received message: " + payload, flush=True)
    upload_data_to_thingspeak(payload)


def upload_data_to_thingspeak(data):
    url = f"https://api.thingspeak.com/update.json"
    headers = {"Content-Type": "application/x-www-form-urlencoded"}
    payload = f"api_key={thingspeak_api_key}&field1={data}"  # Adjust field number as per your ThingSpeak configuration

    response = requests.post(url, headers=headers, data=payload)
    if response.status_code == 200:
        print("Data uploaded to ThingSpeak successfully!", flush=True)
    else:
        print("Failed to upload data to ThingSpeak.", flush=True)


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(mqtt_broker_address, mqtt_broker_port, 60)

client.loop_forever()