#ifndef APICALLS_HH
#define APICALLS_HH
#include <QNetworkAccessManager>
#include <QApplication>
#include <QObject>
#include <QNetworkReply>

class apiCalls : public QObject
{
    Q_OBJECT
public:
    explicit apiCalls(QObject *parent = nullptr);
    ~apiCalls();
    void pullData(std::string source);

private slots:
    void apiData(QNetworkReply* reply);
    //void apiError(QNetworkReply* reply, QList<QSslError> &errors);

private:
    QNetworkAccessManager* mgr;
};

#endif // APICALLS_HH
