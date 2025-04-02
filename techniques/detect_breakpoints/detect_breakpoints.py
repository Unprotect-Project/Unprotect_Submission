import ctypes
import struct

def detect_breakpoints():
    context = ctypes.create_string_buffer(0x4C)
    context_ptr = ctypes.byref(context)
    context_offset = struct.calcsize("Q") * 6
    ctypes.windll.kernel32.RtlCaptureContext(context_ptr)
    dr0, dr1, dr2, dr3 = struct.unpack_from("4Q", context.raw, context_offset)
    if dr0 or dr1 or dr2 or dr3:
        print("detected hardware breakpoint")