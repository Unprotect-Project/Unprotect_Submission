import subprocess
import importlib

packages = ['sentence_transformers', 'pickle', 'termcolor', 'Pyfiglet']

for package in packages:
  try:
      importlib.import_module(package)
  except ImportError:
      subprocess.run(['python', '-m', 'pip', 'install', package, '-q', '--no-input', '--no-python-version-warning'])

import pyfiglet

pyfiglet.print_figlet("Byte", font="poison",colors="red", justify="center")
pyfiglet.print_figlet("Viper", font="poison",colors="green", justify="center")

from sentence_transformers import SentenceTransformer, util
import pickle

model_name = 'nq-distilbert-base-v1'
model = SentenceTransformer(model_name)

with open('opcode_embeddings.pkl', 'rb') as pkl:
    df_trained = pickle.load(pkl)

def getopcode(opcode):
    saved_embeddings = list(df_trained['embedding'])
    hits = util.semantic_search(model.encode(opcode, convert_to_tensor=True), saved_embeddings, top_k=1)
    return str(df_trained.at[hits[0][0]['corpus_id'], 'Opcode']).replace(',','|')
