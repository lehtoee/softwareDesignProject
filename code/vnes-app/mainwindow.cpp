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
int weatherDataTypeDropDownIndex;
int trafficDataTypeDropDownIndex;

/*
 * Constructor for the user interface. Takes pointers to its controller and
 * parent as parameters.
 */
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

    locationDropDownIndex = 0;
    timelineDropDownIndex = 0;
    weatherDataTypeDropDownIndex = 0;
    trafficDataTypeDropDownIndex = 0;

    //Set options for drop downs
    setTrafficDataDropDowns();

    ui->trafficButton->setChecked(true);
}

/*
 * Destuctor for the user interface.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::createTrafficMaintanaceChart
     Function for creating road maintanace chart. Takes traffic data and font size as
     parameters and returns pointer to QChartView object
 * @param data
     Traffic data
 * @param fontSize
     Font size for the title
 * @return *QChartView
     Created chart
 */
QChartView * MainWindow::createTrafficMaintanaceChart(unordered_map<QString, QString> data, int fontSize)
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
    font.setPixelSize(fontSize);
    chart->setTitleFont(font);
    chart->setTitle("Road Maintenance");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(750, 520);
    return chartView;
}


/**
 * @brief MainWindow::createTraffcRoadconditionsChart
    Function for creating roadconditions chart. Takes traffic data and font size as
    parameters and returns pointer to QChartView object
 * @param data
    Traffic data
 * @param fontSize
    Font size for the title
 * @return *QChartView
    Created chart
 */
QChartView * MainWindow::createTraffcRoadconditionsChart(unordered_map<QString, QString> data, int fontSize)
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
    font.setPixelSize(fontSize);
    chart->setTitleFont(font);
    chart->setTitle("Road Condition");
    chart->setBackgroundBrush(weatherLogo);
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(750, 520);
    return chartView;
}

/**
 * @brief MainWindow::createWeatherChart
    Function for creating chart for weather. Takes weather data, data type and font size as
    parameters and returns pointer to QChartView object
 * @param weatherData
    Weather data
 * @param dataType
    What data should be included in chart
 * @param fontSize
    Font size for the title
 * @return *QChartView
    Created chart
 */
QChartView * MainWindow::createWeatherChart(unordered_map<QString, vector<double>> weatherData,
                                            QString dataType, int fontSize)
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
    font.setPixelSize(fontSize);
    chart->setTitleFont(font);
    if(dataType == "observed")
    {
        chart->setTitle("Observed Temperature & Wind Speed");
    } else if(dataType == "forecast")
    {
        chart->setTitle("Forecast Temperature & Wind Speed");
    } else { return nullptr; }
    chart->setTitle("Observed Temperature & Wind Speed");
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(750, 520);
    return chartView;
}

/**
 * @brief MainWindow::createChart
    Creates chart with wanted information
 * @param contentType
    Which type of chart we are creating
 * @param dataType
    What data should be included in chart
 * @param data
    Traffic data
 * @param weatherData
    Weather data
 * @param weatherDataType
    Needed if contentType is 'combined'. Tells which type of weather data
    should be included. "observed" as default.
 */
void MainWindow::createChart(QString contentType, QString dataType, unordered_map<QString, QString> data, unordered_map<QString, vector<double>> weatherData,
                             QString weatherDataType = "observed")
{
    if(contentType == "traffic")
    {
        if(dataType == "maintenance")
        {
            QChartView *chartView = createTrafficMaintanaceChart(data, 36);
            chartView->show();

        }else if(dataType == "roadconditions")
        {
            QChartView *chartView =createTraffcRoadconditionsChart(data, 36);
            chartView->show();
        }

    }else if(contentType == "weather")
    {
        QChartView *chartView = createWeatherChart(weatherData, dataType, 36);
        if (chartView != nullptr) {
            chartView->show();
        }

    } else if(contentType == "combined")
    {
        //Traffic
        QChartView *chartView;
        if(dataType == "maintenance")
        {
            chartView = createTrafficMaintanaceChart(data, 18);

        } else if(dataType == "roadconditions")
        {
            chartView =createTraffcRoadconditionsChart(data, 18);
        } else { return; }
        chartView->resize(500, 300);

        //Weather
        QChartView *chartView1 = createWeatherChart(weatherData, weatherDataType, 18);
        if (chartView == nullptr) { return; }
        chartView1->resize(500, 300);

        QWidget *window = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout(window);
        layout->addWidget(chartView);
        layout->addWidget(chartView1);
        window->resize(1000, 600);
        window->show();

    }

}

/**
 * @brief MainWindow::setTimelineDropDown
    Sets items to the timeline drop down
 */
void MainWindow::setTimelineDropDown()
{
    ui->timelineDropDown->clear();

    ui->timelineDropDown->addItem("2 hours");
    ui->timelineDropDown->addItem("4 hours");
    ui->timelineDropDown->addItem("6 hours");
    ui->timelineDropDown->addItem("12 hours");
    ui->timelineDropDown->setCurrentIndex(timelineDropDownIndex);
}

/**
 * @brief MainWindow::setLocationDropDown
    Sets items to the location drop down
 */
void MainWindow::setLocationDropDown()
{
    ui->locationDropDown->clear();

    ui->locationDropDown->addItem("Tampere");
    ui->locationDropDown->addItem("Oulu");
    ui->locationDropDown->addItem("Helsinki");
    ui->locationDropDown->addItem("Jyväskylä");
    ui->locationDropDown->addItem("Turku");
    ui->locationDropDown->setCurrentIndex(locationDropDownIndex);
}

/**
 * @brief MainWindow::setTrafficDataDropDowns
    Set drop downs for traffic data view
 */
