const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const axios = require("axios");
const FormData = require("form-data");

const app = express();
app.use(bodyParser.json());
app.use(cors());

const port = 3000;
const flaskEndpoint = process.env.FLASK_ENDPOINT;

app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html");
});

app.get("/script.js", (req, res) => {
  //set the mimetype to javascript
  res.setHeader("Content-Type", "text/javascript");
  res.sendFile(__dirname + "/script.js");
});

app.post("/predict", async (req, res) => {
  try {
    const inputData = req.body;
    const jsonData = JSON.stringify(inputData);  
    const response = await axios.post(flaskEndpoint, inputData);
    res.send(response.data);
  } catch (error) {
    console.log ("error:" + error)
    res.status(500).send("Unable to predict the species");
  }
});

app.listen(port, () => {
  console.log(`App listening at http://localhost:${port}`);
});