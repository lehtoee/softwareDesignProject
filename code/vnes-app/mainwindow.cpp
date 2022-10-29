#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <apicalls.hh>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->fetchDataButton, &QPushButton::clicked, this, &MainWindow::onFetchDataButtonClicked);

    //Button icons

    ui->trafficButton->setIcon(QIcon(":/media/traffic.png"));
    ui->weatherButton->setIcon(QIcon(":/media/cloud.png"));
    ui->combinedButton->setIcon(QIcon(":/media/combinedData.png"));
    ui->fetchDataButton->setIcon(QIcon(":/media/fetchData.png"));

    ui->trafficButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onFetchDataButtonClicked()
{
    apiCalls api;
    api.pullData("FMI");
}

void MainWindow::on_trafficButton_clicked()
{
  ui->weatherButton->setChecked(false);
  ui->combinedButton->setChecked(false);
  ui->dataLabel->setText("Traffic Data");
}

void MainWindow::on_weatherButton_clicked()
{
  ui->trafficButton->setChecked(false);
  ui->combinedButton->setChecked(false);
  ui->dataLabel->setText("Weather Data");
}

void MainWindow::on_combinedButton_clicked()
{
  ui->trafficButton->setChecked(false);
  ui->weatherButton->setChecked(false);
  ui->dataLabel->setText("Combined Data");
}
