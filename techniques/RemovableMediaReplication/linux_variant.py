'''
This code sample will detect when a USB drive/other removable media is inserted on a Linux system & enumerate the exact path where it is mounted, allowing an adversary to do other things such as enumerate the contents of that path for interesting files or replicate malware onto the removable media for lateral movement.

Author: github.com/1d8
'''

import pyudev, time, os


def getMountPath(devPath):
    #print(f'[+] Grabbing mount path for {devPath}')
    time.sleep(20) # We sleep for a bit to give the /proc/mounts file time to refresh & contain mount path for devpath
    try:
        with open("/proc/mounts", "r") as mFile:
            #print('[+] Reading /proc/mounts')
            for line in mFile:
                parts = line.split()
                if devPath.strip() in parts:
                        #print(f'[+] Mount path found for {devPath}: {parts[1]}') #parts[1] -> full file path
                        return parts[1]
    except:
        print("[!] Cannot open /proc/mounts!")
        
def getDevPath():
    print('[-] Waiting for USB device insertion...')
    context = pyudev.Context()

    monitor = pyudev.Monitor.from_netlink(context)
    monitor.filter_by('block')

    monitor.start()

    for device in iter(monitor.poll, None):
        if device.device_type in ('disk', 'partition'):
            device_node = device.device_node
            if device.action == 'add':
                print(f'[+] Device connected: {device_node}!')
                

                mntPath = getMountPath(device_node)
                if mntPath is not None:
                	print(f'[+] Mount path for {device_node}: {mntPath}')

def main():
	getDevPath()

if __name__ == '__main__':
	main()
