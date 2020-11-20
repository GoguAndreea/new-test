#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

struct Obiect
{
  int x;
  int y;
};

enum Directii
{
  STOP,
  LEFT,
  RIGHT,
  DOWN,
  UP,
};

   bool GameOver;//ne va spune daca jocul s-a teminat saunu, daca caracterul a murit
   int height;
   int width;
   Obiect snake;//jucatorul
   Obiect tail[200];
   Obiect point;//punctul dupa care merge sarpele
   Directii dir;
   int scor = 0;
   int ntail=0;
   void Setup(){//functie responsabila pentru tot ce se intampla inainte de a intra in jocȘ construirea jucatorilor etc
       GameOver = false;
       height = 15;
       width = 30;
       snake.x = 5;
       snake.y = 5;
       point.x = rand() % width;
       point.y = rand() % height;
       dir = STOP;
   }

   void Draw(){//responsabila pentru ce se intampla pe partea vizuala: desenam caracterele, actualizam pozitia pe fiecare frame
      system("cls"); //system("clear");
       //desenez arena
       for (int i = 0; i < width; i++) cout << "#"; //partea de deasupra a arenei
       cout <<"\n";
       for (int i = 0; i < height; i++)
       {
          for (int j = 0; j < width; j++)
          {
              if (j==0 || j== width - 1) cout <<"#";
              else
                if(i == snake.y && j == snake.x) cout << "o";
                else
                if(i == point.y && j == point.x)cout <<"*";
              else
              {

              bool ecoada = false;
              for(int k = 0; k < ntail; k++)
              {
                  if(tail[k].x == j && tail[k].y == i){ecoada = true; break;};
              }
              if(!ecoada) cout <<" ";
              else cout <<"o";
              }
          }
          cout <<"\n";
       }
      for (int i = 0; i < width; i++) cout << "#"; //partea de jos a arenei
   cout <<"\n";
   cout <<"Scor :" << scor;

   }

   void Input(){//preia tastele apasate de jucator
     if(_kbhit)
        {
            switch(_getch())//returneaza valoarea tastei apasate
        {
        case 'a' : dir = LEFT; break;
        case 's': dir = DOWN; break;
        case 'd': dir = RIGHT; break;
        case 'w': dir = UP; break;
        }
        }

   }

   void Logic(){//se ocupa de toate lucrurile logice petrecute in joc. Dacae apasata tasta w, in functie Logic vom face toate actiunile logice necesare stiind ca am apasat tasta w

switch (dir)
{
case LEFT:snake.x--;
    break;
case RIGHT:snake.x++;
    break;
case DOWN:snake.y++;
    break;
case UP:snake.y--;
    break;
}
int xprev, yprev;
xprev = snake.x;
yprev = snake.y;
int xprev2, yprev2;
for (int i = 0; i<= ntail; i++)
{
   xprev2 = tail[i].x;
   yprev2 = tail[i].y;
   tail[i].x = xprev;
   tail[i].y = yprev;
   xprev = xprev2;
   yprev = yprev2;
}
if(snake.x == point.x && snake.y == point.y)
{
    scor++;
    ntail++;
    point.x = rand() % width;
    point.y = rand() % height;
}
if(snake.x == 0) GameOver = true;
if(snake.x == width) GameOver = true;
if(snake.y == 0) GameOver = true;
if(snake.y == height) GameOver = true;
for(int i = 1; i <= ntail; i++)
{
    if (snake.x == tail[i].x && snake.y == tail[i].y){GameOver = true; break;}
}
   }

   int main()
{
    Setup();//ne asiguram ca toate sunt optime pentru a incepe jocul
    while(!GameOver)//cat timp jocul ruleaza
    {
        Input();
        Logic();
        Draw();
        Sleep(40);//blocheaza codul nostru pentru un anumit numar de milisecunde
    }
    return 0;
}
