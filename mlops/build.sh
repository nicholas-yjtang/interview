#!/bin/bash
SCRIPT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
pushd $SCRIPT_DIR
pushd convertapp
docker build -t iris-convertapp .
docker tag iris-convertapp:latest iris-convertapp:0.1
popd
pushd mlapp
docker build -t iris-mlapp .
docker tag iris-mlapp:latest iris-mlapp:0.1
popd
pushd webapp
docker build -t iris-webapp .
docker tag iris-webapp:latest iris-webapp:0.1
popd
docker compose up -d
popd
