#include<stdio.h>

//Outputting a row of two-dimensional array and adding format to the array
void row_output(int i, int x[9][9]){
    int j, flag;
    for(j = 0; j < 9; j++){
        //Check whether it is a multiple of 3
        flag = (j + 1) % 3;
        //If it is a multiple of 3, add two spaces
        if(flag == 0)
            printf("%d  ", x[i][j]);
        //Otherwise add one space
        else
            printf("%d ", x[i][j]);
    }
}

//000 000 000
//Outputting the array in the form of Sudoku
void output(int x[9][9]){
    int i, flag;
    for(i = 0; i < 9; i++){
        //Check whether it is a multiple of 3
        flag = (i + 1) % 3;
        row_output(i, x);
        //If it is a multiple of 3, add two spaces
        if(flag == 0)
            printf("\n\n");
        //Otherwise add one space
        else
            printf("\n");
    }
}

// 0 0 0
 
// 0 0 0
 
// 0 0 0
//checks whether x[i][j] is a feasible value
int validate(int x[9][9], int i, int j, int num){
    int row, column;
    int isPossible = 1;
    //Traverse line i to query whether there are duplicate values
    for(column = 0; column < 9; column++){
        if(num == x[i][column]) isPossible *= 0;
        else isPossible *= 1;
    }
    //Traverse column j to query whether there are duplicate values
    for(row = 0; row < 9; row++){
        if(num == x[row][j]) isPossible *= 0;
        else isPossible *= 1;
    }
    //Traverse the Palace(box) where x[i][i] is located to query whether there are duplicate values
    int box_i, box_j;
    //Locate the palace
    int offset_x, offset_y;
    //Calculate the offset in the x direction (i.e. the increasing direction of the j sequence number
    offset_x = j - j % 3;
    //Calculate the offset in the y direction (i.e. the increasing direction of i sequence number)
    offset_y = i - i % 3;
    //If the verification is correct, return 1, otherwise return 0
    for(box_i = 0; box_i < 3; box_i++){
        for(box_j = 0; box_j < 3; box_j++){
            //fix box_ i,box_j to the correct Sudoku
            if(num == x[box_i + offset_y][box_j + offset_x]) isPossible *= 0;
            else isPossible *= 1;
        }
    }
    return isPossible;
}
 
void solve_soduku(int x[9][9]){
    int i, j, num, flag = 0;
    //Create a new two-dimensional array to record the position of unchangeable numbers (that is, the numbers filled in at the beginning)
    int can_not_modify[9][9] = { 0 };
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(x[i][j] != 0) can_not_modify[i][j] = 1;
        }
    }
    //Initialize i and j
    i = 0;
    j = 0;
    //Traverse the nine palace grid and try from x[0][0]
    while(i < 9){
        while(j < 9){
        //Judge whether it is a trial and error jump from the previous line
        start:if(flag == 1 && j == -1){
            i--;
            j = 8;
            goto start;
        }
        //Judge whether it is a trial and error jump, and the current value cannot be modified
        else if(flag == 1 && can_not_modify[i][j] == 1){
            //Return to the previous level
            j--;
            continue;
        }
        //Judge whether the current grid cannot be modified
        else if(can_not_modify[i][j] == 1){
            j++;
            continue;
        }
        //Start trying
        else{
            num = x[i][j];
            //If the current grid has not been assigned, that is, it does not jump from the last trial and error, try from 1
            if(num == 0) num = 1;
            //If flag = = 1, it is from the last trial and error. Continue to try from the value of the last error + 1
            else if(flag == 1) num = x[i][j] + 1;
            //Initializes the value of the jump identifier
            flag = 0;
            //Start with num and use backtracking
            for(; num <= 10; num++){
                //Use the validate function to determine whether the attempted value is feasible
                //If possible, change the value of the current grid to num
                if(validate(x, i, j, num) == 1 && num < 10){
                    x[i][j] = num;
                    j++;
                    break;
                }
                //If no feasible value is filled in by 9, it indicates that there is an error in the front. The initial current value is 0, and the last attempt is returned
                else if(num == 10){
                    x[i][j] = 0;
                    j--;
                    //Mark jump flag = 1
                    flag = 1;
                    break;
                }
            }
        }
        }
        //One line is filled, and continue to try from the first on the next line
        j = 0;
        i++;
    }
}
 
int main(){
    int i, j;
    char temp;
    int soduku[9][9];
    printf("Sudoku Solver by Allen:\n2021/01/05\n\n");
    printf("Please type the Sudoku you want to solve:\n");
    printf("  123456789\n");
    for(i = 0; i < 9; i++){
        printf("%d:", i + 1);
        for(j = 0; j < 10; j++){
            temp = getchar();
            if(j < 9) 
                soduku[i][j] = temp - '0';
        }
    }
    printf("\nThe Sudoku you typed is:\n");
    output(soduku);
    solve_soduku(soduku);
    printf("The result is:\n");
    output(soduku);
    return 0;
}


// 003070000
// 010906230
// 050130006
// 060000180
// 901000504
// 082000070
// 700084050
// 048502060
// 000010800


// 6 9 3  2 7 5  4 1 8
// 8 1 7  9 4 6  2 3 5
// 2 5 4  1 3 8  7 9 6
 
// 4 6 5  7 2 9  1 8 3
// 9 7 1  8 6 3  5 2 4
// 3 8 2  4 5 1  6 7 9
 
// 7 2 6  3 8 4  9 5 1
// 1 4 8  5 9 2  3 6 7
// 5 3 9  6 1 7  8 4 2