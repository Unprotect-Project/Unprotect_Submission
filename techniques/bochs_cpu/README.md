# bochs CPU evasion

## Authorship information
* Name: kernelwernel
* Website: https://github.com/kernelwernel

## Technique Information
* Technique title: bochs CPU oversights evasion
* Technique category: Sandbox evasion
* Technique description:  bochs has multiple oversights in its CPU emulation, which allows us to detect if we're running in a bochs emulator:
    - 1. bochs may have invalid CPU brands that don't exist.
    - 2. For AMD CPUs, the "p" in "processor" should be in capital, which bochs doesn't implement.
    - 3. AMD CPUs have easter eggs for their K7 and K8 CPUs ("IT'S HAMMER TIME"), but bochs does not implement this.

## Additional resources
* https://github.com/kernelwernel/VMAware
* https://pferrie.tripod.com/papers/attacks2.pdf

## Code snippets
* bochs_cpu.cpp