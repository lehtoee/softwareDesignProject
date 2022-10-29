#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void onFetchDataButtonClicked();

    void on_trafficButton_clicked();

    void on_weatherButton_clicked();

    void on_combinedButton_clicked();

  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
