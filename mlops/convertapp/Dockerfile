FROM python:3.10.11-bullseye
RUN mkdir -p /opt/app
WORKDIR /opt/app
COPY app.py convert.py requirements.txt ./
RUN pip install -r requirements.txt
EXPOSE 5000
CMD flask run --host=0.0.0.0

