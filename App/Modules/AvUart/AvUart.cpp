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
#include "AvUart/AvUart.h"
#include "Apis/AvEnuminline.h"

#define CHECK_SUM_START 1
#define CHECK_SUM_SPOT  5
#define BUILD_STR_LEN   7


static av_32 BuildCmdCheckSum(char *CmdBuffer, av_32 start_idx, av_32 stop_idx)
{
	if (NULL == CmdBuffer)
	{
		av_error("input param is error...\n");
		return av_false;
	}

	int idx = 0;
    int check_sum = 0;

    for (idx = start_idx; idx <= stop_idx; idx++)
    {
        check_sum += *(CmdBuffer + idx);
    }

    check_sum = check_sum % 0x100;
    check_sum = (check_sum & 0xFF);

    return check_sum;
}


SINGLETON_IMPLEMENT(CAvUart)

static av_bool PtzCmd2Buffer(C_PtzCmd &PtzCmd, av_buf &buf)
{
	char  *pData = buf.base;
	const char PELCO_D[10] = { 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01 };
	memcpy(pData, PELCO_D, sizeof(PELCO_D));

	av_msg("PtzCmd[%s], Value = %d\n", 
		EnumNamePtzCommand((PtzCommand)PtzCmd.PtzCmd), PtzCmd.Value);
	switch (PtzCmd.PtzCmd)
	{
	case PtzCommand_NONE:
		break;
			///����
	case PtzCommand_STOP:
		break;
	case PtzCommand_UP:
		pData[3] = 0x08;
		pData[4] = PtzCmd.PtzSpeed;
		break;
	case PtzCommand_DOWN:
		pData[3] = 0x10;
		pData[4] = PtzCmd.PtzSpeed;
		break;
	case PtzCommand_LEFT:
		pData[3] = 0x04;
		pData[5] = PtzCmd.PtzSpeed;
		break;
	case PtzCommand_RIGHT:
		pData[3] = 0x02;
		pData[5] = PtzCmd.PtzSpeed;
		break;
	case PtzCommand_LEFTUP:
		break;
	case PtzCommand_LEFTDOWN:
		break;
	case PtzCommand_RIGHTUP:
		break;
	case PtzCommand_RIGHTDOWN:
		break;
			///�����˶�
	case PtzCommand_ABSOLUTE_MOVE:
		break;
			///����˶�
	case PtzCommand_RELATIVE_MOVE:
		break;
			///���Ա佹
	case PtzCommand_ABSOLUTE_FOCUS:
		break;
			///�䱶
	case PtzCommand_ZOOM_WIDE:
		pData[3] = 0x40;
		break;
	case PtzCommand_ZOOM_TELE:
		pData[3] = 0x20;
		break;
			///�۽�
	case PtzCommand_FOCUS_FAR:
		break;
	case PtzCommand_FOCUS_NEAR:
		break;
			///��Ȧ
	case PtzCommand_IRIS_LARGE:
		pData[1] = 0x01;
		pData[2] = 0x02;
		break;
	case PtzCommand_IRIS_SMALL:
		pData[1] = 0x01;
		pData[2] = 0x04;
		break;
			///��������
	case PtzCommand_ALARM:
		break;
			///�ƹ�
	case PtzCommand_LIGHT_ON:
		break;
	case PtzCommand_LIGHT_OFF:
		break;
			///����Ԥ�õ�
	case PtzCommand_SETPRESET:
		break;
			///���Ԥ�õ�
	case PtzCommand_CLEARPRESET:
		break;
			///ת��Ԥ�õ�
	case PtzCommand_GOTOPRESET:
		break;
			///ˮƽ��ʼ 
	case PtzCommand_AUTOPANON:
		break;
			///ˮƽ����
	case PtzCommand_AUTOPANOFF:
		break;
			///���ñ߽� 
	case PtzCommand_SETLIMIT:
		break;
			///�Զ�ɨ�迪ʼ
	case PtzCommand_AUTOSCANON:
		break;
			///�Զ�ɨ�迪ֹͣ
	case PtzCommand_AUTOSCANOFF:
		break;
			///����Ѳ����
	case PtzCommand_ADDTOUR:
		break;
			///ɾ��Ѳ���� 	
	case PtzCommand_DELETETOUR:
		break;
			///��ʼѲ��
	case PtzCommand_STARTTOUR:
		break;
			///����Ѳ��
	case PtzCommand_STOPTOUR:
		break;
			///ɾ��Ѳ��
	case PtzCommand_CLEARTOUR:
		break;
			///����ģʽ
	case PtzCommand_SETPATTERN:
		break;
			///��ʼģʽ
	case PtzCommand_STARTPATTERN:
		break;
			///ֹͣģʽ
	case PtzCommand_STOPPATTERN:
		break;
			///���ģʽ
	case PtzCommand_CLEARPATTERN:
		break;
			///���ٶ�λ
	case PtzCommand_POSITION:
		break;
			///��������
	case PtzCommand_AUX_ON:
		break;
	case PtzCommand_AUX_OFF:
		pData[3] = 0x0b;
		pData[4] = PtzCmd.Value;
		av_msg("Auto Cali \n");
		break;
			///����˵�
	case PtzCommand_MENU:
		break;
			///�˳�����˵�
	case PtzCommand_EXIT:
		break;
			///ȷ��
	case PtzCommand_ENTER:
		break;
			///ȡ��
	case PtzCommand_ESC:
		break;
			///�˵����²���
	case PtzCommand_MENUUPDOWN:
		break;
			///�˵����Ҳ���
	case PtzCommand_MENULEFTRIGHT:
		break;
			///�����л�
	case PtzCommand_MATRIXSWITCH:
		break;
			/// ��ͷ��ת
	case PtzCommand_FLIP:
		break;
			///��̨��λ
	case PtzCommand_RESET:
		break;
			///�˵����Ҳ��� ����Ҫ��������Եƹ�������Ŀ��ƣ�
	case PtzCommand_LIGHTCONTROLLER:
		break;

	default:
		return av_false;
		break;
	}

	pData[6] = BuildCmdCheckSum(pData, CHECK_SUM_START, CHECK_SUM_SPOT);
	buf.len = BUILD_STR_LEN;
	
	return av_true;
}
av_bool CAvUart::Initialize()
{
	AvSerialInit();
	UartCaps();
	int i = 0;
	m_Config.Update();
	
	for (i = 0; i < m_SerialCaps.TotalSerials; i++){
		if (av_true != UartOpen(i)){
			av_error("open Uart index  = %d Error\n", i);
			continue;
		}
		ConfigUart &SerialAttr = m_Config.GetConfig(i);
		SetAttr(i, SerialAttr.Attribute);
	}
	return av_true;
}
av_bool CAvUart::Write(av_uchar index, av_buf &buf)
{
	if (index >= m_SerialCaps.TotalSerials) {
		av_error("Ptz Write Index[%d]  TotalSerials [%d]\n", index, m_SerialCaps.TotalSerials);
		return av_false;
	}
	if (buf.len <= 0 || buf.base == NULL) {
		av_error("Ptz Write buf.size[%d]  buf.base [%p]\n", buf.len, buf.base);
		return av_false;
	}
	return AvSerialWrite(index, &buf);
}
av_bool CAvUart::Read(av_uchar index, av_buf &buf)
{
	if (index >= m_SerialCaps.TotalSerials) {
		av_error("Ptz Write Index[%d]  TotalSerials [%d]\n", index, m_SerialCaps.TotalSerials);
		return av_false;
	}
	if (buf.size <= 0 || buf.base == NULL) return av_false;
	return AvSerialRead(index, &buf);
}
av_bool CAvUart::SetAttr(av_uchar index, C_SerialAttr &Attr)
{
	if (index >= m_SerialCaps.TotalSerials) {
		av_error("Ptz Write Index[%d]  TotalSerials [%d]\n", index, m_SerialCaps.TotalSerials);
		return av_false;
	}
	av_bool ret =  AvSerialSetAttribute(index, &Attr);
	return ret;
}

