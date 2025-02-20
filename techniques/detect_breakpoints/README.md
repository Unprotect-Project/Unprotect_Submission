# Technique Name: Detect Hardware Breakpoints

## Author Information

- Nickname: found ITW by Xavier Mertens, added by Matteo Lodi

## Technique Information

- Technique Category: Anti-Debugging
- Technique Tags: breakpoint
- Technique General Detail: Hardware breakpoints are used to avoid patching the program. They contain the address where to pause the execution. Hardware breakpoints are CPU registers: DRO to DR3 (on Intel CPU’s). `RtlCaptureContext()` is used to get the current threat’s execution state which includes the registers. With the help of unpack, the script fills the variable corresponding to the registers, if one of them is not empty, there is a hardware breakpoint defined!

## Additional Resources

- [SANS diary](https://isc.sans.edu/diary/31658)