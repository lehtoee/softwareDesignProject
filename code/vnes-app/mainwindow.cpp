#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <networkhandler.h>
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
#include <QPushButton>
#include <unordered_map>
#include <QVBoxLayout>


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

void MainWindow::createChart(QString contentType, QString dataType, unordered_map<QString, QString> data, unordered_map<QString, vector<double>> weatherData)
{
    if(contentType == "traffic")
    {
        if(dataType == "maintenance")
        {
            QPieSeries *series = new QPieSeries();
            for(auto ele: data)
            {
                series->append(ele.second, 0.2);
            }
            for(int i = 0; i < series->slices().count(); i++)
            {
                QPieSlice *slice = series->slices().at(i);
                slice->setLabelVisible(true);
            }
            QChart *chart = new QChart();
            chart->addSeries(series);
            QFont font;
            font.setPixelSize(36);
            chart->setTitleFont(font);
            chart->setTitle("Road Maintenance");
            chart->legend()->hide();
            chart->setAnimationOptions(QChart::AllAnimations);


            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(750, 520);
            chartView->show();

        }else if(dataType == "roadconditions")
        {
            QString symbol;
            for(auto ele : data)
            {
                if(ele.first == "weatherSymbol")
                {
                    symbol = ele.second;
                }
            }
            QBrush weatherLogo = QImage(":/media/"+symbol+".png");
            QChart *chart = new QChart();
            QFont font;
            font.setPixelSize(36);
            chart->setTitleFont(font);
            chart->setTitle("Road Condition");
            chart->setBackgroundBrush(weatherLogo);
            chart->setAnimationOptions(QChart::AllAnimations);

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(750, 520);
            chartView->show();
        }

    }else if(contentType == "weather")
    {
        if(dataType == "observed")
        {
            QChart *chart = new QChart();
            QValueAxis *axisX = new QValueAxis();
            axisX->setTitleText("Time (h)");
            axisX->setTickCount(7);
            chart->addAxis(axisX, Qt::AlignBottom);

            QBarSeries *b_series = new QBarSeries();
            vector<double> wind = weatherData["Windspeed"];
            QBarSet *set = new QBarSet("Wind");
            for(auto w: wind)
            {
                *set << w;
            }
            b_series->append(set);
            chart->addSeries(b_series);

            QValueAxis *axisY2 = new QValueAxis;
            axisY2->setMax(15);
            axisY2->setMin(0);
            axisY2->setTitleText("Wind (m/s)");
            chart->addAxis(axisY2, Qt::AlignRight);
            b_series->attachAxis(axisX);
            b_series->attachAxis(axisY2);

            QLineSeries *l_series = new QLineSeries();
            vector<double> temp = weatherData["Temperature"];
            int i = 0;
            for(auto t: temp)
            {
                l_series->append(i, t);
                i++;
            }
            l_series->setName("Temperature");
            chart->addSeries(l_series);
            QValueAxis *axisY = new QValueAxis;
            axisY->setMax(10);
            axisY->setMin(-10);
            axisY->setTitleText("Temperature (C)");
            chart->addAxis(axisY, Qt::AlignLeft);
            l_series->attachAxis(axisX);
            l_series->attachAxis(axisY);

            QFont font;
            font.setPixelSize(36);
            chart->setTitleFont(font);
            chart->setTitle("Observed Temperature & Wind Speed");
            chart->setAnimationOptions(QChart::AllAnimations);
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(750, 520);
            chartView->show();


        }else if(dataType == "forecast")
        {
            QChart *chart = new QChart();
            QValueAxis *axisX = new QValueAxis();
            axisX->setTitleText("Time (h)");
            axisX->setTickCount(7);
            chart->addAxis(axisX, Qt::AlignBottom);

            QBarSeries *b_series = new QBarSeries();
            vector<double> wind = weatherData["Windspeed"];
            QBarSet *set = new QBarSet("Wind");
            for(auto w: wind)
            {
                *set << w;
            }
            b_series->append(set);
            chart->addSeries(b_series);

            QValueAxis *axisY2 = new QValueAxis;
            axisY2->setMax(15);
            axisY2->setMin(0);
            axisY2->setTitleText("Wind (m/s)");
            chart->addAxis(axisY2, Qt::AlignRight);
            b_series->attachAxis(axisX);
            b_series->attachAxis(axisY2);

            QLineSeries *l_series = new QLineSeries();
            vector<double> temp = weatherData["Temperature"];
            int i = 0;
            for(auto t: temp)
            {
                l_series->append(i, t);
                i++;
            }
            l_series->setName("Temperature");
            chart->addSeries(l_series);
            QValueAxis *axisY = new QValueAxis;
            axisY->setMax(10);
            axisY->setMin(-10);
            axisY->setTitleText("Temperature (C)");
            chart->addAxis(axisY, Qt::AlignLeft);
            l_series->attachAxis(axisX);
            l_series->attachAxis(axisY);

            QFont font;
            font.setPixelSize(36);
            chart->setTitleFont(font);
            chart->setTitle("Forecast Temperature & Wind Speed");
            chart->setAnimationOptions(QChart::AllAnimations);
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(750, 520);
            chartView->show();
        }

    }else if(contentType == "combined")
    {
        //Traffic maintenance
        QPieSeries *series = new QPieSeries();
        for(auto ele: data)
        {
            series->append(ele.second, 0.2);
        }
        for(int i = 0; i < series->slices().count(); i++)
        {
            QPieSlice *slice = series->slices().at(i);
            slice->setLabelVisible(true);
        }
        QChart *chart = new QChart();
        chart->addSeries(series);
        QFont font;
        font.setPixelSize(18);
        chart->setTitleFont(font);
        chart->setTitle("Road Maintenance");
        chart->legend()->hide();
        chart->setAnimationOptions(QChart::AllAnimations);


        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(500, 300);

        //Weather
        QChart *chart1 = new QChart();
        QValueAxis *axisX = new QValueAxis();
        axisX->setTitleText("Time (h)");
        axisX->setTickCount(7);
        chart1->addAxis(axisX, Qt::AlignBottom);

        QBarSeries *b_series = new QBarSeries();
        vector<double> wind = weatherData["Windspeed"];
        QBarSet *set = new QBarSet("Wind");
        for(auto w: wind)
        {
            *set << w;
        }
        b_series->append(set);
        chart1->addSeries(b_series);

        QValueAxis *axisY2 = new QValueAxis;
        axisY2->setMax(15);
        axisY2->setMin(0);
        axisY2->setTitleText("Wind (m/s)");
        chart1->addAxis(axisY2, Qt::AlignRight);
        b_series->attachAxis(axisX);
        b_series->attachAxis(axisY2);

        QLineSeries *l_series = new QLineSeries();
        vector<double> temp = weatherData["Temperature"];
        int i = 0;
        for(auto t: temp)
        {
            l_series->append(i, t);
            i++;
        }
        l_series->setName("Temperature");
        chart1->addSeries(l_series);
        QValueAxis *axisY = new QValueAxis;
        axisY->setMax(10);
        axisY->setMin(-10);
        axisY->setTitleText("Temperature (C)");
        chart1->addAxis(axisY, Qt::AlignLeft);
        l_series->attachAxis(axisX);
        l_series->attachAxis(axisY);

        QFont font1;
        font.setPixelSize(18);
        chart1->setTitleFont(font);
        chart1->setTitle("Observed Temperature & Wind Speed");
        chart1->setAnimationOptions(QChart::AllAnimations);
        QChartView *chartView1 = new QChartView(chart1);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(500, 300);

        QWidget *window = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout(window);
        layout->addWidget(chartView);
        layout->addWidget(chartView1);
        window->resize(1000, 600);
        window->show();

    }

}

