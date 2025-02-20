import hashlib
import sys

def detect_memory_tampering():
    original_hash = hashlib.md5(open(sys.argv[0], "rb").read()).hexdigest()
    current_hash = hashlib.md5(open(sys.argv[0], "rb").read()).hexdigest()
    if current_hash != original_hash:
        print("memory tampered")