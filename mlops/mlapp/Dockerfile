FROM python:3.10.11-bullseye
RUN mkdir -p /opt/app/model
WORKDIR /opt/app
COPY requirements.txt .
RUN pip install -r requirements.txt
COPY app.py .
EXPOSE 5000
CMD flask run --host=0.0.0.0