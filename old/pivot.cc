#include <stdio.h>

int matrix[5][5] = {
     {11, 12, 13, 14, 15},
     {21, 22, 23, 24, 25},
     {31, 32, 33, 34, 35},
     {41, 42, 43, 44, 45},
     {51, 52, 53, 54, 55}
};

void print_matrix(int n)
{
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         printf(" %d ", matrix[i][j]);
      }
      printf("\n");
   }
}


int *get(int offset, int x, int y)
{
   return &matrix[offset + x][offset + y];
}

void transpose(int offset, int n)
{
   if (n > 1) {
      for (int i = 0; i < n - 1; i++) {
         int *val1 = get(offset, 0, i);
         int *val2 = get(offset, i, n - 1);
         int *val3 = get(offset, n - 1, n - 1 - i);
         int *val4 = get(offset, n - 1 - i, 0);

         int temp = *val1;
         *val1 = *val4;
         *val4 = *val3;
         *val3 = *val2;
         *val2 = temp;
      }

      transpose(offset + 1, n - 2);
   }
}

int main()
{
   print_matrix(5);
   transpose(0, 5);
   print_matrix(5);
   return 0;
}
