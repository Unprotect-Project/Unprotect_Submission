# How to contribute to the Unprotect Project?
The **Unprotect project** is an open-source database that aims to classify malware evasion techniques to strengthen the security in place, but also to understand how malware can bypass security mechanisms. This is a handy resource for the red, blue, and purple teamer.

This project is **community-centric** so that everyone can contribute to the database. The purpose of this repository is to provide a simple way for the community to contribute to the project. For each contributor, we will add your name in the [contributor's section](https://search.unprotect.it/about/).  

Before writing a proposal, we recommend that you review an [example](https://search.unprotect.it/technique/kill-process/).

To add a technique, you can fork this repository, create a folder in the [techniques section](https://github.com/fr0gger/Unprotect_Submission/tree/main/techniques) containing the name of the technique, and add the details. You have a sample model available [here](https://github.com/fr0gger/Unprotect_Submission/tree/main/techniques/template_description). Once you've added your technique, you can PR.

More details on the process of adding, modifying, or updating a technique can be found below.

## Adding a new technique to the database
To contribute, you can send a pull request to this repository containing the title of the technique in the PR and including the following. You can also have a look to the [template description](https://github.com/fr0gger/Unprotect_Submission/blob/main/techniques/template_description/description_template.md).

### 1 - Authorship information 
* Name or Pseudo (required)
* Twitter handle (not required)
* Website (not required) 
* Linkedin profile (not required)
* Email address (not required)

### 2 - Technique Information (required)
Each submission should include several pieces of information to be reviewed:
* Technique title (required): the techniques you want to add with a minimum of words
* Technique category (required): add the category on which your technique is based. Check the [list](https://search.unprotect.it/map)
* Technique description (required): iInclude as much detail as possible about your technique. Don't worry about grammar, the Unprotect team will review the submission.
* Additional ressources: include any additional resources relevant to the techniques.

### 3 - Code snippet (not required but highly recommended)
* For each technique in the database, we try to document it with a functional POC. It is highly recommended to add it if you have it. The Unprotect team will review and test the code.
* Code can be written in any language (C/C++, Python, Golang, Powershell, ASM, Delphi...)
* You can add a small description at the top to mention any specific information such as the library required to run.
* If you are reusing the code from elsewhere, please add a comment at the beginning of your code that includes the original source.

### 4 - Detection Rules (not required but highly recommended)
The detection rules part is particularly important to help the community defend itself against these techniques. Although it is not always possible to create detection rules, we strongly encourage you to do your best to add them.
* Yara rules: Please add the Yara rules related to your technique. If it's yours, add your name in the meta, otherwise keep the original authorship.
* Sigma rules: Please add the Sigma rules related to your technique. If it's yours, add your name in the meta, otherwise keep the original authorship.
* Capa rules: Please add the Capa rules related to your technique.If it's yours, add your name in the meta, otherwise keep the original authorship.

## Modifying a technique 
Sometimes you may have more details on a specific technique or you may notice an error somewhere. You can also have snippets or detection rules.

Please add your modification including the following information:

### 1 - Authorship information

### 2 - Title of the techniques to modify

### 3 - New Description (if required)

### 4 - Code snippet (if you have it)

### 5 - Detection rules (if you have it) 

## Thanks for your contribution!
We created this project to help the infosec community. We hope you like it because we put a lot of effort into it. We have more work in the pipeline and if you're interested, we recommend that you stay on top of future releases by following us:

* Thomas Roccia [@fr0gger_](https://twitter.com/fr0gger_)
* Jean-Pierre Lesueur [@darkcodersc](https://twitter.com/DarkCoderSc)

In the future, we would like to thank our contributors and we are planning some goodies. ;) 

**You can also send greetings to us if you like this project. <3**

