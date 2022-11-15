#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <controller.h>

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
