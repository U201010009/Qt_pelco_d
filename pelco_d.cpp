#include <cstdio>
#include "pelco_d.h"


PELCO_D::PELCO_D() :
    m_speed(0xff)
{}

bool PELCO_D::Init(unsigned int com,
                   BYTE addr,
                   DWORD  dwBaudRate)
{
    m_addr = addr;
    char name[20];
//    bool result = m_comm.open(name, CBR_2400, NOPARITY, ONESTOPBIT, 8);
#ifdef WIN32
    sprintf(name, "COM%d", com);
    bool result = m_comm.open(name, dwBaudRate, NOPARITY, ONESTOPBIT, 8);
#elif __linux__
    sprintf(name, "/dev/ttyS%d", com - 1);
    bool result = m_comm.open(name, dwBaudRate, 'N', 1, 8);
#endif
    return result;
}

void PELCO_D::UnInit()
{
    m_comm.close();
}

int PELCO_D::Up()
{
    if (m_comm.isAvailable())
    {
        //{0xff,0x01,0x00,0x08,0x00,0xff,0x08,}//上
        BYTE code[7] = { 0xff, m_addr, 0x00, 0x08, 0x00, m_speed };
        __CreateCheck(code, sizeof(code));
        return m_comm.output(code, sizeof(code));
    }
    return -1;
}

int PELCO_D::Down()
{
    if (m_comm.isAvailable())
    {
        //{0xff,0x01,0x00,0x10,0x00,0xff,0x10,}//下
        BYTE code[7] = { 0xff, m_addr, 0x00, 0x10, 0x00, m_speed };
        __CreateCheck(code, sizeof(code));
        return m_comm.output(code, sizeof(code));
    }
    return -1;
}

int PELCO_D::Stop()
{
    if (m_comm.isAvailable())
    {
        //{0xff,0x01,0x00,0x00,0x00,0x00,0x01,}//停命令
        BYTE code[7] = { 0xff, m_addr, 0x00, 0x00, 0x00, 0x00 };
        __CreateCheck(code, sizeof(code));
        return m_comm.output(code, sizeof(code));
    }
    return -1;
}

int PELCO_D::Right()
{
    if (m_comm.isAvailable())
    {
        //{0xff,0x01,0x00,0x02,0xff,0x00,0x02,}//右
        BYTE code[7] = { 0xff, m_addr, 0x00, 0x02, m_speed, 0x00 };
        __CreateCheck(code, sizeof(code));
        return m_comm.output(code, sizeof(code));
    }
    return -1;
}

int PELCO_D::Left()
{
    if (m_comm.isAvailable())
    {
        //{0xff,0x01,0x00,0x04,0xff,0x00,0x04,}//左
        BYTE code[7] = { 0xff, m_addr, 0x00, 0x04, m_speed, 0x00 };
        __CreateCheck(code, sizeof(code));
        return m_comm.output(code, sizeof(code));
    }
    return -1;
}

int PELCO_D::FocusNear()
{
    if (m_comm.isAvailable())
    {

        //{0xff,0x01,0x00,0x80,0x00,0x00,0x81,}//聚焦近
        BYTE code[7] = { 0xff, m_addr, 0x00, 0x80, 0x00, 0x00 };
        __CreateCheck(code, sizeof(code));
        return m_comm.output(code, sizeof(code));
    }
    return -1;
}

int PELCO_D::FocusFar()
{
    if (m_comm.isAvailable())
    {
        //{0xff,0x01,0x01,0x00,0x00,0x00,0x02,}//聚焦远
        BYTE code[7] = { 0xff, m_addr, 0x01, 0x00, 0x00, 0x00 };
        __CreateCheck(code, sizeof(code));
        return m_comm.output(code, sizeof(code));
    }
    return -1;
}

int PELCO_D::ZoomOut()
{
    if (m_comm.isAvailable())
    {
        //{0xff,0x01,0x00,0x40,0x00,0x00,0x41,}//变倍长
        BYTE code[7] = { 0xff, m_addr, 0x00, 0x40, 0x00, 0x00 };
        __CreateCheck(code, sizeof(code));
        return m_comm.output(code, sizeof(code));
    }
    return -1;
}

