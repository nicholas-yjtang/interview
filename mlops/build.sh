#!/bin/bash
pip install -r requirements.txt
python convert.py iris.ipynb output_model.py model.pkl
python output_model.py
docker build -t iris-predictapp .
docker tag iris-predictapp:latest iris-predictapp:0.1
pushd webapp
docker build -t iris-webapp .
docker tag iris-webapp:latest iris-webapp:0.1
popd
docker compose up -d