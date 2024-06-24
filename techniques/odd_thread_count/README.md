# Odd thread count

## Authorship information
* Name: kernelwernel
* Website: https://github.com/kernelwernel
  
## Technique Information
* Technique title: Odd Thread Count
* Technique category: Sandbox evasion
* Technique description: The thread count of the CPU must be an even number, which allows us to detect whether the thread count has been modified through the VM creation stage. If the thread count is not an even number, this is a sign of thread tampering (with a few exceptions which are already covered).

## Additional resources
* https://github.com/kernelwernel/VMAware
* https://en.wikichip.org/wiki/WikiChip

## Code snippets
* odd_thread_count.cpp
