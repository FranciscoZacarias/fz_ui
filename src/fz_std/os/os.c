///////////////////////////////////////////////////////
// @Section: OS Handles

///////////////////////////////////////////////////////
// @Section: OS-Dependent implementation

#if OS_WINDOWS
# include "os/win32/os_win32.c"
#elif OS_LINUX
# include "os/linux/os_linux.c"
#else
# error OS core layer not implemented for this operating system.
#endif