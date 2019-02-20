#ifndef __NETPBMPRINTER__
#define __NETPBMPRINTER__

#include "Printer.h"

/**
 * A printer for the netpbm format.
 * 
 * @author Vitor Greati
 * */
template<typename T>
class NetpbmPrinter : public Printer<T> {

    public:

        enum class NetpbmParams {
            IMAGE_SIZE = 0,
            IMAGE_CHANNELS = 1,
            PBM_TYPE = 2,
            PBM_ENCODING = 3
        };

        enum class NetpbmType {
            BIT_MAP = 1<<0,
            GRAY_MAP = 1<<1,
            PIX_MAP = 1<<2
        };

        enum class NetpbmEncoding {
            ASCII = 1<<3,
            BINARY = 1<<4
        };

    protected:

        /**
         * Convert the data array into a string in netpbm format
         *
         * @param data data array
         * @return string representation of that data
         * */
        std::string convert(const std::unique_ptr<T> & data, const Configs & configs) const override;

    private:

        /**
         * Validate configuration options.
         *
         * @param config the configuration
         * */
        void validate(const Configs & params) const;

        /**
         * Give a magic number from a configuration.
         *
         * @param config configuration
         * @return magic number
         * */
        std::string get_magic_number(int config) const;

};

#endif
