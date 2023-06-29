#!/bin/bash

# Install required packages
apt-get update
apt-get install -y python3-pip

# Install Python packages
pip install -r requirements.txt

# Create a directory for the MQTT Sensor service
mkdir -p /opt/mqtt_sensor

# Copy the Python script to the service directory
cp mqtt_sensor.py /opt/mqtt_sensor/mqtt_sensor.py
cp .env /opt/mqtt_sensor/.env

# Create the systemd service file
cat <<EOF > /etc/systemd/system/mqtt_sensor.service
[Unit]
Description=MQTT Sensor Service
After=network.target

[Service]
User=pi
ExecStart=/usr/bin/python3 /opt/mqtt_sensor/mqtt_sensor.py
WorkingDirectory=/opt/mqtt_sensor
Restart=always

[Install]
WantedBy=multi-user.target
EOF

# Reload systemd and enable/start the service
systemctl daemon-reload
systemctl enable mqtt_sensor.service
systemctl start mqtt_sensor.service