#ifndef SIMPLE_LOGGER_HPP_
#error                                                                         \
    "This file should not be included directly. Include simple_logger.hpp instead."
#endif  // SIMPLE_LOGGER_HPP_

typedef int            BOOL;
typedef short          SHORT;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef void*          HANDLE;

typedef struct _COORD {
  SHORT X;
  SHORT Y;
} COORD, *PCOORD;

typedef struct _SMALL_RECT {
  SHORT Left;
  SHORT Top;
  SHORT Right;
  SHORT Bottom;
} SMALL_RECT, *PSMALL_RECT;

typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
  COORD      dwSize;
  COORD      dwCursorPosition;
  WORD       wAttributes;
  SMALL_RECT srWindow;
  COORD      dwMaximumWindowSize;
} CONSOLE_SCREEN_BUFFER_INFO, *PCONSOLE_SCREEN_BUFFER_INFO;

extern "C" __declspec(dllimport) HANDLE __stdcall GetStdHandle(DWORD);
extern "C" __declspec(dllimport) BOOL
    __stdcall GetConsoleScreenBufferInfo(HANDLE, PCONSOLE_SCREEN_BUFFER_INFO);
extern "C" __declspec(dllimport) BOOL
    __stdcall SetConsoleTextAttribute(HANDLE, WORD);

#ifndef _APISETCONSOLEL2_

#define FOREGROUND_BLUE      0x0001
#define FOREGROUND_GREEN     0x0002
#define FOREGROUND_RED       0x0004
#define FOREGROUND_INTENSITY 0x0008

#endif  // _APISETCONSOLEL2_

#ifndef _WINBASE_

#define STD_INPUT_HANDLE  ((win32::DWORD)-10)
#define STD_OUTPUT_HANDLE ((win32::DWORD)-11)
#define STD_ERROR_HANDLE  ((win32::DWORD)-12)

#endif  // _WINBASE_
