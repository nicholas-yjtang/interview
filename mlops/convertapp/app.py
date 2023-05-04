from flask import Flask, jsonify, request
import pickle
from flask import send_file, abort
import os

app = Flask(__name__)
model_dir = "model/"

@app.route('/convert', methods=['POST'])
def convert():
    if (request.content_type != None):
        app.logger.info("Content-Type=" + request.content_type)
    else:
        app.logger.info("Content-Type is null")
    convert_module = __import__('convert')
    timestamp = convert_module.generateTimestamp()

    if (request.content_type == 'application/x-ipynb+json'):
        nb_filename = request.headers.get('X-Notebook-Filename', None)
        if (nb_filename == None):
            nb_filename = "unknown"
        unique_nb_filename = convert_module.createUniqueFilename(nb_filename, timestamp)
        convert_module.writeNotebook(unique_nb_filename, request.get_data())
    else:
        uploaded_file = request.files.get('file', None)
        nb_filename = uploaded_file.filename
        if (uploaded_file == None):
            app.logger.error("Uploaded file is null")
            abort (500, "Expecting a file")
        unique_nb_filename = convert_module.createUniqueFilename(nb_filename, timestamp)
        uploaded_file.save(convert_module.getNotebookFilename(unique_nb_filename))
    
    unique_py_filename = convert_module.createUniqueFilename(convert_module.removeExtension(nb_filename), timestamp)
    convert_module.convertNotebookToPy(unique_nb_filename, unique_py_filename)
    convert_module.runPyScript(unique_py_filename)
    unique_model_filename = "model_" + unique_py_filename + ".pkl"
    return jsonify({'model_name': unique_model_filename})

@app.route('/model', methods=['GET'])
def model():
    model_name = request.args.get('model_name', None)
    if (model_name == None):
        app.logger.error("Model name is null")
        abort (404, "Expecting a model name")
    #if file does not exist
    if (os.path.isfile(model_dir + model_name)):
        return send_file(model_dir + model_name, download_name=model_name)
    else:
        app.logger.error("File not found: " + model_name)
        return abort (404)

@app.errorhandler(500)
def catch_server_errors(e):
    app.logger.error(e)

if __name__ == '__main__':
    app.run(debug=True)
