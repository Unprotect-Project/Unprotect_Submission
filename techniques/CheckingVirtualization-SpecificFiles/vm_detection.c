#include <stdio.h>
#include <string.h>

/**
 * Checks for files that indicate a virtualized environment.
 * Returns 1 if a VM is detected, otherwise 0.
 */
int check_for_vm() {
    // Files commonly associated with virtualization
    const char *files[] = {
        "/sys/class/dmi/id/product_name",  // Product name (e.g., "VMware Virtual Platform")
        "/sys/class/dmi/id/sys_vendor",   // System vendor (e.g., "QEMU", "VMware, Inc.")
        "/proc/scsi/scsi",                // SCSI controllers (some hypervisors leave traces here)
        "/proc/cpuinfo",                  // CPU flags (may contain "hypervisor")
        NULL
    };

    for (int i = 0; files[i] != NULL; i++) {
        FILE *file = fopen(files[i], "r");
        if (file) {
            char content[128];
            fgets(content, sizeof(content), file);
            fclose(file);

            // Check for known hypervisor signatures
            if (strstr(content, "VMware") || 
                strstr(content, "VirtualBox") || 
                strstr(content, "QEMU") || 
                strstr(content, "Xen") || 
                strstr(content, "KVM") ||
                strstr(content, "hypervisor")) {
                return 1;  // VM detected
            }
        }
    }
    return 0;  // No VM detected
}

int main() {
    if (check_for_vm()) {
        printf("[!] Virtual machine detected.\n");
    } else {
        printf("[+] No signs of virtualization found.\n");
    }
    return 0;
}
