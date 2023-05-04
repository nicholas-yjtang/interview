# Scenario

You were just given the jupyter notebook of one of your data scientist, who has created a model based on his analysis. Using this notebook as a start, create a pipeline that deploys the model, and have a web application call this deployed model for predictions. You are given this notebook, iris.ipynb

# Solution

```mermaid
flowchart LR
    A[Jupyter Notebook] -->|Convert| B[Python Code and Model file]
    B --> |Download| C[Model file]
    C --> |Upload| D[ML Web Service]
```

This is a standalone solution if services are to be consumed internally. Created a bash script (run.sh) that will perform the creation and update of a usable machine learning model, namely
1. Takes the jupyter notebook, and uploads it to the conversion web service that converts it to python code, and utilizing this python code to generate a portable ML model
2. Download this ML model from the conversion web service
3. Upload this model to a running machine learning web service will update its currently serving model

```mermaid
C4Container
title Container diagram for deploying and serving the machine learning model

Person(user, User, "A user of the web application", $tags="v1.0")
System(build, "Build System", "The system that builds the necessary models for the end user of the web application")
Container_Boundary(c1, "Services providing ML") {
    Container(web_app, "Web Application", "Javascript, NodeJS", "Delivers the ml results to end users upon receiving sepal and petal information via a form")
    Container(ml_app, "Model Web Service", "Python, Flask", "Returns the results of the model upon being sent the sepal and petal information (width and length)")
    Container(conversion_app, "Conversion Web Service", "Python, Flask", "Converts a jupyter notebook into a serialized model")

    Rel(web_app, ml_app, "Uses", "JSON/HTTP")
}

Rel(user, web_app, "Uses", "HTTP")
Rel(build, ml_app, "Uploads model", "HTTP")
Rel(build, conversion_app, "Convert notebook", "HTTP")
Rel(conversion_app, build, "Download the ML model", "HTTP")

```

The user interacts with the containers in the following manner
1. User will input the relevant sepal/petal length/width via the web app
2. The web app will invoke the ml app at the backend via REST
3. The ml app expects a json object to be posted to its url (/prediction)
4. Upon being called with the relevant sepal_width, sepal_length, petal_width, petal_length, it will return the predicted class, along with the probability, in a json format
6. The web application will display the result of the predicted cclass and probabilities to the end user

# Instructions for Linux
In order to recreate this solution, ensure you are running in a linux console, and have installed docker

1. Clone this repository
2. To build the relevant web services, run docker compose build
3. Use run.sh to simulate the conversion and upload process (upload iris.ipynb, download the model, update the ml web service), call the web app backend with curl
4. Browse to the web application (localhost:[port]) to test it further with other values

# Instructions for Windows
In order to recreate this solution, ensure you are running in a powershell console, and have already installed docker desktop. Make sure you enable WSL

1. Clone this repository
2. Build the relevant web services by running docker compose build
3. Use run.ps1 in the powershell console to create and upload the model, and calling the webapp backend via Web-Request
4. Browse to the web application (localhost:[port]) to test it further with other values