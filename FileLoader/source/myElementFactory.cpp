#include "FileLoader/myElementFactory.h"
#include "FileLoader/myElementContext.h"
#include "FileLoader/myBezierCurve.h"


//============================================================================
myElementFactory::myElementFactory()
{
}

//============================================================================
// Create an element
std::unique_ptr<myElement> myElementFactory::create_element(
  const myElementContext & context
)
{
  switch (context.element_type()) {
    case myElementType::BEZIER_CURVE : {
      auto bezier_curve = std::make_unique<myBezierCurve>(
        context.points(),
        context.degree(),
        context.c_parm(),
        context.u_params()
       );
      return std::move(bezier_curve);
    }
    default: {
      break;
    }

  }

  return nullptr;
}
