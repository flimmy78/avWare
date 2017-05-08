/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  �汾: 1.0
|  ����: Knight [knight@graceport.cn]
|  ����: 2017��3��31��
|  ˵��:
|
|  �汾: 1.1
|  ����:
|  ����:
|  ˵��:
******************************************************************/

#ifndef _AVCONFIG_MANAGER_NETCAPTURE_H_
#define _AVCONFIG_MANAGER_NETCAPTURE_H_

#include "AvConfigs/AvConfigManagerBase.h"
#include "AvConfigs/AvConfigCapture.h"
#include "AvConfigs/AvConfigIndex.h"

class CAvConfigManagerNetCapture :public CAvConfigManagerBase
{
public:
	SINGLETON_DECLARE(CAvConfigManagerNetCapture);
	CAvConfigManagerNetCapture();
	~CAvConfigManagerNetCapture();
	virtual void Initialize();

	int RestoreDefaultAllGeneralConfig();

private:
	CAvConfigProtocol				m_ConfigNetProtocol;
};


#endif //_AVCONFIG_MANAGER_NETCAPTURE_H_