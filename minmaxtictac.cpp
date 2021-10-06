#include <iostream>
using namespace std;


class moves
{   public:
    int row, col, score;
};
class game
{  
    public:
    char player, computer, grid[3][3];
    game()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                grid[i][j] = ' ';
            }
        }
    }

    void player_move()
    {
        while (true)
        {
            cout << "Enter an empty cell (1-9)";
            int cell;
            cin >> cell;
            int r = (cell - 1) / 3;
            int c = (cell - 1) % 3;

            if (cell >= 1 && cell <= 9 && grid[r][c] == ' ')
            {
                grid[r][c] = player;
                break;
            }
        }
    }

    bool win()
    {
        

        for (int i = 0; i < 3; i++)
        {
            if (grid[i][0] == grid[i][1] &&
                grid[i][1] == grid[i][2] &&
                grid[i][0] != ' ')
                return (true);

           
        }
         for (int i = 0; i < 3; i++)
            {
                if (grid[0][i] == grid[1][i] &&
                    grid[1][i] == grid[2][i] &&
                    grid[0][i] != ' ')
                    return (true);
            }
         if (grid[0][0] == grid[1][1] &&
        grid[1][1] == grid[2][2] && 
        grid[0][0] != ' ')
        return(true);
          
    if (grid[0][2] == grid[1][1] &&
        grid[1][1] == grid[2][0] &&
         grid[0][2] != ' ')
        return(true);
    return false;
    }

    bool tie()
    {
        if (win())
            return false;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }
    void play()
    {   
        cout<<"PLY: "<<endl;
        int ply;
        cin>>ply;
        while (true)
        {
            cout << "Which symbol (X or O, X will play first)? ";
            cin >> player;
            if (player == 'X' || player == 'O') //if correct choice is entered
            {
                break;
            }
        }
        if(player=='X')
        {
            computer= 'O';
        }
        else
        {
            computer='X';
        }
      
        if (player == 'O')
        {
            computer_move(ply);
        }
        print();
        while (true)
        {
            player_move();
            print();
            if (win())
            {
                cout << "You  won!\n";
                return;
            }
            else if (tie())
            {
                cout << "Tie!\n";
                return;
            }
            cout << "Computer is making a move.\n";
            computer_move(ply);
            print();
            if (win())
            {
                cout << "Computer wins!\n";
                return;
            }
            else if (tie())
            {
                cout << "Tie!\n";
                return;
            }
        }
    }
    void print()
    {
        cout << '\n';
        for (int i = 0; i < 3; i++)
        {
            if (i)
            {
                cout << "-----------\n";
            }
            for (int j = 0; j < 3; j++)
            {
                if (j)
                {
                    std::cout << "|";
                }
                cout << ' ';
                if (grid[i][j] == ' ')
                {

                    cout << " ";
                }
                else
                {
                    cout << grid[i][j];
                }
                cout << ' ';
            }
            cout << endl;
        }
        cout << '\n';
    }

    moves minimax(bool maximizing_player,int ply)
    {
        moves best_move;
        if(ply==0)
        {
            return best_move;
        }
        if (win())
        {
            if (maximizing_player) //  player won so computer lost so return -1
            {

                best_move.score = -1;
            }
            else
            {
                best_move.score = 1;
            }
            return best_move;
        }
        else if (tie())
        {
            best_move.score = 0;
            return best_move;
        }

        
        if(maximizing_player)
        {
            best_move.score = -2;
        }
        else
        {
            best_move.score  = 2;
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {  
                    if(maximizing_player)
                    {
                        grid[i][j] = computer;
                    }
                    else
                    {
                        grid[i][j] = player;
                    }
                    moves board_state = minimax(!maximizing_player,ply-1);
                    if (maximizing_player)
                    {
                        if (board_state.score > best_move.score)
                        {
                            best_move.score = board_state.score;
                            best_move.row = i;
                            best_move.col = j;
                        }
                    }
                    else
                    {
                        if (board_state.score < best_move.score)
                        {
                            best_move.score = board_state.score;
                            best_move.row = i;
                            best_move.col = j;
                        }
                    }
                    grid[i][j] = ' ';
                }
            }
        }
        return best_move;
    }
    void computer_move(int ply)
    {
        moves best_move = minimax(true,ply);
        cout << "Score:" << best_move.score << endl;
        cout << "Row :" << best_move.row << " ";
        cout << "Column:" << best_move.col << endl;
        grid[best_move.row][best_move.col] = computer;
    }
};

int main()
{    
    
     game tic;
    tic.play();
}
