#include "TileMap.h"
#include <iostream>
#include <fstream>
#include "base64.h"
#include "StringTrim.h"


TileMap::TileMap()
{

}


TileMap::~TileMap()
{

}


void TileMap::clear()
{
  height = 0;
  width = 0;
}


void TileMap::loadTMX(const std::string& filename)
{
  clear();

  // load file
  //int fd = open("", );

  std::string cfilename = filename;
  std::ifstream fileInput;
  int offset;
  std::string line;
  //char search[100] = "width="; // test variable to search in file
  std::string search_token = "width=";
  std::string data_token = "<data encoding=\"csv\">";

  //std::vector<int> layer_data;
  ObjectData current_object;

  int layer_tile = 0;
  int read_layer = 0;

  // open file to search
  fileInput.open(cfilename.c_str());
  if(fileInput.is_open())
  {
    getline(fileInput, line);
    while(!fileInput.eof())
    {

        if ((offset = line.find(search_token.c_str(), 0)) != std::string::npos)
        {
            // std::cout << "found: " << search_token << "    offset: " << offset << std::endl;
            // std::cout << "line: " << line << std::endl;

            int s1 = line.find("\"", offset);
            int s2 = line.find("\"", s1 + 1);
            //std::cout << line.substr(s1 + 1, s2 - s1 - 1) << std::endl;
            if (width == 0)
            {
              width = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());
              search_token="height=";
              continue;
            }

            if (height == 0)
            {
              height = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());
              search_token="<object id=";
              continue;
            }

            if (current_object.id == 0)
            {
              current_object.id = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());
              search_token="type=";
              continue;
            }

            if (current_object.type.length() == 0)
            {
              current_object.type = line.substr(s1 + 1, s2 - s1 - 1);
              search_token="x=";
              continue;
            }

            if (current_object.x == 0)
            {
              current_object.x = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());
              search_token="y=";
              continue;
            }

            if (current_object.y == 0)
            {
              current_object.y = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());
              search_token="<object id=";
              //objects.push_back(current_object);
              current_object = ObjectData();
            }
        }

        // check the other search term
        if ((offset = line.find(data_token.c_str(), 0)) != std::string::npos)
        {
            if (read_layer == 0)
            {
              read_layer = 1;
              layer_tile += 1;
            }
        }

        // read next line
        getline(fileInput, line);

        // Part 2
        if (read_layer)
        {
          int s2 = 0;
          int s1 = 0;
          int c = 0;
          while (s2 != std::string::npos)
          {
            s2 = line.find(",", s1 + 1);
            if (s2 != std::string::npos)
            {
              int x = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());

              // Apply the value to the tile array
              //layer_data.push_back(x);
              // if (layer_tile == 1) layer1.push_back(x);
              // if (layer_tile == 2) layer2.push_back(x);

              ++c;
            }
            s1 = s2;
          }

          if (c <= 1) read_layer = 0;
          //std::cout << c << std::endl;
        }

    }
    fileInput.close();
  }
  else std::cout << "Unable to open file." << std::endl;

}


void TileMap::loadTMX_Base64(const std::string& filename)
{
  clear();

  // load file
  //int fd = open("", );

  std::string cfilename = filename;
  std::ifstream fileInput;
  int offset;
  std::string line;
  //char search[100] = "width="; // test variable to search in file
  std::string search_token = "width=";
  std::string data_token = "<data encoding=\"base64\">";

  //std::vector<int> layer_data;
  ObjectData current_object;

  int layer_tile = 0;
  int read_layer = 0;

  // open file to search
  fileInput.open(cfilename.c_str());
  if(fileInput.is_open())
  {
    getline(fileInput, line);
    while(!fileInput.eof())
    {

        if ((offset = line.find(search_token.c_str(), 0)) != std::string::npos)
        {
            // std::cout << "found: " << search_token << "    offset: " << offset << std::endl;
            // std::cout << "line: " << line << std::endl;

            int s1 = line.find("\"", offset);
            int s2 = line.find("\"", s1 + 1);
            //std::cout << line.substr(s1 + 1, s2 - s1 - 1) << std::endl;
            if (width == 0)
            {
              width = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());
              search_token="height=";
              continue;
            }

            if (height == 0)
            {
              height = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());
              search_token="tilewidth=";
              continue;
            }

            if (tilewidth == 0)
            {
              tilewidth = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());
              search_token="tileheight=";
              continue;
            }

            if (tileheight == 0)
            {
              tileheight = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());
              search_token="<object id=";
              continue;
            }

            // Object
            if (current_object.id == 0)
            {
              current_object.id = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());
              search_token="type=";
              continue;
            }

            if (current_object.type.length() == 0)
            {
              current_object.type = line.substr(s1 + 1, s2 - s1 - 1);
              search_token="x=";
              continue;
            }

            if (current_object.x == 0)
            {
              current_object.x = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());
              search_token="y=";
              continue;
            }

            if (current_object.y == 0)
            {
              current_object.y = std::atoi(line.substr(s1 + 1, s2 - s1 - 1).c_str());
              search_token="<object id=";
              objects.push_back(current_object);
              current_object = ObjectData();
            }
        }

        // check the other search term
        if ((offset = line.find(data_token.c_str(), 0)) != std::string::npos)
        {
            if (read_layer == 0)
            {
              read_layer = 1;
              layer_tile += 1;
            }
        }

        // read next line
        getline(fileInput, line);

        // Hm..
        // Set up layer...
        //Layer layer = ObjectLayer;

        // Part 2
        if (read_layer)
        {
          // Do something?
          TileLayer tileLayer;

          trim(line);

          std::string decoded = base64_decode(line);
          const char* c = decoded.c_str();
          const int* d = (const int*)c;
          int T = decoded.length() / 4;
          for (int i = 0; i < T; ++i)
          {
              tileLayer.data.push_back(d[i]);
          }

          layers.push_back(tileLayer);
          read_layer = 0;
        }

    }
    fileInput.close();
  }
  else std::cout << "Unable to open file." << std::endl;
}
