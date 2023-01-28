#ifndef _INCLUDE_ISHAPE_HPP_
#define _INCLUDE_ISHAPE_HPP_

class IShape {
public:
  virtual IShape* clone() const = 0;
  virtual ~IShape() = 0;
};

inline IShape::~IShape() {};

#endif
