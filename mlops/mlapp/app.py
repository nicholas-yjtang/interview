from flask import Flask, jsonify, request, abort
import pickle
import logging
import os

app = Flask(__name__)

model_dir = "model/"

def makeDir(dir:str):
    if not os.path.exists(dir):
        os.makedirs(dir)

def load_model():
    # Load the scikit-learn model from the saved pickle file
    try:
        with open( model_dir + 'model.pkl', 'rb') as f:
            return pickle.load(f)
    except Exception as e:
        app.logger.error(e)
    return None

prediction_model = load_model()

@app.route('/predict', methods=['POST'])
def predict():
    global prediction_model
    if prediction_model is None:
        abort(500, description="Model not loaded")
    # Get the input data from the request JSON
    data = request.get_json()
    # Convert the input data to a 2D array
    X = [[data['sepal_length'], data['sepal_width'], data['petal_length'], data['petal_width']]]
    # Make a prediction using the loaded model
    y_pred = prediction_model.predict(X)
    # set the class to a string description
    predicted_class = ''
    predicted_probability = 0
    y_prob = prediction_model.predict_proba(X)
    if y_pred[0] == 0:
        predicted_class = 'setosa'
        predicted_probability = y_prob[0][0]
    elif y_pred[0] == 1:
        predicted_class = 'versicolor'
        predicted_probability = y_prob[0][1]
    else:
        predicted_class= 'virginica'
        predicted_probability = y_prob[0][2]
    # Convert the prediction result to a dictionary
    app.logger.debug ("Predicted class: " + predicted_class + ", probability: " + str(predicted_probability))
    result = {'class': predicted_class, 'probability':float(predicted_probability)}
    # Return the prediction result as JSON
    return jsonify(result)

@app.route('/model', methods=['PUT'])
def model():
    global prediction_model
    uploaded_file = request.files.get('file', None)
    if (uploaded_file == None):
        if (request.content_type == 'application/octet-stream'):
            makeDir(model_dir)  
            uploaded_file = request.get_data()
            app.logger.debug ("Uploaded file size: " + str(len(uploaded_file)))
            writeToFile(model_dir + "model.pkl", uploaded_file)
            prediction_model = load_model()           
        else:
            abort(400, description="Invalid content type, expected application/octet-stream")
    else:
        makeDir(model_dir)
        uploaded_file.save(model_dir + "model.pkl")
        prediction_model = load_model()
    return "Model uploaded successfully"


@app.errorhandler(500)
def catch_server_errors(e):
    app.logger.error(e)        

def writeToFile(file:str, data:bytes):
    with open(file, 'wb') as f:
        f.write(data)

if __name__ == '__main__':
    app.run(debug=True)
    logging.getLogger().setLevel(logging.DEBUG)