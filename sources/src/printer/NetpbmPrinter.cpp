#include "printer/NetpbmPrinter.h"
#include <iomanip>

template<typename T>
std::string NetpbmPrinter<T>::convert(
        const std::unique_ptr<T> & data, 
        const Configs & configs) const {

    validate(configs);

    auto config = 0;

    auto magic_number = get_magic_number(config);

    std::stringstream ss;
    ss << magic_number << std::endl;
    auto [w, h] = std::pair{800, 600};
    ss << w << " " << h << std::endl;
    
    for (auto j = 0; j < h; ++j) {
        for (auto i = 0; i < w * 3; ++i) {
            ss << data[j*h + i] << " ";
        }
        ss << std::endl;
    }
    
    return ss.str();
}

template<typename T>
void NetpbmPrinter<T>::validate(const Configs & configs) const {
    
}

template<typename T>
std::string NetpbmPrinter<T>::get_magic_number(int config) const {
    if (config & NetpbmType::BIT_MAP && config & NetpbmEncoding::ASCII)
        return "P1";
    else if (config & NetpbmType::BIT_MAP && config & NetpbmEncoding::BINARY)
        return "P4";
    else if (config & NetpbmType::GRAY_MAP && config & NetpbmEncoding::ASCII)
        return "P2";
    else if (config & NetpbmType::GRAY_MAP && config & NetpbmEncoding::BINARY)
        return "P5";
    else if (config & NetpbmType::PIX_MAP && config & NetpbmEncoding::ASCII)
        return "P3";
    else if (config & NetpbmType::PIX_MAP && config & NetpbmEncoding::BINARY)
        return "P6";
    else 
        throw std::invalid_argument("invalid configuration");
}
