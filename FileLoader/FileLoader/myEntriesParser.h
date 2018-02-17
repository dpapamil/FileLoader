// Class for parsing a number of file entries and creating the specified elements


#ifndef myEntriesParser_H
#define myEntriesParser_H

#include <vector>
#include <list>
#include <memory>
#include "FileLoader/myPoint3D.h"
#include "FileLoader/myFileEntry.h"

class myElementContainer;
class myElement;
class myElementContext;

class myEntriesParser
{
public:
  myEntriesParser();

  // Create the elements specified in the given entries
  myError create_elements(
    const std::vector<myFileEntry>& entries,
    std::list<std::unique_ptr<myElement>>& elements  
  );

  ~myEntriesParser();

private:
  // Adds a vertex described in the given entry
  // Precondition: entry.type() == myEntryType::VERTEX
  myError add_vertex(const myFileEntry& entry);

  // Adds the curve info described in the given entry to the given context
  // Precondition: entry.type() == myEntryType::CURV
  myError add_curve_info(const myFileEntry& entry, myElementContext& context);

  // Adds the parameters described in the given entry to teh given context
  // Precondition: entry.type() == myEntryType::PARM
  myError add_parameters(const myFileEntry& entry, myElementContext& context);

  // Adds the ctech info described in the given entry to teh given context
  // Precondition: entry.type() == myEntryType::CTECH
  myError add_ctech_info(const myFileEntry& entry, myElementContext& context);

  // Returns true if the element described in the context is valid
  bool validate_element(const myElementContext& context);

  // variables
  std::vector<myPoint3D> m_vertices;

};

#endif