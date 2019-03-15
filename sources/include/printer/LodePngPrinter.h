#ifndef __LODEPNGPRINTER__
#define __LODEPNGPRINTER__

#include "Printer.h"

/**
 * A printer for the png format.
 * 
 * @author Vitor Greati
 * */
template<typename T, typename ConfigKeyType>
class LodePngPrinter : public Printer<T, ConfigKeyType> {

    protected:

        /**
         * Convert the data array into a string.
         *
         * @param data data array
         * @return string representation of that data
         * */
        std::string convert(const T* data, const Configs<ConfigKeyType> & configs) const override;

    private:

        /**
         * Validate configuration options.
         *
         * @param config the configuration
         * */
        void validate(const Configs<ConfigKeyType> & params) const;

};

template class Configs<std::string>;

#endif
