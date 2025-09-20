import ctypes

def detect_api_hooks():
    kernel32 = ctypes.windll.kernel32
    original_bytes = ctypes.create_string_buffer(5)
    kernel32.ReadProcessMemory(kernel32.GetCurrentProcess(), kernel32.IsDebuggerPresent, original_bytes, 5, None)
    if original_bytes.raw[0] == 0xE9:
        print("hook detected")