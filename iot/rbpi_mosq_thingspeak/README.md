# Introduction
This is a concept design for an IOT application that is based on using the raspberry pi (with sensehat) as an IOT device, sending the data to a MQTT server (Mosquitto), and using the thingspeak to 
1. Control the sensor frequency update
2. Perform simple data analysis and weather prediction
3. Display custom visualization output with 48hr data trends

# Raspberry PI and Sensehat
Connect the sensehat to the raspberrypi and install the client application that pulls the readings (temperature, humidity, pressure) from the sensehat (found in client/mqtt_sensor.py). Configure the MQTT server address and port in the client application via environment variables or a .env file.

