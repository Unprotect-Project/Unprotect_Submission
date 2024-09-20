# VBA Purging

## Authorship information
* Name or nickname (required): Sylvain Bruyere
* Twitter: https://twitter.com/sylvainbruyere
* Website: https://malva.re/
* Linkedin: https://www.linkedin.com/in/sylvainbruyere/
* Email: nospam@malva.re
  
## Technique Information
* Technique title (required): VBA Purging
* Technique category (required): Antivirus/EDR Evasion
* Technique description (required): VBA Purging is an obfuscation technique designed to evade detection mechanisms used in malware analysis. When a VBA macro is added to a Microsoft Office document, it is stored in two sections: the PerformanceCache (compiled VBA code) and the CompressedSourceCode (compressed VBA source code). In VBA Purging, the PerformanceCache (compiled code) is completely removed from the module stream, along with associated streams like _SRP_, which contain version-dependent compiled code data. Additionally, the MODULEOFFSET is set to 0 to indicate there is no compiled code.

By eliminating the PerformanceCache and its related components, VBA Purging prevents static analysis tools, antivirus programs, and YARA rules from detecting suspicious strings typically found in compiled VBA macros. The document retains its compressed VBA source code, but the compiled code, which many detection tools rely on, is no longer present. As a result, macros can still run using the decompressed source code, but security systems are less likely to detect them.

This technique is particularly useful for attackers as it significantly reduces detection rates in environments like VirusTotal, where purged documents show a much lower detection rate compared to non-purged versions​​.

## Additional resources
* https://blog.didierstevens.com/2020/06/22/vba-purging/
* https://cloud.google.com/blog/topics/threat-intelligence/purgalicious-vba-macro-obfuscation-with-vba-purging/?hl=en
* https://blog.nviso.eu/2020/02/25/evidence-of-vba-purging-found-in-malicious-documents/
* https://github.com/mandiant/OfficePurge
* https://beta-v1.malva.re/File/730a8401140edb4c79d563f306ca529e/Report
* https://beta-v1.malva.re/File/2433e76542036ab53b138a98eeda548a/Report

## Code snippets

## Detection rules
* FEYE_OLE_VBAPurged_2.yar