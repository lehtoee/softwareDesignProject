#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <apicalls.hh>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->fetchDataButton, &QPushButton::clicked, this, &MainWindow::onFetchDataButtonClicked);
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
