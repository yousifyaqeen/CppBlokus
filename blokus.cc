
#include <random>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define Height  700
#define Width  1080
#define BgColor (89,88,86,255)
#define tileWidth 20
#define ptileWidth 12
#define tileHeight 20
#define ptileHeight 13
#define MapSize 24
#define MapOffSetPosX Width/2 - (MapSize*tileWidth)/2
#define MapOffSetPosY Height/2 - (MapSize*tileHeight)/2
#include "tileMap.cpp"
#define OutLineSize 1.0



struct Rectangle {
  float x;
  float y;
  float width;
  float height;
  Color color;
};

int main() {
  sf::Font font;
    if (!font.loadFromFile("src/RobotoMono-Regular.ttf"))
        return EXIT_FAILURE;

        TileMap p1hand;
        TileMap p2hand;
        TileMap p3hand;
        TileMap p4hand;
  TileMap map;
  #include "map.map"
  #include "p1hand.map"

  if (!map.load("src/tileset20m.png", sf::Vector2u(tileWidth, tileHeight), level, MapSize, MapSize, MapOffSetPosX ,MapOffSetPosY))
        {  return -1;}

  RenderWindow window(VideoMode(Width, Height), "Blokus");


  Rectangle p1Area;
  p1Area.x =OutLineSize;
  p1Area.y =OutLineSize;
  p1Area.width=MapOffSetPosX-OutLineSize;
  p1Area.height=Height/2-OutLineSize;
  p1Area.color= Color(250, 177, 160,255);

  Rectangle p2Area;
  p2Area.x =0;
  p2Area.y =Height/2 +OutLineSize;
  p2Area.width=MapOffSetPosX;
  p2Area.height=Height/2-OutLineSize;
  p2Area.color= Color(116, 185, 255,255);

  Rectangle p3Area;
  p3Area.x =MapOffSetPosX + (MapSize*tileWidth)+OutLineSize ;
  p3Area.y =OutLineSize;
  p3Area.width=MapOffSetPosX-OutLineSize;
  p3Area.height=Height/2-OutLineSize;
  p3Area.color= Color(85, 239, 196,255);


  Rectangle p4Area;
  p4Area.x =MapOffSetPosX + (MapSize*tileWidth)+OutLineSize;
  p4Area.y =Height/2+OutLineSize;
  p4Area.width=MapOffSetPosX-OutLineSize;
  p4Area.height=Height/2-OutLineSize;
  p4Area.color= Color(255, 234, 167,255);

  Rectangle Header;
  Header.x =MapOffSetPosX+OutLineSize;
  Header.y =OutLineSize;
  Header.width=MapSize*tileWidth-OutLineSize;
  Header.height=MapOffSetPosY-OutLineSize;
  Header.color= Color(sf::Color BgColor);

  Rectangle Footer;
  Footer.x =MapOffSetPosX;
  Footer.y =MapOffSetPosY+MapSize*tileHeight;
  Footer.width=MapSize*tileHeight;
  Footer.height=Height - MapOffSetPosY+MapSize*tileHeight;
  Footer.color= Color(sf::Color BgColor);



  sf::Text title("Blokus", font, 50);
  title.setPosition(Vector2f(((Width/2 - title.getLocalBounds().width/2)),0.0));

  sf::Text p1("player1", font, 20);
  p1.setPosition(Vector2f(p1Area.width/2 - p1.getLocalBounds().width/2,0.0));

  sf::Text p2("player2", font, 20);
  p2.setPosition(Vector2f(p2Area.width/2 - p2.getLocalBounds().width/2,p2Area.y + p2.getLocalBounds().height/2 ));

  sf::Text p3("player3", font, 20);
  p3.setPosition(Vector2f((p3Area.x) + (p3Area.width/2) - p3.getLocalBounds().width/2,0.0));

  sf::Text p4("player4", font, 20);
  p4.setPosition(Vector2f((p4Area.x) + (p4Area.width/2) - p4.getLocalBounds().width/2,p4Area.y + p4.getLocalBounds().height/2 ));

  if (!p1hand.load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), p1handM, 23, 12, p1Area.width/2-(ptileWidth*23)/2 ,p1Area.height - ptileHeight*12 -10))
        {  return -1;}
        if (!p2hand.load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), p1handM, 23, 12, p2Area.width/2-(ptileWidth*23)/2 ,p2Area.y + p2Area.height - ptileHeight*12 -10))
              {  return -1;}
              if (!p3hand.load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), p1handM, 23, 12, p3Area.x + p3Area.width/2-(ptileWidth*23)/2 ,p3Area.height - ptileHeight*12 -10))
                    {  return -1;}
                    if (!p4hand.load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), p1handM, 23, 12, p4Area.x + p4Area.width/2-(ptileWidth*23)/2 ,p4Area.y + p4Area.height  - ptileHeight*12 -10))
                          {  return -1;}

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

    RectangleShape p1AreaS;
    p1AreaS.setSize(Vector2f(p1Area.width,p1Area.height));
    p1AreaS.setPosition(p1Area.x,p1Area.y);
    p1AreaS.setFillColor(p1Area.color);
    p1AreaS.setOutlineColor(sf::Color::Red);
    p1AreaS.setOutlineThickness(OutLineSize);
    RectangleShape p2AreaS;
    p2AreaS.setSize(Vector2f(p2Area.width,p2Area.height));
    p2AreaS.setPosition(p2Area.x,p2Area.y);
    p2AreaS.setFillColor(p2Area.color);
    p2AreaS.setOutlineColor(sf::Color::Blue);
    p2AreaS.setOutlineThickness(OutLineSize);
    RectangleShape p3AreaS;
    p3AreaS.setSize(Vector2f(p3Area.width,p3Area.height));
    p3AreaS.setPosition(p3Area.x,p3Area.y);
    p3AreaS.setFillColor(p3Area.color);
    p3AreaS.setOutlineColor(sf::Color::Green);
    p3AreaS.setOutlineThickness(OutLineSize);
    RectangleShape p4AreaS;
    p4AreaS.setSize(Vector2f(p4Area.width,p4Area.height));
    p4AreaS.setPosition(p4Area.x,p4Area.y);
    p4AreaS.setFillColor(p4Area.color);
    p4AreaS.setOutlineColor(sf::Color::Yellow);
    p4AreaS.setOutlineThickness(OutLineSize);
    RectangleShape HeaderS;
    HeaderS.setSize(Vector2f(Header.width,Header.height));
    HeaderS.setPosition(Header.x,Header.y);
    HeaderS.setFillColor(Header.color);

    RectangleShape FooterS;
    FooterS.setSize(Vector2f(Footer.width,Footer.height));
    FooterS.setPosition(Footer.x,Footer.y);
    FooterS.setFillColor(Footer.color);


    window.clear(sf::Color BgColor);
    window.draw(map);
    window.draw(HeaderS);
    window.draw(FooterS);
      window.draw(p2AreaS);
    window.draw(p1AreaS);

    window.draw(p3AreaS);
    window.draw(p4AreaS);
    window.draw(p1hand);
    window.draw(p2hand);
    window.draw(p3hand);
    window.draw(p4hand);

    p1.setColor(sf::Color::Blue);
    p2.setColor(sf::Color::Red);
    p3.setColor(sf::Color::Yellow);
    p4.setColor(sf::Color::Green);

    window.draw(p1);
    window.draw(p2);
    window.draw(p3);
    window.draw(p4);
window.draw(title);

    window.display();

  }

  return 0;
}
