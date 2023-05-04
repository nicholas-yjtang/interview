import nbformat
from nbconvert import PythonExporter
import pickle
import logging
import argparse
from argparse import ArgumentParser
import time
import os
import shutil
import sys

notebook_dir = 'notebook/'
script_dir = 'script/'
model_dir = 'model/'

def makeDir(dir:str):
    if not os.path.exists(dir):
        os.makedirs(dir)

def getNotebookFilename(notebook_filename:str):
    makeDir(notebook_dir)
    return notebook_dir + notebook_filename + '.ipynb'

def writeNotebook(notebook_filename:str, data:bytes):
    makeDir(notebook_dir)
    with open(notebook_dir + notebook_filename + '.ipynb', 'wb') as f:
        f.write(data)

def convertNotebookToPy(notebook_filename:str,script_filename:str):
    # Load the Jupyter notebook from file
    makeDir(notebook_dir)
    makeDir(script_dir)
    notebook_filename = notebook_dir + notebook_filename
    script_filename = script_dir + script_filename
    with open(notebook_filename + '.ipynb', 'r') as f:
        nb = nbformat.read(f, as_version=4)

    # Create a PythonExporter instance
    exporter = PythonExporter()

    # Convert the notebook to a Python script
    py_script, _ = exporter.from_notebook_node(nb)
    # Remove the matplotlib inline command that displays and blocks
    py_script = py_script.replace('.show(', '  #.show(')
    py_script = py_script.replace('.imshow(', '  #.imshow(')
    with open(script_filename + '.py', 'w') as f:
        f.write(py_script)

def runPyScript(script_filename:str):
    makeDir(model_dir)
    sys.path.append(script_dir)
    if (not os.path.isfile(script_dir+ script_filename + '.py')):
        print('File not found: ' + script_filename + '.py')
        return
    module_name = script_filename.replace(".py", "")
    print('module_name: ' + module_name)
    notebook_module = __import__(module_name)
    # create a file and write the model to it
    with open (model_dir + 'model_' + script_filename + '.pkl', 'wb') as f:
        pickle.dump(notebook_module.model, f)
    sys.modules.pop(module_name)

def generateTimestamp():
    return str(round(time.time() * 1000))

def removeExtension(filename:str):
    index = filename.find('.')
    if (index != -1):
        filename = filename[:index]
    return filename

def createUniqueFilename(filename:str, timestamp:str):
    # Remove the extension from the filename
    filename = removeExtension(filename)
    return filename + '_' + timestamp

if __name__ == '__main__':
    parser = ArgumentParser(description='Convert a Jupyter notebook to a Python script and export a scikit-learn model to a pickle file')
    parser.add_argument('notebook', type=str, help='input Jupyter notebook filename')
    parser.add_argument('script', type=str, help='output Python script filename')
    args = parser.parse_args()
    timestamp = generateTimestamp()
    args.notebook = removeExtension(args.notebook)
    if (os.path.isfile(args.notebook + '.ipynb')):
        shutil.copyfile(args.notebook + '.ipynb', getNotebookFilename(args.notebook))
    args.script = createUniqueFilename(args.script, timestamp)
    convertNotebookToPy(args.notebook, args.script)
    runPyScript(args.script)