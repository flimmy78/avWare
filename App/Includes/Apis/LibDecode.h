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
#ifndef _LIBDECODE_H_
#define _LIBDECODE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "AvWareType.h"
#include "AvSystemStruct.h"
typedef struct{
	unsigned int CompMask;
	unsigned int ImageSizeMask;// CHL_MAIN_T
	unsigned int MaxOutFrameRate;
	unsigned int MaxChannels;
	unsigned int MainStreamMode[64];
}C_DecodeCaps;


av_bool AvDecodeSplit(int SplitNum);
av_bool AvDecodeClears(int ScreenID);


av_bool AvAudioDecodeBuffer(unsigned  char *buffer, int bufferlen);


av_bool AvDecodeGetCaps(C_DecodeCaps *DecodeCaps);


av_bool AvDecodeStart(int ScreenID);


//�˽ӿڣ�ƽ̨���д��� �ֱ��� �� �������ͣ��������ƽ̨���Ƿ���Ҫ���ý�������
av_bool AvDecodeRenderBuffer(int ScreenID, unsigned  char  *buffer, int bufferlen);


av_u32		 avWareGetWindowsIdByScreenID(int SrceenID);
C_RECT		*avWareGetWindowsRectByScreenID(int SrceenID);


#ifdef __cplusplus
}
#endif

#endif
