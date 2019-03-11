#include "printer/LodePngPrinter.h"
#include "lodepng.h"
#include <iomanip>

template<typename T, typename ConfigKeyType>
std::string LodePngPrinter<T, ConfigKeyType>::convert(
        const T* data, 
        const Configs<ConfigKeyType> & configs) const {
    return "";
}

template<>
std::string LodePngPrinter<unsigned char, std::string>::convert(
        const unsigned char* data, 
        const Configs<std::string> & configs) const {

    return "";
}

template<typename T, typename ConfigKeyType>
void LodePngPrinter<T, ConfigKeyType>::validate(const Configs<ConfigKeyType> & configs) const {
    
}

template class LodePngPrinter<unsigned char, std::string>;
