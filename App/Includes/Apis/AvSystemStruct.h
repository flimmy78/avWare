#ifndef _AVSYSTEMSTRUCT_H_
#define _AVSYSTEMSTRUCT_H_
#include "AvWareType.h"
#include "AvEnum.h"

typedef struct {
	av_u32 tv_sec;		//����ʱ��ʱ���� 1900 ���������
	av_u32 tv_usec;		//����ʱ��ʱ����

	av_u32 t_year;		//ʵ�ʵ��� 2016
	av_u32 t_mon;		//ʵ�ʵ��� 1-12
	av_u32 t_day;		//ʵ�ʵ��� 1-31

	av_uchar t_week;	//rang 1-7
	av_uchar t_hour;
	av_uchar t_min;
	av_uchar t_sec;

	av_u32 t_todaysec;	//���������
}av_timeval;

typedef struct {
	av_int Start;
	av_int End;
}C_Region;

typedef struct{
	av_int Sx;
	av_int Sy;
	av_int Width;
	av_int Heigh;
}C_RECT;

typedef struct {
	av_u32 NetCommMask;
	av_u32 NetCommGetModeMask[8];
}C_NetCommCaps;

typedef struct{
	av_uint FocusCtrlModeMask;
	av_uint FocusSensitivityMax;
	av_uint FocusRegionMask;
	av_uint FocusSearchModeMask;
	av_uint IrisCtrlModeMask;
	av_uint ZoomSpeedMax;
	av_bool bSupportFigureZoom;
}C_PtzAdvancedCameraLensCaps;

typedef struct{
	PtzCameraLensFocusCtrlMode FocusCtrlMode;
	av_uint FocusSensitivity;
	PtzCameraLensFocusRegion FocusRegion;
	PtzCameraLensFocusSearchMode FocusSearchMode;
	PtzCameraLensIrisCtrlMode IrisCtrlMode;
	av_uint ZoomSpeed;
	av_bool bFigureZoom;
}C_PtzAdvancedCameraLensProfile;



typedef struct{
	NetCommT NetComm;
	av_uint NetLinkStatMask;
	av_uint	NetUploadRate;
	av_uint NetDownLoadRate;
}C_NetStatusInfo;

typedef struct {
	av_uint CpuFrequency;
	av_uint CpuFreeRate;
	av_uint MemTotal;
	av_uint MemFree;
}C_CpuMemStatusInfo;


typedef struct {
	av_u32	 CompMask;
	av_u32	 ImageSizeMask;// CHL_MAIN_T
	av_uchar MaxCover;
	av_uchar OverLayMask;
	av_uchar BitRateCtrlMask;

	av_uchar ExtChannelMask;
	av_u32   ExtImageSizeMask[CaptureSize_LAST];
	av_u32   FrameRateMask[CaptureSize_LAST];
}C_EncodeCaps;

typedef struct{
	CaptureSize		ImageSize;
	av_u32			ImageSelfWidth;
	av_u32			ImageSelfHeigh;
	av_u32			FrameRate;
	av_u32			Gop;
	AvComp			Comp;
	BitRateCtrl		BitRateCtl;
	av_u32			BitRateValue;
	av_u32          Qlevel;
}C_EnCodeProfile;


typedef struct {
	av_u32 BrightnessRang;
	av_u32 ContrastRang;
	av_u32 HueRang;
	av_u32 SaturationRang;
}C_ImageCaps;

typedef struct {
	av_u32 Brightness;
	av_u32 Contrast;
	av_u32 Hue;
	av_u32 Saturation;
}C_ImageProfile;

typedef struct {
	av_u32	nMaxEncodePower;
	av_u32	nMaxEncodeChannel;
	av_u32	nMaxEncodeExtChannel;
	av_u32	nMaxDecodeChannel;
	av_u32	nMaxDecodeExtChannel;
}C_DspCaps;


typedef C_DspCaps C_DeviceCaps;

typedef struct {
	av_u32      IrCutMask;
	av_u32      MirrorMask;
	av_u32      ExposureMask;
	C_Region    ExposureValueRegion;
	av_u32      WhiteBalanceMask;
	C_Region    WhiteBalanceValueRegion;
	av_u32      AntiFlckerMask;
	C_Region    AntiFlckerValueRegion;
	av_u32      CvbsMask;
	av_u32		WdrModeMask;
	C_Region	WdrValueRegion;
	av_u32		ShutterModeMask;
	C_Region	ShutterMaxRegion;
}C_CaptureCaps;

typedef struct {
	IrCutMode 			IrCut;
	C_Region 			IrCutTimer;
	av_u32 				MirrorMaskValue;
	ExposureMode 		Exposure;
	av_int 				ExposureValue;
	WhiteBalanceMode 	WhiteBalance;
	av_int 				WhiteBalanceValue;
	AntiFlckerMode 		AntiFlcker;
	av_int 				AntiFlckerValue;
	av_bool 			bOpenCvbs;
	WdrMode				Wdr;
	av_uint				WdrValue;
	ShutterMode			Shutter;
	av_uint				ShutterMax;

}C_CaptureProfile;


typedef struct {
	av_uint CaptureDeviceMask;
	av_uint SoundModeMask;
	av_uint CompMask;
	av_uint SampleRateMask[AvComp_LAST];
	av_uint SampleBitsMask[AvComp_LAST];
	av_uint VolumeRang;
	av_uint VoiceQualityMask;
}C_AudioCaps;

typedef struct{
	AvComp					Comp;
	av_uint					VolumeCapture;
	av_uint					VolumePlay;
	AudioSampleRate			SampleRate;
	AudioSampleBits			SampleBits;
	AudioSoundMode			SoundMode;
	AudioCaptureDevice		CaptureDevice;
	av_uint					VoiceQualityMask;
}C_AudioProfile;



typedef struct {
	av_uint CoverbEnMask;
	av_uint CoverBgRGB;
	C_RECT  CoverZone[ConfMaxCover];
}C_CoverProfile;

typedef struct {
	av_uint OverLayTypeMask;
	av_bool bSupportBg;
	av_bool bSupportFg;
	av_uint OverLayDateTimeSplitMask;
	av_uint OverLayDateTimeStyleMask;
	av_uint FontSizeMask;
	av_uint MaxTextExt;
}C_OverLayCaps;
typedef struct {
	OverLayType		Index;
	av_bool			bOpen;
	
	av_uint			BgRgba;
	av_uint			FgRgba;

	FontSize		Fontsize;
	OverLayDateTimeSplit Split;
	OverLayDateTimeStyle Style;
	C_RECT			Rect;

	char			TextChannel[128];
	char			TextExt1[128];
	char			TextExt2[128];
	char			TextExt3[128];
}C_OverLayProfile;

typedef struct {
	unsigned int AlarmEventMask;
	int MaxAlmIn;
	int MaxAlmOut;
}C_AlarmCaps;


typedef struct{
	av_u32 Mask;
}C_IntelligentCaps;



#endif

