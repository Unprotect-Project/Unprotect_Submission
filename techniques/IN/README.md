# *IN instruction*

## Authorship information
* Name or nickname: *omer872*
* Linkedin: *https://www.linkedin.com/in/omer-kahlon/*
* Email: *omerka189@gmail.com*
  
## Technique Information
* Technique title: IN
* Technique category: Sandbox Evasion
* Technique description: The IN instruction is a type of machine code instruction that is used to read data from an input port. This instruction can only be executed in privileged mode, such as in kernel mode, and an attempt to execute it in user mode will generate an exception. However, some virtual machine monitors, such as VMWare, use a special port called the VX port as an interface between the virtual machine monitor (VMM) and the virtual machine. If a malware executes the IN instruction in user mode on a VMWare virtual machine, it will not generate an exception, since the VX port allows the instruction to be executed without triggering an exception. This behavior can be used by the malware to detect the presence of a VMWare virtual machine.


## Additional resources
* https://www.kea.nu/files/textbooks/humblesec/practicalmalwareanalysis.pdf (Chapter 17)
