FROM ubuntu:20.04
RUN apt update && DEBIAN_FRONTEND=noninteractive TZ=Etc/UTC apt install -y \
    python3 \
    python3-pip \
    python3-dev \
    libpq-dev \
    build-essential
RUN pip3 install --upgrade pip
RUN mkdir /opt/bridge
WORKDIR /opt/bridge
COPY requirements.txt .
COPY bridge.py .
RUN pip3 install -r requirements.txt
CMD ["python3", "bridge.py"]