void MainWindow::setTrafficDataDropDowns()
{
    setTimelineDropDown();
    setLocationDropDown();

    ui->datatypeDropDown->clear();
    ui->datatypeDropDown->addItem("Road Maintenance");
    ui->datatypeDropDown->addItem("Road Condition Forecast");
    ui->datatypeDropDown->setCurrentIndex(trafficDataTypeDropDownIndex);
    ui->datatypeDropDown->show();
}

/**
 * @brief MainWindow::setWeatherDataDropDowns
    Set drop downs for weather data view
 */
void MainWindow::setWeatherDataDropDowns()
{
    setTimelineDropDown();
    setLocationDropDown();

    ui->datatypeDropDown->clear();
    ui->datatypeDropDown->addItem("Observed Temperature & Wind");
    ui->datatypeDropDown->addItem("Predicted Temperature & Wind");
    ui->datatypeDropDown->setCurrentIndex(weatherDataTypeDropDownIndex);
    ui->datatypeDropDown->show();
}

/**
 * @brief MainWindow::setCombinedDataDropDowns
    Set drop downs for combined data view
 */
void MainWindow::setCombinedDataDropDowns()
{
    setTimelineDropDown();
    setLocationDropDown();

    ui->datatypeDropDown->clear();
    ui->datatypeDropDown->hide();
}

/**
 * @brief MainWindow::onFetchDataButtonClicked
    Starts creating chart if user clicks Fetch data button
 */
void MainWindow::onFetchDataButtonClicked()
{
    //std::vector<QString> j({"21","61","22","62"});
    //controller_->pushButtonClicked("Digitraffic", "traffic", j, "2022-01-19T10:06:38Z");
    if(ui->trafficButton->isChecked())
    {
        QString dataType = getTrafficDataType();
        unordered_map<QString, QString> j = controller_->getData(dataType);
        createChart("traffic", dataType, j, {});
    }else if(ui->weatherButton->isChecked())
    {
        unordered_map<QString, vector<double>> j = {{"Temperature", {0.4, 0.4, 0.3, 0.3, 0.2, -0.2, -0.4}}, {"Windspeed", {3.6, 3.8, 3.8, 4.4, 4.5, 4.8, 4.2}}};
        createChart("weather", getWeatherDataType(), {}, j);
    }else if(ui->combinedButton->isChecked())
    {
        unordered_map<QString, QString> j = controller_->getData("maintenance");
        unordered_map<QString, vector<double>> weather = {{"Temperature", {0.4, 0.4, 0.3, 0.3, 0.2, -0.2, -0.4}}, {"Windspeed", {3.6, 3.8, 3.8, 4.4, 4.5, 4.8, 4.2}}};
        createChart("combined",  getTrafficDataType(), j, weather, getWeatherDataType());
    }

}

/**
 * @brief MainWindow::getWeatherDataType
    Checks witch weather data type user have selected
 * @return QString
    Selected weather data type
 */
QString MainWindow::getWeatherDataType()
{
    if (weatherDataTypeDropDownIndex == 0) {
        return "observed";
    } else if (weatherDataTypeDropDownIndex == 1) {
        return "forecast";
    }
    return NULL;
}

/**
 * @brief MainWindow::getTrafficDataType
    Checks witch traffic data type user have selected
 * @return QString
    Selected traffic data type
 */
QString MainWindow::getTrafficDataType()
{
    if (trafficDataTypeDropDownIndex == 0) {
        return "maintenance";
    } else if (trafficDataTypeDropDownIndex == 1) {
        return "roadconditions";
    }
    return NULL;
}

/**
 * @brief MainWindow::on_trafficButton_clicked
    Set the UI to show traffic view when the traffic button is clicked
 */
void MainWindow::on_trafficButton_clicked()
{
  ui->weatherButton->setChecked(false);
  ui->combinedButton->setChecked(false);
  ui->dataLabel->setText("Traffic Data");

  ui->datatypeLabel->show();
  setTrafficDataDropDowns();
  std::cout << "Hep";
}

/**
 * @brief MainWindow::on_weatherButton_clicked
    Set the UI to show weather view when the weather button is clicked
 */
void MainWindow::on_weatherButton_clicked()
{
  ui->trafficButton->setChecked(false);
  ui->combinedButton->setChecked(false);
  ui->dataLabel->setText("Weather Data");

  ui->datatypeLabel->show();
  setWeatherDataDropDowns();
}

/**
 * @brief MainWindow::on_combinedButton_clicked
    Set the UI to show combined view when combined button is clicked
 */
void MainWindow::on_combinedButton_clicked()
{
  ui->trafficButton->setChecked(false);
  ui->weatherButton->setChecked(false);
  ui->dataLabel->setText("Combined Data");

  ui->datatypeLabel->hide();
  setCombinedDataDropDowns();
}

/**
 * @brief MainWindow::on_locationDropDown_activated
    Saves users selection on location drop down, saves value every time it is changed
 * @param index
    Selected drop down items index
 */
void MainWindow::on_locationDropDown_activated(int index)
{
  locationDropDownIndex = index;
}

/**
 * @brief MainWindow::on_timelineDropDown_activated
    Saves users selection on timeline drop down, saves value every time it is changed
 * @param index
    Selected drop down items index
 */
void MainWindow::on_timelineDropDown_activated(int index)
{
    timelineDropDownIndex = index;
}

/**
 * @brief MainWindow::on_datatypeDropDown_activated
    Saves users selection on datatype drop down, saves value every time it is changed
 * @param index
    Selected drop down items index
 */
void MainWindow::on_datatypeDropDown_activated(int index)
{
    if (ui->trafficButton->isChecked()) {
        trafficDataTypeDropDownIndex = index;
    } else {
        weatherDataTypeDropDownIndex = index;
    }

}
