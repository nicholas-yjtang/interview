Scenario

You were just given the jupyter notebook of one of your data scientist, who has created a model based on his analysis. Using this notebook as a start, create a pipeline that deploys the model, and have a web application call this deployed model for predictions. You are given this notebook, iris.ipynb

Solution

```mermaid
flowchart LR
    A[Jupyter Notebook] -->|Convert| B[Python Code]
    B --> |Output| C[Model file]
    C --> |Create| D[Flask Microservice, Web application]
```

```mermaid
C4Container
title Container diagram for deploying and serving the machine learning model

Person(user, User, "A user of the web application", $tags="v1.0")

Container_Boundary(c1, "Services providing ML") {
    Container(web_app, "Web Application", "Javascript, NodeJS", "Delivers the ml results to end users upon receiving sepal and petal information via a form")
    Container(ml_app, "Model Web Service", "Python, Flask", "Returns the results of the model upon being sent the sepal and petal information (width and length)")
    Rel(web_app, ml_app, "Uses", "JSON/HTTP")
}

Rel(user, web_app, "Uses", "HTTP")

```

Created a bash script (build.sh) that will build all the relevant components, namely
1. Using convert.py, that will convert the ipynb to a python file, suppressing the plots created by commenting them out in the final python file
2. Add lines to the end of the converted python file (output_model.py) that will export the model to a pickle file format
3. Create a flask container application (app.py) that will load this model file via docker build
4. Create the web application container that will use the flask container via docker build
5. Compose both containers via docker compose

The user interacts with the containers in the following manner
1. User will input the relevant sepal/petal length/width via the web app
2. The web app will invoke the ml app at the backend via REST
3. The ml app expects a json object to be posted to its url (/prediction)
4. Upon being called with the relevant sepal_width, sepal_length, petal_width, petal_length, it will return the predicted class, along with the probability, in a json format
6. The web application will display the result of the predicted cclass and probabilities to the end user