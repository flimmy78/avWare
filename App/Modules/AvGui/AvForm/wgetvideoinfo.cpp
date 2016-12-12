#include "wgetvideoinfo.h"
#include "ui_wgetvideoinfo.h"
#include "AvUiComm/IconComm.h"

WgetVideoInfo::WgetVideoInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WgetVideoInfo)
{
    ui->setupUi(this);
// 	setMouseTracking(true);
// 	setWindowFlags(Qt::FramelessWindowHint);
//     setAttribute(Qt::WA_TranslucentBackground, true);
	//setWindowOpacity(0.1);
	raise();
	m_Palette = new QPalette;
	m_Palette->setColor(QPalette::WindowText, Qt::green);
	m_Palette->setColor(QPalette::Background, QColor(0x00, 0xff, 0x00, 0x00));

	m_PaletteTrigger = new QPalette;
	m_PaletteTrigger->setColor(QPalette::WindowText, QColor(0x00, 0xff, 0x00, 0x00));
	m_PaletteTrigger->setColor(QPalette::Background, QColor(0x00, 0xff, 0x00, 0x00));
	ui->LabAlarm->setPalette(*m_Palette);
	ui->LabStreamInfo->setPalette(*m_Palette);
	ui->LabListen->setPalette(*m_Palette);
	ui->LabRecord->setPalette(*m_Palette);
	ui->LabSpeak->setPalette(*m_Palette);
	
	m_bBtnEnableVideoClicked = false;
	m_bBtnListenClicked = false;
	m_bBtnRecordClicked = false;
	m_bBtnSnapClicked = false;
	m_bBtnSpeakListenCliecked = false;
	ResetOSDVideoInfo();
	ResizeIconSize(12);
	
}

WgetVideoInfo::~WgetVideoInfo()
{
    delete ui;
}

void WgetVideoInfo::ResizeIconSize(int size)
{
	m_IconSize = size;
	IconComm::Instance()->SetIcon(ui->BtnEnableVideo, QChar(0xf04b), m_IconSize);
	IconComm::Instance()->SetIcon(ui->BtnListen, QChar(0xf025), m_IconSize);
	IconComm::Instance()->SetIcon(ui->BtnRecord, QChar(0xf0c7), m_IconSize);
	IconComm::Instance()->SetIcon(ui->BtnSnap, QChar(0xf03e), m_IconSize);
	IconComm::Instance()->SetIcon(ui->BtnSpeakListen, QChar(0xf130), m_IconSize);


	IconComm::Instance()->SetIcon(ui->LabAlarm, QChar(0xf0a2), m_IconSize);
	IconComm::Instance()->SetIcon(ui->LabListen, QChar(0xf025), m_IconSize);
	IconComm::Instance()->SetIcon(ui->LabRecord, QChar(0xf03d), m_IconSize);

	IconComm::Instance()->SetIcon(ui->LabSpeak, QChar(0xf130), m_IconSize);
	QFont font = QApplication::font();
	font.setPointSize(m_IconSize);
	ui->LabStreamInfo->setFont(font);
}
void  WgetVideoInfo::ResetOSDVideoInfo()
{
	SetOSDVideoInfo(QString("0 kbps"), QString("0*0"), QString("0 FPS"), QString("H264"));
}
void WgetVideoInfo::SetOSDVideoInfo(QString kbps, QString ImageSize, QString FrameRate, QString EncodeType)
{

	QString Text;
	Text = ImageSize;
	if (FrameRate.size() != 0){
		Text += "\n";
		Text += FrameRate;
	}
	if (kbps.size() != 0){
		Text += "\n";
		Text += kbps;
	}
	if (EncodeType.size() != 0){
		Text += "\n";
		Text += EncodeType;
	}
	ui->LabStreamInfo->setText(Text);

	
}
void WgetVideoInfo::mousePressEvent(QMouseEvent *event)
{
	emit SignalsMousePress(event);
}
void WgetVideoInfo::mouseDoubleClickEvent(QMouseEvent *event)
{
	emit SignalsMouseDoubleClickEvent(event);
}

void WgetVideoInfo::contextMenuEvent(QContextMenuEvent *event)
{
	emit SignalsContextMenuEvent(event);
}

void WgetVideoInfo::resizeEvent(QResizeEvent* size)
{
	printf("size %d, %d \n", size->size().width(), size->size().height());
	int height = size->size().height();
	int IconSize = 0;
	if (height > 600){
		IconSize = 16;
	}
	else if (height > 400){
		IconSize = 14;
	}
	else if (height > 200){
		IconSize = 12;
	}
	else {
		IconSize = 10;
	}

	if (m_IconSize != IconSize){
		ResizeIconSize(IconSize);
	}
}

void WgetVideoInfo::on_BtnRecord_clicked()
{
	if (m_bBtnRecordClicked == false){
		ui->LabRecord->setPalette(*m_PaletteTrigger);
		//ui->LabRecord->show();
		
	}
	else{
		ui->LabRecord->setPalette(*m_Palette);
		//ui->LabRecord->hide();
	}

	m_bBtnRecordClicked = !m_bBtnRecordClicked;
}

void WgetVideoInfo::on_BtnSnap_clicked()
{
	m_bBtnSnapClicked = !m_bBtnSnapClicked;
}

void WgetVideoInfo::on_BtnSpeakListen_clicked()
{
	if (m_bBtnSpeakListenCliecked == false){
		//ui->LabSpeak->show();
		//ui->LabListen->show();
		ui->LabSpeak->setPalette(*m_PaletteTrigger);
		ui->LabListen->setPalette(*m_PaletteTrigger);
	}
	else{
		//ui->LabSpeak->hide();
		//ui->LabListen->hide();
		ui->LabSpeak->setPalette(*m_Palette);
		ui->LabListen->setPalette(*m_Palette);
	}
	m_bBtnSpeakListenCliecked = !m_bBtnSpeakListenCliecked;
}

void WgetVideoInfo::on_BtnListen_clicked()
{
	if (m_bBtnListenClicked == false){
		//ui->LabListen->show();
		ui->LabListen->setPalette(*m_PaletteTrigger);
	}
	else{
		//ui->LabListen->hide();
		ui->LabListen->setPalette(*m_Palette);
	}
	m_bBtnListenClicked = !m_bBtnListenClicked;
}

void WgetVideoInfo::on_BtnEnableVideo_clicked()
{
	if (m_bBtnEnableVideoClicked == false){
		IconComm::Instance()->SetIcon(ui->BtnEnableVideo, QChar(0xf0c8), m_IconSize);
	}
	else{
		IconComm::Instance()->SetIcon(ui->BtnEnableVideo, QChar(0xf04b), m_IconSize);
	}
	m_bBtnEnableVideoClicked = !m_bBtnEnableVideoClicked;
}
