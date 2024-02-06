# *Runtime Function Decryption*

## Authorship information
* Name or nickname (required): *irfan_eternal*
* Twitter: https://twitter.com/irfan_eternal
* Website: https://irfan-eternal.github.io/

  
## Technique Information
* Technique title (required):  Runtime Function Decryption
* Technique category (required): Antivirus/EDR Evasion
* Technique description (required): This Technique is used to store the function body  in an Encrypted form . They will only be Decrypted just before execution of that code. And will be re-encrypted after that code has been executed. This Technique is used by SmokeLoader to evade from Anti-Virus and EDRs since the function body is in Encrypted form except at the time of Execution of Function . It aslo makes the static analysis of SmokeLoader harder 

## Additional resources
https://irfan-eternal.github.io/understanding-internals-of-smokeloader/#encrypted-function-code

## Code snippets
![Example](https://irfan-eternal.github.io/understanding-internals-of-smokeloader/stage2AfterFunctionDecryption.PNG)

The above image Shows an Example of this Technique. The last call to 40131a is wrapper for decryption_function, which will cause the code to be re-encrypted