int PELCO_D::ZoomIn()
{
    if (m_comm.isAvailable())
    {
        //{0xff,0x01,0x00,0x20,0x00,0x00,0x21,}//变倍短
        BYTE code[7] = { 0xff, m_addr, 0x00, 0x20, 0x00, 0x00 };
        __CreateCheck(code, sizeof(code));
        return m_comm.output(code, sizeof(code));
    }
    return -1;
}

int PELCO_D::ApertureLarge()
{
    if (m_comm.isAvailable())
    {
        //{0xff,0x01,0x04,0x00,0x00,0x00,0x05,}//光圈大
        BYTE code[7] = { 0xff, m_addr, 0x04, 0x00, 0x00, 0x00 };
        __CreateCheck(code, sizeof(code));
        return m_comm.output(code, sizeof(code));
    }
    return -1;
}

int PELCO_D::ApertureSmall()
{
    if (m_comm.isAvailable())
    {
        //{0xff,0x01,0x02,0x00,0x00,0x00,0x03,}//光圈小
        BYTE code[7] = { 0xff, m_addr, 0x02, 0x00, 0x00, 0x00 };
        __CreateCheck(code, sizeof(code));
        return m_comm.output(code, sizeof(code));
    }
    return -1;
}

int PELCO_D::SetPresetPoint(BYTE num)
{
    if(m_comm.isAvailable())
    {
        //{0xff,0x01,0x00,0x03,0x00,0x01,0x05,}//设置预置点001
        if(num >= 1 && num <= 32)
        {
            BYTE code[7] = { 0xff, m_addr, 0x00, 0x03, 0x00, num };
            __CreateCheck(code, sizeof(code));
            return m_comm.output(code, sizeof(code));
        }
        else if(num >= 33 && num <= 64)
        {
            BYTE code[7] = { 0xff, m_addr, 0x00, 0x03, 0x00, num };
//            BYTE code[7] = { 0xff, m_addr, 0x02, 0xff, num, 0x00 };
            __CreateCheck(code, sizeof(code));
            return m_comm.output(code, sizeof(code));
        }
        return -1;
    }
    return -1;
}

int PELCO_D::CallPresetPoint(BYTE num)
{
    if(m_comm.isAvailable())
    {
        //{0xff,0x01,0x00,0x07,0x00,0x01,0x09,}//转至预置点001
        if(num >= 1 && num <= 32)
        {
            BYTE code[7] = { 0xff, m_addr, 0x00, 0x07, 0x00, num };
            __CreateCheck(code, sizeof(code));
            return m_comm.output(code, sizeof(code));
        }
        else if(num >= 33 && num <= 64)
        {
            BYTE code[7] = { 0xff, m_addr, 0x00, 0x07, 0x00, num };
//            BYTE code[7] = { 0xff, m_addr, 0x02, 0xff, num, 0x01 };
            __CreateCheck(code, sizeof(code));
            return m_comm.output(code, sizeof(code));
        }
        return -1;
    }
    return -1;
}

int PELCO_D::DeletePresetPoint(BYTE num)
{
    if(m_comm.isAvailable())
    {
        //{0xff,0x01,0x00,0x05,0x00,0x01,0x07,}//删除预置点001
        if(num >= 1 && num <= 32)
        {
            BYTE code[7] = { 0xff, m_addr, 0x00, 0x05, 0x00, num };
            __CreateCheck(code, sizeof(code));
            return m_comm.output(code, sizeof(code));
        }
        else if(num >= 33 && num <= 64)
        {
            BYTE code[7] = { 0xff, m_addr, 0x00, 0x05, 0x00, num };
            __CreateCheck(code, sizeof(code));
            return m_comm.output(code, sizeof(code));
        }
        return -1;
    }
    return -1;
}

bool PELCO_D::Available()
{
    return m_comm.isAvailable();
}

void PELCO_D::SetSpeed(int speed)
{
    //speed range from 00H to 3FH(63)
    this->m_speed = speed > 63 ? 63 : (speed < 0 ? 0 : speed);
}

int PELCO_D::GetSpeed()
{
    return this->m_speed;
}

void PELCO_D::__CreateCheck(BYTE* code, int len)
{
    BYTE tmp = 0x00;
    for(int i = 1; i < len - 1; ++i)
    {
        tmp += code[i];
    }
    code[len - 1] = tmp % 0x100;
}
