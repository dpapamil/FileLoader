// Class that represents an entry in an .obj file
// It contains info about the type of the entry and its arguments
// as strings

#ifndef myFileEntry_H
#define myFileEntry_H

#include "FileLoader/myEnums.h"
#include <vector>

class myFileEntry
{
public:
  myFileEntry();

  myFileEntry(const myFileEntry&) = default;
  myFileEntry& operator=(const myFileEntry&) = default;

  myEntryType type() const;
  void set_type(myEntryType type);

  void add_argument(const std::string& arg);

  const std::vector<std::string>& arguments() const;

  bool has_arguments() const;

  ~myFileEntry();

private:
  myEntryType m_type;
  std::vector<std::string> m_args;
};

#endif