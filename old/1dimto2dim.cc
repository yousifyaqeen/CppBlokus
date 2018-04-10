#include <iostream>
#include <stdio.h>

struct Board{
  //definning the board to be refrenced after and modified
  int table[24*24];
  int matrix[24][24];
};



struct tile{
  //definning the tile to be refrenced after and modified
int id;
int table[25];
int matrix[5][5];
int size;
};
//for debugging purposes only ********{

void print_matrix(int n[24][24]){
  //a function to print the board not to be used in the game
  //for debugging purposes only
  //activated when called with a square matrix of size 24
  for (int i = 0; i < 24; i++) {
       for (int j = 0; j < 24; j++) {
          std::cout << n[i][j] << " ";
       }
      std::cout << " " << std::endl;
    }
}
//for debugging purposes only ********}


//for debugging purposes only ********{
void print_matrix(int n[5][5]){
  //a function to print the tile not to be used in the game
  //activated when called with a square matrix of size 5
  for (int i = 0; i < 5; i++) {
       for (int j = 0; j < 5; j++) {
          std::cout << n[i][j] << " ";
       }
      std::cout << " " << std::endl;
    }
}
//for debugging purposes only ******}

//********************************
Board setBoard(int input[]){
  Board tmp ;
tmp =  boardToMatrix(input);
tmp = boardToArray(tmp.matrix,tmp);
return tmp;
}


//*************************************
tile setTile(int input[]){
  tile tmp;
  tmp= tileToMatrix(input);
  tmp=tileToArray(tmp.table,tmp);
return tmp;
}
//**************************************************************


  tile rotateCW(tile input){
    //an algorithme to rotate a matrix clockwise
    //can only be used for a matrix of size 5*5
    //returns a tile
    for(int r = 0; r < 5; r++) {
      for(int c = r; c < 5; c++) {
          int tmp=input.matrix[r][c];
          input.matrix[r][c]=input.matrix[c][r];
          input.matrix[c][r]=tmp;
      }
    }
    for(int r = 0; r < 5; r++) {
      for(int c =0; c < 5/2; c++) {
        int tmp=input.matrix[r][c];
        input.matrix[r][c]=input.matrix[r][5-c-1];
        input.matrix[r][5-c-1]=tmp;
      }
    }
    return input;
  }
//**************************************************************


  tile rotateCCW(tile input){
    //an algorithme to rotate a matrix counter clockwise
    //can only be used for a matrix of size 5*5
    //returns a tile
    for(int r = 0; r < 5; r++) {
      for(int c = r; c < 5; c++) {
          int tmp=input.matrix[r][c];
          input.matrix[r][c]=input.matrix[c][r];
          input.matrix[c][r]=tmp;
      }
    }
    for(int r = 0; r < 5; r++) {
      for(int c =0; c < 5/2; c++) {
        int tmp=input.matrix[r][c];
        input.matrix[r][c]=input.matrix[r][5-c-1];
        input.matrix[r][5-c-1]=tmp;
      }
    }
    return input;
  }



  //*************************************************************
  tile tileToMatrix(int input[]){
    //a function to create a matrix from a tile table
    tile tmp;
    int n=0;
    for(int i=0;i<5;i++){
      for(int j=0;j<5;j++){
        tmp.matrix[i][j]=input[n];
        n++;
      }
    }
    return tmp;
  }

//**************************************************************


  Board boardToMatrix(int input[]){
    //a function to create a matrix from the map
    Board tmp;
    int n=0;
    for(int i=0;i<24;i++){
      for(int j=0;j<24;j++){
        tmp.matrix[i][j]=input[n];
        n++;
      }
    }
    return tmp;
  }


  //**************************************************************
    Board boardToMatrix(int input[],Board tmp){
      //a function to create a matrix from the map
      int n=0;
      for(int i=0;i<24;i++){
        for(int j=0;j<24;j++){
          tmp.matrix[i][j]=input[n];
          n++;
        }
      }
      return tmp;
    }

  //**************************************************************


  tile tileToArray(int input[5][5],tile tmp){
    //a function to create a table from the tile matrix
    int n=0;
    for(int i=0;i<5;i++){
      for(int j=0;j<5;j++){
        tmp.table[n]= input[i][j];
        n++;
      }
    }
  return tmp;
  }

  //**************************************************************
tile tileToArray(tile input){
  //a function to create a table from the tile matrix

  tile tmp;
  int n=0;
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      tmp.table[n]= input.matrix[i][j];
      n++;
    }
  }
return tmp;
}

//**************************************************************

Board boardToArray(int input[24][24]){
  //a function to create a table from the map matrix
  Board tmp;
  int n=0;
  for(int i=0;i<24;i++){
    for(int j=0;j<24;j++){
      tmp.table[n]= input[i][j];
      n++;

    }
  }
return tmp;
}

//**************************************************************

