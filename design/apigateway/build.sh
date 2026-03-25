#!/bin/bash
if [[ ! -f models/fraud_detector_v1.pkl ]]; then
    echo "Model file not found. Please run the training script first."
    python generate_frauddetector.py
fi
if [[ ! -f models/fraud_detector_v1.pkl ]]; then
    echo "Model file still not found after training. Exiting."
    exit 1
fi
if [[ ! -f .env.kong ]]; then
    echo ".env.kong file not found. Please create it with the necessary JWT configurations."
    exit 1
fi
source .env.kong
cp -f kong/kong.yml.template kong/kong.yml
sed -i -E "s/\{JWT_KEY\}/${JWT_KEY}/g" kong/kong.yml
sed -i -E "s/\{JWT_SECRET\}/${JWT_SECRET}/g" kong/kong.yml
sed -i -E "s/\{JWT_CONSUMER\}/${JWT_CONSUMER}/g" kong/kong.yml
sed -i -E "s/\{JWT_ALGORITHM\}/${JWT_ALGORITHM}/g" kong/kong.yml
docker build -t fraud-detector:latest .