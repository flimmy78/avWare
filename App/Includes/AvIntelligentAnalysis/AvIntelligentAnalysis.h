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

#ifndef _AVINTELLIGENTANALYSIS_H_
#define _AVINTELLIGENTANALYSIS_H_

#include "Signals.h"
#include "Apis/AvWareCplusplus.h"
#include "AvThread/AvThread.h"
#include "Apis/LibSystem.h"
#include "AvThread/AvQmsg.h"
#include "Apis/LibLocalAlm.h"
#include "AvThread/AvTask.h"
#include "AvConfigs/AvConfigNetService.h"
#include "AvConfigs/AvConfigAlarm.h"

class CAvIntelligentanalysis :public CThread
{
public:
	SINGLETON_DECLARE(CAvIntelligentanalysis);
private:
	CAvIntelligentanalysis();
	~CAvIntelligentanalysis();
public:

	av_bool Initialize();


private:
	av_void ThreadProc();
};



#define g_AvIntelligentanalysis (*CAvIntelligentanalysis::instance())










#endif

