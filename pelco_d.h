#ifndef PELCO_D_H
#define PELCO_D_H

#include "serial_comm.h"
#include <iostream>

class PELCO_D {
public:
    PELCO_D();
    bool Init(unsigned int com,
              BYTE addr,
              DWORD  dwBaudRate);
    void UnInit();
    int Up();
    int Down();
    int Right();
    int Left();
    int Stop();
    int FocusNear();//焦距
    int FocusFar();
    int ZoomOut();//变倍
    int ZoomIn();
    int ApertureLarge();//光圈
    int ApertureSmall();
    int SetPresetPoint(BYTE num);
    int CallPresetPoint(BYTE num);
    int DeletePresetPoint(BYTE num);
    bool Available();//判断云台是否可用
    void SetSpeed(int speed);
    int  GetSpeed();

private:
    void __CreateCheck(BYTE* code, int len);

private:
    SerialComm m_comm;
    int m_speed;
    BYTE m_addr;
};

#endif // PELCO_D_H

