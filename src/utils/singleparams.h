#ifndef SINGLEPARAMS_H
#define SINGLEPARAMS_H
#include <string>
#include <QtDebug>
#include "json.hpp"
using json = nlohmann::json;
class SingleParams
{
public:
    json _(const std::string& key);
    static SingleParams* instance();
private:
    SingleParams();
    static SingleParams *single;
    json params;
};

#endif // SINGLEPARAMS_H
