#include <windows.h>
#include <stdio.h>

int main() {
    DWORD pcbNeeded;
    DWORD pcReturned;

    if (!EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 2, NULL, 0, &pcbNeeded, &pcReturned)) {
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
            PRINTER_INFO_2* pPrinterEnum = (PRINTER_INFO_2*)malloc(pcbNeeded);
            if (EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 2, (LPBYTE)pPrinterEnum, pcbNeeded, &pcbNeeded, &pcReturned)) {
                printf("Printer number: %d\n", pcReturned);
                for (int i = 0; i < pcReturned; i++) {
                    printf("printerName %ls\n", pPrinterEnum[i].pPrinterName);
                }
            }
            free(pPrinterEnum);
        }
    }
}