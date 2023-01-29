# Domain Fronting

## Authorship Information

## Technique Information
* Technique Title: Domain Fronting
* Technique Category: Defense Evasion [Mitre] T1090.004

* Technique Description: Domain fronting is a technique used to hide the true destination of internet traffic. It may be used to hide the real destination of an offensive payload or is could be used to bypass censorship or any form of network restriction. The technique may be used through CDN infrastructure or on any infrastructure that perform separation between SSL and http backend.

It involves SSL/TLS connection since it abuse of the destination requested in the SNI (Server Name Indication) field at SSL level at "Front"  and the real hosname requested by the HOST header at the HTTP level. In clear you declare one destination at SSL level and another one at HTTP level. From an defender point on view you see only the SSL destination in the firewall logs and not the real final destination.

Additionally, some other headers may be used to facilitate domain fronting like "X-Forwarded-Host" and "X-Originating-URL". But these headers may vary depending on the implementation.

Such techniques were exploited by groups like APT29. Hovewer, some cloud providers like AWS, Google Cloud, and Cloudflare among others, have started to detect and block domain fronting attempts. Since then a new technics named domain hiding as been discovered. This is a complementary technique that as been presented by Erik Hunstad at defcon 2020. This techniques use the ESNI header in the TLS3.1 version.


