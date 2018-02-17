// Factory to create an entry object out of a line

#ifndef myEntryFactory_H
#define myEntryFactory_H


#include <string>
#include <memory>

class myFileEntry;

class myEntryFactory
{
public:

  static myFileEntry create_entry(const std::string& line);

private:
  myEntryFactory();
};

#endif