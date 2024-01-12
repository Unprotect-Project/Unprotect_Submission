# *NixImports*

## Authorship information
* Name or nickname (required): dr4k0nia
* Twitter: https://twitter.com/dr4k0nia
* Website: https://dr4k0nia.github.io
  
## Technique Information
* Technique title (required): NixImports
* Technique category (required): Packers
* Technique description (required): A .NET malware loader, using API-Hashing and dynamic invoking to evade static analysis. NixImports uses managed API-Hashing, to dynamically resolve most of it's called functions at runtime. To resolve the functions HInvoke requires two hashes the typeHash and the methodHash. These hashes represent the type name and the methods FullName, on runtime HInvoke parses the entire mscorlib to find the matching type and method. Due to this process, HInvoke does not leave any import references to the methods called trough it. Another interesting feature of NixImports is that it avoids calling known methods as much as possible, whenever applicable NixImports uses internal methods instead of their wrappers. By using internal methods only we can evade basic hooks and monitoring employed by some security tools.

## Additional resources
* https://github.com/dr4k0nia/NixImports/tree/master
* https://dr4k0nia.github.io/posts/NixImports-a-NET-loader-using-HInvoke/

## Detection rules
* mal_net_niximports_loader.yar
* mal_msil_net_niximports_loader.yar
