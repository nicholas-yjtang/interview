#!/bin/bash
curl localhost:5000/predict -d '{"sepal_length": 5.1, "sepal_width": 3.5, "petal_length": 1.4, "petal_width": 0.2}' -H "Content-Type: application/json"
curl -X POST localhost:3000/predict -d '{"sepal_length": 5.1, "sepal_width": 3.5, "petal_length": 1.4, "petal_width": 0.2}' -H "Content-Type: application/json"