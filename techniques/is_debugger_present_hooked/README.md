# Technique Name: Hooked IsDebuggerPresent

## Author Information

- Nickname: found ITW by Xavier Mertens, added by Matteo Lodi

## Technique Information

- Technique Category: Anti-Monitoring
- Technique Tags: hook
- Technique General Detail: Sometimes `IsDebuggerPresent()` is hooked to prevent the simple detection of a debugger. This is called "trampoline" technique.
By detecting that this API has been hooked, the malware author can detect that is being monitored.

## Additional Resources

- [SANS diary](https://isc.sans.edu/diary/31658)