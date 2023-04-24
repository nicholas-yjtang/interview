import argparse
import nbformat
from nbconvert import PythonExporter
import pickle

# Parse command line arguments
parser = argparse.ArgumentParser(description='Convert a Jupyter notebook to a Python script and export a scikit-learn model to a pickle file')
parser.add_argument('notebook', type=str, help='input Jupyter notebook filename')
parser.add_argument('script', type=str, help='output Python script filename')
parser.add_argument('pickle', type=str, help='output pickle filename for scikit-learn model')
args = parser.parse_args()

# Load the Jupyter notebook from file
with open(args.notebook, 'r') as f:
    nb = nbformat.read(f, as_version=4)

# Create a PythonExporter instance
exporter = PythonExporter()

# Convert the notebook to a Python script
py_script, _ = exporter.from_notebook_node(nb)
# Remove the matplotlib inline command
py_script = py_script.replace('.show()', '  # .show()')
# Add the code to export the scikit-learn model to a pickle file
py_script += '# Export the scikit-learn model to a pickle file\n'
py_script += 'import pickle\n'
py_script += 'with open("' + args.pickle + '", "wb") as f:\n'
py_script += '    pickle.dump(model, f)'
# Write the Python script to file
with open(args.script, 'w') as f:
    f.write(py_script)
