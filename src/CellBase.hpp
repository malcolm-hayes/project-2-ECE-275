#ifndef CELL_BASE_H_
#define CELL_BASE_H_

class CellBase {
public:
  CellBase() = default;
  virtual ~CellBase() = default;

  virtual void nextColor(void) = 0;
  virtual int get_orientationChange() = 0;
  
  unsigned int color = 0;
};

#endif
