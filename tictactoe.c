#include <stdio.h>
#include <stdlib.h>

// Macros
#define PLAYER_ONE 'X'
#define PLAYER_TWO 'O'
#define NO_WINNER 'N'

#define PLAYGROUND_SIZE 3

#define INVALID_CELL 0XFF
#define BUSY_CELL 0XFE


// Prototypes

void render_board(void);
int get_input(void);
char judge(void);


// Global Variables
char playground[3][3] = {{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}};

int main(void){
    int empty_cells = 9;
    char current_player = PLAYER_ONE;
    char winner;
    int input;
    int error_mssg;

    while(empty_cells != 0 ){
        winner = judge();
        render_board();
        if(error_mssg == INVALID_CELL){
            printf("\nThe selected cell is out of boundary, Please try another vaild cell\n");
        }else if(error_mssg == BUSY_CELL){
            printf("\nThe selected cell is aleardy selected before, Please try another vaild cell\n");
        }

        if(winner != NO_WINNER){
            printf("\n%c player wins!\n\n", winner);
            return 0;
        }
        error_mssg = 0;
        input = get_input();
        if(input == INVALID_CELL || input == BUSY_CELL){
            error_mssg = input;
        }
        else{
            playground[input/10 - 1][input%10 -1] = current_player;
            current_player = (current_player == PLAYER_ONE? PLAYER_TWO:PLAYER_ONE);
            empty_cells--;
        }
    }

}


void render_board(void){
    system("cls");
    printf("\n");
    //printf(" --  --  -- \n");
    printf("-------------\n");
    for(int i =0; i < 3; i++){
        printf("| %c | %c | %c |\n",playground[i][0],playground[i][1],playground[i][2]);
        //printf(" --  --  -- \n");
        printf("-------------\n");
    }


}

int get_input(void){
    int input;
    scanf("%d",&input);

    switch (input)
    {
    case 11:
    case 12:
    case 13:
    case 21:
    case 22:
    case 23:
    case 31:
    case 32:
    case 33:
        if(playground[input/10 - 1][input%10 - 1] != ' '){
            return BUSY_CELL;
        }
        break;
    default:
        return INVALID_CELL;
        break;
    }

    return input;
}



char judge(void){
    char winner = NO_WINNER;

    // Diagonals check
    if(playground[0][0] == playground[1][1] && playground[1][1] == playground[2][2]){
        if(playground[0][0] != ' '){
            return playground[0][0];
        }
    }

    if(playground[0][2] == playground[1][1] && playground[1][1] == playground[2][0]){
        if(playground[0][2] != ' '){
            return playground[0][2];
        }
    }

    // Horizontal and Vertical check
    for(int i = 0; i < 3; i++){
        // Horizonal check
        if(playground[i][0] == playground[i][1] && playground[i][1] == playground[i][2]){
            if(playground[i][0] != ' '){
                return playground[i][0];
            } 
        }

        // Vertical check
        if(playground[0][i] == playground[1][i] && playground[1][i] == playground[2][i]){
            if(playground[0][i] != ' '){
                return playground[0][i];
            } 
        }
    }

    return NO_WINNER;
}