#include "map.h"
#include <iostream>
#include <fstream>
#include <string>

Map::Map(int width, int height)
{
  if (width<2) width=2;
  if (height<2) height=2;
  for (int i{0}; i<height; i++)
    m_map.push_back(std::vector<int> (width));
  m_map[0][0] = TileType::start;
  m_map[1][0] = TileType::finish;
}

Map Map::map_from_file(std::ifstream &file){
  std::string line;
  Map m;
  int i = 0;
  
  std::getline(file, line);
  int row_length = line.length();
  do 
  {
    m.m_map.push_back({});
    m.m_map[i].reserve(row_length);
    for (char c : line)
    {
      if (c == 10) break;
      m.m_map[i].push_back(static_cast<int>(c)-48);
    }
    std::getline(file, line);
    ++i;
  }while(!file.eof());

  return m;
}

Map Map::map_from_file(const std::string &file_path){
  std::ifstream file{file_path};
  return Map::map_from_file(file);
}

MapPosition &Map::get_special_tile(MapPosition &out, Map::TileType type) const
{
  out.x = -1;
  out.y = -1;
  for (int y=0; const auto &row: m_map)
  {
    for (int x=0; const auto tile: row)
    {
      if(static_cast<Map::TileType>(tile) == type) 
      {
        out.x = x;
        out.y = y;
        return out;
      }
      ++x;
    }
    ++y;
  }
  return out;
}
PositionVector &Map::get_next_possible(const MapPosition &current, PositionVector &vectorOut)const
{
  vectorOut.clear();
  vectorOut.reserve(8);
  const Map &m = *this;
  for (int x{-1}; x <= 1; ++x)
  {
    for(int y{-1}; y <= 1; ++y)
    { 
      if (x==0 && y==0) continue;
      
      TileType type = m(current.x + x, current.y + y);
      if (type != Map::border && type != Map::out_of_map)
      {
        vectorOut.push_back({current.x+x, current.y+y});
      }
    }
  }
  return vectorOut;
}

bool Map::is_legit()const
{
  MapPosition pos;
  this->get_special_tile(pos, Map::TileType::start);
  if (pos.x == -1) return false;
  this->get_special_tile(pos, Map::TileType::finish);
  if (pos.x == -1) return false;
  return true;
}


Map::TileType Map::operator()(const MapPosition &pos)const
{
  return (*this)(pos.x, pos.y);
}

Map::TileType Map::operator()(int x, int y)const
{
  try
  {
    return static_cast<Map::TileType>(m_map.at(y).at(x));
  }
  catch(const std::out_of_range &e)
  {
    return out_of_map;
  }
}

bool Map::updateTile(const MapPosition &to_update, Map::TileType type){
  Map::TileType changed_tile = (*this)(to_update);
  if (changed_tile == TileType::out_of_map ||
      changed_tile == TileType::finish ||
      changed_tile == TileType::start) return false;

  if (type == TileType::finish || type == TileType::start)
  {
    MapPosition tmp;
    tmp = get_special_tile(tmp, type);
    m_map.at(tmp.y).at(tmp.x) = TileType::empty;
  }
  m_map.at(to_update.y).at(to_update.x) = type;
  return true;

}


bool operator==(const MapPosition &pos1, const MapPosition &pos2){
  return (pos1.x == pos2.x && pos1.y == pos2.y);
}

std::ostream &operator<<(std::ostream &os, const MapPosition& pos)
{
  os << "x: " << pos.x << " y: " << pos.y << '\n';
  return os;
}


std::ostream &operator<<(std::ostream &os, const Map& map)
{
  for (const auto& row: map.m_map)
  {
    for (const auto val: row)
      os << val << ' ';
    os << '\n';
  }
  return os;
}

