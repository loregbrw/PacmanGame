#include "terminal.h"

char terminal_buffer[8192];

void configureTerminal()
{
    //system("chcp 65001");
    setvbuf(stdout, terminal_buffer, _IOFBF, sizeof(terminal_buffer));
    setlocale(LC_ALL, "en_US.UTF-8");

#ifdef __WIN32
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;

    GetConsoleMode(handle, &mode);
    mode |= TERMINAL_PROCESSING;

    SetConsoleMode(handle, mode);
#endif
}

