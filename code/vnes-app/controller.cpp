#include "controller.h"

Controller::Controller(NetworkHandler* networkhandler)
    : networkhandler_(networkhandler)
{

}

Controller::~Controller()
{
    delete networkhandler_;
}

void Controller::pushButtonClicked(std::string source, std::string datatype,
                                   std::vector<QString> coordinates, std::string time ) {
    networkhandler_->fetchDataJson(source, datatype, coordinates, time);
}
