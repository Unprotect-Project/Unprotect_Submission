# *Internet Connectivity Check*

## Authorship information
* Name or nickname (required): *Serhii*
* Twitter: https://twitter.com/semelnyk
* Linkedin: https://www.linkedin.com/in/serhii-melnyk
* Email: serhiimelnyk@outlook.com
  
## Technique Information
* Technique title (required): Internet Connectivity Check
* Technique category (required): Sandbox Evasion
* Technique description (required): Malware often verifies internet connectivity to distinguish between being within a lab or sandbox environment versus a genuine system. This check allows malware to obscure its behavior from both human analysts and automated sandbox environments. Typically, this involves assessing whether the infected system is online. While many systems used by targeted victims have internet access, lab setups or sandboxes are often isolated from the internet. Typically, API calls necessary for implementing such functionality start with InternetConnectA, or HttpOpenRequestA and HttpSendRequestA, which facilitate the construction and transmission of HTTP requests. For instance, certain functions may return a value of 1 upon detecting a successful connection to a designated destination, and 0 otherwise.

## Additional resources
* https://sensei-infosec.netlify.app/forensics/windows/api-calls/2020/04/29/win-api-calls-1.html

## Code snippets
* Please add your code in separate files.

## Detection rules
* Please add your rules in separate files.
