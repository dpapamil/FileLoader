#include "FileLoader/myUtils.h"


//============================================================================
myUtils::myUtils()
{
}

//============================================================================
// Decode the entry type
myEntryType myUtils::decode_entry_type(const std::string& type) {
  if (type == "v") {
    return myEntryType::VERTEX;
  }
  else if (type == "cstype") {
    return myEntryType::CSTYPE;
  }
  else if (type == "curv") {
    return myEntryType::CURV;
  }
  else if (type == "parm") {
    return myEntryType::PARM;
  }
  else if (type == "deg") {
    return myEntryType::DEGREE;
  }
  else if (type == "g") {
    return myEntryType::GROUP;
  }
  else if (type == "ctech") {
    return myEntryType::CTECH;
  } else if (type == "end") {
    return myEntryType::END;
  }

  return myEntryType::INVALID;
}

//============================================================================
// Decode the element type
myElementType myUtils::decode_element_type(const std::string& type) {
  if (type == "bezier") {
    return myElementType::BEZIER_CURVE;
  }

  return myElementType::NONE;
}

//============================================================================
// Decode teh ctech type
myCTechType myUtils::decode_ctech_type(const std::string & type)
{
  if (type == "cparm") {
    return myCTechType::CPARM;
  }

  return myCTechType::NONE;
}

//============================================================================
// Decode the error type
std::string myUtils::decode_error_type(myError type)
{
  switch (type) {
    case myError::FILE_NOT_FOUND : {
      return "File was not found!";
    }
    case myError::NONE: {
      return "No Error";
    }
    case myError::NOT_VALID: {
      return "Invalid syntax";
    }
    default: {
      return "";
    }
  }
}
