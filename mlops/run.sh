#!/bin/bash
convert_id=$(docker ps -f name=convert-app --format "{{.ID}}")
convert_port=$(docker port $convert_id | grep 0.0.0.0 | cut -d ":" -f 2)
model_name=$(curl -s -X POST localhost:$convert_port/convert -F 'file=@iris.ipynb' | jq '.model_name' | tr -d '"')
echo model_name: $model_name
curl -s -X GET localhost:$convert_port/model?model_name=$model_name -o model.pkl
predict_id=$(docker ps -f name=predict-app --format "{{.ID}}")
predict_port=$(docker port $predict_id | grep 0.0.0.0 | cut -d ":" -f 2)
curl -s -X PUT localhost:$predict_port/model -F 'file=@model.pkl'
webapp_id=$(docker ps -f name=web-app --format "{{.ID}}")
webapp_port=$(docker port $webapp_id | grep 0.0.0.0 | cut -d ":" -f 2)
echo 
curl -X POST localhost:$webapp_port/predict -d '{"sepal_length": 5.1, "sepal_width": 3.5, "petal_length": 1.4, "petal_width": 0.2}' -H "Content-Type: application/json"
echo