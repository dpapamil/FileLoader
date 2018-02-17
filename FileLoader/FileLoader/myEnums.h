// Enums to be used when reading a file


#ifndef myEnums_H
#define myEnums_H

#include <string>

// Enum for the type of element
enum class myElementType {
  POINT3D,
  BEZIER_CURVE,
  NONE
};

// Enum for the type of entry
enum class myEntryType {
  VERTEX,
  CSTYPE,
  CURV,
  PARM,
  DEGREE,
  CTECH,
  GROUP,
  END,
  INVALID
};

// Enum for errors
enum class myError {
  NONE,
  FILE_NOT_FOUND,
  NOT_VALID
};

// Enum for the ctech entry type
enum class myCTechType {
  NONE,
  CPARM
};

// TODO:give more meaningful names to the enums

#endif