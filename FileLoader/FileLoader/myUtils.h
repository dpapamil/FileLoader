// Static utilities class

#ifndef myUtils_H
#define myUtils_H

#include "FileLoader/myEnums.h"

class myUtils
{
public:

  // Decode the entry type 
  static myEntryType decode_entry_type(const std::string& type) ;

  // Decode the element type
  static myElementType decode_element_type(const std::string& type);

  // Decode the ctech type
  static myCTechType decode_ctech_type(const std::string& type);

  // Return the string corresponding to the given error type
  static std::string decode_error_type(myError type);

private:
  myUtils();

};

#endif