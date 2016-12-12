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
#ifndef _AVNETSERVICE_H_
#define _AVNETSERVICE_H_
#include "Apis/AvWareCplusplus.h"
#include "AvConfigs/AvConfigNetService.h"
#include "AvThread/AvThread.h"
#include "CAvObject.h"
#include "AvNetService/AvRtmp.h"


class CAvNetService :public CThread
{
public:
	SINGLETON_DECLARE(CAvNetService);

	av_bool Initialize();
	av_bool Start();
	av_bool Stop();
	av_bool Restart();

private:
	CAvNetService();
	~CAvNetService();

private:
	av_void OnConfigRtmpModify(CAvConfigRtmp *configRtmp, int &result);

private:
	void ThreadProc();

private:
	CAvConfigRtmp				m_ConfigRtmp;
	std::map<av_u32, AvRtmp*>	m_AvRtmpMap;
};
#define g_AvNetService (*CAvNetService::instance())

#endif
