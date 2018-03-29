
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
#define OutLineSize 1.0
#include "tileMap.cpp"



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

  TileMap map;
   int level[] =
      {
        #include "map.map"

            };




  RenderWindow window(VideoMode(Width, Height), "Blokus");
//-----------------------------------------------------------------------------------------
  //Initialisation des variables concernantes les zones des joueurs
  Rectangle pAreas [4] ;

  pAreas[0].x =OutLineSize;
  pAreas[0].y =OutLineSize;
  pAreas[0].width=MapOffSetPosX-OutLineSize;
  pAreas[0].height=Height/2-OutLineSize;
  pAreas[0].color= Color(250, 177, 160,255);

  pAreas[1].x =0;
  pAreas[1].y =Height/2 +OutLineSize;
  pAreas[1].width=MapOffSetPosX;
  pAreas[1].height=Height/2-OutLineSize;
  pAreas[1].color= Color(116, 185, 255,255);

  pAreas[2].x =MapOffSetPosX + (MapSize*tileWidth)+OutLineSize ;
  pAreas[2].y =OutLineSize;
  pAreas[2].width=MapOffSetPosX-OutLineSize;
  pAreas[2].height=Height/2-OutLineSize;
  pAreas[2].color= Color(85, 239, 196,255);


  pAreas[3].x =MapOffSetPosX + (MapSize*tileWidth)+OutLineSize;
  pAreas[3].y =Height/2+OutLineSize;
  pAreas[3].width=MapOffSetPosX-OutLineSize;
  pAreas[3].height=Height/2-OutLineSize;
  pAreas[3].color= Color(255, 234, 167,255);
//---------------------------------------------------
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

  //*********************************************************************************************************


  sf::Text title("Blokus", font, 50);
  title.setPosition(Vector2f(((Width/2 - title.getLocalBounds().width/2)),0.0));
//*********************************************************************************************************
  sf::Text PlayerName[4];

  for(int i=0 ; i<=3;i++){

    PlayerName[i].setString("player");
    PlayerName[i].setFont(font);
    PlayerName[i].setCharacterSize (20);
  }

  PlayerName[0].setPosition(Vector2f(pAreas[0].width/2 - PlayerName[0].getLocalBounds().width/2,0.0));
  PlayerName[1].setPosition(Vector2f(pAreas[1].width/2 - PlayerName[1].getLocalBounds().width/2,pAreas[1].y + PlayerName[1].getLocalBounds().height/2 ));
  PlayerName[2].setPosition(Vector2f((pAreas[2].x) + (pAreas[2].width/2) - PlayerName[2].getLocalBounds().width/2,0.0));
  PlayerName[3].setPosition(Vector2f((pAreas[3].x) + (pAreas[3].width/2) - PlayerName[3].getLocalBounds().width/2,pAreas[3].y + PlayerName[3].getLocalBounds().height/2 ));
//****************************************************************************************************
  TileMap playerHand[4];

  int p1handM[] =
    {
      #include "p1hand.map"
    };
    if (!map.load("src/tileset20m.png", sf::Vector2u(tileWidth, tileHeight), level, MapSize, MapSize, MapOffSetPosX ,MapOffSetPosY))
        {  return -1;}
    if (!playerHand[0].load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), p1handM, 23, 12, pAreas[0].width/2-(ptileWidth*23)/2 ,pAreas[0].height - ptileHeight*12 -10))
        {  return -1;}
    if (!playerHand[1].load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), p1handM, 23, 12, pAreas[1].width/2-(ptileWidth*23)/2 ,pAreas[1].y + pAreas[1].height - ptileHeight*12 -10))
        {  return -1;}
    if (!playerHand[2].load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), p1handM, 23, 12, pAreas[2].x + pAreas[2].width/2-(ptileWidth*23)/2 ,pAreas[2].height - ptileHeight*12 -10))
        {  return -1;}
    if (!playerHand[3].load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), p1handM, 23, 12, pAreas[3].x + pAreas[3].width/2-(ptileWidth*23)/2 ,pAreas[3].y + pAreas[3].height  - ptileHeight*12 -10))
        {  return -1;}
//*********************************************************************************************************

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
    RectangleShape pAreasShape[4];

    for(int i=0 ; i <=3;i++){
      pAreasShape[i].setSize(Vector2f(pAreas[i].width,pAreas[i].height));
      pAreasShape[i].setSize(Vector2f(pAreas[i].width,pAreas[i].height));
      pAreasShape[i].setPosition(pAreas[i].x,pAreas[i].y);
      pAreasShape[i].setFillColor(pAreas[i].color);
      pAreasShape[i].setOutlineColor(sf::Color::Black);
      pAreasShape[i].setOutlineThickness(OutLineSize);
  }
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
    for (int i = 0 ; i<=3;i++){
      window.draw(pAreasShape[i]);
    }
    for (int i = 0 ; i<=3;i++){
      window.draw(playerHand[i]);
    }

    for (int i=0 ; i<=3;i++){
      window.draw(PlayerName[i]);
    }
    sf::VertexArray lines(sf::LinesStrip, 4);
lines[0].position = sf::Vector2f(10, 0);
lines[1].position = sf::Vector2f(20, 0);
lines[2].position = sf::Vector2f(30, 5);
lines[3].position = sf::Vector2f(40, 2);
window.draw(lines);

    window.draw(title);

    window.display();

  }

  return 0;
}
