# Technique Name: **Checking for Virtualization-Specific Files**

## Author Information

- Nickname: **weird raven**
- First Name: Sadoc
- Last Name: ADONON
- GitHub: https://github.com/weirdraven
- Twitter: https://x.com/sadocadonon

## Technique Information

- Technique Category: **Sandbox Evasion**
- Technique Tags: brand of the CPU, Hypervisor, virtualization, plateforms, KVM, Microsoft Hv, Hyper V, VMware, VirtualBox, QEMU, Xen, CPU flags
- Technique General Detail: **Virtual machines often leave traces in the filesystem, such as specific drivers or configuration files.**

```
Virtual machines (VMs) often leave traces in the filesystem, such as specific drivers, configuration files,
or hardware identifiers. Checking for these files can help determine if a system is running in a
virtualized environment.
```

* Technique Platform Specific Detail: Linux



@Linux:
```
This technique detects a virtual machine (VM) by checking for the presence of specific files
in the system that are commonly associated with virtualization platforms (e.g., VMware, VirtualBox, QEMU).
These files often contain identifiable strings (like vendor names) that reveal whether
the system is running inside a VM.
```


## Additional Resources: Optional


- [Virtualization-Specific Files](https://github.com/weirdraven/LAB/tree/main/Reverse%20engineering/VM%20Detect#8-checking-for-virtualization-specific-files)
