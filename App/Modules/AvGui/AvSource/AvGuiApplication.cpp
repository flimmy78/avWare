#include "AvGuiApplication.h"


SINGLETON_IMPLEMENT(CAvGuiApp);
static int    AppArgc = 1;
static char *AppArgs = __FILE__;
CAvGuiApp::CAvGuiApp() :m_Application(AppArgc, &AppArgs)
{
	m_MainWindows = NULL;

}

CAvGuiApp::~CAvGuiApp()
{


}

av_bool CAvGuiApp::Initialize()
{
	Q_INIT_RESOURCE(avWare);
	CAvUiComm::SetUTF8Code();
	CAvUiComm::SetStyle("black");//��ɫ���
	//CAvUiComm::SetStyle("blue");//��ɫ���
	//CAvUiComm::SetStyle("gray");//��ɫ���
	//CAvUiComm::SetStyle("navy");//����ɫ���
	CAvUiComm::SetChinese();



	m_MainWindows = new FrmMainWindows;
	m_MainWindows->show();
	CAvUiComm::FormInCenter(m_MainWindows);

#if defined (WIN32)
	FloatingButton	*m_FloatButton = new FloatingButton;
	QObject::connect(m_FloatButton, SIGNAL(SignalsButtonClick()), m_MainWindows, SLOT(on_BtnOpenMenu_clicked()));
	m_FloatButton->show();

#else
	QAvEvent e(QAvEvent::QAvEvent_MaxVideoAreaWindows);
	CAvGuiApp::PostQAvEvent(e);


// 	QAvEvent e(QAvEvent::QAvEvent_MaxWindows);
// 	CAvGuiApp::PostQAvEvent(e);
#endif



	return av_true;
}

av_void CAvGuiApp::exec()
{


	//QAvEvent event(QAvEvent::QAvEvent_SearchDevice);
	//PostQAvEvent(event);
	m_Application.exec();

	Q_CLEANUP_RESOURCE(avWare);

}

FrmMainWindows *CAvGuiApp::GetMainWindows()
{
	return m_MainWindows;
}
av_bool CAvGuiApp::PostQAvEvent(QAvEvent &event)
{
	QApplication::postEvent(m_MainWindows, new QAvEvent(event));
	return av_true;
}

