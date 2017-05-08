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
#ifndef _AVCONFIG_MANAGER_BASE_H_
#define _AVCONFIG_MANAGER_BASE_H_

#include <map>
#include <string>
#include "AvConfigs/AvConfigTable.h"

#ifdef WIN32
#define  AvConfigFileName					"avWare1.json"
#define  AvConfigFileNameBak				"avWare2.json"
#define  AvConfigFileNameNetCapture			"avWareNetCapture.json"
#define  AvConfigFileNameNetCaptureBak		"avWareNetCaptureBk.json"
#define  AvConfigFileNameNetWork			"avWareNetWork.json"
#define  AvConfigFileNameNetWorkBak			"avWareNetWorkBk.json"
#else
#define  AvConfigFileName					"avWare1.conf"
#define  AvConfigFileNameBak				"avWare2.conf"
#define  AvConfigFileNameNetCapture			"avWareNetCapture.conf"
#define  AvConfigFileNameNetCaptureBak		"avWareNetCaptureBk.conf"
#define  AvConfigFileNameNetWork			"avWareNetWork.conf"
#define  AvConfigFileNameNetWorkBak			"avWareNetWorkBk.conf"
#endif



class CAvConfigBase;
class CAvConfigManagerBase:public CAvObject
{
public:
	CAvConfigManagerBase(const std::string & DefConfPath, const std::string &DefCongPathBak);
	virtual ~CAvConfigManagerBase();
	virtual void Initialize() = 0;

	//TODO:�������롢����������
	virtual int ExportConfig(void *buf, int &len);
	virtual int ImportConfig(void *buf, const int len);

protected:
	av_bool SetAvConfigPath(const std::string &ConfPath, const std::string &ConfFile, const std::string &ConfFileBak);
	av_bool LoadConfigFromFile();
	void SetUpConfig(const char *name, CAvConfigBase &conf, const int index);
	int RestoreDefault(const char *ConfName, const int index = -1);
	int RestoreDefaultAll();
	av_int WriteFile();
private:
	//id ���ñ�TAvConfigģ����ʵ�������id
	//index ���������������ο�AvConfigIndex
	//name �������ͱ��������л���json��䵱key
	//table �������Ͷ���ʵ��
	std::map<int, std::string> m_id_name;
	std::map<std::string, CAvConfigBase*> m_name_table;
	std::map<std::string, int> m_name_index;

private:
	const char* IdToName(int id);
	CAvConfigBase* NameToTable(const char *name);
	av_bool ReadConfigFile(const char *path, std::string &conf);
	void CBConfigChange(CAvConfigBase *conf, int &req);

private:
	std::string m_ConfigFullPath;
	std::string m_ConfigFullPathBak;

	AvConfigValue m_total;
	static CMutex m_mutex;
	std::string m_config_data;
};

#endif //_AVCONFIG_MANAGER_BASE_H_