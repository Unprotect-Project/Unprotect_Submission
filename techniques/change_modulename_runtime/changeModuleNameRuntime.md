# Change module name at runtime

## Authorship Information
* Name: Alex Schwarz
* Website: 
* Twitter:
* Linkedin:
  
## Technique Information
* Technique Title: Change Module Name at Runtime
* Technique Category: Process Manipulation
* Technique Description: You can change the name of the current process or any of its modules at runtime. This is achieved by accessing the process PEB's member 'Ldr', in particular it has a member 'InOrderMemoryLinks' which we can iterate through to get a list of the processes modules. On each iteration we get a PLDR_DATA_TABLE_ENTRY structure to work with which contains a member 'UNICODE_STRING FullDllName', which can be overwritten with our new module name.

## Code Snippets
* changeModuleNameRuntime.cpp
