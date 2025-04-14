# Process Argument argv[0] Spoofing

## Authorship information

* Name or nickname : Wietze
* Twitter: <https://twitter.com/wietze>
* Website: <https://wietze.github.io>

## Technique Information

* Technique title : argv[0] Spoofing
* Technique category : Process Manipulating
* Technique description : `argv[0]` is the first argument on a process' command line, typically representing the name or path of the executable. For most processes, `argv[0]` can be set to an arbitrary value without it affecting the process flow.

  Detections relying on command-line arguments may, by manipulating `argv[0]`, be bypassed. For example:

  * Setting `argv[0]` to an empty string may bypass detections that look for the executable name in the command line component;
  * Similarly, by setting `argv[0]` to a different executable name, it may be possible to bypass detections, or fool security analysts by making them believe the command is doing something different;
  * By putting a very long string in `argv[0]`, it may be possible to 'hide' the actual command-line arguments at the very end; and,
  * By including known detection exclusions in `argv[0]`, it may be possible to prevent the alerting logic from triggering.

## Additional resources

* <https://www.wietzebeukema.nl/blog/why-bother-with-argv0>

## Code snippets

* argv0-spoofing.c
* argv0-spoofing.py
