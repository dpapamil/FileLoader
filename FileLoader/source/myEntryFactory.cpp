#include "FileLoader/myEntryFactory.h"

#include "FileLoader/myEnums.h"

#include <vector>
#include <sstream>
#include <assert.h>
#include "FileLoader/myPoint3D.h"
#include "FileLoader/myFileEntry.h"
#include "FileLoader/myUtils.h"

//============================================================================
myEntryFactory::myEntryFactory()
{
}

//============================================================================
// Create an entry from the given line string
myFileEntry myEntryFactory::create_entry(
  const std::string& line
)
{
  std::istringstream iss(line);
  std::string word;
  // Get first word and decode it
  iss >> word;
  myEntryType type = myUtils::decode_entry_type(word);

  myFileEntry entry;
  entry.set_type(type);

  while (iss >> word) {
    entry.add_argument(word);
  }
  return entry;
}
