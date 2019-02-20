#ifndef __CONFIGS__
#define __CONFIGS__

#include <string>
#include <map>

/**
 * Represents a bundle of configurations.
 *
 * @author Vitor Greati
 * */
class Configs {

    protected:

        using ConfigsData = std::map<std::string, std::string>;

    private:

        ConfigsData _configs;

    public:

        Configs(ConfigsData configs) : _configs {configs} {/*empty*/}

        /**
         * Takes a value from the configurations and try to
         * convert it to a given type.
         *
         * @param key the key
         * @return the value of the indicated type
         * */
        template<typename T = std::string>
        T get(const std::string & key) const;

};

#endif
