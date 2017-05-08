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


#ifndef _AVCONFIG_MANAGER_NETWORK_H_
#define _AVCONFIG_MANAGER_NETWORK_H_

#include "AvConfigs/AvConfigIndex.h"
#include "AvConfigs/AvConfigManagerBase.h"
#include "AvConfigs/AvConfigNetService.h"







// typedef C_LanAttribute			ConfigLanAttribute;
// typedef C_BlueToothAttribute	ConfigBlueTooth;
// typedef C_SimAttribute			ConfigSimAttribute;
// typedef C_WirelessAttribute		ConfigWirelessAttribute;
// 
// typedef struct {
// 	av_bool			Enable;		//�򿪻��߹ر�
// 	av_bool			Support;	//Ӳ�����Ƿ�֧��
// 	NetCommT		type;
// 	NetCommGetMode	GetMode;
// 	av_char			Ifrname[24];
// 	union
// 	{
// 		ConfigLanAttribute		LanAttr;
// 		ConfigBlueTooth			BlueToothAttr;
// 		ConfigWirelessAttribute	WirelessAttr;
// 		ConfigSimAttribute		SimAttr;
// 	};
// }ConfigNetComm;

typedef C_NetCommAttribute ConfigNetComm;
typedef struct {
	char HostName[128];
}ConfigDeviceInfo;


typedef TAvConfig<ConfigNetComm, 0, NetCommT_LAST> CAvConfigNetComm;
typedef TAvConfig<ConfigDeviceInfo, 0, 1>CAvConfigDeviceInfo;



class CAvConfigManagerNetWork :public CAvConfigManagerBase
{
public:
	SINGLETON_DECLARE(CAvConfigManagerNetWork);
	CAvConfigManagerNetWork();
	~CAvConfigManagerNetWork();
	virtual void Initialize();

	int RestoreDefaultAllGeneralConfig();

private:
	CAvConfigNetComm				m_ConfigNetComm;
	CAvConfigDeviceInfo				m_ConfigDeviceInfo;
};


#endif //_AVCONFIG_MANAGER_NETCAPTURE_H_
