#include "PlotNetCLS.h"


NetPlotCLS::NetPlotCLS(QWidget *parent):QWidget(parent),
              timer(new QTimer(this)),
              startTime(QTime::currentTime()),
              totalBytesReceived(200)
{

    connect(timer, &QTimer::timeout, this, &NetPlotCLS::updatePlot);
    ++totalBytesReceived;
    timer->start(1000);
   // m_pChart->show();
}

void NetPlotCLS::updatePlot()
{
    QTime currentTime = QTime::currentTime();
    int elapsedSeconds = startTime.secsTo(currentTime);
    qreal speed = totalBytesReceived / elapsedSeconds;

    // Add data to the series
    m_pSeries->append(elapsedSeconds, speed);

    // Update chart axis

    m_pChart->axes(Qt::Horizontal).first()->setRange(0, elapsedSeconds);
    //chart->axes(Qt::Vertical).first()->setRange(0, speed * 1.2);
    m_pChart->axes(Qt::Vertical).first()->setRange(0, speed * 2);
    // Update the chart
    m_pChart->update();
    //m_pChart->show();
}













