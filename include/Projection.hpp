#ifndef _INCLUDE_PROJECTION_HPP_
#define _INCLUDE_PROJECTION_HPP_

class Projection {
public:
  Projection(double min, double max): min(min), max(max) {};

  bool overlap(Projection other) {
    if(max > other.min || min > other.max) {
      return true;
    }
    return false;
  };

private:
  double min;
  double max;
};

#endif
