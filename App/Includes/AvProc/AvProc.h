/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  �汾: 1.0
|  ����: Knight [knight@graceport.cn]
|  ����: 2016��6��6��
|  ˵��: ��ģ�������Ƕ��ʽ�豸����linux ϵͳ�е�/proc/avWare/Ŀ¼��������ϵͳ
|		����ģ�������״̬��
|
|  �汾: 1.1
|  ����:
|  ����:
|  ˵��:
******************************************************************/
#ifndef _AV_PROC_H_
#define _AV_PROC_H_
#include "Apis/AvWareCplusplus.h"
#include "CAvObject.h"
#include "logAvWareExport.h"
#define logAvWarePath "/dev/avWare"



class CAvProc:public CAvObject
{
public:
	SINGLETON_DECLARE(CAvProc);
	static av_bool Initialize();
	static av_bool avProcSet(IOCTRL_CMD cmd, av_void *data);

private:
	CAvProc();
	~CAvProc();

private:
	static av_int m_ProcHandle;

};


#define g_AvProc (*CAvProc::instance())

#if defined(_AV_WARE_M_HAVE_PROC)
#define AvProcInit() CAvProc::Initialize()
#define AvProcSet(cmd, data) CAvProc::avProcSet(cmd, data)
#else

#define AvProcInit()
#define AvProcSet(cmd, data)
#endif

#endif