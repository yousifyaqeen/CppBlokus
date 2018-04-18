
#include <random>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include "Chronometer.hpp"
#include <SFML/Audio.hpp>


using namespace std;
using namespace sf;

//height of the window
int window_height                = 700 ;
//width of the window
int window_width                 = 1080 ;
//the window's background color
#define BgColor (89,88,86,255)
//the width of the main board tiles(same as the size in the texture file)
const int   main_board_tile_width      = 20 ;
//the width of the tiles in the player board area
const int   player_board_tile_width    = 12 ;
//the height of the main board tiles(same as the size in the texture file)
const int   main_board_tile_height     = 20 ;
//the width of the tiles in the player board area
const int   player_board_tile_height   = 12 ;
//main board size (the board is a 24*24 matrix )
const int   main_board_size            = 24 ;
//the height of the player hand matrix
const int   player_board_matrix_width  = 12 ;
//the width of the player hand matrix
const int   player_board_matrix_height = 23 ;
//position of the main board in the x axes
const int   main_board_position_x      = window_width/2  - ( main_board_size * main_board_tile_width)/2 ;
//position of the main board in the y axes
const int   main_board_position_y      = window_height/2 - ( main_board_size * main_board_tile_height)/2 ;
//to improve the display of player area
const float out_line_size              = 2.0 ;
//improve the display of player board
const int   overflowcorrect            = 10 ;
//define a start time (representing minutes seconds are added later when defining the time for each player and is always equal to 00)
const int   time_for_each_player       = 0 ;
//define the size of a single tile
const int   tile_matrix_size           = 5 ;

const int   total_number_of_tiles      = 21;

const int   number_of_players          = 4;//between 1 and 4

int tilesTableWithCenter[] =
// an array defining the player board and each piece has 2 associated to its
// center and no id
{
  0, 0, 0, 2, 0, 0, 0, 1, 2, 0, 0, 0, 1, 2, 0, 0, 0, 1, 2, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  2, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 1,
  1, 1, 0, 0, 1, 2, 1, 0, 0, 1, 2, 1, 1, 0, 0, 1, 1, 2, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
  1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 2, 1, 1, 0, 1, 2, 1, 0, 1,
  1, 2, 1, 1, 0, 1, 2, 1, 0, 2, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 2,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
  1, 1, 0, 1, 2, 0, 0, 2, 0, 0, 0, 1, 2, 0, 0, 1, 2, 1, 0, 0, 1, 0, 0,
  2, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 2, 1, 1,

};

int tilesTableWithEachPiece[]=
// an array defining the player board and each piece has an id
//associated to it
{
  0, 0, 0, 1, 0, 0, 0, 2, 2, 0, 0, 0, 3, 3, 0, 0, 0, 4, 4, 4, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  5, 5, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 9, 9,
  5, 5, 0, 0, 6, 6, 6, 0, 0, 7, 7, 7, 7, 0, 0, 8, 8, 8, 0, 0, 9, 9, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,11, 0, 0,12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,14, 0, 15,
  10, 0, 0, 0, 0, 0,11, 0, 0,12, 0, 0, 0, 0,13, 13, 13, 0, 14, 14, 14, 0, 15,
  10, 10, 10, 10, 0, 11, 11, 11, 0, 12, 12, 12, 0, 13, 13, 0, 0, 0,14, 0, 0, 0,15,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15,
  16, 0, 0, 0, 17, 17, 0, 18, 18, 0, 0, 0, 19, 19, 0, 0, 20, 0, 0, 0, 0, 0,15,
  16, 16, 0, 17, 17, 0, 0,18, 0, 0, 0, 19, 19, 0, 0, 20, 20, 20, 0, 0, 21, 0, 0,
  16, 16, 0, 17, 0, 0, 0,18, 18, 0, 0, 0, 19, 0, 0, 0,20, 0, 0, 21, 21, 21, 21,


};
int iniMap[] =
{
  //to initialise the main game board
  //7 represents the walls
  //1 is the first players (red)
  //2 is the second player(blue)
  //3 is the third player(green)
  //4 is the fourth player(yellow)
  1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
  2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4,

};
//definning the tile array see the full table in tile.map
int t1[]={0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,};

int t2[]={0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,};

int t3[]={0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,1,0,0,0,0,0,0,0,};

int t4[]={0,0,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,0,0,};

int t5[]={0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,1,1,0,0,0,0,0,0,};

int t6[]={0,0,0,0,0,0,0,1,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,0,0,};

int t7[]={0,0,0,0,0,0,0,0,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,};

int t8[]={0,0,0,0,0,0,0,1,0,0,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,};

int t9[]={0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,1,1,0,0,0,0,0,0,0,};

int t10[]={0,0,0,0,0,0,1,0,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,};

int t11[]={0,0,1,0,0,0,0,1,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,0,0,};

int t12[]={0,0,1,0,0,0,0,1,0,0,0,0,2,1,1,0,0,0,0,0,0,0,0,0,0,};

int t13[]={0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,0,1,1,0,0,0,0,0,0,0,};

int t14[]={0,0,0,0,0,0,0,0,1,0,0,1,2,1,0,0,1,0,0,0,0,0,0,0,0,};

int t15[]={0,0,1,0,0,0,0,1,0,0,0,0,2,0,0,0,0,1,0,0,0,0,1,0,0,};

int t16[]={0,0,1,0,0,0,0,1,1,0,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,};

int t17[]={0,0,0,0,0,0,0,1,1,0,0,1,2,0,0,0,1,0,0,0,0,0,0,0,0,};

int t18[]={0,0,0,0,0,0,0,1,1,0,0,0,2,0,0,0,0,1,1,0,0,0,0,0,0,};

