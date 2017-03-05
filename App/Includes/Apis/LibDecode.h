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
}C_DecodeCaps;


av_bool AvAudioDecodeBuffer(unsigned  char *buffer, int bufferlen);

av_bool AvDecodeSplit(int SplitNo);
av_bool AvDecodeGetCaps(C_DecodeCaps *DecodeCaps);

//����4�׽ӿڣ����ܻ�ɶԵ��á���AvDecodeStartByWid AvDecodeStopByWid,���Ӳ��ƽ̨��ֻʵ��һ�׼��ɡ�
//���������ӿ��и�PC����ʾʱʹ�õģ���ΪPC ��������wind ���ڡ�
av_bool AvDecodeStartByWid(int ScreenID, unsigned int hWid);
av_bool AvDecodeStopByWid(int ScreenID);

//���������ӿ��и�NVR �� ��ʾʹ�õģ���ΪNVR������������������ġ�
av_bool AvDecodeStartByPos(int ScreenID, C_RECT *pRenderRect);
av_bool AvDecodeStopByPos(int ScreenID);

//�˽ӿڣ�ƽ̨���д��� �ֱ��� �� �������ͣ��������ƽ̨���Ƿ���Ҫ���ý�������
av_bool AvDecodeRenderBuffer(int ScreenID, unsigned  char  *buffer, int bufferlen);


#ifdef __cplusplus
}
#endif

#endif
