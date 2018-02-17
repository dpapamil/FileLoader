#include "FileLoader/myFileReader.h"

#include <fstream>
#include <sstream>
#include "FileLoader/myEntryFactory.h"
#include "FileLoader/myFileEntry.h"
#include "FileLoader/myEntriesParser.h"
#include "FileLoader/myElement.h"

//============================================================================
myFileReader::myFileReader()
{
}

//============================================================================
// Read the file and create the described elements, if there are any.
myError myFileReader::parse_file(
  const std::string& path, 
  std::list<std::unique_ptr<myElement>>& elements
) 
{
  std::vector<myFileEntry> entries;
  
  // Open the file to a stream
  std::ifstream infile(path);
  if (!infile.is_open()) {
    return myError::FILE_NOT_FOUND;
  }

  // Create an entry from each line, and pass the valid ones
  // to a container
  std::string line;
  while (std::getline(infile, line)) {
    myFileEntry entry = myEntryFactory::create_entry(line);
    if (entry.type() != myEntryType::INVALID) {
      entries.push_back(entry);
    }
  }

  // Parse the entries we got and create the elements
  myEntriesParser parser;
  return parser.create_elements(entries, elements);
}

//============================================================================
myFileReader::~myFileReader()
{
}
