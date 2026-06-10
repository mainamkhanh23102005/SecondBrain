#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
private:
    double width;
    double length;
public:
    // Exception "tag" classes - their TYPE identifies the error
    class NegativeWidth  { };
    class NegativeLength { };

    Rectangle() { width = 0.0; length = 0.0; }

    void   setWidth(double);
    void   setLength(double);
    double getWidth()  const { return width; }
    double getLength() const { return length; }
    double getArea()   const { return width * length; }
};
#endif
