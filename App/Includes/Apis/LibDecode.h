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

typedef struct{
	unsigned int CompMask;
	unsigned int ImageSizeMask;// CHL_MAIN_T
	unsigned int MaxOutFrameRate;
	unsigned int MaxChannels;
}C_DecodeCaps;

bool AvAudioDecodeBuffer(unsigned  char *buffer, int bufferlen);

bool AvDecodeSplit(int SplitNo, unsigned int hWid[]);

bool AvDecodeGetCaps(C_DecodeCaps *DecodeCaps);
bool AvDecodeStart(int ScreenID, unsigned int hWid);
bool AvDecodeStop(int ScreenID);

bool AvDecodeRenderBuffer(int ScreenID, unsigned  char  *buffer, int bufferlen);


#ifdef __cplusplus
}
#endif

#endif
