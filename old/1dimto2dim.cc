#include <iostream>
#include <stdio.h>


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


Arrays toMatrix(int input[]){
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


Arrays toArray(Arrays input){
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

int main(){
  int level[25] =
     {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
       25};
  Arrays mat = toMatrix(level);
  mat = rotateclockWise(mat);
  mat = rotateclockWise(mat);
  mat = toArray(mat);
  for(int i=0 ; i<25;i++){
    level[i] = mat.array1d[i];
    std::cout << " "<< level[i]<<std::endl;
  }
return 0;
}
