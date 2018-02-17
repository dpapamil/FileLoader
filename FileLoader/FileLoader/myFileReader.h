// Class to read an obj file, parse it and create any elements
// described in it

#ifndef myFileReader_H
#define myFileReader_H

#include "FileLoader/myEnums.h"
#include <string>
#include <memory>
#include <list>

class myElement;

class myFileReader
{
public:
  myFileReader();

  myError parse_file(
    const std::string& path, 
    std::list<std::unique_ptr<myElement>>& elements
  );

  ~myFileReader();
};

#endif