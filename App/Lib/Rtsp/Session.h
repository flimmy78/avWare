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
#ifndef _SESSION_H_
#define _SESSION_H_

#include "RtspMedia.h"
#include "Rbuffer.h"
#include "Rtsp.h"


typedef enum{
	MediaRtp,
	MediaRtcp,
	MediaNr,
}MediaTranType;

typedef enum {
	RTSP_MediaVideo,
	RTSP_MediaAudio,
	RTSP_MediaNr,
}RtspMediaType;

#define RTP_PORT_POOL 20000




class CRtspSession:public CAvObject
{

public:
	CRtspSession();
	virtual ~CRtspSession();

protected:
	virtual int PduRtsp(const char *data, int len) = 0;
	virtual int OnOptions(CRtspPdu &pdu) = 0;
	virtual int OnDescribe(CRtspPdu &pdu) = 0;
	virtual int OnSetup(CRtspPdu &pdu) = 0;
	virtual int OnRecord(CRtspPdu &pdu) = 0;
	virtual int OnPlay(CRtspPdu &pdu) = 0;
	virtual int OnPause(CRtspPdu &pdu) = 0;
	virtual int OnGetParameter(CRtspPdu &pdu) = 0;
	virtual int OnSetParameter(CRtspPdu &pdu) = 0;
	virtual int OnTeardown(CRtspPdu &pdu) = 0;
	virtual int OnError(CRtspPdu &pdu) = 0;
private:
	
};

class CRtspSessionSer :public CRtspSession
{
public:
	typedef CRtspMedia *(CAvObject::*COBJCREATEMEDIAPROC)(std::string url);
	typedef bool(CAvObject::*COBJDESTORYMEDIAPROC)(CRtspMedia *media);

	typedef CRtspMedia *(*CREATEMEDIAPROC)(std::string url);
	typedef bool(*DESTORYMEDIAPROC)(CRtspMedia *media);


	CRtspSessionSer();
	virtual ~CRtspSessionSer();

	int SetRemoteAddr(const char *ip);
	int SetRemotePort(const int Port);
	int SetSock(const int sock);

	unsigned int GetRemoteAddr();
	int GetRemotePort();
	int GetSock();

	int OnData(char *buffer, int buflen);
public:
	bool SetCreateMediaProc(COBJCREATEMEDIAPROC proc, CAvObject *obj);
	bool SetDestoryMediaProc(COBJDESTORYMEDIAPROC proc, CAvObject *obj);

	bool SetCreateMediaProc(CREATEMEDIAPROC proc);
	bool SetDestoryMediaProc(DESTORYMEDIAPROC proc);



public:
	virtual int PduRtsp(const char *data, int len);
	virtual int OnOptions(CRtspPdu &pdu);
	virtual int OnDescribe(CRtspPdu &pdu);
	virtual int OnSetup(CRtspPdu &pdu);
	virtual int OnRecord(CRtspPdu &pdu);
	virtual int OnPlay(CRtspPdu &pdu);
	virtual int OnPause(CRtspPdu &pdu);
	virtual int OnGetParameter(CRtspPdu &pdu);
	virtual int OnSetParameter(CRtspPdu &pdu);
	virtual int OnTeardown(CRtspPdu &pdu);
	virtual int OnError(CRtspPdu &pdu);

private:
	unsigned int m_Session;
	unsigned int m_RemoteAddr;
	unsigned int m_RemotePort;
	int			 m_sock;

	int			 m_RtpScok[CRtspMedia::RTSP_MEDIA_Nr];
	int			 m_RtcpSock[CRtspMedia::RTSP_MEDIA_Nr];
	
	CRBuffer	 m_RBuffer;
	CRtspMedia   *m_Media;
	static int			 m_RtpPortPool;

	static CAvObject		 *m_CreateMediaObj;
	static CAvObject		 *m_DestoryMediaObj;

	static COBJCREATEMEDIAPROC  m_CreateMediaProc;
	static COBJDESTORYMEDIAPROC m_DestoryMediaProc;

	static CREATEMEDIAPROC		 m_CcreateMediaProc;
	static DESTORYMEDIAPROC	 m_CdestoryMediaProc;
};

class CRtspSessionCli:public CRtspSession
{
public:
	CRtspSessionCli();
	virtual ~CRtspSessionCli();
	av_bool  SplitUrl();
protected:
	av_int		m_RtspSock;
	av_int		m_RtpSock[4];//0 video rtp; 1 video rtcp ; 2 audio rtp; 3 audio rtcp


protected:
	char			m_RemoteIpAddr[64];
	int				m_RemotePort;
	char			m_RtspUrl[128];
	CRBuffer		m_RBuffer;
	RTSP_METHOD_E	m_ReqMethod;
	int				m_CSeq;

public:
	av_void OnData(const char *buffer, int bufferlen);

public:
	virtual int PduRtsp(const char *data, int len);
	virtual int OnOptions(CRtspPdu &pdu);
	virtual int OnDescribe(CRtspPdu &pdu);
	virtual int OnSetup(CRtspPdu &pdu);
	virtual int OnRecord(CRtspPdu &pdu);
	virtual int OnPlay(CRtspPdu &pdu);
	virtual int OnPause(CRtspPdu &pdu);
	virtual int OnGetParameter(CRtspPdu &pdu);
	virtual int OnSetParameter(CRtspPdu &pdu);
	virtual int OnTeardown(CRtspPdu &pdu);
	virtual int OnError(CRtspPdu &pdu);

};


#endif
