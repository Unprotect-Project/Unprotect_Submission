# *FontAbuse*

## Authorship information
* Name or nickname (required): Maldork
* Website: https://www.maldork.com
* Linkedin: https://www.linkedin.com/in/frank-galambos/
  
## Technique Information
* Technique title (required): FontEnumeration
* Technique category (required): Defense Evasion

* Technique description (required): Malware will enumerate fonts based on size and space between characters, and color. Then 
set its preferences using functions such as SetBkMode, SetBKColor, SetCharset, SetPollyFillMode, SetBTextColorSetFont, 
SetPixel, TWin32WSCustomListView.SetColor, and more. It will modify registry values and search  
through keys such as:

HKCU\SOFTWARE\Microsoft\Windows\CurrentVersion\Themes\Personalize\AppsUseLightTheme
HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\LanguagePack\SurrogateFallback\Segoe UI

This could be for querying the host's set language and changing it, then manipulating interface settings in order to drop or 
run malicious code. With samples I've ran into, I've seen the Russian language attempting to be set. 
