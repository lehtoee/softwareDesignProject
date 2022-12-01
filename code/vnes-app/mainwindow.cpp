#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <networkhandler.h>
#include <iostream>

using namespace std;

int locationDropDownIndex;
int timelineDropDownIndex;
int dataTypeDropDownIndex;

MainWindow::MainWindow(Controller *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    controller_(controller)
{
    ui->setupUi(this);


    connect(ui->fetchDataButton, &QPushButton::clicked, this, &MainWindow::onFetchDataButtonClicked);

    //Button icons

    ui->trafficButton->setIcon(QIcon(":/media/traffic.png"));
    ui->weatherButton->setIcon(QIcon(":/media/cloud.png"));
    ui->combinedButton->setIcon(QIcon(":/media/combinedData.png"));
    ui->fetchDataButton->setIcon(QIcon(":/media/fetchData.png"));


    //Set options for drop downs
    setTrafficDataDropDowns();

    ui->trafficButton->setChecked(true);
    locationDropDownIndex = 0;
    timelineDropDownIndex = 0;
    dataTypeDropDownIndex = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTimelineDropDown()
{
    ui->timelineDropDown->clear();

    ui->timelineDropDown->addItem("1 day");
    ui->timelineDropDown->addItem("1 week");
    ui->timelineDropDown->addItem("1 month");
    ui->timelineDropDown->addItem("1 year");
    ui->timelineDropDown->addItem("10 years");
}

void MainWindow::setLocationDropDown()
{
    ui->locationDropDown->clear();

    ui->locationDropDown->addItem("Tampere");
    ui->locationDropDown->addItem("Oulu");
    ui->locationDropDown->addItem("Helsinki");
    ui->locationDropDown->addItem("Jyväskylä");
    ui->locationDropDown->addItem("Turku");
}

void MainWindow::setTrafficDataDropDowns()
{
    setTimelineDropDown();
    setLocationDropDown();

    ui->datatypeDropDown->clear();
    ui->datatypeDropDown->addItem("Road maintenance");
    ui->datatypeDropDown->addItem("Road condition forecast");
    ui->datatypeDropDown->addItem("Traffic messages");
    ui->datatypeDropDown->show();
}

void MainWindow::setWeatherDataDropDowns()
{
    setTimelineDropDown();
    setLocationDropDown();

    ui->datatypeDropDown->clear();
    ui->datatypeDropDown->addItem("Temperature");
    ui->datatypeDropDown->addItem("Observed wind");
    ui->datatypeDropDown->addItem("Predicted wind");
    ui->datatypeDropDown->addItem("Predicted temperature");
    ui->datatypeDropDown->show();
}

void MainWindow::setCombinedDataDropDowns()
{
    setTimelineDropDown();
    setLocationDropDown();

    ui->datatypeDropDown->clear();
    ui->datatypeDropDown->hide();
}

void MainWindow::onFetchDataButtonClicked()
{
    std::vector<QString> j({"21","61","22","62"});
    controller_->pushButtonClicked("Digitraffic", "trafficmessages", j, "2022-01-19T10:06:38Z");
}

void MainWindow::on_trafficButton_clicked()
{
  ui->weatherButton->setChecked(false);
  ui->combinedButton->setChecked(false);
  ui->dataLabel->setText("Traffic Data");

  ui->datatypeLabel->show();
  setTrafficDataDropDowns();
}

void MainWindow::on_weatherButton_clicked()
{
  ui->trafficButton->setChecked(false);
  ui->combinedButton->setChecked(false);
  ui->dataLabel->setText("Weather Data");

  ui->datatypeLabel->show();
  setWeatherDataDropDowns();
}

void MainWindow::on_combinedButton_clicked()
{
  ui->trafficButton->setChecked(false);
  ui->weatherButton->setChecked(false);
  ui->dataLabel->setText("Combined Data");

  ui->datatypeLabel->hide();
  setCombinedDataDropDowns();
}

void MainWindow::on_locationDropDown_activated(int index)
{
    locationDropDownIndex = index;
}


void MainWindow::on_timelineDropDown_activated(int index)
{
    timelineDropDownIndex = index;
}


void MainWindow::on_datatypeDropDown_activated(int index)
{
    dataTypeDropDownIndex = index;
}

