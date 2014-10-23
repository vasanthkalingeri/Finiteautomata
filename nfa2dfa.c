#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define NUMSYM 2
#define NUMSTATES 3
#define LIM 2<<NUMSTATES

char done[LIM][NUMSTATES + 10];
int top = 0;

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

void stringof(int a[],char value[])
{
    int i=0, temp, j=0;
    while(a[i] != -1)
    {
        temp = a[i++];
        do
        {
            value[j++] = (temp % 10) + 48;
            temp = temp / 10;
        }while(temp != 0);
        value[j++] = ',';
    }
    value[--j] = '\0';
}

int present(char string[NUMSTATES + 10])
{
    int i,j;
    if(top == 0)
        return 0;
    for(i=0;i<top;i++)
    {
        if(!strcmp(string, done[i]))
            return 1;
    }
    return 0;
}

void set_union(int a1[], int a2[], int res[])
{
    int i,j,present, k;
    i = 0;
    while(a1[i] != -1)
        res[k++] = a1[i++];
    j = 0;
    while(a2[j] != -1)
    {
        i = 0;
        present = 0;
        while(a1[i] != -1)
        {
            if(a1[i++] == a2[j])
            {
                present = 1;
                break;
            }
        }
        if(!present)
            res[k++] = a2[j];
        j++;
    }
}

void build_dfa(int table[NUMSTATES][NUMSYM][NUMSTATES], int final[NUMSTATES])
{
    int i,j,k;
    
    int checkfinal[LIM];
    char dfa[LIM][NUMSYM][NUMSTATES + 10];
    char string[NUMSTATES + 10];
    int array[NUMSTATES + 1], temp[NUMSTATES + 1];
/*    printf("delta\t");*/
/*    for(i=0;i<NUMSYM;i++)*/
/*        printf("%d\t",i);*/
/*    printf("\n");*/

    //First simply copy the initial state of nfa to dfa    
    k = 1;
    for(j=0;j<NUMSYM;j++)
    {
        stringof(table[0][j], string);
        if(!present(string))
            strcpy(done[top++], string);
        strcpy(dfa[0][j], string);
    }
        
    //expand all the unseen ones
    i = 0;
    while(i < top)
    {
        valueof(done[i], temp);
        j = 0;
        while(temp[j] != -1)
        {
            
        }
    }    
}

int main()
{
    int table[NUMSTATES][NUMSYM][NUMSTATES], final[NUMSTATES];
/*    display(table);*/
    input_nfa(table, final);
    build_dfa(table, final);
    display(table);
    return 0;
}
