import paho.mqtt.client as mqtt
from sense_hat import SenseHat
import json
import time
import os
from dotenv import load_dotenv

# Load the environment variables from the .env file
load_dotenv()

# Read the MQTT broker address, port, and default publish interval from the environment variables
broker_address = os.getenv("MQTT_BROKER_ADDRESS")
port = int(os.getenv("MQTT_PORT"))
topic_sensor_data = "sensors/sensehat"
topic_frequency = "sensors/sensehat/frequency"

default_publish_interval = int(os.getenv("DEFAULT_PUBLISH_INTERVAL", "10"))  # Default publish interval in seconds
current_publish_interval = default_publish_interval

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe(topic_frequency)

def on_disconnect(client, userdata, rc):
    print("Disconnected with result code " + str(rc))

def on_message(client, userdata, msg):
    global current_publish_interval
    if msg.topic == topic_frequency:
        try:
            interval = int(msg.payload)
            if interval > 0:
                current_publish_interval = interval
                print("Updated publish interval: " + str(current_publish_interval) + " seconds")

                # Update the DEFAULT_PUBLISH_INTERVAL in the .env file
                update_publish_interval_env(current_publish_interval)
            else:
                print("Invalid publish interval")
        except ValueError:
            print("Invalid publish interval")

def on_publish(client, userdata, mid):
    print("Message published")

def update_publish_interval_env(interval):
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
client.on_message = on_message
client.on_publish = on_publish
client.connect(broker_address, port, 60)
client.loop_start()

def publish_sensor_data():
    sense = SenseHat()
    while True:
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

        time.sleep(current_publish_interval)

publish_sensor_data()