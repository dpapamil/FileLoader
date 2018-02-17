// Factory class to create an element from a context

#ifndef myElementFactory_H
#define myElementFactory_H

#include <memory>

class myElement;
class myElementContext;

class myElementFactory
{
public:
  
  // Create an element from the given context
  static std::unique_ptr<myElement> create_element(
    const myElementContext& context
  );

private:
  myElementFactory();
};

#endif