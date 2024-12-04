import json, sys, getpass, os, sqlite3

def parseExtensionsFile(path):
    with open(path) as f:
        data = json.load(f)
   
    uniqueExts = []
    for (i, x) in enumerate(data["addons"]):
        if x["name"] not in uniqueExts:
            uniqueExts.append(x["name"])

    if len(uniqueExts) > 0:
        print("[+] Extensions found! Possibly not a sandbox, continuing with checks...")
        print(f"[+] Discovered extensions: {uniqueExts}")
    else:
        print(f"[!] No extensions found! Possible sandbox: {uniqueExts}")

def findExtensionsFile():
    baseDir = "/home/" + getpass.getuser() + "/.mozilla/firefox/"
    print(f"[+] Searching {baseDir}")
    files = os.listdir(baseDir)
    for file in files:
        # "default-release" is typically the directory with all the juicy json & sqlite files
        if "default-release" in file: 
            print(f"[+] Searching {baseDir}{file} for addons json file...")
            fullDir = baseDir + file + "/addons.json"
            return fullDir

def checkSearchbarHistory(path):
    print(f"[+] Grabbing searchbar history from {path}...")
    conn = sqlite3.connect(path)
    cursor = conn.execute('''
    SELECT * FROM moz_formhistory
    ''')
    rows = cursor.fetchall()
    typedHist = []
    for row in rows:
        if "searchbar-history" in row:
            typedHist.append(row[2])
    
    if len(typedHist) > 0:
        print(f"[+] Typed searchbar history found! Potential user activity, possibly not a sandbox: {typedHist}")
    else:
        print(f"[!] No searchbar history found! Possible sandbox: {typedHist}")



if __name__ == '__main__':
    path = findExtensionsFile()
    parseExtensionsFile(path)

    # Building path to formhistory.sqlite file
    formPath = path.strip("addons.json") + "formhistory.sqlite"
    checkSearchbarHistory(formPath)
