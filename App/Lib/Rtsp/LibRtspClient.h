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
#ifndef _LIBRTSPCLIENT_H_
#define _LIBRTSPCLIENT_H_

#include "Session.h"


class CRtspClient;

class CRtspClientsManager:public CThread
{

public:
	CRtspClientsManager();
	~CRtspClientsManager();
public:
	av_bool Init();
	av_bool DeInit();

public:
	av_bool Add(CRtspClient *pClient);
	av_bool Del(CRtspClient *pClient);

private:
	void ThreadProc();
	void Processor();

private:
	CMutex		m_Mutex;
	std::map<int, CRtspClient *>	m_RtspClients;
	char		m_Buffer[8 * 1024];
};




class CRtspClient :public CRtspSessionCli
{

	friend class CRtspClientsManager;
public:
	CRtspClient();
	~CRtspClient();


public:
	av_bool Connect(const char *Url);
	av_bool DisConnect();

	av_void GetStreamPacket(CAvPacket *Packet);
private:
	std::queue <CAvPacket *>	m_PacketQueue;

private:
	

private:
	static av_bool			   m_bRtspClientsManInited;
	static CRtspClientsManager m_s_RtspClientsManager;
};






#endif
