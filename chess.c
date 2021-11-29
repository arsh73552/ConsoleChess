#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void setup(char *board[8][8]);
void display(char *board[8][8]);
bool make_move(char *board[8][8]);
bool game_over(char *board[8][8]);
bool check_if_move(char *piece,int initial_x_coordinates, int initial_y_coordinates, int final_x_coordinates, int final_y_coordinates,char *board[8][8]);
bool piece_block(char *piece,int initial_x_coordinates, int initial_y_coordinates, int final_x_coordinates, int final_y_coordinates,char *board[8][8]);

int counter=0;

int main()
{
  char *board[8][8];
  int warning=0;
  setup(board);
  while(true)
  {
    display(board); // Display the board
    if(!make_move(board)) // Check if Move is possible.
    {
      if(warning==0 || warning==1) // If more than 2 Illegal moves are made, End game.
      {
        printf("Invalid move\nWarning %d\n", warning+1);
        warning++;
        continue;
      }
      printf("Invalid move!");
      return 0;
    }
    if(game_over(board)) // Check if Kings are still on the board, if so continue else end game.
    {
      printf("Game over!\n");
      display(board);
      return 0;
    }
  }
}

void setup(char *board[8][8])
{
  for(int i=0;i<8;i++) // Prints gaps where no pieces are placed.
  {
    for(int j=0;j<8;j++)
    {
      board[i][j]="     ";
    }
  }
  // Format: Piece_Abreviation(Piece_Color)
  board[0][0]="Ro(w)"; // Rooks(White)
  board[0][1]="Kn(w)"; // Knights(White)
  board[0][2]="Bi(w)"; // Bishop(White)
  board[0][3]="Qu(w)"; // Queen(White)
  board[0][4]="Ki(w)"; // Kings(White)
  board[0][5]="Bi(w)";
  board[0][6]="Kn(w)";
  board[0][7]="Ro(w)";

  board[7][0]="Ro(b)"; // Rooks(Black)
  board[7][1]="Kn(b)"; // Knights(Black)
  board[7][2]="Bi(b)"; // Bishop(Black)
  board[7][3]="Qu(b)"; // Queen(Black)
  board[7][4]="Ki(b)"; // Kings(Black)
  board[7][5]="Bi(b)";
  board[7][6]="Kn(b)";
  board[7][7]="Ro(b)";


  for(int i=0;i<8;i++) //Names all pawns
  {
    board[1][i]="Pa(w)";
    board[6][i]="Pa(b)";
  }
}
void display(char *board[8][8])
{
  printf("--------------------------------------------------\n");
  printf(" |  a  |  b  |  c  |  d  |  e  |  f  |  g  |  h  |\n");
  for(int i=0;i<8;i++)  //2x for loop printing the board with aesthetic changes.
  {
    printf("  ________________________________________________\n%d|", i+1);
    for (int j=0;j<8;j++)
    {
      printf("%s|", board[i][j]);
    }
    printf("\n");
  }
  printf("--------------------------------------------------\n");
  printf("\n\n");
}
bool game_over(char *board[8][8])
{
  int temp=0;
  for(int i=0;i<8;i++) //Searching board for White king.
  {
    for(int j=0;j<8;j++)
    {
      if(!strcmp(board[i][j],"Ki(w)"))
      {
        temp++;
      }
    }
  }
  if(temp==0)
  {
    printf("Black is victorious!"); // If king not found.
    return true;
  }
  else
  {
    temp=0;
  }
  for(int i=0;i<8;i++) //Searching board for Black king.
  {
    for(int j=0;j<8;j++)
    {
      if(!strcmp(board[i][j],"Ki(b)"))
      {
        temp++;
      }
    }
  }
  if(temp==0)
  {
    printf("White is victorious!\n"); //If king not found.
    return true;
  }
  return false;
}
bool make_move(char *board[8][8])
{
  int initial_x_coordinates,initial_y_coordinates,final_x_coordinates,final_y_coordinates;
  char a[6];
  char piece[2];
  scanf("%s", a);

  initial_x_coordinates=(int)a[2]-97; //obtaining initial x coordinates
  initial_y_coordinates=(int)a[3]-49; //obtaining initial y coordinates
  final_x_coordinates=(int)a[4]-97; //obtaining final x coordinates
  final_y_coordinates=(int)a[5]-49; //obtaining final y coordinates

  if(final_x_coordinates>7 || final_x_coordinates<0 || final_y_coordinates>7 || final_y_coordinates<0 || initial_x_coordinates>7 || initial_x_coordinates<0 || initial_y_coordinates>7 || initial_y_coordinates<0)
  {
    return false; // Make sure move isn't out of bounds.
  }

  for(int i=0;i<2;i++) //Copying input piece name.
  {
    piece[i]=a[i];
  }
  piece[2]='\0';
  if(check_if_move(piece,initial_x_coordinates,initial_y_coordinates,final_x_coordinates,final_y_coordinates,board)) // If move's legitimate then place the piece on its new position.
  {
    board[final_y_coordinates][final_x_coordinates]=board[initial_y_coordinates][initial_x_coordinates];
    board[initial_y_coordinates][initial_x_coordinates]="     ";
    return true;
  }
  else
  {
    return false;
  }
}
bool check_if_move(char *piece,int initial_x_coordinates, int initial_y_coordinates, int final_x_coordinates, int final_y_coordinates,char *board[8][8])
{
  if(counter%2==0) // Pick your own pieces.
  {
    if(board[initial_y_coordinates][initial_x_coordinates][3]!='w')
    {
      return false;
    }
    if(board[final_y_coordinates][final_x_coordinates][3]=='w')
    {
      return false;
    }
  }
  else       //Ensures that the players picks up his piece and doesn't self-capture.
  {
    if(board[initial_y_coordinates][initial_x_coordinates][3]!='b')
    {
      return false;
    }
    if(board[final_y_coordinates][final_x_coordinates][3]=='b')
    {
      return false;
    }
  }
  char temp[2];
  for(int i=0;i<2;i++)            // Just Ensuring
  {
    temp[i]=board[initial_y_coordinates][initial_x_coordinates][i];
  }
  temp[2]='\0';                   // Input piece
  if(strcasecmp(temp,piece))      // name is correct.
  {
    return false;
  }

  if(!piece_block(piece,initial_x_coordinates,initial_y_coordinates,final_x_coordinates,final_y_coordinates,board))
  {
    if (!strcasecmp(piece,"Pa")) // Pawn implementation
    {
      if(final_x_coordinates!=initial_x_coordinates)
      {
        if(initial_x_coordinates+1!=final_x_coordinates && initial_x_coordinates-1!=final_x_coordinates)
        {
          return false;
        }
        if(initial_y_coordinates+1 -2*(counter%2)==final_y_coordinates)
        {
          if(strcmp(board[final_y_coordinates][final_x_coordinates],"     ")==0)
          {
            return false;
          }
          else
          {
            counter++;
            return true;
          }
        }
        return false;
      }
      if(counter%2==0)
      {
       if(initial_y_coordinates+1 != final_y_coordinates)
        {
          if(initial_y_coordinates=1 && initial_y_coordinates+2==final_y_coordinates)
          {
              counter++;
              return true;
          }
          return false;
        }
        else
        {
          counter++;
          return true;
        }
      }
       else
        {
          if(initial_y_coordinates -1 != final_y_coordinates)
          {
            if(initial_y_coordinates=6 && initial_y_coordinates-2==final_y_coordinates)
            {
                counter++;
                return true;
            }
            return false;
          }
          else
          {
            counter++;
            return true;
          }
       }
    }
    if (!strcasecmp(piece,"Ro")) // Rook implementation
    {
      if(initial_x_coordinates==final_x_coordinates)
        {
          counter++;
          return true;
        }
      else if(final_y_coordinates==initial_y_coordinates)
        {
          counter++;
          return true;
        }
      else
        return false;
    }
    if (!strcasecmp(piece,"Bi")) // Bishop implementation
    {
      for(int i=1;i<8;i++)
      {
        if(initial_x_coordinates+i==final_x_coordinates || initial_x_coordinates-i==final_x_coordinates)
        {
          if(initial_y_coordinates+i==final_y_coordinates || initial_y_coordinates-i==final_y_coordinates)
          {
            counter++;
            return true;
          }
        }
      }
      return false;
    }
    if (!strcasecmp(piece,"Ki")) // King implementation
    {
      int tempx = (final_x_coordinates-initial_x_coordinates);
      int tempy = (final_y_coordinates-initial_y_coordinates);
      int move_length = floor(sqrt(tempx*tempx + tempy*tempy));
      if (move_length==1)
      {
        counter++;
        return true;
      }
      else
      {
        return false;
      }
    }
    if (!strcasecmp(piece,"Qu")) // Queen implementation
    {
      for(int i=1;i<8;i++)
      {
        if(initial_x_coordinates+i==final_x_coordinates || initial_x_coordinates-i==final_x_coordinates)
        {
          if(initial_y_coordinates+i==final_y_coordinates || initial_y_coordinates-i==final_y_coordinates)
          {
            counter++;
            return true;
          }
        }
      }
      if(initial_x_coordinates==final_x_coordinates)
        {
          counter++;
          return true;
        }
      else if(final_y_coordinates==initial_y_coordinates)
        {
          counter++;
          return true;
        }
      else
        return false;
    }
    if (!strcasecmp(piece,"Kn")) // Knight implementation
    {
      if(final_x_coordinates==initial_x_coordinates+2 || final_x_coordinates==initial_x_coordinates-2)
      {
        if(initial_y_coordinates+1==final_y_coordinates || initial_y_coordinates-1==final_y_coordinates)
        {
          counter++;
          return true;
        }
      }
      if(final_y_coordinates==initial_y_coordinates+2 || final_y_coordinates==initial_y_coordinates-2)
      {
        if(initial_x_coordinates+1==final_x_coordinates || initial_x_coordinates-1==final_x_coordinates)
        {
          counter++;
          return true;
        }
      }
      return false;
    }
  }
  else
  {
    return false;
  }
  counter++;
  return true;
}
bool piece_block(char *piece,int initial_x_coordinates, int initial_y_coordinates, int final_x_coordinates, int final_y_coordinates,char *board[8][8])
{
  if(!strcasecmp(piece,"Pa")) // Pawn movement block
  {
    if(initial_x_coordinates==final_x_coordinates)
    {
      if(strcmp(board[final_y_coordinates][final_x_coordinates],"     ")!=0)
      {
        return true; // Ensure that pawn is moving to an empty square if walking forward.
      }
      if(abs(final_y_coordinates-initial_y_coordinates)==2)
      {
        if(strcmp(board[final_y_coordinates-1+2*(counter%2)][final_x_coordinates],"     ")!=0) // Ensure that pawn isn't walking over pieces in case of a first 2-step move.
        {
          return true;
        }
      }
    }
    return false;
  }
  if(!strcasecmp(piece,"Ro")) // Rook movement block
  {
    here:
    if(final_x_coordinates==initial_x_coordinates)
    {
      for(int i=initial_y_coordinates+1;i<final_y_coordinates;i++)
      {
        if(strcmp(board[i][initial_x_coordinates],"     "))
        {
          return true; // check all squares from initial square to final square in a straight line to ensure that the piece isn't being blocked.
        }
      }
    }
    else if(final_y_coordinates==initial_y_coordinates)
    {
      for(int i=initial_x_coordinates+1;i<final_x_coordinates;i++)
      {
        if(strcmp(board[initial_y_coordinates][i],"     "))
        {
          return true; // check all squares from initial square to final square in a straight line to ensure that the piece isn't being blocked.
        }
      }
    }
    else
    {
      return true;
    }
    return false;
  }
  if(!strcasecmp(piece,"Bi")) // Bishop movement block
  {
    there: ;
    int InitialTempX = initial_x_coordinates;
    int InitialTempY = initial_y_coordinates;
    int ChangeinX = 1;
    int ChangeinY = 1;
    if(final_x_coordinates < initial_x_coordinates)
      ChangeinX = -1;
    if(final_y_coordinates < initial_y_coordinates)
      ChangeinY = -1;
    InitialTempX = InitialTempX + ChangeinX;
    InitialTempY = InitialTempY + ChangeinY;
    while(InitialTempX != final_x_coordinates)
    {
      if(strcmp(board[InitialTempY][InitialTempX],"     "))
        return true;
      InitialTempX = InitialTempX + ChangeinX;
      InitialTempY = InitialTempY + ChangeinY;
    }
    return false;
  }
  if(!strcasecmp(piece,"Ki")) // King movement block
  {
    return false;
  }
  if(!strcasecmp(piece,"Qu")) // Queen movement block
  {
    if(final_x_coordinates == initial_x_coordinates || final_y_coordinates == initial_y_coordinates) // If X coordinates/Y Coordinates dont change check rook implementation
    {
      goto here;
    }
    else
    {
      goto there; // IF Y coordinates/ X coordinates do change check Bishop Implementation.
    }
  }
  if(!strcasecmp(piece,"Kn")) // Knight movement block
  {
    return false; // Knights can jump over pieces.
  }
  return false;
}
