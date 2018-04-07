
#include <random>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

const int Height=700;
const int Width=1080;
#define BgColor (89,88,86,255)
const int tileWidth =20;
const int ptileWidth =12;
const int tileHeight =20;
const int ptileHeight =13;
const int MapSize =24;
const int ptileH =12;
const int ptileW =23;
const int MapOffSetPosX = Width/2 - (MapSize*tileWidth)/2;
const int MapOffSetPosY = Height/2 - (MapSize*tileHeight)/2;
const float OutLineSize = 1.0;
const int overflowcorrect = 10;

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize,  int* tiles, unsigned int width, unsigned int height,int offSetX,int offSetY)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;


        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(offSetX + (i * tileSize.x),offSetY + j * tileSize.y);
                quad[1].position = sf::Vector2f(offSetX + (i + 1) * tileSize.x,offSetY + j * tileSize.y);
                quad[2].position = sf::Vector2f(offSetX +(i + 1) * tileSize.x,offSetY + (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(offSetX + (i * tileSize.x), offSetY +(j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

};

struct tiles{
int id;
TileMap map;
float angle;
};
struct countTime{
  int min;
  int sec;
};

struct Rectangle {
  float x;
  float y;
  float width;
  float height;
  Color color;
};
struct player{
  Color color;
  int score;
  countTime Time;
  TileMap Hand;
  Rectangle pos;
};


  struct Arrays {
    int array2d[5][5];
    int array1d[25];

  };

    Arrays rotateclockWise(Arrays input){
      for(int r = 0; r < 5; r++) {
        for(int c = r; c < 5; c++) {
            int tmp=input.array2d[r][c];
            input.array2d[r][c]=input.array2d[c][r];
            input.array2d[c][r]=tmp;
        }
      }
      for(int r = 0; r < 5; r++) {
      for(int c =0; c < 5/2; c++) {
        int tmp=input.array2d[r][c];
        input.array2d[r][c]=input.array2d[r][5-c-1];
        input.array2d[r][5-c-1]=tmp;
      }
  }

      return input;
    }


  Arrays TotheMatrix(int input[]){
    Arrays tmp;
    int n;
    n=0;
    for(int i=0;i<5;i++){
      tmp.array2d[0][n]=input[i];
      n++;
    }
    n=0;
    for(int i=5;i<10;i++){
      tmp.array2d[1][n]=input[i];
      n++;
    }
    n=0;
    for(int i=10;i<15;i++){
      tmp.array2d[2][n]=input[i];
      n++;
    }
    n=0;
    for(int i=15;i<20;i++){
      tmp.array2d[3][n]=input[i];
      n++;
    }
    n=0;
    for(int i=20;i<25;i++){
      tmp.array2d[4][n]=input[i];
      n++;
    }
    return tmp;
    }


  Arrays totheArray(Arrays input){
    Arrays tmp;
    int n=0;
    for(int i=0;i<5;i++){
    tmp.array1d[i]= input.array2d[0][n];
      n++;
    }
    n=0;
    for(int i=5;i<10;i++){
      tmp.array1d[i]=input.array2d[1][n];
      n++;
    }
    n=0;
    for(int i=10;i<15;i++){
      tmp.array1d[i]=input.array2d[2][n];
      n++;
    }
    n=0;
    for(int i=15;i<20;i++){
      tmp.array1d[i]=input.array2d[3][n];
      n++;
    }
    n=0;
    for(int i=20;i<25;i++){
      tmp.array1d[i]=input.array2d[4][n];
      n++;
    }

  return tmp;
  }






int main() {
  sf::Font font;
  if (!font.loadFromFile("src/RobotoMono-Regular.ttf"))
      return EXIT_FAILURE;

  TileMap map;
   int level[] =
      {

        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 3, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,

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
  player players[4];
  players[0].pos.x=pAreas[0].width/2-(ptileWidth*ptileW)/2;
  players[0].pos.y= pAreas[0].height - ptileHeight*ptileHeight -overflowcorrect;


  players[1].pos.x=pAreas[1].width/2-(ptileWidth*ptileW)/2 ;
  players[1].pos.y=  pAreas[1].y + pAreas[1].height - ptileHeight*ptileH -overflowcorrect;

  players[2].pos.x =pAreas[2].x + pAreas[2].width/2-(ptileWidth*ptileW)/2 ;
  players[2].pos.y=pAreas[2].height - ptileHeight*ptileH -overflowcorrect;

  players[3].pos.x =pAreas[3].x + pAreas[3].width/2 - (ptileWidth*ptileW)/2 ;
  players[3].pos.y =  pAreas[3].y + pAreas[3].height - ptileHeight*ptileH -overflowcorrect;

//*********************

  for(int i=0 ; i<=3;i++){
    String tmp = std::to_string(i+1);
    PlayerName[i].setString("player" + tmp);
    PlayerName[i].setFont(font);
    PlayerName[i].setCharacterSize (20);
  }

  PlayerName[0].setPosition(Vector2f(pAreas[0].width/2 - PlayerName[0].getLocalBounds().width/2,0.0));
  PlayerName[1].setPosition(Vector2f(pAreas[1].width/2 - PlayerName[1].getLocalBounds().width/2,pAreas[1].y + PlayerName[1].getLocalBounds().height/2 ));
  PlayerName[2].setPosition(Vector2f((pAreas[2].x) + (pAreas[2].width/2) - PlayerName[2].getLocalBounds().width/2,0.0));
  PlayerName[3].setPosition(Vector2f((pAreas[3].x) + (pAreas[3].width/2) - PlayerName[3].getLocalBounds().width/2,pAreas[3].y + PlayerName[3].getLocalBounds().height/2 ));
//****************************************************************************************************
//***************************************************************************
TileMap piece1;
  int phandM[] =
    {
              0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1,
              1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0,
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
              1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
              1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1,
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
              1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
              1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0,
              1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1,

    };
    int p1[] =
      {
        0,0,0,0,0,
        0,0,0,0,0,
        0,1,1,0,0,
        0,0,1,1,0,
        0,0,0,0,0,
      };


//*********************************************************************************************************

  while (window.isOpen()) {


    Event event;
    while (window.pollEvent(event)) {

      if (event.type == Event::Closed) {
        window.close();

       }

      if (event.type == Event::KeyPressed) {
        switch (event.key.code) {
          case Keyboard::Up:
          Arrays mat = TotheMatrix(p1);
          mat = rotateclockWise(mat);
          mat = totheArray(mat);
          for(int i=0 ; i<25;i++){
            p1[i] = mat.array1d[i];
          }            break;}
      }
}
if (!map.load("src/tileset20m.png", sf::Vector2u(tileWidth, tileHeight), level, MapSize, MapSize, MapOffSetPosX ,MapOffSetPosY))
    {  return -1;}
if (!players[0].Hand.load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), phandM, ptileW, ptileH, players[0].pos.x,players[0].pos.y))
    {  return -1;}
if (!players[1].Hand.load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), phandM, ptileW, ptileH, players[1].pos.x,players[1].pos.y))
    {  return -1;}
if (!players[2].Hand.load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), phandM, ptileW, ptileH,players[2].pos.x ,players[2].pos.y))
    {  return -1;}
if (!players[3].Hand.load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), phandM, ptileW, ptileH,players[3].pos.x ,players[3].pos.y))
    {  return -1;}
if (!piece1.load("src/ptiles.png", sf::Vector2u(ptileWidth, ptileHeight), p1, 5, 5,Width/2 ,Height/2))
        {  return -1;}

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
      window.draw(players[i].Hand);
    }
    for (int i=0 ; i<=3;i++){
      window.draw(PlayerName[i]);
    }
      window.draw(piece1);
  //  window.draw(title);

    window.display();

  }

  return 0;
}
