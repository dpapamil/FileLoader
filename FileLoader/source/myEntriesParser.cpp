#include "FileLoader/myEntriesParser.h"
#include "FileLoader/myElement.h"
#include <assert.h>
#include "FileLoader/myElementContext.h"
#include "FileLoader/myUtils.h"
#include "FileLoader/myElementFactory.h"

//============================================================================
myEntriesParser::myEntriesParser()
{
}

//============================================================================
// Parse the entries and create the elements that are described
myError myEntriesParser::create_elements(
  const std::vector<myFileEntry>& entries, 
  std::list<std::unique_ptr<myElement>>& elements
)
{
  myElementContext context;
  myError err = myError::NONE;
  for (myFileEntry entry : entries) {
    switch (entry.type()) {
      case myEntryType::VERTEX : {
        // add the vertex to our points container
        err = add_vertex(entry);
        break;
      }
      case myEntryType::CSTYPE : {
        // return an error if there are no arguments or the type isn't a bzier curve
        if (!entry.has_arguments() ||
            myUtils::decode_element_type(entry.arguments()[0]) != myElementType::BEZIER_CURVE) {
          err = myError::NOT_VALID;
          break;
        }
        context.set_element_type(
          myUtils::decode_element_type(entry.arguments()[0])
        );
        break;
      }
      case myEntryType::DEGREE: {
        // Error if there are no arguments
        if (!entry.has_arguments()) {
          err = myError::NOT_VALID;
          break;
        }
        context.set_degree(std::atoi(entry.arguments()[0].c_str()));
        break;
      }
      case myEntryType::GROUP: {
        // TODO: use it
        break;
      }
      case myEntryType::CTECH: {
        err = add_ctech_info(entry, context);
        break;
      }
      case myEntryType::END: {
        context.finish_building();
        break;
      }
      case myEntryType::CURV: {
        // add the curve info to the context
        err = add_curve_info(entry, context);
        break;
      }
      case myEntryType::PARM: {
        // add the parameters to the context
        err = add_parameters(entry, context);
        break;
      }
      default:{
        return myError::NOT_VALID;
      }
    }
    if (err != myError::NONE) {
      return err;
    }
  }

  // TODO: make it handle multiple elemtns

  if (!validate_element(context)) {
    return myError::NOT_VALID;
  }
  auto element = myElementFactory::create_element(context);
  if (element) {
    elements.push_back(std::move(element));
  }

  return myError::NONE;
}

//============================================================================
// Add the vertex described by the given entry to our container
myError myEntriesParser::add_vertex(const myFileEntry& entry)
{
  assert(entry.type() == myEntryType::VERTEX);
  std::vector<std::string> args = entry.arguments();
  if (args.size() < 3) {
    return myError::NOT_VALID;
  }
  m_vertices.push_back(
    myPoint3D(
      std::atof(args[0].c_str()), 
      std::atof(args[1].c_str()), 
      std::atof(args[2].c_str())
    )
  );
  return myError::NONE;
}

//============================================================================
// Add the curve info to the context
myError myEntriesParser::add_curve_info(
  const myFileEntry & entry, 
  myElementContext & context
)
{
  assert(entry.type() == myEntryType::CURV);
  std::vector<std::string> args = entry.arguments();
  // We need at least 4 argument (start/end range + 2 points)
  if (args.size() < 4) {
    return myError::NOT_VALID;
  }
  context.set_start_range(std::atof(args[0].c_str()));
  context.set_end_range(std::atof(args[1].c_str()));

  // Set the points
  for (int i = 2; i < args.size(); ++i) {
    int vertex_index = std::atoi(args[i].c_str());
    if (vertex_index > 0 && vertex_index <= m_vertices.size()) {
      context.add_point(m_vertices[vertex_index-1]);
    }
  }
  if (context.points().size() < 2) {
    return myError::NOT_VALID;
  }

  return myError::NONE;
}

//============================================================================
// Add the paraemters described in the entry to the context 
myError myEntriesParser::add_parameters(
  const myFileEntry & entry, 
  myElementContext & context
)
{
  assert(entry.type() == myEntryType::PARM);

  // The parameters entry must be between declaring the curve and
  // ending the entry
  if (context.points().empty() ||
      context.finished_building()) {
    return myError::NOT_VALID;
  }

  std::vector<std::string> args = entry.arguments();
  if (!args.empty()) {
    if (args[0] == "u") {
      for (int i=1; i<args.size(); ++i) {
        context.add_u_param(std::atof(args[i].c_str()));
      }
    }
  }
  return myError::NONE;
}

//============================================================================
// Add the tech info to the context
myError myEntriesParser::add_ctech_info(
  const myFileEntry & entry, 
  myElementContext & context
)
{
  assert(entry.type() == myEntryType::CTECH);
  std::vector<std::string> args = entry.arguments();
  if (!args.empty()) {
    // We need to decode the tech type and pass it on to the context
    // if there is one
    myCTechType tech_type = myUtils::decode_ctech_type(args[0]);
    switch (tech_type) {
      case myCTechType::CPARM: {
        context.set_curve_tech_type(myCTechType::CPARM);
        if (args.size() < 2) {
          return myError::NOT_VALID;
        }
        context.set_c_parm(std::atof(args[1].c_str()));
      }
      default: {
        break;
      }
    }
  }
  return myError::NONE;
}

//============================================================================
// Returns true if the element described in the context is valid
bool myEntriesParser::validate_element(const myElementContext & context)
{
  // It must have finished building
  if (!context.finished_building()) {
    return false;
  }

  switch (context.element_type()) {
    case myElementType::BEZIER_CURVE : {
      bool valid = true;
      // It must have at least 2 points
      valid &= context.points().size() > 1;
      // it must have a degree
      valid &= context.degree() > 0;
      if (!valid) return false;
      // number of params == ctrl_points/degree + 1
      valid &= context.u_params().size() == context.points().size() / context.degree() + 1;
      if (!valid) return false;
      break;
    }
    default: {
      return false;
    }
  }

  return true;
}

//============================================================================
myEntriesParser::~myEntriesParser()
{
}
