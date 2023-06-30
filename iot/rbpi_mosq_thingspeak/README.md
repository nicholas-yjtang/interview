# Introduction
This is a concept design for an IOT application that is based on using the raspberry pi (with sensehat) as an IOT device, sending the data to a MQTT server (Mosquitto), and using the thingspeak to 
1. Control the sensor frequency update
2. Perform simple data analysis and weather prediction
3. Display custom visualization output with 48hr data trends

# Raspberry PI and Sensehat
Connect the sensehat to the raspberrypi and install the client application that pulls the readings (temperature, humidity, pressure) from the sensehat (found in client/mqtt_sensor.py). Configure the MQTT server address and port in the client application via environment variables or a .env file.

In this application, it will also poll the talkback api from thingspeak to get the sensor update frequency. The sensor update frequency is set by the user via the thingspeak dashboard. The client application will then update the sensor readings to the MQTT server based on the frequency.

Usage example, if you want the update frequency to be 20 seconds, you can add via the dashboard and send the command update_frequency:20, or use
curl -X POST https://api.thingspeak.com/talkbacks/{TALKBACK_ID}/commands.json?api_key={TALKBACK_API_KEY} -d "command_string=update_frequency:20"

# Middleware Mosquitto
The MQTT server is run as a docker instance. You can create the middleware by running docker compose up -d under the middleware folder (docker-compose.yml)

