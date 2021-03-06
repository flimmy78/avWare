#include "AvPreview/AvPreview.h"
#include "Apis/LibDecode.h"

#define PreviewStatisticsMs 3000

av_uint							CAvPreview::m_SpiltScreenNum								= 0;
C_DecodeCaps					CAvPreview::m_DecodeCaps									= {0};

av_bool							m_gPause													= av_false;
std::map <int, CAvPreview*>		m_gPreviewManager;

CAvPreview::CAvPreview()
{
	m_hWid = 0;
	m_Channel = -1;
	m_Slave = -1;
	m_isStarted = av_false;
	m_Capture = NULL;
	m_ScreenID = -1;
	m_bAudioOpen = av_false;

	m_bStatistics = av_true;
	m_StatisticsBitRate = 0;
	m_StatisticsFrameRate = 0;
	m_StatisticsGop = 0;



	m_Gop = 0;
	m_ImageWidth = 0;
	m_ImageHeigh = 0;
	m_FrameRate = 0;
	m_BitRate = 0;
	m_bPause = av_false;
	m_bStartDecode = av_false;
	m_RenderRect.Sx = 0;
	m_RenderRect.Sy = 0;
	m_RenderRect.Width = 0;
	m_RenderRect.Heigh = 0;

	m_Timer.SetContinual(av_true);
	m_Timer.SetInterlvalMsec(PreviewStatisticsMs);
	m_Timer.SetStartRunMSec(0);
	m_Timer.SetOnTimerProc(this, (CAvTimer::ONTIMER_PROC)&CAvPreview::OnTimer);
}
CAvPreview::~CAvPreview()
{
	if (m_isStarted == av_true){
		Stop();
	}
	m_bStartDecode = av_false;
}

av_bool CAvPreview::Set(unsigned int hWid, int ScreenID)
{
	m_ScreenID = ScreenID;
	m_hWid = hWid;
	m_gPreviewManager[ScreenID] = this;
	return av_true;
}
av_bool CAvPreview::Start(int Channel, int Slave)
{
	if (m_isStarted == av_true){
		Stop();
	}
	m_Channel = Channel;
	m_Slave = Slave;
	m_Capture = g_AvManCapture.GetAvCaptureInstance(Channel);
	AvDecodeStart(m_ScreenID);

	m_Capture->Start(m_Slave, this, (Capture::SIG_PROC_ONDATA)&CAvPreview::OnStream);
	m_isStarted = av_true;

	CAvTimer::StartTimer(m_Timer);
	return av_true;
}
av_uint CAvPreview::GetWindowsID()
{
	return m_hWid;
}
av_int  CAvPreview::GetScreenID()
{
	return m_ScreenID;
}
C_RECT  &CAvPreview::GetWindowsRect()
{
	return m_RenderRect;
}
av_bool CAvPreview::GetChannleSlave(int &Channel, int &Slave)
{
	Channel = m_Channel;
	Slave = m_Slave;
	if (Channel == -1 || Slave == -1){
		return av_false;
	}
	else {
		return av_true;
	}
}
av_bool CAvPreview::StartAudio(av_bool bOpen)
{
	m_bAudioOpen = bOpen;
	return av_true;
}
av_bool CAvPreview::SetStatistics(av_bool bOpen)
{
	m_bStatistics = bOpen;
	
	m_StatisticsBitRate = 0;
	m_StatisticsFrameRate = 0;
	m_StatisticsGop = 0;

	return av_true;
}
av_bool CAvPreview::GetStatistics(std::string &ImageSize, std::string &Comp, std::string &FrameRate, std::string &BitRate)
{
	if (m_bStatistics == av_false){
		return av_false;
	}
	char tempbuff[64] =  {0};
	sprintf(tempbuff, "%d*%d", m_ImageWidth, m_ImageHeigh);
	ImageSize.append(tempbuff);
	sprintf(tempbuff, "%d FPS", m_FrameRate);
	FrameRate.append(tempbuff);
	switch (m_Comp)
	{
	case AvComp_H264:
		sprintf(tempbuff, "H264");
		break;
	case AvComp_H265:
		sprintf(tempbuff, "H265");
		break;
	case AvComp_JPEG:
		sprintf(tempbuff, "JPEG");
		break;
	case AvComp_MJPEG:
		sprintf(tempbuff, "MJPEG");
		break;
	default:
		sprintf(tempbuff, "ENCODE");
		break;
	}
	Comp.append(tempbuff);

	sprintf(tempbuff, "%d kbps", (m_BitRate * 8) / 1024);
	BitRate.append(tempbuff);
	return av_true;
}
av_bool CAvPreview::Stop()
{
	if (m_isStarted == false){
		return av_true;
	}
	m_bStartDecode = av_false;
	m_Capture->Stop(m_Slave, this, (Capture::SIG_PROC_ONDATA)&CAvPreview::OnStream);

	AvDecodeClears(m_ScreenID);

	m_Slave = -1;
	m_Channel = -1;
	m_Capture = NULL;
	m_isStarted = av_false;
	CAvTimer::StopTimer(m_Timer);
	return av_true;
}
av_bool CAvPreview::Pause(av_bool bPause)
{
	m_bPause = bPause;
	return av_true;
}
av_bool  CAvPreview::RenderResize(C_RECT &RenderRect)
{
	m_RenderRect = RenderRect;
	return av_true;
}
av_void CAvPreview::OnStream(int Channel, int Slave, CAvPacket *Pack)
{
	if (m_gPause == av_true){
		return;
	}

	if (m_bAudioOpen == av_false && Pack->StreamCont() == StreamContent_AUDIO){
		return;
	}
	if (Pack->StreamCont() == StreamContent_VIDEO && av_true == m_bStatistics){
		m_StatisticsBitRate += Pack->GetRawLength();
		m_StatisticsFrameRate++;
		if (Pack->FrameType() != avFrameT_I) {
			m_StatisticsGop++;
		}
		else{
			m_Gop = m_StatisticsGop + 1;
			m_StatisticsGop = 0;
			m_ImageHeigh = Pack->ImageHeigh();
			m_ImageWidth = Pack->ImageWidth();
			m_Comp = Pack->Comp();
		}
	}

	if (m_bStartDecode == av_false && Pack->FrameType() != avFrameT_I){
		return;
	}
	AvDecodeRenderBuffer(m_ScreenID, (unsigned char *)Pack->GetBuffer(), Pack->GetLength());
	m_bStartDecode = av_true;
}

