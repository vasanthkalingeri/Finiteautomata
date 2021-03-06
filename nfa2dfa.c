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
    if(j > 0)
        value[--j] = '\0';
    else
        value[0] = '\0';
}

int present(char string[NUMSTATES + 10])
{
    int i,j;
    if(top == 1)
        return 0;
    for(i=0;i<top;i++)
    {
        if(!strcmp(string, done[i]))
            return 1;
    }
    return 0;
}

void set_union(int a1[], int res[])
{
    int i,j,present, k;
    char string[100];
    k = 0;
    while(res[k++] != -1);
    k--;    
    i = 0;
    while(a1[i] != -1)
    {
        present = 0;
        j = 0;
        while(res[j] != -1)
        {
            if(res[j++] == a1[i])
            {
                present = 1;
                break;
            }
        }
        if(!present)
            res[k++] = a1[i];
        i++;
    }
    res[k] = -1;
    
    stringof(res, string);
    printf("%s\n", string);
}

void valueof(char str[], int val[])
{
    int i,j, k=0, temp;
    i = 0;
    while(i < strlen(str))
    {
        temp = 0;
        j = 0;
        while(str[i + j] != ',' && str[i+j] != '\0')
        {
            temp += (pow(10, j) * (str[i+j] - 48));
            j++;
        }
        val[k++] = temp; 
        i = i + j + 1;
    }
    val[k] = -1;
}

void build_dfa(int table[NUMSTATES][NUMSYM][NUMSTATES], int final[NUMSTATES])
{
    int i,j,k;
    
    int checkfinal[LIM];
    char dfa[LIM][NUMSYM][NUMSTATES + 10];
    char string[NUMSTATES + 10];
    int array[NUMSTATES + 1], temp[NUMSTATES + 1], stackarr[NUMSTATES + 1];
/*    printf("delta\t");*/
/*    for(i=0;i<NUMSYM;i++)*/
/*        printf("%d\t",i);*/
/*    printf("\n");*/

    //First simply copy the initial state of nfa to dfa    
    strcpy(done[0], "0\0"); 
    k = 1;
    top = 1;
    for(j=0;j<NUMSYM;j++)
    {
        stringof(table[0][j], string);
        if(!present(string))
            strcpy(done[top++], string);
        strcpy(dfa[0][j], string);
    }
    
/*    for(i=1;i<top;i++)*/
/*    {*/
/*        strcpy(string, done[i]);*/
/*        printf("%s ", string);*/
/*    }*/
/*    printf("\n");*/
    //expand all the unseen ones
    i = 1;
    while(i < top)
    {
        valueof(done[i], temp);
        j = 0;
        array[0] = -1;
        stringof(array, string);
        printf("array is %s\n", string);
        while(temp[j] != -1)
        {
            set_union(table[temp[j]][1], array);
/*            stringof(array, string);*/
/*            printf("%s ", string);*/
/*            stringof(table[0][j], string);*/
/*            printf("%s ", string);   */
            j++;
        }
        printf("\n");
        i++;        
    }
    printf("\n");    
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
