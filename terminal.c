#include "terminal.h"

char terminal_buffer[8192];

void configureTerminal()
{
    setvbuf(stdout, terminal_buffer, _IOFBF, sizeof(terminal_buffer));

#ifdef __WIN32
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;

    GetConsoleMode(handle, &mode);
    mode |= TERMINAL_PROCESSING;

    SetConsoleMode(handle, mode);
#endif
}