int t19[]={0,0,0,0,0,0,0,1,1,0,0,1,2,0,0,0,0,1,0,0,0,0,0,0,0,};

int t20[]={0,0,0,0,0,0,0,1,0,0,0,1,2,1,0,0,0,1,0,0,0,0,0,0,0,};

int t21[]={0,0,0,0,0,0,0,1,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,};


struct Board{
  //definning the board to be refrenced after and modified
  int table[main_board_size*main_board_size];
  int matrix[main_board_size][main_board_size];
};


struct playerHand{
  //definning the board to be refrenced after and modified
  int table[ player_board_matrix_width* player_board_matrix_height];
  int matrix[ player_board_matrix_width][ player_board_matrix_height];
};


class TileMap : public sf::Drawable, public sf::Transformable
{
public:

  bool load(const std::string& tileset, sf::Vector2u tileSize,  int* tiles, unsigned int width, unsigned int height,int offSetX,int offSetY)
  {
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
    return false;
    m_tileset.setSmooth(false);


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


struct tile{
  //definning the tile to be refrenced after and modified
  int id;//each tile has its unique id
  int table[tile_matrix_size*tile_matrix_size];//the tile as a 1 dimension array
  int matrix[tile_matrix_size][tile_matrix_size];//the tile as a 2 dimension array
  int size;//the tile size (0< && >6)
};


//****************************************
struct countTime{
  //time structure to be used to define the time for each player
  int min;
  int sec;
};
//****************************************
struct Rectangle {
  //a rectangle structure (not to be confused with RectangleShape is sfml)
  //this structure is used to define a rectangle before transforming it
  //to sfml RectangleShape
  float x;//position in x
  float y;//position in y
  float width;//width of the rectangle
  float height;//height of the rectangle
  Color color;//the color of the rectangle (must use sfml colors)

};
//****************************************
struct player{
  int        id;
  Color      color;
  int        score;
  countTime  Time;
  TileMap    FullHand;
  int        Have[total_number_of_tiles];
  tile       Hand[total_number_of_tiles];
  TileMap    cTile;
  playerHand pboard;
  Rectangle  pos;
  bool canPlay;

};

//****************************************


//for debugging purposes only ********{

void print_matrix(int input[main_board_size][main_board_size]){
  //a function to print the board not to be used in the game
  //for debugging purposes only
  //activated when called with a square matrix of size 24
  for (int i = 0; i < main_board_size; i++) {
    for (int j = 0; j < main_board_size; j++) {
      std::cout << input[i][j] << " ";
    }
    std::cout << " " << std::endl;
  }
}
//for debugging purposes only ********}


//for debugging purposes only ********{
void print_matrix(int input[tile_matrix_size][tile_matrix_size]){
  //a function to print the tile not to be used in the game
  //activated when called with a square matrix of size 5
  for (int i = 0; i < tile_matrix_size; i++) {
    for (int j = 0; j < tile_matrix_size; j++) {
      std::cout << input[i][j] << " ";
    }
    std::cout << " " << std::endl;
  }
}
//for debugging purposes only ******}

//**************************************************************



tile rotate_Clock_Wise(tile input){
  //an algorithme to rotate a matrix clockwise
  //can only be used for a matrix of size 5*5
  //returns a tile
  for(int r = 0; r < tile_matrix_size; r++) {
    for(int c = r; c < tile_matrix_size; c++) {
      int tmp=input.matrix[r][c];
      input.matrix[r][c]=input.matrix[c][r];
      input.matrix[c][r]=tmp;
    }
  }
  for(int r = 0; r < tile_matrix_size; r++) {
    for(int c =0; c < tile_matrix_size/2; c++) {
      int tmp=input.matrix[r][c];
      input.matrix[r][c]=input.matrix[r][5-c-1];
      input.matrix[r][5-c-1]=tmp;
    }
  }
  return input;
}
//**************************************************************
tile rotate_Counter_Clock_Wise(tile input)
{
  // Consider all squares one by one
  for (int x = 0; x < tile_matrix_size / 2; x++)
  {

    // Consider elements in group of 4 in
    // current square
    for (int y = x; y < tile_matrix_size-x-1; y++)
    {
      // store current cell in temp variable
      int temp =  input.matrix[x][y];

      // move values from right to top
      input.matrix[x][y] = input.matrix[y][tile_matrix_size-1-x];

      // move values from bottom to right
      input.matrix[y][tile_matrix_size-1-x] =  input.matrix[tile_matrix_size-1-x][tile_matrix_size-1-y];

      // move values from left to bottom
      input.matrix[tile_matrix_size-1-x][tile_matrix_size-1-y] =  input.matrix[tile_matrix_size-1-y][x];

      // assign temp to left
      input.matrix[tile_matrix_size-1-y][x] = temp;
    }
  }

  return input;
}

//*************************************************************
tile to_Tile(int input[]){
  //a function to create a matrix from a tile table
  tile tmp;
  int n=0;
  for(int i=0;i<tile_matrix_size;i++){
    for(int j=0;j<tile_matrix_size;j++){
      tmp.matrix[i][j]=input[n];
      n++;
    }
  }
  return tmp;
}

tile to_Tile(tile input){
  //a function to create a table from the tile matrix

  tile tmp;
  int n=0;
  for(int i=0;i<tile_matrix_size;i++){
    for(int j=0;j<tile_matrix_size;j++){
      tmp.table[n]= input.matrix[i][j];
      n++;
    }
  }
  return tmp;
}

tile to_Tile(int input[tile_matrix_size][tile_matrix_size],tile tmp){
  //a function to create a table from the tile matrix

  int n=0;
  for(int i=0;i<tile_matrix_size;i++){
    for(int j=0;j<tile_matrix_size;j++){
      tmp.table[n]= input[i][j];
      n++;
    }
  }
  return tmp;
};
//**************************************************************


Board to_Board(int input[]){
  //a function to create a matrix from the map
  Board tmp;
  int n=0;
  for(int i=0;i<main_board_size;i++){
    for(int j=0;j<main_board_size;j++){
      tmp.matrix[i][j]=input[n];
      n++;
    }
  }
  return tmp;
}



//**************************************************************
Board to_Board(int input[],Board tmp){
  //a function to create a matrix from the map
  int n=0;
  for(int i=0;i<main_board_size;i++){
    for(int j=0;j<main_board_size;j++){
      tmp.matrix[i][j]=input[n];
      n++;
    }
  }
  return tmp;
}


Board to_Board(int input[main_board_size][main_board_size]){
  //a function to create a table from the map matrix
  Board tmp;
  int n=0;
  for(int i=0;i<main_board_size;i++){
    for(int j=0;j<main_board_size;j++){
      tmp.table[n]= input[i][j];
      n++;

    }
  }
  return tmp;
}

//**************************************************************

Board to_Board(int input[main_board_size][main_board_size],Board tmp){
  //a function to create a table from the map matrix
  int n=0;
  for(int i=0;i<main_board_size;i++){
    for(int j=0;j<main_board_size;j++){
      tmp.table[n]= input[i][j];
      n++;

    }
  }
  return tmp;
}


//********************************

playerHand set_Player_Hand(int input[12*23]){
  //a function to create a table from the map matrix
  playerHand tmp;
  int n=0;
  for(int i=0;i<12*23;i++){
    tmp.table[i]= input[i];
  }
  for(int i=0;i<12;i++){
    for(int j=0;j<23;j++){
      tmp.matrix[i][j]=tmp.table[n];
      n++;
    }
  }
  return tmp;
}

playerHand set_Player_Hand(int input[12][23]){
  //a function to create a table from the map matrix
  playerHand tmp;
  int n=0;
  for(int i=0;i<12;i++){
    for(int j=0;j<23;j++){
      tmp.matrix[i][j]=input[i][j];
    }
  }
  for(int i=0;i<12;i++){
    for(int j=0;j<23;j++){
      tmp.table[n]= tmp.matrix[i][j];
      n++;
    }
  }
  n=0;

  return tmp;
}

Board set_Board(int input[]){
  Board tmp ;
  tmp =  to_Board(input);
  tmp = to_Board(tmp.matrix,tmp);
  return tmp;
}

tile set_Tile(int id,int input[],int size){
  tile tmp;
  tmp = to_Tile(input);
  tmp = to_Tile(tmp.matrix,tmp);
  tmp.id=id;
  tmp.size=size;
  return tmp;
}


//**************************************************************


int is_Equal(int input[main_board_size][main_board_size],int x,int y,int color){
  return input[x][y]==color;
}
int is_Equal(int input[tile_matrix_size][tile_matrix_size],int x,int y,int to_check){
  return input[x][y]==to_check;
}

//**************************************************************

int is_Valid(tile check,Board lvl,int x,int y,int color){
  //check if a tile placement location is empty (0)
  //return true or false depending on the condition
  int center =2;
  int tmp[main_board_size][main_board_size];
  int n = 0;
  int col[check.size];
  int row[check.size];
  for(int i=0 ; i<tile_matrix_size ; i++){
    for(int j=0; j<tile_matrix_size;j++){
      if(check.matrix[i][j]!=0){
        col[n]=i-center;
        row[n]=j-center;
        n++;
      }
    }
  }
  for(int i=0 ; i<check.size ; i++){

  }
  bool side=1;
  bool corner[tile_matrix_size] ={0,0,0,0,0};

  for(int i=0;i<check.size;i++){
    for(int j=0;j<main_board_size;j++){
      for(int m=0;m<main_board_size;m++){
        tmp[j][m]=lvl.matrix[j][m];
      }
    }
    //for debugging purposes only ******{}
    //    std::cout <<" this is the " << i <<"time  x = " << x+col[i]<<" y = " <<y+row[i]<<"\n";
    //for debugging purposes only ******}
    if(is_Equal(tmp,x+col[i],y+row[i],7)){
      //for debugging purposes only to be removed later
      //    std::cout << "one or more boxes are depassing the borders \n";
      //for debugging purposes only to be removed later
      return 0;
    }
    else if(!is_Equal(tmp,x+col[i],y+row[i],0 )){
      //for debugging purposes only to be removed later
      //    std::cout << "Case is not empty " << "x = " << x+col[i]<<" y = " <<y+row[i] <<" = "<< tmp[x+col[i]][y+row[i]]  <<"\n";
      //for debugging purposes only to be removed later

      return 0;
    }else{


    }
    bool s1 = is_Equal(tmp,1+x+col[i],y+row[i],color);
    //tmp[1+x+col[i]][y+row[i]]=1;
    bool s2 = is_Equal(tmp,x+col[i],1+y+row[i],color);
    //tmp[x+col[i]][y+row[i]+1]=2;

    bool s3 = is_Equal(tmp,x+col[i]-1,y+row[i],color);
    //tmp[x+col[i]-1][y+row[i]]=3;

    bool s4 = is_Equal(tmp,x+col[i],y+row[i]-1,color);
    // tmp[x+col[i]][y+row[i]-1]=4;


    if(s1){
      //for debugging purposes only to be removed later
      //  std::cout << "problem with the sides\n";
      //for debugging purposes only to be removed later
      side=0;
    }
    if(s2){
      //for debugging purposes only to be removed later
      //    std::cout << "problem with the sides\n";
      //for debugging purposes only to be removed later
      side=0;
    }
    if(s3){
      //for debugging purposes only to be removed later
      //    std::cout << "problem with the sides\n";
      //for debugging purposes only to be removed later
      side=0;
    }
    if(s4){
      //for debugging purposes only to be removed later
      //    std::cout << "problem with the sides\n";
      //for debugging purposes only to be removed later
      side=0;
    }

    bool  c1 = is_Equal(tmp,1+x+col[i],1+y+row[i],color);
    bool  c2 = is_Equal(tmp,x+col[i]-1,1+y+row[i],color);
    bool  c3 = is_Equal(tmp,x+col[i]+1,y+row[i]-1,color);
    bool  c4 = is_Equal(tmp,x+col[i]-1,y+row[i]-1,color);

    if(c1||c2||c3||c4){
      //  std::cout << "corners are ok \n";
      corner[i] =1;
    }else{

      //    std::cout << "corners are not ok \n";
    }
  }
  if(side==0){

    return 0;
  }
  for(int k=0;k<5;k++){
    if(corner[k]==1){
      return 1;
    }
  }

  return 0;
}

playerHand is_Valid(playerHand input,playerHand pb,int x, int y,int size,int id){

  int col[size];
  int row[size];
  int n=0;
  for(int i=0 ; i<12 ; i++){
    for(int j=0; j<23;j++){
      if(input.matrix[i][j]==id){
        col[n]=i;
        row[n]=j;
        n++;
      }
    }
  }

  for(int i=0;i<size;i++){
    pb.matrix[col[i]][row[i]]=0;
  }
  pb = set_Player_Hand(pb.matrix);
  return pb;
}


//**************************************************************

Board do_Move(tile check,Board lvl,int x,int y,int color){
  //check if a tile placement location is empty (0)
  //return true or false depending on the condition
  Board tmp;

  int n = 0;
  int col[check.size];
  int row[check.size];
  for(int i=0 ; i<5 ; i++){
    for(int j=0; j<5;j++){
      if(check.matrix[i][j]!=0){
        col[n]=i-2;
        row[n]=j-2;
        n++;
      }
    }
  }
  for(int j=0;j<24;j++){
    for(int m=0;m<24;m++){
      tmp.matrix[j][m]=lvl.matrix[j][m];
    }
  }
  for(int i=0;i<check.size;i++){
    tmp.matrix[x+col[i]][y+row[i]]=color;
  }
  tmp = to_Board(tmp.matrix);
  lvl = set_Board(tmp.table);
  return lvl;
}


player set_Player(int id,sf::Color color,int time,tile tiles[]){
  player tmp;
  tmp.id=id;
  tmp.color= color;
  tmp.score =0;
  tmp.Time.min =time_for_each_player;
  tmp.Time.sec =0;
  for(int i=0;i<21;i++){
    tmp.Have[i]=1;
  }
  for(int i=0;i<21;i++){
    tmp.Hand[i]=set_Tile(tiles[i].id,tiles[i].table,tiles[i].size);
  }
  tmp.pboard=set_Player_Hand(tilesTableWithCenter);
  tmp.canPlay=true;
  return tmp;
}

tile flip_Matrix(tile input){


  for(int i=0;i<5;i++){
    int tmp;
    tmp =input.matrix[i][0];
    input.matrix[i][0]=input.matrix[i][4];
    input.matrix[i][4]=tmp;
    tmp =input.matrix[i][1];
    input.matrix[i][1]=input.matrix[i][3];
    input.matrix[i][3]=tmp;
  }
  return input= to_Tile(input.matrix,input);
}
//**************************************************************

int main() {
  bool start_game =true;

  bool  continue_playing = true ;

  Time times[4];

  sftools::Chronometer chrono[4];

  int current_player=0;

  TileMap map;


  sf::View view;
  //putting the tiles into one array for easy access
  tile tiles[21];
  tiles[0]=set_Tile(1,t1,1);
  tiles[1]=set_Tile(2,t2,2);
  tiles[2]=set_Tile(3,t3,3);
  tiles[3]=set_Tile(4,t4,3);
  tiles[4]=set_Tile(5,t5,4);
  tiles[5]=set_Tile(6,t6,4);
  tiles[6]=set_Tile(7,t7,4);
  tiles[7]=set_Tile(8,t8,4);
  tiles[8]=set_Tile(9,t9,4);
  tiles[9]=set_Tile(10,t10,5);
  tiles[10]=set_Tile(11,t11,5);
  tiles[11]=set_Tile(12,t12,5);
  tiles[12]=set_Tile(13,t13,5);
  tiles[13]=set_Tile(14,t14,5);
  tiles[14]=set_Tile(15,t15,5);
  tiles[15]=set_Tile(16,t16,5);
  tiles[16]=set_Tile(17,t17,5);
  tiles[17]=set_Tile(18,t18,5);
  tiles[18]=set_Tile(19,t19,5);
  tiles[19]=set_Tile(20,t20,5);
  tiles[20]=set_Tile(21,t21,5);
  sf::Font font;
  if (!font.loadFromFile("src/RobotoMono-Regular.ttf")){
    cout << "cant load the Texture file associated to rotate_Counter_Clock_Wise button : src/CCWrotate.png";
    return EXIT_FAILURE;

  }

  int idp[4];
  for(int i=0;i<4;i++){
    idp[i]=1;
  }

  sf::Text title("Blokus", font, 50);
  title.setPosition(Vector2f(((window_width/2 - title.getLocalBounds().width/2)),0.0));

  RenderWindow window(VideoMode(window_width, window_height), title.getString());

  //-----------------------------------------------------------------------------------------
  //Initialisation des variables concernantes les zones des joueurs
  Rectangle pAreas [4] ;
  pAreas[0].x =out_line_size;
  pAreas[0].y =out_line_size;
  pAreas[0].width=main_board_position_x-(2*out_line_size);
  pAreas[0].height=window_height/2-out_line_size;
  pAreas[0].color= Color(250, 177, 160,255);

  pAreas[1].x =out_line_size;
  pAreas[1].y =window_height/2 +(2*out_line_size);
  pAreas[1].width=main_board_position_x-(2*out_line_size);
  pAreas[1].height=window_height/2-3*out_line_size;
  pAreas[1].color= Color(116, 185, 255,255);

  pAreas[2].x =main_board_position_x + ( main_board_size* main_board_tile_width)+out_line_size ;
  pAreas[2].y =out_line_size;
  pAreas[2].width=main_board_position_x-(2*out_line_size);
  pAreas[2].height=window_height/2-out_line_size;
  pAreas[2].color= Color(85, 239, 196,255);


  pAreas[3].x =main_board_position_x + ( main_board_size* main_board_tile_width)+out_line_size;
  pAreas[3].y =window_height/2+(2*out_line_size);
  pAreas[3].width=main_board_position_x-(2*out_line_size);
  pAreas[3].height=window_height/2-3*out_line_size;//multiply by 3 because of the middle outline
  pAreas[3].color= Color(255, 234, 167,255);
  //---------------------------------------------------



  Rectangle Header;
  Header.x      =main_board_position_x+out_line_size;
  Header.y      =out_line_size;
  Header.width= main_board_size* main_board_tile_width-out_line_size;
  Header.height=main_board_position_y-out_line_size;
  Header.color= Color(sf::Color BgColor);



  Rectangle Footer;
  Footer.x      = main_board_position_x;
  Footer.y      = main_board_position_y + main_board_size * main_board_tile_height;
  Footer.width  = main_board_size * main_board_tile_height;
  Footer.height = Header.height;
  Footer.color  = Color(sf::Color BgColor);




  Rectangle skip_turn_buttonR;
  skip_turn_buttonR.width=window_width*0.1;
  skip_turn_buttonR.height=window_height*0.1;
  skip_turn_buttonR.x =Footer.x+Footer.width/2-skip_turn_buttonR.width/2;
  skip_turn_buttonR.y =main_board_position_y-skip_turn_buttonR.height;





  Rectangle flip_tile_buttonR;
  flip_tile_buttonR.width=window_width*0.1;
  flip_tile_buttonR.height=window_height*0.1;
  flip_tile_buttonR.x =Footer.x+Footer.width/2-flip_tile_buttonR.width/2;
  flip_tile_buttonR.y =Footer.y+(Footer.height/2)-flip_tile_buttonR.height/2;




  Rectangle rotate_Counter_Clock_WiseR;
  rotate_Counter_Clock_WiseR.width=window_width*0.1;
  rotate_Counter_Clock_WiseR.height=window_height*0.1;
  rotate_Counter_Clock_WiseR.x =Footer.x+Footer.width/4-rotate_Counter_Clock_WiseR.width/2;
  rotate_Counter_Clock_WiseR.y =Footer.y+Footer.height/2-rotate_Counter_Clock_WiseR.height/2;;



  Rectangle rotate_Clock_WiseR;
  rotate_Clock_WiseR.width=window_height*0.1;
  rotate_Clock_WiseR.height=window_height*0.1;
  rotate_Clock_WiseR.x =Footer.x+Footer.width/2+Footer.width/4-rotate_Clock_WiseR.width/2;
  rotate_Clock_WiseR.y =Footer.y+Footer.height/2-rotate_Clock_WiseR.height/2;;



  Rectangle start_game_buttonR;
  start_game_buttonR.width=window_width*0.15;
  start_game_buttonR.height=window_height*0.15;
  start_game_buttonR.x =window_width/2-start_game_buttonR.width/2;
  start_game_buttonR.y =window_height/3;


  player players[4];
  players[0]=set_Player(1,sf::Color::Red,time_for_each_player,tiles);
  players[1]=set_Player(2,sf::Color::Blue,time_for_each_player,tiles);
  players[2]=set_Player(3,sf::Color::Green,time_for_each_player,tiles);
  players[3]=set_Player(4,sf::Color::Yellow,time_for_each_player,tiles);

  for(int i=0;i<4;i++){
    players[i].pos.x=pAreas[i].x + pAreas[i].width/2-( player_board_tile_width* player_board_matrix_height)/2;
    players[i].pos.y= pAreas[i].y + pAreas[i].height - player_board_tile_height* player_board_tile_height -overflowcorrect;

  }


  Rectangle playerTileDisplay[4];

  for(int i=0;i<4;i++){
    playerTileDisplay[i].width=player_board_tile_width*tile_matrix_size;
    playerTileDisplay[i].height=player_board_tile_height*tile_matrix_size;
    playerTileDisplay[i].y=pAreas[i].y +pAreas[i].height/2 - playerTileDisplay[i].height;
    playerTileDisplay[i].x=pAreas[i].x+pAreas[i].width/2 -playerTileDisplay[i].width/2;
  }

  sf::Texture skip_turn_buttonRTexture;

  sf::Texture flip_tile_buttonRTexture;

  sf::Texture rotate_Counter_Clock_WiseRTexture;

  sf::Texture rotate_Clock_WiseRTexture;

  sf::Texture start_game_buttonRTexture;


  if (!rotate_Clock_WiseRTexture.loadFromFile("src/CWrotate.png"))
  {
    cout << "cant load the Texture file associated to rotate_Clock_Wise button : src/CWrotate.png";
  }

  if (!skip_turn_buttonRTexture.loadFromFile("src/skip.png"))
  {
    cout << "cant load the Texture file associated to rotate_Counter_Clock_Wise button : src/CCWrotate.png";
  }

  if (!flip_tile_buttonRTexture.loadFromFile("src/flip.png"))
  {
    cout << "cant load the Texture file associated to rotate_Counter_Clock_Wise button : src/CCWrotate.png";
  }

  if (!rotate_Counter_Clock_WiseRTexture.loadFromFile("src/CCWrotate.png"))
  {
    cout << "cant load the Texture file associated to rotate_Counter_Clock_Wise button : src/CCWrotate.png";
  }

  if (!start_game_buttonRTexture.loadFromFile("src/startgame.png"))
  {
    cout << "cant load the Texture file associated to rotate_Clock_Wise button : src/CWrotate.png";
  }


  RectangleShape rotate_Counter_Clock_WiseRS;
  rotate_Counter_Clock_WiseRS.setSize(Vector2f(rotate_Clock_WiseR.width,rotate_Counter_Clock_WiseR.height));
  rotate_Counter_Clock_WiseRS.setPosition(rotate_Counter_Clock_WiseR.x,rotate_Counter_Clock_WiseR.y);
  rotate_Counter_Clock_WiseRS.setTexture(&rotate_Counter_Clock_WiseRTexture);

  RectangleShape rotate_Clock_WiseRS;
  rotate_Clock_WiseRS.setSize(Vector2f(rotate_Clock_WiseR.width,rotate_Clock_WiseR.height));
  rotate_Clock_WiseRS.setPosition(rotate_Clock_WiseR.x,rotate_Clock_WiseR.y);
  rotate_Clock_WiseRS.setTexture(&rotate_Clock_WiseRTexture);


  RectangleShape flip_tile_buttonRS;
  flip_tile_buttonRS.setSize(Vector2f(flip_tile_buttonR.width,flip_tile_buttonR.height));
  flip_tile_buttonRS.setPosition(flip_tile_buttonR.x,flip_tile_buttonR.y);
  flip_tile_buttonRS.setTexture(&flip_tile_buttonRTexture);


  RectangleShape skip_turn_buttonRS;
  skip_turn_buttonRS.setSize(Vector2f(skip_turn_buttonR.width,skip_turn_buttonR.height));
  skip_turn_buttonRS.setPosition(skip_turn_buttonR.x,skip_turn_buttonR.y);
  skip_turn_buttonRS.setTexture(&skip_turn_buttonRTexture);


  RectangleShape start_game_buttonRS;
  start_game_buttonRS.setSize(Vector2f(start_game_buttonR.width,start_game_buttonR.height));
  start_game_buttonRS.setPosition(start_game_buttonR.x,start_game_buttonR.y);
  start_game_buttonRS.setTexture(&start_game_buttonRTexture);


  sf::Text PlayerName[4];

  for(int i=0 ; i<=3;i++){
    String tmp = std::to_string(i+1);
    PlayerName[i].setString("player" + tmp);
    PlayerName[i].setFont(font);
    PlayerName[i].setCharacterSize (25);
    PlayerName[i].setStyle(sf::Text::Bold);
    PlayerName[i].setColor(sf::Color::Black);
    PlayerName[i].setPosition(Vector2f(pAreas[i].x+pAreas[i].width/2-PlayerName[i].getGlobalBounds().width/2,pAreas[i].y));

  }


  sf::Text player_score_display[4];

  for(int i=0 ; i<4;i++){

    player_score_display[i].setString("score :");
    player_score_display[i].setFont(font);
    player_score_display[i].setCharacterSize (20);
    player_score_display[i].setStyle(sf::Text::Bold);
    player_score_display[i].setColor(sf::Color::Black);
    player_score_display[i].setPosition(Vector2f(pAreas[i].x+overflowcorrect, PlayerName[i].getLocalBounds().height*2 + PlayerName[i].getPosition().y ));

  }
  sf::Text player_clock_display[4];

  for(int i=0 ; i<4;i++){

    player_clock_display[i].setString("time:00:00");
    player_clock_display[i].setFont(font);
    player_clock_display[i].setCharacterSize (20);
    player_clock_display[i].setStyle(sf::Text::Bold);
    player_clock_display[i].setColor(sf::Color::Black);
    player_clock_display[i].setPosition(Vector2f(pAreas[i].x+pAreas[i].width-player_clock_display[i].getLocalBounds().width-2*out_line_size,  PlayerName[i].getLocalBounds().height*2 + PlayerName[i].getPosition().y ));

  }

  sf::Text GameOverText;
  GameOverText.setPosition(Vector2f(window_width/2-GameOverText.getLocalBounds().width/2,window_height/2));
  GameOverText.setFont(font);
  GameOverText.setCharacterSize (50);
  GameOverText.setStyle(sf::Text::Bold);
  GameOverText.setColor(sf::Color::Red);


  RectangleShape pAreasShape[4];

  for(int i=0 ; i <=3;i++){
    pAreasShape[i].setSize(Vector2f(pAreas[i].width,pAreas[i].height));
    pAreasShape[i].setPosition(pAreas[i].x,pAreas[i].y);
    pAreasShape[i].setFillColor(pAreas[i].color);
    pAreasShape[i].setOutlineThickness(out_line_size);
  }

  RectangleShape HeaderS;
  HeaderS.setSize(Vector2f(Header.width,Header.height));
  HeaderS.setPosition(Header.x,Header.y);
  HeaderS.setFillColor(Header.color);

  RectangleShape FooterS;
  FooterS.setSize(Vector2f(Footer.width,Footer.height));
  FooterS.setPosition(Footer.x,Footer.y);
  FooterS.setFillColor(Footer.color);
  RectangleShape contain[4];
//for debug purposes only to be removed after
for(int i=0 ; i<4;i++){
  contain[i].setSize(Vector2f(tile_matrix_size* player_board_tile_width,tile_matrix_size* player_board_tile_width));
  contain[i].setPosition(playerTileDisplay[i].x ,playerTileDisplay[i].y);
  contain[i].setOutlineThickness(out_line_size);
  contain[i].setFillColor(sf::Color::Transparent);
}

SoundBuffer placebuffer;
placebuffer.loadFromFile("place.wav");
sf::Sound placesound;
placesound.setBuffer(placebuffer);

SoundBuffer pickbuffer;
pickbuffer.loadFromFile("pick.wav");
sf::Sound picksound;
picksound.setBuffer(pickbuffer);

SoundBuffer flipbuffer;
flipbuffer.loadFromFile("flip.wav");
sf::Sound flipsound;
flipsound.setBuffer(flipbuffer);

SoundBuffer rotatebuffer;
rotatebuffer.loadFromFile("rotate.wav");
sf::Sound rotatesound;
rotatesound.setBuffer(rotatebuffer);

SoundBuffer winbuffer;
winbuffer.loadFromFile("win.wav");
sf::Sound winsound;
winsound.setBuffer(winbuffer);


bool playwinsound=true;


//for debug purposes only
  Board GameBoard = set_Board(iniMap);
  playerHand testFull=set_Player_Hand(tilesTableWithEachPiece);

  while (window.isOpen()) {
    window.setSize(Vector2u(window_width,window_height));

    for(int i=0 ; i <4;i++){
      if(i==current_player){
        pAreasShape[i].setOutlineColor(sf::Color::Red);
        contain[i].setOutlineColor(sf::Color::Red);
      }else{
        pAreasShape[i].setOutlineColor(sf::Color::White);
        contain[i].setOutlineColor(sf::Color::White);
      }
    }
    Event event;
    while (window.pollEvent(event)) {


      if (event.type == Event::Closed) {
        window.close();

      }

      if (event.type == Event::KeyPressed) {

        if(event.key.code==Keyboard::Up) {



        }
      }
      //*********************************************************************************************************************************************************

      //game play algorthme for each player
      int MousPosx = (int) event.mouseButton.x;
      int MousPosy = (int)event.mouseButton.y;
      chrono[current_player].resume();

      if (event.type == sf::Event::MouseButtonPressed&&players[current_player].canPlay) {


        if(MousPosx>main_board_position_x&&MousPosy>main_board_position_y&&MousPosx<main_board_position_x+ main_board_size* main_board_tile_width&&MousPosy<main_board_position_y+ main_board_size* main_board_tile_height){

          int transx = (MousPosx-main_board_position_x)/20;
          int transy = (MousPosy-main_board_position_y)/20;

          if(is_Valid(players[current_player].Hand[idp[current_player]-1],GameBoard,transy,transx,players[current_player].id)){

            players[current_player].score++;
            GameBoard= do_Move(players[current_player].Hand[idp[current_player]-1],GameBoard,transy,transx,players[current_player].id);
            players[current_player].pboard=is_Valid(testFull, players[current_player].pboard,transy,transx,players[current_player].Hand[idp[current_player]-1].size,idp[current_player]);
            players[current_player].Have[idp[current_player]]=0;
            chrono[current_player].pause();
            placesound.play();

            if(players[current_player].score==21){

              String rep=to_string(current_player+1);
              GameOverText.setString("Game Over \nplayer " + rep + " wins");
              continue_playing = false;

            }else{
              if(idp[current_player]<21&&players[current_player].Have[idp[current_player]+1]!=0){

                idp[current_player]++;

              }else{

                for(int i=0;i<21;i++){

                  if(players[current_player].Have[i]!=0){

                    idp[current_player]=i;
                  }
                }
              }

            }
            if(current_player+1<4){
              current_player++;
            }else{
              current_player=0;
            }
          }

        }
        if(MousPosx>players[current_player].pos.x&&MousPosx<players[current_player].pos.x+(12*23)&&MousPosy<players[current_player].pos.y+(player_board_tile_height*player_board_matrix_height)&&MousPosy>players[current_player].pos.y){

          int transx = (MousPosx-players[current_player].pos.x)/player_board_tile_width;
          int transy = (MousPosy-players[current_player].pos.y)/player_board_tile_height;

          if(players[current_player].pboard.matrix[transy][transx]!=0){
            idp[current_player]=testFull.matrix[transy][transx];
            picksound.play();
          }
        }
        if(MousPosx<rotate_Clock_WiseR.x + rotate_Clock_WiseR.width &&MousPosx>rotate_Clock_WiseR.x &&MousPosy<rotate_Clock_WiseR.y+rotate_Clock_WiseR.height&&MousPosy>rotate_Clock_WiseR.y){

          players[current_player].Hand[idp[current_player]-1]= rotate_Clock_Wise(players[current_player].Hand[idp[current_player]-1]);
          players[current_player].Hand[idp[current_player]-1]=to_Tile(players[current_player].Hand[idp[current_player]-1].matrix,players[current_player].Hand[idp[current_player]-1]);
          rotatesound.play();

        }

        if(MousPosx<rotate_Counter_Clock_WiseR.x + rotate_Counter_Clock_WiseR.width &&MousPosx>rotate_Counter_Clock_WiseR.x &&MousPosy<rotate_Counter_Clock_WiseR.y+rotate_Counter_Clock_WiseR.height&&MousPosy>rotate_Counter_Clock_WiseR.y){
          players[current_player].Hand[idp[current_player]-1]= rotate_Counter_Clock_Wise(players[current_player].Hand[idp[current_player]-1]);
          players[current_player].Hand[idp[current_player]-1]=to_Tile(players[current_player].Hand[idp[current_player]-1].matrix,players[current_player].Hand[idp[current_player]-1]);
          rotatesound.play();
                }

        if(MousPosx<skip_turn_buttonR.x + skip_turn_buttonR.width &&MousPosx>skip_turn_buttonR.x &&MousPosy<skip_turn_buttonR.y+skip_turn_buttonR.height&&MousPosy>skip_turn_buttonR.y){
          players[current_player].canPlay =false;
        }
        if(MousPosx<flip_tile_buttonR.x + flip_tile_buttonR.width &&MousPosx>flip_tile_buttonR.x &&MousPosy<flip_tile_buttonR.y+flip_tile_buttonR.height&&MousPosy>flip_tile_buttonR.y){
          players[current_player].Hand[idp[current_player]-1]= flip_Matrix(players[current_player].Hand[idp[current_player]-1]);
          players[current_player].Hand[idp[current_player]-1]=to_Tile(players[current_player].Hand[idp[current_player]-1].matrix,players[current_player].Hand[idp[current_player]-1]);
          flipsound.play();
        }

      }else if(!players[current_player].canPlay){
        if(current_player+1<4){
          current_player++;
        }else{
          current_player=0;
        }
      }

    }

    //*************************************************************************************************************

    //handling time in the game for each player
    times[current_player] = chrono[current_player].getElapsedTime();

    if(players[current_player].Time.sec<60){
      players[current_player].Time.sec=times[current_player].asSeconds();
      if(players[current_player].Time.sec<10){
        if(players[current_player].Time.min<10){
          player_clock_display[current_player].setString("time:0" + to_string(players[current_player].Time.min) + ":0" + to_string(players[current_player].Time.sec) );
        }else{
          player_clock_display[current_player].setString("time:" + to_string(players[current_player].Time.min) + ":0" + to_string(players[current_player].Time.sec) );
        }
      }else{

        if(players[current_player].Time.min<10){
          player_clock_display[current_player].setString("time:0" + to_string(players[current_player].Time.min) + ":" + to_string(players[current_player].Time.sec) );
        }else{
          player_clock_display[current_player].setString("time:" +to_string(players[current_player].Time.min) + ":" + to_string(players[current_player].Time.sec) );
        }
      }
      if(players[current_player].Time.min>9){
        players[current_player].canPlay=false;
      }
    }else{
      chrono[current_player].reset();
      players[current_player].Time.sec=0;
      players[current_player].Time.min++;
      chrono[current_player].resume();
    }

    //************************************************************************************************************************************************************************
    if (!map.load("src/tileset20m.png", sf::Vector2u( main_board_tile_width,  main_board_tile_height), GameBoard.table , main_board_size,  main_board_size, main_board_position_x ,main_board_position_y)){
      cout << "cant load the Texture file associated to main board load  : src/tileset20m.png";

      return -1;
    }
    for (int i=0;i<4;i++){
      if (!players[i].FullHand.load("src/ptiles36.png", sf::Vector2u( player_board_tile_width, player_board_tile_height), players[i].pboard.table,  player_board_matrix_height,  player_board_matrix_width, players[i].pos.x,players[i].pos.y)){
        cout << "cant load the Texture file associated to main board load  : src/tileset20m.png";

        return -1;
      }
      if (!players[i].cTile.load("src/ptiles36.png", sf::Vector2u( player_board_tile_width, player_board_tile_height), players[i].Hand[idp[i]-1].table, tile_matrix_size, tile_matrix_size,playerTileDisplay[i].x ,playerTileDisplay[i].y)){
        cout << "cant load the Texture file associated to main board load  : src/tileset20m.png";

        return -1;
      }

    }



    if(start_game){
      if((players[0].canPlay||players[1].canPlay||players[2].canPlay||players[3].canPlay)&&continue_playing){
        window.clear(sf::Color BgColor);

        window.draw(map);
        window.draw(HeaderS);
        window.draw(FooterS);
        window.draw(rotate_Clock_WiseRS);
        window.draw(rotate_Counter_Clock_WiseRS);
        window.draw(rotate_Counter_Clock_WiseRS);
        window.draw(flip_tile_buttonRS);
        window.draw(skip_turn_buttonRS);

        for (int i=0 ; i<=3;i++){
          window.draw(pAreasShape[i]);
          window.draw(PlayerName[i]);
          window.draw(players[i].FullHand);
          window.draw(players[i].cTile);
          player_score_display[i].setString("score: " + to_string(players[i].score));
          window.draw(player_score_display[i]);
          window.draw(player_clock_display[i]);
          window.draw(contain[i]);
        }
        window.draw(title);
        window.display();
      }else{
        int max=players[0].score;
        for(int i=1;i<4;i++){
          if(players[i].score>max){
            max =players[i].id;
          }
        }
        window.clear(sf::Color::Transparent);

        String rep=to_string(max);
        GameOverText.setString("Game Over \nplayer " + rep + " wins");
        while (playwinsound){
        winsound.play();
        playwinsound=false;
      }
        window.draw(GameOverText);

        window.display();
      }

    }else{
      window.draw(start_game_buttonRS);
      window.display();

    }
  }
  return 0;
}
