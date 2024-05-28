# Process Ghosting

## Authorship Information
* Name: 一半人生
* Website: https://github.com/TimelifeCzy
* Twitter:
* Linkedin:
  
## Technique Information
* Technique Title: Process Ghosting
* Technique Category: Process Manipulating
* Technique Description: Process Ghosting is a technique used to bypass detection by manipulating the executable image when a process is loaded. Windows attempts to prevent mapped executables from being modified. Once a file is mapped into an image section, attempts to open it with FILE_WRITE_DATA (to modify it) will fail with ERROR_SHARING_VIOLATION. Deletion attempts via FILE_DELETE_ON_CLOSE/FILE_FLAG_DELETE_ON_CLOSE fail with ERROR_SHARING_VIOLATION …

## Code Snippets
* process_ghosting.cpp
