#pragma once
#include <QApplication>
#include <QtWidgets>
#include <QtCharts>

class NetPlotCLS : public QWidget
{
    Q_OBJECT
public:
    explicit NetPlotCLS(QWidget *parent = nullptr);

    void setChart(QtCharts::QChart* Chart) {m_pChart = Chart;}
    void setChartView(QtCharts::QChartView* chartView) {m_pChartView = chartView;}
    void setSeries( QtCharts::QLineSeries* series) {m_pSeries = series;}
    void setBoxLayout(QVBoxLayout* HboxLayout) {m_pChartlayout = HboxLayout;}

    QtCharts::QChart* getPChart() {return m_pChart;}
    QtCharts::QChartView* getChartView () {return m_pChartView;}
    QtCharts::QLineSeries* getSeries() { return m_pSeries;}
    QVBoxLayout* getVBoxLayout() { return m_pChartlayout;}

public slots:
    void updatePlot();
private:
    QVBoxLayout *m_pChartlayout;
    QtCharts::QChart* m_pChart;
    QtCharts::QChartView* m_pChartView;
    QtCharts::QLineSeries* m_pSeries;
    QTimer *timer;
    QTime startTime;
    quint64 totalBytesReceived;
};



