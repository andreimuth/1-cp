#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXX 505

typedef struct
{
    int points;
    int games;
    int sets;
} player;

typedef struct
{
    int scoreA;
    int scoreB;
} setScore;

void deleteNewLineChar (char * s, int * len)
{
    s[(*len) - 1] = '\0';
    (*len)--;
}

void displayFinalResult (char winner, setScore * setScoreVector, int setsNumber)
{
    for (int i = 0; i < setsNumber; i++)
    {
        printf ("Set score: A-%d B-%d\n", setScoreVector[i].scoreA, setScoreVector[i].scoreB);
    }
    printf ("Match over, %c wins.\n\n", winner);
}

void displayIncompleteResult (setScore * setScoreVector, int setsNumber, int partialSetGamesA, int partialSetGamesB)
{
    for (int i = 0; i < setsNumber; i++)
    {
        printf ("Set score: A-%d B-%d\n", setScoreVector[i].scoreA, setScoreVector[i].scoreB);
    }
    printf ("Partial set score: A-%d B-%d\nMatch incomplete\n\n", partialSetGamesA, partialSetGamesB);

}

void checkGame (char * s)
{
    player a, b;
    setScore * setScoreVector  = (setScore*) malloc (sizeof (setScore) * 3);
    a.points = a.games = a.sets = b.points = b.games = b.sets = 0;
    int len = strlen (s);
    int setsNumber = 0;
    if (s[len - 1] == '\n')
    {
        deleteNewLineChar (s, &len);
    }
    int gameOver = 0;
    for (int i = 0; i < len; i++)
    {
        if (s[i] == 'A')
        {
            a.points++;
            if (a.points >= 4 && a.points - b.points >= 2)
            {
                a.games++;
                a.points = 0;
                b.points = 0;
                if (a.games >= 6 && a.games - b.games >= 2)
                {
                    a.sets++;
                    setScoreVector[setsNumber].scoreA = a.games;
                    setScoreVector[setsNumber].scoreB = b.games;
                    setsNumber++;
                    a.games = 0;
                    b.games = 0;
                    if (a.sets == 2)
                    {
                        displayFinalResult ('A', setScoreVector, setsNumber);
                        i = len;
                        gameOver = 1;
                    }
                }
            }
        }
        else
        {
            b.points++;
            if (b.points >= 4 && b.points - a.points >= 2)
            {
                b.games++;
                a.points = 0;
                b.points = 0;
                if (b.games >= 6 && b.games - a.games >= 2)
                {
                    b.sets++;
                    setScoreVector[setsNumber].scoreA = a.games;
                    setScoreVector[setsNumber].scoreB = b.games;
                    setsNumber++;
                    a.games = 0;
                    b.games = 0;
                    if (b.sets == 2)
                    {
                        displayFinalResult ('B', setScoreVector, setsNumber);
                        i = len;
                        gameOver = 1;
                    }
                }
            }
        }
    }
    if (gameOver == 0)
    {
        displayIncompleteResult (setScoreVector, setsNumber, a.games, b.games);
    }
}

int main()
{
    FILE * fin = fopen ("input.txt", "r");
    char * s = (char*) malloc (sizeof (char) * MAXX);
    while (fgets (s, MAXX, fin) != NULL)
    {
        checkGame (s);
    }
    fclose (fin);
    return 0;
}
