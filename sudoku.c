/*
 * CSC A48 - Exercise 11 - Sudoku Solver
 * 
 * Your goal in this exercise is to practice recursion and
 * to see how a properly written recursive solution can
 * take care of fairly complicated tasks with a few lines
 * of (well thought out) code.
 * 
 * We will be solving Sudoku puzzles. In case you have never
 * solved or seen a Sudoku, you can learn more about them
 * here:
 * 
 * https://en.wikipedia.org/wiki/Sudoku
 * 
 * Your task if to write a function that takes an input
 * Sudoku in the form of a 9x9 array of integers. the
 * array will have a few entries filled with numbers in
 * [1, 9], and the remaining entries set to zero.
 * 
 * For the example in the wiki, the input array will
 * be
 * 
 * 5 3 0 0 7 0 0 0 0
 * 6 0 0 1 9 5 0 0 0
 * 0 9 8 0 0 0 0 6 0
 * 8 0 0 0 6 0 0 0 3
 * 4 0 0 8 0 3 0 0 1
 * 7 0 0 0 2 0 0 0 6
 * 0 6 0 0 0 0 2 8 0 
 * 0 0 0 4 1 9 0 0 5
 * 0 0 0 0 8 0 0 7 9
 * 
 * Your code should find the values that correctly
 * complete the Sudoku. 
 * 
 * As a brief reminder, a correctly solved Sudoku is
 * one in which there are no repeated digits in any
 * row, any column, or any of the 3x3 sub-arrays that
 * make up the large 9x9 grid. Another way to think
 * about it is, every row, column, and 3x3 subgrid
 * uses all of the different digits.
 * 
 * How to solve this?
 * 
 * * RECURSIVELY!
 * 
 * (hint) - Solving a Sudoku with N unknown values
 * may involve trying something, then solving an
 * easier Sudoku problem.
 * 
 * * How to approach this?
 * 
 * - As noted in class:
 * 	a) Determine the base case(s)
 * 	b) Figure out the recursive case
 * 	c) Determine what needs to happen to
 * 	   the solution for the entire problem
 * 	   is returned once the recursion hits
 * 	   the base case(s)
 * 
 * - Conditions on the input Sudoku
 * 	- It will have AT LEAST ONE DIGIT in each
 * 	  3x3 subgrid. Likely there will be several
 * 	  3x3 subgrids with several digits already
 * 	  set to some value.
 * 
 * - Conditions on your solution
 * 	- It should return a solution if there
 * 	  exists one.
 * 	- If no solution can be found, return the
 * 	  original input array
 * 	- If multiple solutions exist, any one of
 *        them is valid
 * 
 * - Can I use helper functions?
 * 	- Yes, by all means!
 * 
 * - Can I add extra libraries?
 * 	- No, they won't be needed.
 * 
 * - Can I change the 'print_sudoku()' function?
 * 	- Please don't, we may need it for testing!
 * 
 * (c) F. Estrada, March 2019
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print_sudoku(int sudoku[9][9])
{
  printf("The Sudoku contains:\n");
  for (int j=0; j<9; j++)
  {
    for (int i=0; i<9;i++)
    {
      printf("%d  ",sudoku[j][i]);
    }
    printf("\n");
  }
}

int check_sudoku(int sudoku[9][9])
{
  /*
   *  This function checks whether a Sudoku is properly
   * solved. That means that each row, column, and
   * 3x3 subgrid uses each digit only once.
   * 
   *  If *ignores* zeros, so you can use it to check
   * that a partial solution is valid
   */
  
  /*****
   * TO DO:
   * Complete this function
   *   -- BUT ONLY IF YOU WANT TO!
   * Our testing script only checks your Sudoku
   * solution, if you want to solve it without
   * using this function, or if you want to write
   * your own helper functions, that's ok!
   * *****/

  int row_counts=0;
  int col_counts=0;
  int sub_counts=0;
  for (int i=1; i<10; i++) {
    // Check rows and columns
    for (int row=0;row<9;row++) {
      for (int col=0;col<9;col++) {
        if (sudoku[row][col] == i) {
          row_counts++;
        }
        if (sudoku[col][row] == i) {
          col_counts++;
        }
      }
      if ((row_counts > 1) || (col_counts > 1)) {
        return 0;
      }
      row_counts=0;
      col_counts=0;
    }

    // Check all 3x3 subgrids
    for (int sub_row=0; sub_row<3; sub_row++) {
      for (int sub_col=0; sub_col<3; sub_col++) {
        for (int row_delta=0; row_delta<3; row_delta++) {
          for (int col_delta=0; col_delta<3; col_delta++) {
            if (sudoku[sub_row*3 + row_delta][sub_col*3 + col_delta] == i) {
              sub_counts++;
            }
          }
        }
        if (sub_counts > 1) {
          return 0;
        }
        sub_counts=0;
      }
    }
  }
  return 1;
}

int solved(int sudoku[9][9])
{
  /*
   * This function checks whether a given Sudoku is
   * completely solved (it has no zeros, all digits
   * are used once per row, column, and sub-grid.
   * It returns 1 if the Sudoku is solved, zero
   * otherwise
   */
  
  /*****
   * TO DO
   * Complete this function
   * BUT ONLY IF YOU WANT TO!
   *   You can solve the Sudoku without using this function,
   * or you can write a different helper function, whatever
   * makes more sense to yoU! our checker won't look at this
   * function, 
   * ****/
  for (int row=0; row<9; row++) {
    for (int col=0; col<9; col++) {
      if (sudoku[row][col] == 0) {
        return 0;
      }
    }
  }
  return check_sudoku(sudoku);
}

