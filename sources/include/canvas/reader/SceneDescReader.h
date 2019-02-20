#ifndef __SCENEREADER__
#define __SCENEREADER__

#include <string>

/**
 * Interface for scene description readers.
 *
 * @author Vitor Greati
 * */
class SceneDescReader {

    public:
        
       /**
        * Takes a file path for the description file.
        * 
        * @param filename The path to the description file.
        * */
       virtual void read(const std::string & filename) = 0; 

};

#endif
