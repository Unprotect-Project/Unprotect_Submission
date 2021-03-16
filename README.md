# Unprotect Submission
The Unprotect Project is an open-source database that aims to classify the malware evasion techniques to strenghten the security in place but also understand how malware can bypass security mechanisms. This is also a handy resource for red teamer. For every contributors we will add your name in the contributor section [here](https://search.unprotect.it/about/). 

This project is community centric so everyone can contribute to the database. 

## Adding a new technique to the database
To contribute you can send a pull request to this repository containing the technique title in the PR and including the following elements:

1 - Authorship information 
* Name or Pseudo (required)
* Twitter handle (not required)
* Website (not required) 
* Linkedin profile (not required)
* Email address (not required)

2 - Technique Information (required)
Every submission must include several information to be reviewed:
* Technique title (required): the techniques you want to add with minimal words
* Technique category (required): add the category where your technique rely. Check the list [here](https://search.unprotect.it/map)
* Technique description (required): include as most as possible detail about your technique. Don't worry about the grammar, the Unprotect team will review the submission. 
* Additional ressources: include any additional resources that are relevant to the techniques.

3 - Code snippet (not required but higly recommended)
* For each techniques in the database we try to document it with a working POC. It is higly recommended to add it if you have it. The Unprotect team will review and test the code. 
* The code can be written in any languages (C/C++, Python, Golang, Powershell, ASM, Delphi...)
* You can add a small description on the top to mention any specific information such as library required to work. 
* If you reuse the code from somewhere else, please add a comment at the beginning of your code that includes the original source.

4 - Detection Rules (not required but higly recommended)
The detection rules part is particularly important to help the community to defend against those techniques. While it is not always possible to create a detection rules, we highly encourage to do your best to add them. 
* Yara rules: Please add the yara rules related to your techniques. If it is your add your name in the meta otherwise keep the original authorship. 
* Sigma rules: Please add the sigma rules related to your techniques. If it is your add your name in the meta otherwise keep the original authorship. 
* Capa rukes: Please add the sigma rules related to your techniques. If it is your add your name in the meta otherwise keep the original authorship.

## Modifying a techniques 
Sometimes you might have more details in a specific techniques or you might notice an error somewhere. You might also have a code snippets or a detection rules. 

Please add your modification including the following information:

1 - Authorship information

2 - Title of the techniques to modify

3 - New Desccription (if required)

4 - Code snippet (if you have it)

5 - Detection rules (if you have it) 

## Thanks for your contribution!
We created this project to help the infosec community. We hope that you like it as we put a lot of effort to it. We have more work in the pipe and if you are interested about it, we recommend you to stay up to date about furture releases by following us: 

* Thomas Roccia [fr0gger_](https://twitter.com/fr0gger_)
* Jean-Pierre Lesueur [darkcodersc](https://twitter.com/DarkCoderSc)

You can also send us greeting if you like this project. <3 

