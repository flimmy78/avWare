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
#ifndef _LIB_LOCALALM_H_
#define _LIB_LOCALALM_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "AvWareType.h"
#include "AvSystemStruct.h"



	av_bool AvAlarmCaps(C_AlarmCaps *AlarmCaps);
	av_bool AvGetIoAlmStatus(av_u32 *result);
	av_bool avSetIoAlmOut(av_uchar AlmOutNo, av_bool bOpen);
	av_bool avGetMdAlmStatus(av_u32 result[]);
	av_bool avSetMdProfile(av_u32 Area[], av_32 level);
	av_bool avAlarmCreate();
	av_bool avAlarmDestory();

#ifdef __cplusplus
}
#endif

#endif