# Killing Windows Event Log (Phant0m)

## Authorship Information
* Name: Halil Dalabasmaz
* Website: artofpwn.com
* Twitter: https://twitter.com/hlldz
* Linkedin: https://www.linkedin.com/in/hlldz
  
## Technique Information
* Technique Title: Killing Windows Event Log (Phant0m)
* Technique Category: Defense Evasion [Mitre]
* Technique Description: Svchost is essential in the implementation of so-called shared service processes, where a number of services can share a process in order to reduce resource consumption. Grouping multiple services into a single process conserves computing resources, and this consideration was of particular concern to NT designers because creating Windows processes takes more time and consumes more memory than in other operating systems, e.g. in the Unix family. This means briefly that on Windows operating systems svchost.exe manages the services and services are actually running under svchost.exe’s as threads. Phant0m targets the Event Log service and finding the process responsible for the Event Log service, it detects and kills the threads responsible for the Event Log service. Thus, while the Event Log service appears to be running in the system (because Phant0m didn't kill process), it does not actually run (because Phant0m killed threads) and the system does not collect logs.

## Additional resources
* https://github.com/hlldz/Phant0m
