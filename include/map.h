#ifndef MAP_gsdjghsj_H
#define MAP_gsdjghsj_H
#include <iostream>
#include <vector>
#include <fstream>


struct MapPosition
{
  int x;
  int y;
  friend std::ostream &operator<<(std::ostream &os, const MapPosition& pos);
  friend bool operator==(const MapPosition &pos1, const MapPosition &pos2);
};

using PositionVector = std::vector<MapPosition>;  
using MapVectorRaw = std::vector<std::vector<int>>;
class Map
{

  public:
    enum TileType
    {
      empty,
      start,
      finish,
      border,
      out_of_map
    };
    Map(){}
    Map(int width, int height);
    Map(MapVectorRaw &&map_data):m_map{map_data}{}
    Map(MapVectorRaw &map_data):m_map{map_data}{}

    static Map map_from_file(std::ifstream &file);
    static Map map_from_file(const std::string &file_path);
    //nezajem jen testovaci
    bool is_legit()const;

    // Map pozice -> in, tyletype -> vrati to prvni kde ten type je (existuje jeden cil a zacatek, takhle najdes)
    MapPosition &get_special_tile(MapPosition &out, TileType type) const;
    // Vraci position vektor vsechn moznych dalsich pozice z pozice current
    PositionVector &get_next_possible(const MapPosition &current, PositionVector &vectorOut) const;
    // dam pozici a jakej typ tile tam chci a ono ho na te pozici pokude nenarusi pravidla
    bool updateTile(const MapPosition &to_update, TileType type);

    // pomocny funkce na pretizeni zavorejk Map(3,7) -> vrati tiletype na 3,7
    // nemusi uplne zajimat
    TileType operator()(int x, int y)const;
    TileType operator()(const MapPosition &pos)const;

    const MapVectorRaw &get_raw_data()const{return m_map;}

  private:
    MapVectorRaw m_map;


  friend std::ostream &operator<<(std::ostream &os, const Map& map);
};

#endif
