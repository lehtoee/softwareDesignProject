#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <controller.h>
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
    explicit MainWindow(Controller *controller, QWidget *parent = nullptr);
    ~MainWindow();
    int locationDropDownIndex;
    int timelineDropDownIndex;
    int dataTypeDropDownIndex;

private slots:
    void createChart(QString, QString, unordered_map<QString, QString>, unordered_map<QString, vector<double>>);

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
    Ui::MainWindow *ui;
    Controller* controller_;
};

#endif // MAINWINDOW_H
