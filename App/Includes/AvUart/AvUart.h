/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  �汾: 1.0
|  ����: Knight [knight@graceport.cn]
|  ����: 2016��6��6��
|  ˵��:
|
|  �汾: 1.1
|  ����:
|  ����:
|  ˵��:
******************************************************************/
#ifndef _AVUART_H_
#define _AVUART_H_
#include "Apis/AvWareCplusplus.h"
#include "Apis/LibSystem.h"
#include "AvConfigs/AvConfigDevice.h"
#include "CAvObject.h"
#include "Apis/AvWareStruct.h"


class CAvUart
{
public:
	SINGLETON_DECLARE(CAvUart)
public:
	av_bool Initialize();
	av_bool Write(av_uchar index, av_buf &buf);
	av_bool Read(av_uchar index, av_buf &buf);
public:
	av_bool PtzGetCaps(C_PtzCaps &PtzCaps);
	av_bool PtzGetProfile(C_PtzProfile &PtzProfile);
	av_bool PtzSetProfile(C_PtzProfile &PtzProfile);
	av_bool PtzSetCommand(C_PtzCmd &PtzCmd);


private:
	av_bool UartOpen(av_uchar index);
	av_bool UartClose(av_uchar index);
	av_bool UartCaps();
	av_bool SetAttr(av_uchar index, C_SerialAttr &Attr);
	av_void OnConfigsModify(CAvConfigUart *Config, int &result);

private:
	C_SerialCaps m_SerialCaps;

private:
	CAvConfigUart m_Config;

private:
	CAvUart();
	~CAvUart();
};

#define g_AvUart (*CAvUart::instance())






#endif