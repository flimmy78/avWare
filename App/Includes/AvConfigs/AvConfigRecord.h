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

#ifndef _AVCONFIGRECORD_H_
#define _AVCONFIGRECORD_H_

#include "Apis/AvWareCplusplus.h"
#include "AvConfigs/AvConfigTable.h"

typedef enum {
	EAvRecord_NONE,
	EAvRecord_Timer,
	EAvRecord_Manul,
	EAvRecord_Alarm,
	EAvRecord_LAST,
}EAvRecordType;

typedef struct{
	av_bool bEnable;
	av_u32  tStart;
	av_u32  tEnd;
}RecordTime;

#define RECORD_MAX_TIME_RANGE 3



typedef struct {
	av_uint			RecordTypeMask;
	av_uint			RecordChlMask;
	RecordTime		RecordTm[RECORD_MAX_TIME_RANGE];
}ConfigRecordFormats;

typedef TAvConfig<ConfigRecordFormats, 0, SYS_CHN_NUM> CAvConfigRecord;


typedef enum{
	EAvRecord_LimitNONE,
	EAvRecord_LimitTime,
	EAvRecord_LimitSize,
	EAvRecord_LimitLAST,
}EAvRecordLimitType;


#define EAvRecordMaxRecordFileSize (500*1024*1024)
#define EAvRecordMaxPrerecordSec   15

// �Ƿ���ѭ��¼�࣬���Ǵ���ֹͣ¼��
typedef struct {
	EAvRecordLimitType	LimitType;
	av_uint				LimitArgs;//��ʱ������ʱ���˲���Ϊһ��¼���ļ�������;����С����ʱ���˲���Ϊ¼���ļ����ֽ���;
	av_uint				LimitPrerecordSec;
}ConfigRecordCtrlFormats;

typedef TAvConfig<ConfigRecordCtrlFormats> CAvConfigRecordCtrl;


#endif