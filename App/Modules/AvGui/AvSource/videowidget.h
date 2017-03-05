﻿#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QAction>

#include "AvForm/wgetvideoinfo.h"
#include "AvPreview/AvPreview.h"


namespace Ui {
class VideoWidget;
}

class VideoWidget : public QWidget
{
    Q_OBJECT

public:
	void SetTotalWindows(int totalWins);
    explicit VideoWidget(QWidget *parent = 0);
	void	BindWidgetScreenID(int ScreenID);
    ~VideoWidget();
	void PreviewSetStatistics(bool bOpen = true);
	void PreviewGetStatistics(QString &ImageSize, QString &Comp, QString &FrameRate, QString &BitRate);
	void SelectWindowsLive();
public:
	void PreviewStart(int Channel, int Slave, bool bOpen);
	void resizeEvent(QResizeEvent *e);

	void setGeometry(const QRect &);
private:
	void contextMenuEvent(QContextMenuEvent *event);

private slots:
	void SlotsMenuTriggered(QAction *Action);
	void SlotsContextMenuEvent(QContextMenuEvent *event);
signals:
    void widgetSelecting(QWidget *);
    void videoWidgetResize();
	void WidgetChange(QRect &Rect);
	void SignalsSpiltScreen(int split);
	void SignalsMaxWindows(QWidget *, bool);

private slots:
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

public:
    QString		m_filePath;
    bool		m_bSelected;

	CAvPreview	*	m_Preview;
	bool		m_bPreview;
	int			m_Channel;
	int			m_ScreenID;
	int			m_TotalWindows;

};

#endif // VIDEOWIDGET_H
