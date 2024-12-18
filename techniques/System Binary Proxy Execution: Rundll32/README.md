# Technique Name: System Binary Proxy Execution: Rundll32

## Author Information: Dino Dunn

- Nickname: Dino 
- First Name: Dino 
- Last Name: Dunn
- GitHub: https://github.com/db0109
- LinkedIn: https://www.linkedin.com/in/dino-dunn-cyber/

## Technique Information

- Technique Category:  Defense Evasion [MITRE]/ System Binary Proxy Execution Rundll32
- Technique Tags: #Defense Evasion #rundll32.exe {DLLname DLLfunction}
- Technique General Detail: Adveraries abused rundll32.exe to proxy executtion of malicious code, the goal is to bypass security tools by utilizing a legitimate process. for our example we will run a simple .dll file that displays an Ascii cat as a proof of concept. 

```
> Utilizing RunDLL32.exe a trusted windows binary, attackers are able to execute code within a potentially malicious .dll file. This can allow attackers to bypass security tools as it is being run with a trusted windows binary. 

~Markdown Supported~
```rundll32.exe evil.dll, run'''

* Technique Platform Specific Detail: Optional

@Windows:
```
> Start with creating a .dll file with malicious code in it. Our example .dll file is going to produce an Ascii cat but can be used for any number of malicious purpouses. 

~Markdown Supported~
```


- [Resource 1]https://github.com/PacktPublishing/Malware-Development-for-Ethical-Hackers/blob/main/chapter01/04-pefile-exe-dll/hack4.c  (You can find a precompiled version of the file here if you don't want to compile it https://github.com/PacktPublishing/Malware-Development-for-Ethical-Hackers/blob/main/chapter02/01-traditional-injection/evil.dll)
- [Resource 2]https://hadess.io/system-binary-proxy-execution/
- ...
- [Resource n]https://attack.mitre.org/techniques/T1218/011/ 
- [Resource 4] rundll32.exe evil.dll, run

