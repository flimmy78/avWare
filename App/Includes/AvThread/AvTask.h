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
#ifndef _AV_TASK_H_
#define _AV_TASK_H_
#include "Apis/AvWareCplusplus.h"
#include "AvThread/AvThread.h"

class CAvTask:public CThread
{
//protected:
public:
	CAvTask();
	virtual ~CAvTask();
public:
	typedef av_void(CAvObject::*CAvTaskThreadProc)(void);
public:
	av_bool StartTask(av_bool bAtutoDestruct = av_true);
	av_bool SetTaskName(std::string TaskName); 
	av_bool StartTask(CAvObject *Obj, CAvTaskThreadProc proc, av_bool bAtutoDestruct = av_true);
protected:
	virtual av_void TaskJob(){};

private:
	void ThreadProc();

private:
	CAvObject *m_Obj;
	CAvTaskThreadProc m_Proc;
};



#endif
