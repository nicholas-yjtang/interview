FROM node:14

WORKDIR /app
COPY app.js .
COPY index.html .
COPY script.js .
COPY package.json .
RUN npm install

ENV FLASK_ENDPOINT=http://predict-app:5000/predict
EXPOSE 3000

CMD [ "npm", "start" ]