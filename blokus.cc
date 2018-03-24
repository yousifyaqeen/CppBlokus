
#include <random>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define Height  700
#define Width  1080
#define BgColor (89,88,86,255)
#define tileWidth 16
#define tileHeight 16
#define MapSize 24
#define MapOffSetPosX Width/2 - (MapSize*tileWidth)/2
#define MapOffSetPosY Height/2 - (MapSize*tileHeight)/2
#include "tileMap.cpp"


struct Rectangle {
  float x;
  float y;
  float width;
  float height;
  Color color;
};

int main() {
  TileMap map;
  #include "map.map"
  if (!map.load("src/tileset16.png", sf::Vector2u(tileWidth, tileHeight), level, MapSize, MapSize, MapOffSetPosX ,MapOffSetPosY))
        {  return -1;}

  RenderWindow window(VideoMode(Width, Height), "Blokus");

  while (window.isOpen()) {

    Event event;
    while (window.pollEvent(event)) {

      if (event.type == Event::Closed) {
        window.close();
      }

      if (event.type == Event::KeyPressed) {

      }

      if (event.type == Event::KeyReleased) {
      }

      if (event.type == sf::Event::MouseButtonPressed) {
      }
    }

    // draw it
    window.clear(sf::Color BgColor);
    window.draw(map);

    window.display();

  }

  return 0;
}
