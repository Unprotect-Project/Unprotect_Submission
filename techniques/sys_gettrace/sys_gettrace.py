import sys

def debugger_detect():
    if sys.gettrace():
        print("debugger detected")