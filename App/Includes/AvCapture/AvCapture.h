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
#ifndef _AVCAPTURE_H_
#define _AVCAPTURE_H_
#include "AvPacket/AvPacket.h"
#include "Apis/AvWareCplusplus.h"
#include "Signals.h"
#include "CAvObject.h"
#include "Apis/AvEnum.h"
#include "Apis/AvWareStruct.h"
#include "AvConfigs/AvConfigCapture.h"
#include "AvProtocol/AvNetProto.h"


typedef enum{
	ARGS_GET,
	ARGS_SET,
}ARGS_M;

class Capture:public CThread
{
public:
	typedef enum {
		EAvCapture_NONE,
		EAvCapture_ING,
		EAvCapture_STOP,
		EAvCapture_DropFrame,
		EAvCapture_DropLink,
	}EAvCaptureStatus;

public:
	Capture();
	virtual ~Capture();

public:
	typedef TSignal3 <av_int, av_int, CAvPacket *>::SigProc SIG_PROC_ONDATA;
	virtual av_bool Initialize(av_int Channel) = 0;
	virtual av_bool Start(av_int Slave) = 0;
	virtual av_bool Stop(av_int Slave) = 0;

	virtual av_bool Start(av_int Slave, CAvObject *obj, SIG_PROC_ONDATA pOnData) = 0;
	virtual av_bool Stop(av_int Slave, CAvObject *obj, SIG_PROC_ONDATA pOnData) = 0;

	virtual EAvCaptureStatus GetCaptureStatus(av_int Slave = -1) = 0;




public:
	virtual av_bool CaptureGetCaps		(C_CaptureCaps &CaptureCaps) = 0;
	virtual av_bool CaptureGetProfile	(C_CaptureProfile &CaptureProfile) = 0;
	virtual av_bool CaptureSetProfile	(C_CaptureProfile &CaptureProfile) = 0;

	virtual av_bool EncodeGetCaps		(C_EncodeCaps &EncodeCaps) = 0;
	virtual av_bool EncodeGetProfile	(int Slave, C_EnCodeProfile &EnCodeProfile) = 0;
	virtual av_bool EncodeSetProfile	(int Slave, C_EnCodeProfile &EnCodeProfile) = 0;

	virtual av_bool AudioGetCaps		(C_AudioCaps &AudioCaps) = 0;
	virtual av_bool AudioGetProfile		(C_AudioProfile &AudioProfile) = 0;
	virtual av_bool AudioSetProfile		(C_AudioProfile &AudioProfile) = 0;

	virtual av_bool ImageGetCaps		(C_ImageCaps &ImageCaps) = 0;
	virtual av_bool ImageGetProfile		(C_ImageProfile &ImageProfile) = 0;
	virtual av_bool ImageSetProfile		(C_ImageProfile &ImageProfile) = 0;

	virtual av_bool PtzGetCaps			(C_PtzCaps &PtzCaps) = 0;
	virtual av_bool PtzGetProfile		(C_PtzProfile &PtzProfile) = 0;
	virtual av_bool PtzSetProfile		(C_PtzProfile &PtzProfile) = 0;
	virtual av_bool PtzSetCommand		(C_PtzCmd &PtzCmd) = 0;

	virtual av_bool AdvancedSystemGetCaps		(C_AdvancedSystemCaps &AdvancedSystemCaps) = 0;
	virtual av_bool AdvancedSystemGetProfile	(C_AdvancedSystemProfile &AdvancedSystemProfile) = 0;
	virtual av_bool AdvancedSystemSetProfile	(C_AdvancedSystemProfile &AdvancedSystemProfile) = 0;


	virtual av_bool StartNetCapture		(CAvNetProto *Handle);
	virtual av_bool StopNetCapture		();
	virtual CAvNetProto *AvNetProtoHandle();

	virtual CAvPacket * Snapshot(av_bool bRealTime = av_false, av_uint SnapshotInterval = 0, av_uint ContinuousTimes = 0) = 0;
protected:
	CAvNetProto *m_NetProtoHandle;
};





#endif


