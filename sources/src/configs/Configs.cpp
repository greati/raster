#include "configs/Configs.h"

template<>
std::string Configs::get<std::string>(const std::string & key) const {
    return _configs.at(key);
}

template<>
int Configs::get<int>(const std::string & key) const {
    return std::stoi(_configs.at(key));
}

template<>
long Configs::get<long>(const std::string & key) const {
    return std::stol(_configs.at(key));
}

template<>
double Configs::get<double>(const std::string & key) const {
    return std::stod(_configs.at(key));
}

template<>
float Configs::get<float>(const std::string & key) const {
    return std::stof(_configs.at(key));
}

