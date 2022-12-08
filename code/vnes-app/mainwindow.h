#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <unordered_map>

using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int locationDropDownIndex;
    int timelineDropDownIndex;
    int weatherDataTypeDropDownIndex;
    int trafficDataTypeDropDownIndex;

    void createChart(QString, QString, unordered_map<QString, QString>, unordered_map<QString, vector<double>>);

signals:
    void fetchDigiTraffic(QString source, QString datatype, QString location, QString time);
    void fetchFMI(QString source, QString datatype, QString location, QString time);

private slots:

    void onFetchDataButtonClicked();

    void on_trafficButton_clicked();

    void on_weatherButton_clicked();

    void on_combinedButton_clicked();

    void setTimelineDropDown();

    void setLocationDropDown();

    void setTrafficDataDropDowns();

    void setWeatherDataDropDowns();

    void setCombinedDataDropDowns();

    void on_locationDropDown_activated(int index);

    void on_timelineDropDown_activated(int index);

    void on_datatypeDropDown_activated(int index);

private:
    QChartView * createTrafficMaintanaceChart(unordered_map<QString, QString>, int);
    QWidget * createTraffcRoadconditionsChart(unordered_map<QString, QString>, int);
    QChartView * createMonthlyWeatherChart(unordered_map<QString, vector<double>>, int);
    QChartView * createWeatherChart(unordered_map<QString, vector<double>>, QString, int);
    QString getWeatherDataType();
    QString getTrafficDataType();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

