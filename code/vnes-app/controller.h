#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "networkhandler.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(NetworkHandler* networkhandler);
    ~Controller();

    void pushButtonClicked(std::string source, std::string datatype,
                           std::vector<QString> coordinates, std::string time);


private:

    NetworkHandler* networkhandler_;

};
#endif // CONTROLLER_H
