import inotify.adapters
import psutil

def main():
    i = inotify.adapters.Inotify()

    i.add_watch("/tmp")

    for event in i.event_gen(yield_nones=False):
        (_, type_names, path, filename) = event
        if "IN_CREATE" in type_names:
            fullPath = path + "/" + filename 
            # Testing to see if its a swp file that was created
            if fullPath.split("/")[-1].startswith(".") and fullPath.split("/")[-1].endswith(".swp"):
                newPath = path + "/" + fullPath.split("/")[-1][1:].replace(".swp", "")

            elif fullPath.split("/")[-1].startswith(".") and fullPath.split("/")[-1].endswith(".swx"):
                newPath = path + "/" + fullPath.split("/")[-1][1:].replace(".swx", "")

            while isOpen(fullPath) == True:
                pass
            
            f = open(newPath, 'r')
            data = f.readlines()
            print(f"[+] Contents of {newPath}: {data}")


def isOpen(path):
    for proc in psutil.process_iter():
        try:
            for item in proc.open_files():
                if path == item.path:
                    return True
        except Exception:
            pass
    return False

if __name__ == '__main__':
    main()
