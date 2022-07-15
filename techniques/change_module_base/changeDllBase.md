# Change module base address at runtime

## Authorship Information
* Name: Alex Schwarz
* Website: 
* Twitter:
* Linkedin: [https://www.linkedin.com/in/alex-schwarz](https://www.linkedin.com/in/alex-schwarz-94248269/)
  
## Technique Information
* Technique Title: Change Module Base Address at Runtime
* Technique Category: Process Manipulation
* Technique Description: You can change the 'DllBase' of a module at runtime. This can trick debugging and analysis tools such as IDA or Cheat Engine into thinking a module's base is actually at some other address which you can specify. This is achieved by accessing the process PEB's member 'Ldr', in particular it has a member 'InOrderMemoryLinks' which we can iterate through to get a list of the processes modules. On each iteration we get a PLDR_DATA_TABLE_ENTRY structure to work with which contains a member PVOID 'DllBase', which can be overwritten with our new module base address.

## Code Snippets
* changeModuleDllBase.cpp