void MainWindow::setTimelineDropDown()
{
    ui->timelineDropDown->clear();

    ui->timelineDropDown->addItem("2 hours");
    ui->timelineDropDown->addItem("4 hours");
    ui->timelineDropDown->addItem("6 hours");
    ui->timelineDropDown->addItem("12 hours");
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
    ui->datatypeDropDown->addItem("Road Maintenance");
    ui->datatypeDropDown->addItem("Road Condition Forecast");
    ui->datatypeDropDown->show();
}

void MainWindow::setWeatherDataDropDowns()
{
    setTimelineDropDown();
    setLocationDropDown();

    ui->datatypeDropDown->clear();
    ui->datatypeDropDown->addItem("Observed Temperature & Wind");
    ui->datatypeDropDown->addItem("Predicted Temperature & Wind");
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
    //std::vector<QString> j({"21","61","22","62"});
    //controller_->pushButtonClicked("Digitraffic", "traffic", j, "2022-01-19T10:06:38Z");
    if(ui->dataLabel->text() == "Traffic Data")
    {
        QString dataType;
        if(ui->datatypeDropDown->currentText() == "Road Maintenance")
        {
            dataType = "maintenance";
        }else if(ui->datatypeDropDown->currentText() == "Road Condition Forecast")
        {
            dataType = "roadconditions";
        }
        unordered_map<QString, QString> j = controller_->getData(dataType);
        createChart("traffic", dataType, j, {});
    }else if(ui->dataLabel->text() == "Weather Data")
    {
        QString dataType;
        if(ui->datatypeDropDown->currentText() == "Observed Temperature & Wind")
        {
            dataType = "observed";
            unordered_map<QString, vector<double>> j = {{"Temperature", {0.3, 0.3, 0.2, 0.2, 0.1, -0.1, -0.3}}, {"Windspeed", {3.5, 3.7, 3.7, 4.3, 4.4, 4.7, 4.1}}};
            createChart("weather", dataType, {}, j);
        }else if(ui->datatypeDropDown->currentText() == "Predicted Temperature & Wind")
        {
            dataType = "forecast";
            unordered_map<QString, vector<double>> j = {{"Temperature", {0.4, 0.4, 0.3, 0.3, 0.2, -0.2, -0.4}}, {"Windspeed", {3.6, 3.8, 3.8, 4.4, 4.5, 4.8, 4.2}}};
            createChart("weather", dataType, {}, j);
        }

    }else if(ui->dataLabel->text() == "Combined Data")
    {
        unordered_map<QString, QString> j = controller_->getData("maintenance");
        unordered_map<QString, vector<double>> weather = {{"Temperature", {0.4, 0.4, 0.3, 0.3, 0.2, -0.2, -0.4}}, {"Windspeed", {3.6, 3.8, 3.8, 4.4, 4.5, 4.8, 4.2}}};
        createChart("combined", "maintenance", j, weather);
    }

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
  std::unordered_map<QString, QString> j = controller_->getData("roadconditions");
  for(auto ele : j){
      qDebug() << ele.second;
  }

}


void MainWindow::on_timelineDropDown_activated(int index)
{
    timelineDropDownIndex = index;
}


void MainWindow::on_datatypeDropDown_activated(int index)
{
    dataTypeDropDownIndex = index;
}

