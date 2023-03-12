#include <libloaderapi.h>

int main()
{
  hLibModule = GetModuleHandleA("av_edr_dllName.dll");
	FreeLibrary(hLibModule);
  return 0;
}
