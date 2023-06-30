import paho.mqtt.client as mqtt
from sense_hat import SenseHat
import json
import time
import os
import requests
from dotenv import load_dotenv

# Load the environment variables from the .env file
load_dotenv()

# Read the MQTT broker address, port, and default publish interval from the environment variables
broker_address = os.getenv("MQTT_BROKER_ADDRESS")
port = int(os.getenv("MQTT_BROKER_PORT"))
topic_sensor_data = os.getenv("TOPIC", "sensors/sensehat")

talkback_api_key = os.getenv("TALKBACK_API_KEY")
talkback_command_id = os.getenv("TALKBACK_ID")

default_publish_interval = float(os.getenv("DEFAULT_PUBLISH_INTERVAL", "10"))  # Default publish interval in seconds
current_publish_interval = default_publish_interval

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

def on_disconnect(client, userdata, rc):
    print("Disconnected with result code " + str(rc))

def on_publish(client, userdata, mid):
    print("Message published")

def update_publish_interval_env(interval):
    global current_publish_interval
    current_publish_interval = interval
    print ("Updating publish interval to " + str(interval) + " seconds")
    with open(".env", "r") as file:
        lines = file.readlines()

    updated_lines = []
    for line in lines:
        if line.startswith("DEFAULT_PUBLISH_INTERVAL="):
            line = "DEFAULT_PUBLISH_INTERVAL=" + str(interval) + "\n"
        updated_lines.append(line)

    with open(".env", "w") as file:
        file.writelines(updated_lines)

client = mqtt.Client()
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_publish = on_publish
client.connect(broker_address, port, 60)
client.loop_start()

def execute_command():
    url = f"https://api.thingspeak.com/talkbacks/{talkback_command_id}/commands/execute.json"
    headers = {"Content-Type": "application/json"}
    params = {"api_key": talkback_api_key}
    response = requests.get(url, headers=headers, params=params)
    if response.status_code == 200:
        command_data = response.json()
        return command_data.get("command_string", "")
    else:
        return ""
    
def publish_sensor_data():
    sense = SenseHat()
    temperature = sense.get_temperature()
    humidity = sense.get_humidity()
    pressure = sense.get_pressure()

    payload = {
        "temperature": temperature,
        "humidity": humidity,
        "pressure": pressure
    }

    # Convert the payload to JSON
    json_payload = json.dumps(payload)

    # Publish the sensor data to the MQTT topic
    (result, mid) = client.publish(topic_sensor_data, json_payload)

    # Wait for the message to be published
    while result != mqtt.MQTT_ERR_SUCCESS:
        time.sleep(0.1)
        result = client.publish(topic_sensor_data, json_payload)[0]

    # Print a success message
    print("Published message with ID: " + str(mid))

while True:
    command = execute_command()
    #check command is None or empty
    if command and command.startswith("update_frequency"):
        frequency = command.split(":")[1]        
        try:
            new_frequency = float(frequency)
            update_publish_interval_env(new_frequency)            
        except ValueError:
            print("Invalid frequency value. Frequency must be a number.")            
    publish_sensor_data()
    time.sleep(current_publish_interval)
