# Technique Name: Python GetTrace Anti-Debug

## Author Information

- Nickname: found ITW by Xavier Mertens, added by Matteo Lodi

## Technique Information

- Technique Category: Anti-Debugging
- Technique Tags: python
- Technique General Detail: If a debugger is attached to the Python process, `sys.gettrace()` will return a trace function.

## Additional Resources

- [SANS diary](https://isc.sans.edu/diary/31658)