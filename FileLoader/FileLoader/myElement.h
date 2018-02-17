// Interface representing an element you can draw.


#ifndef myElement_H
#define myElement_H

class myDrawing;

class myElement
{
public:

  virtual void draw(myDrawing& drawing) = 0;

  virtual ~myElement();

protected:
  myElement();
};

#endif