void init_poss(int sudoku[9][9], int poss[9][9][9]) {
  for (int row=0; row<9; row++) {
    for (int col=0; col<9; col++) {
      if (sudoku[row][col] == 0){
        for (int i=0; i<9; i++) {
          poss[row][col][i] = 1;
        }
      }
    }
  }
}

int set_to_zero(int pos[9][9][9], int n, int row, int col, int chng) {
  if (pos[row][col][n] == 1) {
      // printf("(%d, %d, %d) is 1\n", row, col, n);
      pos[row][col][n] = 0;
      chng++;
      // printf("chng is : %d\n", chng);
  }
  return chng;
}

int clear_common(int pos[9][9][9], int n, int nrow, int ncol, int chng) {
  for (int rowcol=0; rowcol<9; rowcol++) {
    chng = set_to_zero(pos, n, nrow, rowcol, chng);
    chng = set_to_zero(pos, n, rowcol, ncol, chng);
  }

  // Find coordinate of top right of subgrid n lies in.
  int subgridr = nrow-(nrow % 3);
  int subgridc = ncol-(ncol % 3);

  for (int row_delta=0; row_delta<3; row_delta++) {
    for (int col_delta=0; col_delta<3; col_delta++) {
      chng = set_to_zero(pos, n, subgridr+row_delta, subgridc+col_delta, chng);
    }
  }
  return chng;
}

int clear_impos(int sudoku[9][9], int pos[9][9][9]) {
  if (check_sudoku(sudoku) == 0) {
    return 0;
  }
  int chng=0;
  for (int row=0; row<9; row++) {
    for (int col=0; col<9; col++) {
      if (sudoku[row][col] != 0) {
        // printf("(%d, %d) is not zero\n", row, col);
        chng = clear_common(pos, sudoku[row][col]-1, row, col, chng);
      }
    }
  }
  return (chng != 0);
}

int only_one_num(int pos[9][9][9], int row, int col) {
  int one_count=0;
  int one_index;
  for (int i=0; i<9; i++) {
    if (pos[row][col][i] == 1) {
      one_count++;
      one_index = i;
    }
  }
  if (one_count == 1) {
    return one_index+1;
  }
  return -1;
}

void set_all_single_options(int sudoku[9][9], int pos[9][9][9])
{
  for (int row=0; row<9; row++) {
    for (int col=0; col<9; col++) {
      if ((sudoku[row][col] == 0) && (only_one_num(pos, row, col) != -1)) {
        printf("(%d, %d) set to %d\n", row, col, only_one_num(pos, row, col));
        sudoku[row][col] = only_one_num(pos, row, col);
      }
    }
  }
}

void sift_pos(int sudoku[9][9], int pos[9][9][9])
{
  if (solved(sudoku)) {
    printf("Solved!\n");
    return;
  }
  if (clear_impos(sudoku, pos) == 0) {
    return;
  }
  printf("%s\n", "Hello there.");
  set_all_single_options(sudoku, pos);
  for (int i=0; i<9; i++) {
    printf("%d", pos[0][0][i]);
  }
  printf("\n");
  sift_pos(sudoku, pos);
}

void solve_sudoku(int sudoku[9][9], int depth)
{
  /*
   * This function solves an input Sudoku, the
   * input has a value of 0 for any entries that
   * are not yet decided. If no solution exists
   * the function returns the input array *exactly
   * as it was* when the function was called.
   * 
   * The 'depth' parameter is provided in case you
   * want to use it to help debug and trace your
   * code. You do not need to use it if you don't
   * want to, and the problem can be solved without
   * using the depth value at all. 
   * 
   * The automated checker won't look at the depth
   * either.
   */
  
  /*****
   * TO DO:
   * Complete this function
   *****/  

  int pos[9][9][9];
  init_poss(sudoku, pos);

  sift_pos(sudoku, pos);  
}

#ifndef __testing

int main()
{
   // We'll provide you with the same test case
   // from the Wiki, so you can check your output.
   // But as always, be aware we will test your
   // solution on different Sudoku puzzles.
  
   int Sudoku[9][9]={
         {5, 3, 0, 0, 7, 0, 0, 0, 0},
		     {6, 0, 0, 1, 9, 5, 0, 0, 0},
		     {0, 9, 8, 0, 0, 0, 0, 6, 0},
		     {8, 0, 0, 0, 6, 0, 0, 0, 3},
		     {4, 0, 0, 8, 0, 3, 0, 0, 1},
		     {7, 0, 0, 0, 2, 0, 0, 0, 6},
		     {0, 6, 0, 0, 0, 0, 2, 8, 0},
		     {0, 0, 0, 4, 1, 9, 0, 0, 5},
		     {0, 0, 0, 0, 8, 0, 0, 7, 9}};

   int Sudoku2[9][9]={
         {5, 3, 4, 6, 7, 8, 9, 1, 2},
         {6, 7, 2, 1, 9, 5, 3, 4, 8},
         {1, 9, 8, 3, 4, 2, 5, 6, 7},
         {8, 5, 9, 7, 6, 1, 4, 2, 3},
         {4, 2, 6, 8, 5, 3, 7, 9, 1},
         {7, 1, 3, 9, 2, 4, 8, 5, 6},
         {9, 6, 1, 5, 3, 7, 2, 8, 4},
         {2, 8, 7, 4, 1, 9, 6, 3, 5},
         {3, 4, 5, 2, 8, 6, 1, 7, 9}};


  printf("Input puzzle is:\n");
  print_sudoku(Sudoku);
  
  solve_sudoku(Sudoku,0);
  
  printf("Solution is:\n");
  print_sudoku(Sudoku);
  
}

#endif