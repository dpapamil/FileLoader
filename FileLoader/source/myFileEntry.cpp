#include "FileLoader/myFileEntry.h"


//============================================================================
myFileEntry::myFileEntry()
  : m_type(myEntryType::INVALID)
{
}

//============================================================================
myEntryType myFileEntry::type() const
{
  return m_type;
}

//============================================================================
void myFileEntry::set_type(myEntryType type)
{
  m_type = type;
}

//============================================================================
void myFileEntry::add_argument(const std::string& arg)
{
  m_args.push_back(arg);
}

//============================================================================
const std::vector<std::string>& myFileEntry::arguments() const
{
  return m_args;
}

//============================================================================
bool myFileEntry::has_arguments() const
{
  return !m_args.empty();
}

//============================================================================
myFileEntry::~myFileEntry()
{
}
