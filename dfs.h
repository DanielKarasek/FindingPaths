#ifndef DFS_H
#define DFS_H

#include "solvingmethod.h"
#include "map.h"

#include <memory>


class DFS : public SolvingMethod
{
public:
  DFS();

  virtual void init(std::shared_ptr<Map> map) override;
  virtual void step(SolutionDecorator *out) override;
protected:
  std::shared_ptr<Map> m_map;

  MapPosition m_fin;
  PositionPairList m_to_check;
};

#endif // DFS_H
