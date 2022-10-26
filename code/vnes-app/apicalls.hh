#ifndef APICALLS_HH
#define APICALLS_HH
#include <QNetworkAccessManager>
#include <QApplication>
#include <QObject>

class apiCalls : public QObject
{
    Q_OBJECT
public:
    explicit apiCalls(QObject *parent = nullptr);
    ~apiCalls();
    void pullData(std::string source);

private slots:
    void apiData(QNetworkReply* reply);
};

#endif // APICALLS_HH