av_void CAvUart::OnConfigsModify(CAvConfigUart *Config, int &result)
{
	for (int i = 0; i < m_SerialCaps.TotalSerials; i++){
		ConfigUart &newConf = Config->GetConfig(i);
		ConfigUart &oldConf = m_Config.GetConfig(i);
		if (0 != memcmp(&newConf.Attribute, &oldConf.Attribute, sizeof(C_SerialAttr))){
			SetAttr(i, newConf.Attribute);
			newConf.Attribute = oldConf.Attribute;
			newConf.Enable = oldConf.Enable;
		}
	}
}

av_bool CAvUart::PtzGetCaps(C_PtzCaps &Ptzcaps)
{
	return av_true;
}
av_bool CAvUart::PtzSetProfile(C_PtzProfile &PtzProfile)
{
	return av_true;
}
av_bool CAvUart::PtzGetProfile(C_PtzProfile &PtzProfile)
{
	return av_true;
}

av_bool CAvUart::PtzSetCommand(C_PtzCmd &PtzCmd)
{
	av_buf buf;
	char buffer[16] = {0};
	buf.base = buffer;
	buf.size = sizeof(buffer);
	buf.len = 0;
	if (av_false == PtzCmd2Buffer(PtzCmd, buf)){
		return av_false;
	}
	av_uchar index = -1;
	for (int i = 0; i < m_SerialCaps.TotalSerials; i++){
		if (COM_PTZ == m_SerialCaps.Com_t[i]){
			index = i;
			break;
		}
	}
	return Write(index, buf);
}


av_bool CAvUart::UartOpen(av_uchar index)
{
	if (index >= m_SerialCaps.TotalSerials) {
		av_error("UartOpen Index[%d]  TotalSerials [%d]\n", index, m_SerialCaps.TotalSerials);
		return av_false;
	}
	return AvSerialOpen(index);
}
av_bool CAvUart::UartClose(av_uchar index)
{
	if (index >= m_SerialCaps.TotalSerials) {
		av_error("UartClose Index[%d]  TotalSerials [%d]\n", index, m_SerialCaps.TotalSerials);
		return av_false;
	}
	return AvSerialClose(index);
}

av_bool CAvUart::UartCaps()
{
	av_bool ret = AvSerialCaps(&m_SerialCaps);
	if (ret != av_true){
		memset(&m_SerialCaps, 0x00, sizeof(C_SerialCaps));
		return av_false;
	}
	return av_true;
}

CAvUart::CAvUart()
{
	memset(&m_SerialCaps, 0x00, sizeof(C_SerialCaps));
}

CAvUart::~CAvUart()
{

}
