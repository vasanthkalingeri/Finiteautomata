#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define NUMSYM 2
#define NUMSTATES 3

void input_nfa(int table[NUMSTATES][NUMSYM][NUMSTATES], int final[NUMSTATES])
{
    int i, j, k, fi, ch;
    fi = 0;
    for(i=0;i<NUMSTATES;i++)
    {
        final[i] = -1;
/*        printf("is %d a final state (1/0)?\n", i);*/
        scanf("%d", &ch);
        if(ch)
            final[fi++] = i;
        for(j=0;j<NUMSYM;j++)
        {
/*            printf("On reading symbol %d,list the transitions for state %d, (-1 to indicate end)\n", j, i);*/
            k = 0;
            while(1)
            {
                scanf("%d",&ch);
                if(ch == -1)
                {
                    table[i][j][k++] = ch;
                    break;
                }
                table[i][j][k++] = ch;                   
            }
        }        
    }
}

void display(int table[NUMSTATES][NUMSYM][NUMSTATES])
{
    int i,j,k;
    
    printf("delta\t");
    for(i=0;i<NUMSYM;i++)
        printf("%d\t",i);
    printf("\n");
    
    for(i=0;i<NUMSTATES;i++)
    {
        printf("%d\t", i);
        for(j=0;j<NUMSYM;j++)
        {
            k = 0;
            printf("[");
            
            //for formatting it neatly
            if(table[i][j][k] != -1)
                printf("%d",table[i][j][k++]);
            while(table[i][j][k] != -1)
                printf(",%d",table[i][j][k++]);
            printf("]\t");
        }
        printf("\n");
    }
}

char *stringof(int a[])
{
    char value[NUMSTATES + 10];
    int i=0, temp, j=0;
    while(a[i] != -1)
    {
        temp = a[i];
        while(temp != 0)
        {
            value[j++] = temp % 10;
            temp = temp / 10;
        }
        value[j++] = "/";
    }
    return value;
}

void build_dfa(int table[NUMSTATES][NUMSYM][NUMSTATES], int final[NUMSTATES])
{
    int i,j,k, lim = (int)pow(2, NUMSTATES);
    char done[lim][NUMSTATES];
    int visited[lim], top=-1;
    int dfa[lim][NUMSYM][NUMSTATES];
    
/*    printf("delta\t");*/
/*    for(i=0;i<NUMSYM;i++)*/
/*        printf("%d\t",i);*/
/*    printf("\n");*/
    
    done[0] = "0";
    visited[0] = 0;
    k = 1;
    for(i=0;i<NUMSTATES;i++)
    {
            
    }
        
}

int main()
{
    int table[NUMSTATES][NUMSYM][NUMSTATES], final[NUMSTATES];
/*    display(table);*/
    input_nfa(table, final);
    display(table);
    return 0;
}
