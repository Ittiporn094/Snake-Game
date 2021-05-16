
#include <stdio.h>
#include <conio.h>  //for kbhit, getch()
#include <stdlib.h>  //for exit(0), system("cls")
#include <unistd.h>
#include <time.h>  //for clock(),clock_t

int i , j , k , height = 25 , width = 25;
int gameover , goal;
int x , y , fruitx , fruity , flag;
int numdelay , ms;
int tailX[100] , tailY[100] , counttail=0;

void Print() //page one-two
{
    //page one
    system("color 3f");
    printf("\t-----------------------------------------\n");
    printf("\tl\t\t\t\t\tl\n");
    printf("\tl\t   COMPUTER PROGRAMING     \tl\n");
    printf("\tl\t\tPROJECT\t\t\tl\n");
    printf("\tl\t\t\t\t\tl\n");
    printf("\tl\t      GAME  SNAKE  \t\tl\n");
    printf("\tl\t\t\t\t\tl\n");
    printf("\tl      PRESS ENTER TO CONTINUOUS...     l\n");
    printf("\tl\t\t\t\t\tl\n");
    printf("\t-----------------------------------------\n");
    getch();
    system("cls");

    //page two
    system("color 3f");
    printf("\t---------------------------------------------------------\n");
    printf("\tl\t\t\t\t\t\t\tl\n");
    printf("\tl\t\t     HOW TO PLAY GAME     \t\tl\n");
    printf("\tl\t\t\t\t\t\t\tl\n");
    printf("\tl\t\t\t\t\t\t\tl\n");
    printf("\tl      PRESS (W) FOR TURN UP / (A) FOR TURN LEFT\tl\n");
    printf("\tl         (S) FOR TURN DOWN / (D) FOR TURN RIGHT\tl\n");
    printf("\tl\t\t\t\t\t\t\tl\n");
    printf("\tl     PRESS (P) FOR PAUSE GAME / (O) FOR EXIT GAME\tl\n");
    printf("\tl\t\t\t\t\t\t\tl\n");
    printf("\tl\t\tGOAL: GET 200 SCORE TO WIN\t\tl\n");
    printf("\tl\t\t\t\t\t\t\tl\n");
    printf("\tl\t\tPRESS ENTER TO CONTINUOUS...\t\tl\n");
    printf("\tl\t\t\t\t\t\t\tl\n");
    printf("\t---------------------------------------------------------\n");
    if(getch()==1)
        exit(0);
}

void setup()
{
    gameover = 0;
    goal = 0;
    numdelay;

    x = height / 2 ;
    y = width / 2 ;
    label1:
        fruitx = rand() % 25;
            if (fruitx == 0)
                goto label1;
    label2:
        fruity = rand() % 25;
            if (fruity == 0)
                goto label2;
}

//page game
void draw()
{
    system("cls");
    system("color 1f");
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
            {
                printf("#");
            }
            else
            {
                if (i == x && j == y)
                    printf("0");
                else if (i == fruitx && j == fruity)
                    printf("F");
                else
                {
                    int ch=0;
                    for (k = 0 ; k < counttail ; k++)
                    {
                        if (i==tailX[k] && j==tailY[k])
                        {
                            printf("o");
                            ch=1;
                        }
                    }
                    if(ch==0)
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("YOUR SCORE = %d\n", goal);
    printf("CHOOSE YOUR SPEED\n");
    printf("PRESS (Z) FOR FAST\n");
    printf("PRESS (X) FOR MEDIUM\n");
    printf("PRESS (C) FOR SLOW");
}

//hit keyboard
void input()
{
    if (kbhit())
    {
        switch (getch())
        {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'p':  //pause
            flag = 5;
            break;
        case 'o':  //exit
            gameover = 7;
            break;
        case 'z':  //fast
            numdelay = 1;
            break;
        case 'x':  //mid
            numdelay = 50;
            break;
        case 'c':  //slow
            numdelay = 150;
            break;
        }
    }
}

//move
void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X , prev2Y;
    tailX[0]=x;
    tailY[0]=y;

    for (i = 1 ; i < counttail ; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    

    switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    case 5:
        break;
    default:
        break;
    }
    
    //snake hit
    if (x < 0 || x > height|| y < 0 || y > width)
    {
        gameover = 3;
    }

    for (i = 0 ; i<counttail ; i++)
    {
        if (x == tailX[i] && y == tailY[i])
        {
            gameover = 3;
        }
    }
    
    if (goal>200)
    {
        gameover = 2;
    }
    
    //snake eat (F)
    if (x == fruitx && y == fruity)
    {
    //new (F) / update score and tail
    label3:
        fruitx = rand() % 20;
        if (fruitx == 0)
            goto label3;

    label4:
        fruity = rand() % 20;
        if (fruity == 0)
            goto label4;
        goal += rand()%20;
        counttail++;
    }
}

//make delay
void delay(ms)
{
    clock_t timeDelay = ms + clock();
    while (timeDelay > clock());
}

//if win
void winend()
{
    system("cls");
    system("color 3f");
    printf("\n\tYOU WON\n");
    printf("\tCONGRATULATIONS\n");
    printf("\tTHANK YOU FOR PLAYING");
    getch();
}

//if die
void deadend()
{
    system("cls");
    system("color 3f");
    printf("\n\tYOU DIE\n");
    printf("\tLET'S TRY ONE MORE TIME IN NEXT TIME\n");
    printf("\tTHANK YOU FOR PLAYING");
    getch();
}

void main()
{
    setup();
    Print();
    while (!gameover)
    {
        draw();
        input();
        logic();
        delay(numdelay);
    }
    if (gameover==2)
    {
        winend();
    }
    else if (gameover==3)
    {
        deadend();
    }
}
