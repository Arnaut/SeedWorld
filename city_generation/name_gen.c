#include <stdlib.h>
#include <time.h>
#include "city_gen.h"
#include <stdio.h>
char* defined_tab_c(int type, int* max_c)
{
    char* tab_c=malloc(sizeof(char));
    char tab[20]={'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z'};
    int i=0;
    int j=i;
    if(type==1)
    {
        tab_c=realloc(tab_c,18);
        while (i<18)
        {
            if(tab[j]=='k'||tab[j]=='x'||tab[j]=='z')
            {   
                while(tab[j]=='k'||tab[j]=='x'||tab[j]=='z')
                {
                    j++;
                }
            }
            tab_c[i]=tab[j];
            i++;
            j++;
        }
        *max_c=17;

    }
    else if(type==2)
    {
        tab_c=realloc(tab_c,15);
        while (i<15)
        {
            if(tab[j]=='j'||tab[j]=='k'||tab[j]=='w'||tab[j]=='x'||tab[j]=='z')
            {
                while(tab[j]=='j'||tab[j]=='k'||tab[j]=='w'||tab[j]=='x'||tab[j]=='z')
                {
                    j++;
                }
            }
            tab_c[i]=tab[j];
            i++;
            j++;
        }
        *max_c=14;
    }
    else
    {
        tab_c=realloc(tab_c,20);
        while (i<20)
        {
            tab_c[i]=tab[i];
            i++;
        }
        *max_c=19;
    }
    return tab_c;
}

char* defined_tab_v(int type, int* max_v)
{
    char* tab_v=malloc(sizeof(char));
    char tab[6]={'a','e','i','o','u','y'};
    int i=0;
    int j=i;
    if(type==1 || type==3)
    {
        tab_v=realloc(tab_v,6);
        while (i<6)
        {
            tab_v[i]=tab[i];
            i++;
        }
        *max_v=5;

    }
    else
    {
        tab_v=realloc(tab_v,5);
        while (i<5)
        {
            if(tab[j]=='y')
            {
                j++;
            }
            tab_v[i]=tab[j];
            i++;
            j++;
        }
        *max_v=4;
    }
    return tab_v;
}

void choose_letter(char* tab,char* word,int max,int i)
{
    printf("============CHOOSE LETTER=============\n");
    printf("choose letter for index = %i\n",i);

    int index = nb_rand(0,max);
    char letter=tab[index];
    if(i>0 && ((word[i-1]=='y')||(word[i-1]=='u')))
    {
        while(letter=='y'||letter=='u')
        {
            index = nb_rand(0,max);
            letter=tab[index];
        }
    }
    word[i]=letter;
    printf("index letter= %i\n", index);
    printf("letter picked= %c\n",letter);
    printf("======================================\n");
}

char* finding_name(int p_voy, int type,int len, char* word)
{
    printf("len word= %i\n",len);
    int c = 0;
    int r_percent = 0;
    int d_v=0;
    int d_c=0;
    int double_it=0;
    int vo_picked=0;
    int max_v=0;
    int max_c=0;
    char* tab_v=defined_tab_v(type,&max_v);
    char* tab_c=defined_tab_c(type,&max_c);
    printf("max_c= %i\n",max_c);
    printf("max_v= %i\n",max_v);
    printf("tab_v= ");
    for(int i=0;i<=max_v;i++)
    {
        printf("%c ",tab_v[i]);
    }
    printf("\n");
    printf("tab_c= ");
    for(int i=0;i<=max_c;i++)
    {
        printf("%c ",tab_c[i]);
    }
    printf("\n");
    if(type==2 || type==3)
    {
        choose_letter(tab_c,word,max_c,c);
        vo_picked=0;
        c+=1;
    }
    while (c < len)
    {
        printf("word= %s\n",word);
        printf("index = %i\n",c);
        r_percent=nb_rand(0,100);
        printf("r_percent= %i \n",r_percent);
        printf("p_voy = %i\n",p_voy);
        if (d_v)//double vowel
        {
            printf("double voyelle\n");
            choose_letter(tab_c,word,max_c,c);
            vo_picked=0;
            d_v=0;
        }
        else if (d_c)//double consonne
        {
            printf("double consonne\n");
            choose_letter(tab_v,word,max_v,c);
            vo_picked=1;
            d_c=0;
        }
        else
        {
            if(c>=2 && (word[c-2]=='q'))
            {
                choose_letter(tab_v,word,max_v,c);
                d_v=1;
                vo_picked=1;
            }
            else if((c!=0)&&(word[c-1]=='q'))
            {
                word[c]='u';
                vo_picked=1;
            }
            else if((c!=0) && (!vo_picked))
            {
                if(c<=1)
                {
                    double_it=0;
                }
                else
                {
                    double_it=nb_rand(0,1);
                }
                if((double_it) &&(word[c-1]=='m'||word[c-1]=='r'||word[c-1]=='s'||word[c-1]=='n'||word[c-1]=='p'||word[c-1]=='t'||word[c-1]=='l'||word[c-1]=='f'))
                {

                    printf("have to double the letter\n");
                    word[c]=word[c-1];
                    vo_picked=0;
                    d_c=1;
                }
                else
                {
                    printf("have to pick a voyelle\n");
                    choose_letter(tab_v,word,max_v,c);//obligation to pick vowel
                    vo_picked=1;
                }
            }
            else if(word[c]=='a'||word[c]=='o'||word[c]=='e'||word[c]=='i')
            {
                if(c<=1)
                {
                    double_it=0;
                }
                else
                {
                    double_it=nb_rand(0,1);
                }
                double_it=nb_rand(0,1);
                if(double_it)//can double the letter or not
                {
                    printf("have to double the letter\n");
                    word[c+1]=word[c];
                    d_v=1;
                }
            }
            else if(r_percent<=p_voy)//other case we can choose what we want
            {
                printf("aucun cas validé pick voyelle\n");
                choose_letter(tab_v,word,max_v,c);
                if(vo_picked)
                {
                    d_v=1;
                }
                vo_picked=1;
            }
            else
            {
                printf("aucun cas validé pick consonne\n");
                choose_letter(tab_c,word,max_c,c);
                if(!vo_picked && c!=0)
                {
                    d_c=1;
                }
                vo_picked=0;
            }
        }
        c+=1;
    }
    free(tab_c);
    free(tab_v);
    return word;
}

char* name_gen(int type)
{
    int len = nb_rand(6, 8);
    int p_voy = 0;
    char* word= malloc(sizeof(char) * len);
    if (type==1)//fairy world
    {
        p_voy = 100;
    }
    else if (type ==2)//medieval world
    {
        printf("monde type= médiéval\n");
        p_voy = 40;
    }
    else//future world
    {
        p_voy = 20;
    }
    return finding_name(p_voy, type,len, word);
}