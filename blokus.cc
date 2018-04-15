
#include <random>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <ctime>


using namespace std;
using namespace sf;

//height of the window
const int window_height                = 720 ;
//width of the window
const int window_width                 = 1080 ;
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
const int   time_for_each_player       = 10 ;
//define the size of a single tile
const int   tile_matrix_size           = 5 ;

const int   total_number_of_tiles      = 21;

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
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 7,
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
  7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,

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
  return tmp;
}


//**************************************************************

int main() {
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


  TileMap map;

  TileMap p1;
  RenderWindow window(VideoMode(window_width, window_height), "Blokus");

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
  pAreas[1].height=window_height/2-out_line_size;
  pAreas[1].color= Color(116, 185, 255,255);

  pAreas[2].x =main_board_position_x + ( main_board_size* main_board_tile_width)+out_line_size ;
  pAreas[2].y =out_line_size;
  pAreas[2].width=main_board_position_x-(2*out_line_size);
  pAreas[2].height=window_height/2-out_line_size;
  pAreas[2].color= Color(85, 239, 196,255);


  pAreas[3].x =main_board_position_x + ( main_board_size* main_board_tile_width)+out_line_size;
  pAreas[3].y =window_height/2+(2*out_line_size);
  pAreas[3].width=main_board_position_x-(2*out_line_size);
  pAreas[3].height=window_height/2-out_line_size;
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


//**************************************************************


 Rectangle skip_turn_buttonR;
 skip_turn_buttonR.width=window_height*0.2;
 skip_turn_buttonR.height=window_height*0.1;
 skip_turn_buttonR.x =Footer.x+Footer.width/2-skip_turn_buttonR.width/2;
 skip_turn_buttonR.y =Footer.y+Footer.height/2-skip_turn_buttonR.height/2;;
 sf::Texture skip_turn_buttonRTexture;
 //loading and checking for the files
 if (!skip_turn_buttonRTexture.loadFromFile("src/skip.png"))
 {
   cout << "cant load the Texture file associated to rotate_Counter_Clock_Wise button : src/CCWrotate.png";
 }

 RectangleShape skip_turn_buttonRS;
 skip_turn_buttonRS.setSize(Vector2f(skip_turn_buttonR.width,skip_turn_buttonR.height));
 skip_turn_buttonRS.setPosition(skip_turn_buttonR.x,skip_turn_buttonR.y);
 skip_turn_buttonRS.setTexture(&skip_turn_buttonRTexture);

  Rectangle rotate_Counter_Clock_WiseR;
  rotate_Counter_Clock_WiseR.width=window_height*0.1;
  rotate_Counter_Clock_WiseR.height=window_height*0.1;
  rotate_Counter_Clock_WiseR.x =Footer.x+Footer.width/4-rotate_Counter_Clock_WiseR.width/2;
  rotate_Counter_Clock_WiseR.y =Footer.y+Footer.height/2-rotate_Counter_Clock_WiseR.height/2;;
  sf::Texture rotate_Counter_Clock_WiseRTexture;
  //loading and checking for the files
  if (!rotate_Counter_Clock_WiseRTexture.loadFromFile("src/CCWrotate.png"))
  {
    cout << "cant load the Texture file associated to rotate_Counter_Clock_Wise button : src/CCWrotate.png";
  }

  Rectangle rotate_Clock_WiseR;
  rotate_Clock_WiseR.width=window_height*0.1;
  rotate_Clock_WiseR.height=window_height*0.1;
  rotate_Clock_WiseR.x =Footer.x+Footer.width/2+Footer.width/4-rotate_Clock_WiseR.width/2;
  rotate_Clock_WiseR.y =Footer.y+Footer.height/2-rotate_Clock_WiseR.height/2;;
  sf::Texture rotate_Clock_WiseRTexture;
  if (!rotate_Clock_WiseRTexture.loadFromFile("src/CWrotate.png"))
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
  //*********************************************************************************************************


  sf::Text title("Blokus", font, 50);
  title.setPosition(Vector2f(((window_width/2 - title.getLocalBounds().width/2)),0.0));
  //*********************************************************************************************************



  player players[4];
  players[0]=set_Player(1,sf::Color::Red,time_for_each_player,tiles);
  players[0].pos.x=pAreas[0].width/2-( player_board_tile_width* player_board_matrix_height)/2;
  players[0].pos.y= pAreas[0].height - player_board_tile_height* player_board_tile_height -overflowcorrect;

  players[1]=set_Player(2,sf::Color::Blue,time_for_each_player,tiles);
  players[1].pos.x=pAreas[1].width/2-( player_board_tile_width* player_board_matrix_height)/2 ;
  players[1].pos.y=  pAreas[1].y + pAreas[1].height - player_board_tile_height* player_board_matrix_width -overflowcorrect;

  players[2]=set_Player(3,sf::Color::Green,time_for_each_player,tiles);
  players[2].pos.x =pAreas[2].x + pAreas[2].width/2-( player_board_tile_width* player_board_matrix_height)/2 ;
  players[2].pos.y=pAreas[2].height - player_board_tile_height* player_board_matrix_width -overflowcorrect;

  players[3]=set_Player(4,sf::Color::Yellow,time_for_each_player,tiles);
  players[3].pos.x =pAreas[3].x + pAreas[3].width/2 - ( player_board_tile_width* player_board_matrix_height)/2 ;
  players[3].pos.y =  pAreas[3].y + pAreas[3].height - player_board_tile_height* player_board_matrix_width -overflowcorrect;

  //*********************
  sf::Text PlayerName[4];

  for(int i=0 ; i<=3;i++){
    String tmp = std::to_string(i+1);
    PlayerName[i].setString("player" + tmp);
    PlayerName[i].setFont(font);
    PlayerName[i].setCharacterSize (20);
    PlayerName[i].setStyle(sf::Text::Bold);
    PlayerName[i].setColor(sf::Color::Black);

  }
  PlayerName[0].setPosition(Vector2f(overflowcorrect,0.0));
  PlayerName[1].setPosition(Vector2f(overflowcorrect,pAreas[1].y + PlayerName[1].getLocalBounds().height/2 ));
  PlayerName[2].setPosition(Vector2f((pAreas[2].x) + overflowcorrect,0.0));
  PlayerName[3].setPosition(Vector2f((pAreas[3].x) + overflowcorrect,pAreas[3].y + PlayerName[3].getLocalBounds().height/2 ));

  sf::Text PlayerClockDisplay[4];

  for(int i=0 ; i<=3;i++){
    String tmp = std::to_string(i+1);
    PlayerClockDisplay[i].setFont(font);
    PlayerClockDisplay[i].setCharacterSize (20);
    PlayerClockDisplay[i].setStyle(sf::Text::Bold);
    PlayerClockDisplay[i].setColor(sf::Color::Black);

  }

  //****************************************************************************************************
  //***************************************************************************
  Rectangle playerTileDisplay[4];
  playerTileDisplay[0].width=60;
  playerTileDisplay[0].height=60;
  playerTileDisplay[0].y=(players[0].pos.y -(PlayerName[0].getLocalBounds().height +PlayerName[0].getPosition().y ))/2;
  playerTileDisplay[0].x=pAreas[0].width/2 -playerTileDisplay[0].width/2;

  playerTileDisplay[1].width=60;
  playerTileDisplay[1].height=60;
  playerTileDisplay[1].y=(players[1].pos.y +(PlayerName[1].getLocalBounds().height +PlayerName[1].getPosition().y ))/2;
  playerTileDisplay[1].x=pAreas[1].width/2 -playerTileDisplay[1].width/2;

  playerTileDisplay[2].width=60;
  playerTileDisplay[2].height=60;
  playerTileDisplay[2].y=(players[2].pos.y -(PlayerName[2].getLocalBounds().height +PlayerName[2].getPosition().y ))/2;
  playerTileDisplay[2].x=pAreas[2].x+ pAreas[2].width/2 -playerTileDisplay[2].width/2;

  playerTileDisplay[3].width=60;
  playerTileDisplay[3].height=60;
  playerTileDisplay[3].y=(players[3].pos.y +(PlayerName[1].getLocalBounds().height +PlayerName[1].getPosition().y ))/2;
  playerTileDisplay[3].x=pAreas[3].x+ pAreas[3].width/2 -playerTileDisplay[2].width/2;


  TileMap piece1;
  sf::Text GameOverText;

  //*********************************************************************************************************
  int player=0;
  bool player_one_can_play=true;
  bool player_two_can_play=true;
  bool player_three_can_play=true;
  bool player_four_can_play=true;
  Board GameBoard = set_Board(iniMap);
  playerHand testFull=set_Player_Hand(tilesTableWithEachPiece);
  while (window.isOpen()) {

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
    window.clear(sf::Color BgColor);

    for(int i=0 ; i <=3;i++){
      if(i==player){
      pAreasShape[i].setOutlineColor(sf::Color::Red);
    }else{
      pAreasShape[i].setOutlineColor(sf::Color::White);
    }}
    Event event;
    while (window.pollEvent(event)) {


      if (event.type == Event::Closed) {
        window.close();

      }

      if (event.type == Event::KeyPressed) {

        if(event.key.code==Keyboard::Up) {



        }
      }
  //**********************************************************************************************************************************************************

      int MousPosx = (int) event.mouseButton.x;
      int MousPosy = (int)event.mouseButton.y;

      switch(player){
        case 0:{

          if (event.type == sf::Event::MouseButtonPressed&&player_one_can_play) {


            if(MousPosx>main_board_position_x&&MousPosy>main_board_position_y&&MousPosx<main_board_position_x+ main_board_size* main_board_tile_width&&MousPosy<main_board_position_y+ main_board_size* main_board_tile_height){

              int transx = (MousPosx-main_board_position_x)/20;
              int transy = (MousPosy-main_board_position_y)/20;

              if(is_Valid(players[player].Hand[idp[player]-1],GameBoard,transy,transx,players[player].id)){

                players[player].score++;
                GameBoard= do_Move(players[player].Hand[idp[player]-1],GameBoard,transy,transx,players[player].id);
                players[player].pboard=is_Valid(testFull, players[player].pboard,transy,transx,players[player].Hand[idp[player]-1].size,idp[player]);
                players[player].Have[idp[player]]=0;

                if(players[player].score==21){

                    String rep=to_string(player+1);
                    GameOverText.setString("Game Over \nplayer " + rep + " wins");

                }else{
                  if(idp[player]<21&&players[player].Have[idp[player]+1]!=0){

                    idp[player]++;

                  }else{

                    for(int i=0;i<21;i++){

                      if(players[player].Have[i]!=0){

                        idp[player]=i;
                      }
                    }
                  }
                  player=1;

                }
            }
          }

            if(MousPosx<main_board_position_x&&MousPosy<pAreas[player].height){

              int transx = (MousPosx-players[player].pos.x)/12;
              int transy = (MousPosy-players[player].pos.y)/12;
              if(players[player].pboard.matrix[transy][transx]!=0){
                idp[player]=testFull.matrix[transy][transx];
              }
            }
            if(MousPosx<rotate_Clock_WiseR.x + rotate_Clock_WiseR.width &&MousPosx>rotate_Clock_WiseR.x &&MousPosy<rotate_Clock_WiseR.y+rotate_Clock_WiseR.height&&MousPosy>rotate_Clock_WiseR.y){

              players[player].Hand[idp[player]-1]= rotate_Clock_Wise(players[player].Hand[idp[player]-1]);
              players[player].Hand[idp[player]-1]=to_Tile(players[player].Hand[idp[player]-1].matrix,players[player].Hand[idp[player]-1]);
            }

            if(MousPosx<rotate_Counter_Clock_WiseR.x + rotate_Counter_Clock_WiseR.width &&MousPosx>rotate_Counter_Clock_WiseR.x &&MousPosy<rotate_Counter_Clock_WiseR.y+rotate_Counter_Clock_WiseR.height&&MousPosy>rotate_Counter_Clock_WiseR.y){
              players[player].Hand[idp[player]-1]= rotate_Counter_Clock_Wise(players[player].Hand[idp[player]-1]);
              players[player].Hand[idp[player]-1]=to_Tile(players[player].Hand[idp[player]-1].matrix,players[player].Hand[idp[player]-1]);
            }

            if(MousPosx<skip_turn_buttonR.x + skip_turn_buttonR.width &&MousPosx>skip_turn_buttonR.x &&MousPosy<skip_turn_buttonR.y+skip_turn_buttonR.height&&MousPosy>skip_turn_buttonR.y){
              player_one_can_play =false;
            }

          }else if(!player_one_can_play){
            player=1;
          }
          break;
        }

//--------------------------------------------------------------------------------------------------------------------------------

        case 1:{
          sf::Clock clock2;
          if (event.type == sf::Event::MouseButtonPressed&&player_two_can_play) {

            if(MousPosx>main_board_position_x&&MousPosy>main_board_position_y&&MousPosx<main_board_position_x+ main_board_size* main_board_tile_width&&MousPosy<main_board_position_y+ main_board_size* main_board_tile_height){

              int transx = (MousPosx-main_board_position_x)/20;
              int transy = (MousPosy-main_board_position_y)/20;

              if(is_Valid(players[player].Hand[idp[player]-1],GameBoard,transy,transx,players[player].id)){

                players[player].score++;
                GameBoard= do_Move(players[player].Hand[idp[player]-1],GameBoard,transy,transx,players[player].id);
                players[player].pboard=is_Valid(testFull, players[player].pboard,transy,transx,players[player].Hand[idp[player]-1].size,idp[player]);
                players[player].Have[idp[player]]=0;

                if(players[player].score==21){

                    String rep=to_string(player+1);
                    GameOverText.setString("Game Over \nplayer " + rep + " wins");
                    player = 5;

                }else{

                  if(idp[player]<21&&players[player].Have[idp[player]+1]!=0){

                    idp[player]++;

                  }else{

                    for(int i=0;i<21;i++){

                      if(players[player].Have[i]!=0){

                        idp[player]=i;

                      }
                    }
                  }
                  player=2;

                }
            }
          }

              if(MousPosx<main_board_position_x&&MousPosy>pAreas[player].y+((pAreas[player].height/2)-players[player].pos.x)){
                int transx = (MousPosx-players[player].pos.x)/12;
                int transy = (MousPosy-players[player].pos.y)/12;
                if(players[player].pboard.matrix[transy][transx]!=0){
                  idp[player]=testFull.matrix[transy][transx];


                }
              }

              if(MousPosx<rotate_Clock_WiseR.x + rotate_Clock_WiseR.width &&MousPosx>rotate_Clock_WiseR.x &&MousPosy<rotate_Clock_WiseR.y+rotate_Clock_WiseR.height&&MousPosy>rotate_Clock_WiseR.y){

                players[player].Hand[idp[player]-1]= rotate_Clock_Wise(players[player].Hand[idp[player]-1]);
                players[player].Hand[idp[player]-1]=to_Tile(players[player].Hand[idp[player]-1].matrix,players[player].Hand[idp[player]-1]);

              }

              if(MousPosx<rotate_Counter_Clock_WiseR.x + rotate_Counter_Clock_WiseR.width &&MousPosx>rotate_Counter_Clock_WiseR.x &&MousPosy<rotate_Counter_Clock_WiseR.y+rotate_Counter_Clock_WiseR.height&&MousPosy>rotate_Counter_Clock_WiseR.y){
                players[player].Hand[idp[player]-1]= rotate_Counter_Clock_Wise(players[player].Hand[idp[player]-1]);
                players[player].Hand[idp[player]-1]=to_Tile(players[player].Hand[idp[player]-1].matrix,players[player].Hand[idp[player]-1]);
              }
              if(MousPosx<skip_turn_buttonR.x + skip_turn_buttonR.width &&MousPosx>skip_turn_buttonR.x &&MousPosy<skip_turn_buttonR.y+skip_turn_buttonR.height&&MousPosy>skip_turn_buttonR.y){
                player_two_can_play =false;
              }

            }else if(!player_two_can_play){
              player=2;
            }
        break;

        }
//--------------------------------------------------------------------------------------------------------------------------------

        case 2:{
          sf::Clock clock3;
          if (event.type == sf::Event::MouseButtonPressed&&player_three_can_play) {


            if(MousPosx>main_board_position_x&&MousPosy>main_board_position_y&&MousPosx<main_board_position_x+ main_board_size* main_board_tile_width&&MousPosy<main_board_position_y+ main_board_size* main_board_tile_height){
              int transx = (MousPosx-main_board_position_x)/20;
              int transy = (MousPosy-main_board_position_y)/20;
              if(is_Valid(players[player].Hand[idp[player]-1],GameBoard,transy,transx,players[player].id)){
                players[player].score++;
                GameBoard= do_Move(players[player].Hand[idp[player]-1],GameBoard,transy,transx,players[player].id);
                players[player].pboard=is_Valid(testFull, players[player].pboard,transy,transx,players[player].Hand[idp[player]-1].size,idp[player]);
                players[player].Have[idp[player]]=0;
                if(players[player].score==21){
                    String rep=to_string(player+1);
                    GameOverText.setString("Game Over \nplayer " + rep + " wins");
                }else{
                  if(idp[player]<21&&players[player].Have[idp[player]+1]!=0){
                    idp[player]++;
                  }else{
                    for(int i=0;i<21;i++){
                      if(players[player].Have[i]!=0){
                        idp[player]=i;
                      }
                    }
                  }
                  player=3;

                }
            }
          }
            if(MousPosx>main_board_position_x+ main_board_size* main_board_tile_width&&MousPosy<pAreas[player].height){
              int transx = (MousPosx-players[player].pos.x)/12;
              int transy = (MousPosy-players[player].pos.y)/12;

              if(players[player].pboard.matrix[transy][transx]!=0){
                idp[player]=testFull.matrix[transy][transx];


              }
            }
            if(MousPosx<rotate_Clock_WiseR.x + rotate_Clock_WiseR.width &&MousPosx>rotate_Clock_WiseR.x &&MousPosy<rotate_Clock_WiseR.y+rotate_Clock_WiseR.height&&MousPosy>rotate_Clock_WiseR.y){

              players[player].Hand[idp[player]-1]= rotate_Clock_Wise(players[player].Hand[idp[player]-1]);
              players[player].Hand[idp[player]-1]=to_Tile(players[player].Hand[idp[player]-1].matrix,players[player].Hand[idp[player]-1]);

            }if(MousPosx<rotate_Counter_Clock_WiseR.x + rotate_Counter_Clock_WiseR.width &&MousPosx>rotate_Counter_Clock_WiseR.x &&MousPosy<rotate_Counter_Clock_WiseR.y+rotate_Counter_Clock_WiseR.height&&MousPosy>rotate_Counter_Clock_WiseR.y){
              players[player].Hand[idp[player]-1]= rotate_Counter_Clock_Wise(players[player].Hand[idp[player]-1]);
              players[player].Hand[idp[player]-1]=to_Tile(players[player].Hand[idp[player]-1].matrix,players[player].Hand[idp[player]-1]);
            }
            if(MousPosx<skip_turn_buttonR.x + skip_turn_buttonR.width &&MousPosx>skip_turn_buttonR.x &&MousPosy<skip_turn_buttonR.y+skip_turn_buttonR.height&&MousPosy>skip_turn_buttonR.y){
              player_three_can_play =false;
            }
          }else if(!player_three_can_play){
            player=3;
          }

          break;
        }
//--------------------------------------------------------------------------------------------------------------------------------

        case 3:{
               sf::Clock clock4;
               if (event.type == sf::Event::MouseButtonPressed&&player_four_can_play) {


                 if(MousPosx>main_board_position_x&&MousPosy>main_board_position_y&&MousPosx<main_board_position_x+ main_board_size* main_board_tile_width&&MousPosy<main_board_position_y+ main_board_size* main_board_tile_height){
                   int transx = (MousPosx-main_board_position_x)/20;
                   int transy = (MousPosy-main_board_position_y)/20;
                   if(is_Valid(players[player].Hand[idp[player]-1],GameBoard,transy,transx,players[player].id)){
                     players[player].score++;
                     GameBoard= do_Move(players[player].Hand[idp[player]-1],GameBoard,transy,transx,players[player].id);
                     players[player].pboard=is_Valid(testFull, players[player].pboard,transy,transx,players[player].Hand[idp[player]-1].size,idp[player]);
                     players[player].Have[idp[player]]=0;
                     if(players[player].score==21){
                         String rep=to_string(player+1);
                         GameOverText.setString("Game Over \nplayer " + rep + " wins");
                     }else{
                       if(idp[player]<21&&players[player].Have[idp[player]+1]!=0){
                         idp[player]++;
                       }else{
                         for(int i=0;i<21;i++){
                           if(players[player].Have[i]!=0){
                             idp[player]=i;
                           }
                         }
                       }
                       player=0;

                     }
                 }
               }
            if(MousPosx>main_board_position_x+ main_board_size* main_board_tile_width&&MousPosx<window_width&&MousPosy>pAreas[player].y+((pAreas[player].height/2)-players[player].pos.x)){

              int transx = (MousPosx-players[player].pos.x)/12;


              int transy = (MousPosy-players[player].pos.y)/12;

              if(players[player].pboard.matrix[transy][transx]!=0){
                idp[player]=testFull.matrix[transy][transx];


              }
            }
            if(MousPosx<rotate_Clock_WiseR.x + rotate_Clock_WiseR.width &&MousPosx>rotate_Clock_WiseR.x &&MousPosy<rotate_Clock_WiseR.y+rotate_Clock_WiseR.height&&MousPosy>rotate_Clock_WiseR.y){

              players[player].Hand[idp[player]-1]= rotate_Clock_Wise(players[player].Hand[idp[player]-1]);
              players[player].Hand[idp[player]-1]=to_Tile(players[player].Hand[idp[player]-1].matrix,players[player].Hand[idp[player]-1]);

            }if(MousPosx<rotate_Counter_Clock_WiseR.x + rotate_Counter_Clock_WiseR.width &&MousPosx>rotate_Counter_Clock_WiseR.x &&MousPosy<rotate_Counter_Clock_WiseR.y+rotate_Counter_Clock_WiseR.height&&MousPosy>rotate_Counter_Clock_WiseR.y){
              players[player].Hand[idp[player]-1]= rotate_Counter_Clock_Wise(players[player].Hand[idp[player]-1]);
              players[player].Hand[idp[player]-1]=to_Tile(players[player].Hand[idp[player]-1].matrix,players[player].Hand[idp[player]-1]);
            }if(MousPosx<skip_turn_buttonR.x + skip_turn_buttonR.width &&MousPosx>skip_turn_buttonR.x &&MousPosy<skip_turn_buttonR.y+skip_turn_buttonR.height&&MousPosy>skip_turn_buttonR.y){
              player_four_can_play =false;
            }
          }
          else if(!player_four_can_play){
            player=0;
          }

        break;
      }
    }
  }
//}
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

    if(player_one_can_play||player_two_can_play||player_three_can_play||player_four_can_play){

    window.draw(map);
    window.draw(HeaderS);
    window.draw(FooterS);
    window.draw(rotate_Clock_WiseRS);
    window.draw(rotate_Counter_Clock_WiseRS);
    window.draw(rotate_Counter_Clock_WiseRS);
      window.draw(skip_turn_buttonRS);
    for (int i = 0 ; i<=3;i++){
      window.draw(pAreasShape[i]);
    }

    for (int i = 0 ; i<=3;i++){
      window.draw(players[i].FullHand);
      window.draw(players[i].cTile);
    }
    for (int i=0 ; i<=3;i++){
      window.draw(PlayerName[i]);
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
          String rep=to_string(max);
          GameOverText.setString("Game Over \nplayer " + rep + " wins");

    window.draw(GameOverText);

    window.display();
}
  }

  return 0;
}
