/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  �汾: 1.0
|  ����: FootMan [FootMan@graceport.cn]
|  ����: 2016��6��6��
|  ˵��:
|
|  �汾: 1.1
|  ����:
|  ����:
|  ˵��:
******************************************************************/
#ifndef __ONVIF_INIT_H__
#define __ONVIF_INIT_H__

#include "onvifAPI.h"
#include "network.h"


OnvifSerHandle_S	*GetOnvifSerHandle();
NetWorkSerHandle_S	*GeonvifSerNetHandle();
NetWorkSerHandle_S	*GetonvifMulicatstserHandle();
NetWorkSerHandle_S	*GetonvifSerNetHandle();


int		OnvifInitAllValue();
int		OnvifCreateInitProfile();
int		initUuid();
char *	GetAddressUuid();
char *	GetMsgUuid(char *MsgID,int len);

#endif


