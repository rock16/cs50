/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int value = 0;
    int temp;
    
    // fills board with values from 1 up to d-1.
    for (int row = (d -1); row >= 0; row--)
    {
        for (int col = (d - 1); col >= 0; col--)
        {
            board[row][col] = value;
            value++;
        }
    }
    
    // swap the position of 2 and 1 for board with even size.
    if (d % 2 == 0)
    {
        temp = board[d-1][1];
        board[d-1][1] = board[d-1][2];
        board[d-1][2] = temp;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            
            // replace 0 with underscor for blank space.
            if (board[row][col] == 0)
            {
                printf("  _");
            }
            
            // prints board tiles
            else
            {
                printf("%3d", board[row][col]);
            }
        }
        printf("\n\n");
    }
}
/**
 * swaps empty tiles with tiles on it border
 */
void swap(int t_rw, int b_rw, int t_cl, int b_cl, int tile)
{
    board[t_rw][t_cl] = 0;
    board[b_rw][b_cl] = tile;
}


/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int b_rw = 0, b_cl = 0;
    int t_rw, t_cl;
    bool t_found = false, b_found = false;
    
    // find tile position.
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == 0)
            {
                b_rw = i;
                b_cl = j;
                b_found = true;
            }
            if (board[i][j] == tile)
            {
                t_rw = i;
                t_cl = j;
                t_found = true;
            }
            
            // stop loop if tile position found.
            if (t_found && b_found)
            break;
        }
        if (t_found && b_found)
        break;
    }
    // check if tile boarders empty tile.
    if (t_rw == b_rw)
    {
        if (abs(t_cl - b_cl) == 1)
        {
            swap(t_rw, b_rw, t_cl, b_cl, tile);
            return true;
        }
    }
    
    // check if tile on boarders empty tile
    else if (t_cl == b_cl)
    {
        if (abs(t_rw - b_rw) == 1)
        {
            swap(t_rw, b_rw, t_cl, b_cl, tile);
            return true;
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int firstTile = board[0][0], lastTile = board[d-1][d-2];
    
    // start loop only when first and last tile are in place.
    if ((firstTile == 1) && (lastTile == (d * d)-1))
    {
        bool colCorrect = false;
        int pre_value = board[0][0];
        
        // compare present tile and previous tile
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                // compare only non empty tile.
                if(board[i][j] > 0 && (j > 0 && i > 0))
                {
                    if ((board[i][j] - pre_value) == 1)
                    {
                        colCorrect = true;
                    }
                    else
                    {
                        colCorrect = false;
                    }
                }
                pre_value = board[i][j];
            }
        }
        if (colCorrect)
        {
            return true;
        }
    }
    return false;
}