#pragma once


#include <string>
#include <vector>


class TileMap
{
public:
    TileMap();
    ~TileMap();

    void clear();

    void loadTMX(const std::string& filename);
    void loadTMX_Base64(const std::string& filename);

    class ObjectData
    {
    public:
      int id = 0;
      std::string type;
      int x = 0;
      int y = 0;
    };

    class Layer
    {
    public:
      virtual bool isTile() { return false; }
      virtual bool isObject() { return false; }
      std::vector<int> data;
    };

    class ObjectLayer : public Layer
    {
    public:
      bool isObject() { return true; }
    };

    class TileLayer : public Layer
    {
    public:
      bool isTile() { return true; }
    };

    std::vector<ObjectData> objects;
    std::vector<Layer> layers;

    int height = 0;
    int width = 0;
    const int tileheight = 32;
    const int tilewidth = 32;
};