Board boardToArray(int input[24][24],Board tmp){
  //a function to create a table from the map matrix
  int n=0;
  for(int i=0;i<24;i++){
    for(int j=0;j<24;j++){
      tmp.table[n]= input[i][j];
      n++;

    }
  }
return tmp;
}


//********************************



Board setBoard(int input[]){
  Board tmp ;
tmp =  boardToMatrix(input);
tmp = boardToArray(tmp.matrix,tmp);
return tmp;
}

//**************************************************************


int IsEqual(int input[24][24],int x,int y,int color){
  return input[x][y]==color;
}

//**************************************************************

  int IsValid(tile check,Board lvl,int x,int y,int size,int color){
    //check if a tile placement location is empty (0)
    //return true or false depending on the condition
    int tmp[24][24];
    int n = 0;
    int col[size];
    int row[size];
    for(int i=0 ; i<5 ; i++){
      for(int j=0; j<5;j++){
        if(check.matrix[i][j]!=0){
          col[n]=i-2;
          row[n]=j-2;
          n++;
        }
      }
    }
    bool side=1;
    bool corner[5] ={0,0,0,0,0};

    for(int i=0;i<size;i++){
      for(int j=0;j<24;j++){
        for(int i=0;i<24;i++){
          tmp[j][i]=lvl.matrix[j][i];
        }
      }
    if(IsEqual(lvl.matrix,x+col[i],y+row[i],7)){
      //for debugging purposes only to be removed later
      //std::cout << "one or more boxes are depassing the borders \n";
      //for debugging purposes only to be removed later

      return 0;
    }
      else if(!IsEqual(lvl.matrix,x+col[i],y+row[i],0 )){
        //for debugging purposes only to be removed later
        //std::cout << "Case is not empty\n";
        //for debugging purposes only to be removed later
      return 0;
}
        bool s1 = IsEqual(lvl.matrix,1+x+col[i],y+row[i],color);
         //tmp[1+x+col[i]][y+row[i]]=1;
        bool s2 = IsEqual(lvl.matrix,x+col[i],1+y+row[i],color);
         //tmp[x+col[i]][y+row[i]+1]=2;

        bool s3 = IsEqual(lvl.matrix,x+col[i]-1,y+row[i],color);
        //tmp[x+col[i]-1][y+row[i]]=3;

        bool s4 = IsEqual(lvl.matrix,x+col[i],y+row[i]-1,color);
        // tmp[x+col[i]][y+row[i]-1]=4;


        if(s1){
          //for debugging purposes only to be removed later
          std::cout << "problem with the sides\n";
          //for debugging purposes only to be removed later
          side=0;
        }
        if(s2){
          //for debugging purposes only to be removed later
          std::cout << "problem with the sides\n";
          //for debugging purposes only to be removed later
          side=0;
        }
        if(s3){
          //for debugging purposes only to be removed later
          std::cout << "problem with the sides\n";
          //for debugging purposes only to be removed later
          side=0;
        }
        if(s4){
          //for debugging purposes only to be removed later
          std::cout << "problem with the sides\n";
          //for debugging purposes only to be removed later
          side=0;
        }

      bool  c1 = IsEqual(lvl.matrix,1+x+col[i],1+y+row[i],color);
      bool  c2 = IsEqual(lvl.matrix,x+col[i]-1,1+y+row[i],color);
      bool  c3 = IsEqual(lvl.matrix,x+col[i]+1,y+row[i]-1,color);
      bool  c4 = IsEqual(lvl.matrix,x+col[i]-1,y+row[i]-1,color);

        if(c1||c2||c3||c4){
          std::cout << "corners are ok \n";
          corner[i] =1;
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

  //**************************************************************

  Board DoMove(tile check,Board lvl,int x,int y,int size,int color){
    //check if a tile placement location is empty (0)
    //return true or false depending on the condition
    int n = 0;
    int col[size];
    int row[size];
    for(int i=0 ; i<5 ; i++){
      for(int j=0; j<5;j++){
        if(check.matrix[i][j]!=0){
          col[n]=i-2;
          row[n]=j-2;
          n++;
        }
      }
    }
      for(int i=0;i<size;i++){
        lvl.matrix[x+col[i]][y+row[i]]=color;
    }
    print_matrix(lvl.matrix);

    return lvl;
  }

  //**************************************************************

int main(){
  int p1[] =
    {
      0,0,0,0,0,
      0,0,1,0,0,
      0,0,1,1,0,
      0,0,0,1,0,
      0,0,0,0,0,
    };
  int level[] =
     { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3,
       1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       4, 0, 0, 0, 0, 0, 0, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       5, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 7,
       8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       9, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       2, 0, 0, 0, 3, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       3, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       4, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       5, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
       3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
};
  Board mat = boardToMatrix(level);
  tile tmo = tileToMatrix(p1);

 if(IsValid(tmo,mat,15,12,5,1)){
 mat=DoMove(tmo,mat,15,12,5,1);
 }


return 0;
}
