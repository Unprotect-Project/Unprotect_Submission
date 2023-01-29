# Domain Fronting

## Authorship Information
Myself :) probably other pentest guys

## Technique Information
* Technique Title: Domain member
* Technique Category: Sandbox Evasion

* Technique Description: This technique allows, without any API call, to determine if the host is member of an Active Directory Domain. Since the vast majority of the enterprise sandboxes are not member nor even simulating a join of an Active Directory domain, this technics permit to avoid execution of the malicious payload on the sandbox. The discrepancy is performed by looking into the environnements variable named "LoggonServer" and "ComputerName". In the case of a host logged in an active directory to a domain controller, this value contains the name of the logged in server. I case of a host not join to the domain, both variables contains the same hostname (with a preprend // for the loggonserver varialble). Since the entire data resides in the process memory, it is possible to validate this domain membership without any API calll in order not be detectable by any hooks.