av_void CAvPreview::OnTimer(CAvTimer &Timer)
{
	m_BitRate = m_StatisticsBitRate / 3;
	m_FrameRate = m_StatisticsFrameRate / 3;
	
	m_StatisticsBitRate = 0;
	m_StatisticsFrameRate = 0;
	m_StatisticsGop = 0;
}

av_void CAvPreview::SetSpiltScreen(int SpiltScreenNum)
{
	m_SpiltScreenNum = SpiltScreenNum;
	AvDecodeSplit(SpiltScreenNum);
	m_gPause = av_false;
}
av_void	CAvPreview::SplitScreenClear(int ScreenID)
{
	if (ScreenID == -1){
		m_gPause = av_true;
	}
	else{
		m_gPreviewManager[ScreenID]->Pause(av_true);
	}
	AvDecodeClears(ScreenID);
}

E_EncodeCHL		CAvPreview::GetShowCHL(av_int Channel)
{
	if (m_DecodeCaps.MaxChannels == 0){
		AvDecodeGetCaps(&m_DecodeCaps);
	}
	
	if (Channel > 31){
		return CHL_SUB1_T;
	}

	if (m_DecodeCaps.MainStreamMode[m_SpiltScreenNum] & AvMask(Channel)){
		return CHL_MAIN_T;
	}
	else{
		return CHL_SUB1_T;
	}
}


av_u32		 avWareGetWindowsIdByScreenID(int SrceenID)
{
	if (NULL == m_gPreviewManager[SrceenID]){
		return 0;
	}
	else{
		return m_gPreviewManager[SrceenID]->GetWindowsID();
	}
}
C_RECT		*avWareGetWindowsRectByScreenID(int SrceenID)
{
	if (NULL == m_gPreviewManager[SrceenID]){
		return NULL;
	}
	else{
		return &m_gPreviewManager[SrceenID]->GetWindowsRect();
	}
}
