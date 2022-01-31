#ifndef BFS_H
#define BFS_H
#include "solvingmethod.h"
#include "map.h"
#include <memory>

class BFS : public SolvingMethod
{
public:

  BFS();
  virtual void init(std::shared_ptr<Map> map) override;
  virtual void step(SolutionDecorator *out) override;
protected:
  std::shared_ptr<Map> m_map;

  MapPosition m_fin;
  PositionPairList m_to_check;

};

#endif // BFS_H
