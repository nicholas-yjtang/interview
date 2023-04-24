from flask import Flask, jsonify, request
import pickle
import logging

app = Flask(__name__)

# Load the scikit-learn model from the saved pickle file
with open('model.pkl', 'rb') as f:
    model = pickle.load(f)

@app.route('/predict', methods=['POST'])
def predict():
    # Get the input data from the request JSON
    data = request.get_json()
    # Convert the input data to a 2D array
    X = [[data['sepal_length'], data['sepal_width'], data['petal_length'], data['petal_width']]]
    # Make a prediction using the loaded model
    y_pred = model.predict(X)
    # set the class to a string description
    predicted_class = ''
    predicted_probability = 0
    y_prob = model.predict_proba(X)
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
    result = {'class': predicted_class, 'probability':predicted_probability}
    # Return the prediction result as JSON
    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True)
    logging.getLogger().setLevel(logging.DEBUG)