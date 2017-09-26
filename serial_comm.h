#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#ifdef WIN32
#include <windows.h>
#elif __linux__
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

typedef unsigned long       DWORD;
typedef unsigned char       BYTE;
typedef const void       *LPCVOID;

#endif

class SerialComm {
public:

    SerialComm();
    ~SerialComm();

    int open(char* lpszPortNum/* = "com1"*/,    // 串口号
        DWORD  dwBaudRate/* = CBR_2400*/,  // 波特率
        BYTE   byParity/* = NOPARITY*/,  // 奇偶校验
        BYTE   byStopBits/* = ONESTOPBIT*/,// 停止位个数
        BYTE   byByteSize/* = 8*/);       // 字节长度

    DWORD   output(LPCVOID pdata, DWORD len);

#ifdef WIN32
    DWORD   input(LPVOID  pdest, DWORD len, DWORD dwMaxWait = 500);
    char*   GetErrorMessage(void);
#endif

    void close();
    bool isAvailable();
private:

#ifdef WIN32
    VOID    ErrorToString(char* lpszMessage);
    BOOL    IsNT(void);
    char       m_lpszErrorMessage[256];
    HANDLE      m_hCom;   // 串口句柄
    OVERLAPPED  m_ov;     // 包含异步输入输出操作信息的结构
#elif __linux__

    int set_opt(DWORD  dwBaudRate,  // 波特率
                BYTE   byParity,  // 奇偶校验
                BYTE   byStopBits,// 停止位个数
                BYTE   byByteSize = 8);

    int m_fd;
#endif
};


#endif // SERIAL_COMM_H

