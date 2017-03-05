/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  �汾: 1.0
|  ����: Xman [xman@graceport.cn]
|  ����: 2016��12��5��
|  ˵��:
|
******************************************************************/
#ifndef _AVCONFIG_MANAGER_GENERAL_H_
#define _AVCONFIG_MANAGER_GENERAL_H_

#include "AvConfigs/AvConfigManagerBase.h"

#include "AvConfigs/AvConfigUserManager.h"
#include "AvConfigs/AvConfigDevice.h"
#include "AvConfigs/AvConfigNetService.h"
#include "AvConfigs/AvConfigCapture.h"
#include "AvConfigs/AvConfigAlarm.h"
#include "AvConfigs/AvConfigRecord.h"

class CAvConfigManagerGeneral :public CAvConfigManagerBase
{
public:
	SINGLETON_DECLARE(CAvConfigManagerGeneral);
	CAvConfigManagerGeneral();
	~CAvConfigManagerGeneral();
	virtual void Initialize();

	int RestoreDefaultAllGeneralConfig();

private:
	CAvConfigEncode					m_ConfigEncode;
	CAvConfigCover					m_ConfigCover;
	CAvConfigOverLay				m_ConfigOverLay;
	CAvConfigAlarm					m_ConfigAlarm;
	CAvConfigNetComm				m_ConfigNetComm;
	CAvConfigProtocol				m_ConfigNetProtocol;
	CAvConfigImage					m_ConfigImage;
	CAvConfigAudio					m_ConfigAudio;

	CAvConfigCapture				m_ConfigCapture;

	CAvConfigUart					m_config_device_uart;
	CAvConfigUserManager			m_config_user_manager;

	
	CAvConfigNetSmtp				m_confignet_smtp;
	CAvConfigNetFtp					m_confignet_ftp;
	CAvConfigNetDdns				m_confignet_ddns;
	CAvConfigNetUpnp				m_confignet_upnp;
	CAvConfigNetNtp					m_confignet_ntp;
	CAvConfigRtmp					m_config_rtmp;
	CAvConfigNetP2p					m_config_p2p;
	CAvConfigNetRtsp				m_config_rtsp;


	CAvConfigRecord					m_config_record;
	CAvConfigRecordCtrl				m_config_recordctrl;
	CAvConfigPtzCameraLensProfile	m_config_ptzCameraLens;
};

#define g_AvConfigMagagerGeneral (*CAvConfigManagerGeneral::instance())
#endif //_AVCONFIG_MANAGER_GENERAL_H_