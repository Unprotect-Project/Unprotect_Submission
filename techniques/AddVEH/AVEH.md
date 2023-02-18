# Detect single-stepping in VEH Debuggers

## Authorship Information
* Name: Alex Schwarz
* Website: 
* Twitter:
* Linkedin:
  
## Technique Information
* Technique Title: AddVectoredExceptionHandler
* Technique Category: Anti-Debugging
* Technique Description: We can detect the presence of debuggers which use Vectored Exception Handlers by calling AddVectoredExceptionHandler(1, ourHandler). Stepping through code after this call has taken place will produce an EXCEPTION_SINGLE_STEP exception, which is caught by our top level handler.

## Code Snippets
* AVEH.cpp
