import xml.etree.ElementTree as ET
import os.path

XMLFile = os.path.expanduser("~/.local/share/recently-used.xbel")

# Threshold is how many recently accessed files to look for to differentiate between sandbox/VM & real user
# If the recently accessed count is lower than the threshold, it's assumed to be a sandbox/VM
threshold = 10 

# Parse XML file & extract filenames & the respective application name that was used to open/view file
def extractElements(XMLFile):
    tree = ET.parse(XMLFile)

    root = tree.getroot()

    appFile = []

    for item in root.findall("./bookmark"):
        filePath = item.get("href")
    

        applicationHandle = item.find(".//{*}application")
        applicationName = applicationHandle.get("name")
    
        
        appFile.append(f"{applicationName}:{filePath}")

    return appFile

if __name__ == "__main__":
    elements = extractElements(XMLFile)
    if len(elements) < threshold:
        print(f"[!] Recently accessed file count is lower than set threshold! Possible sandbox/VM (file count: threshold): {len(elements)}:{threshold}")
    else:
        print(f"[+] Recently accessed file count is higher than set threshold. Possibly an active user (file count: threshold): {len(elements)}:{threshold}")
