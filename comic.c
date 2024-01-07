#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "comic.h"

/**
 * “As a Hokie, I will conduct myself with honor and integrity at all times. I will not lie, cheat, or steal, nor will I accept the actions of those who do.”
 * */

/*
takes a file and puts the comics it mentions in a comic list
*/
void load(struct Comic_List* list, char * filename)
{
    
    FILE * in = fopen(filename, "r");// opens correct file
    char date[1000];
    char code[1000];
    char pub[1000];
    char title[1000];
    char price[1000];// variables for the information eacch comic contain
    struct Comic com;
    fscanf(in, "%*[^\n]\n");// scans the first line to get rid of the header
    
    while (!feof(in))// loops until end of file
    {
        fscanf(in, "%[^,],", date);
        fscanf(in, "%[^,],", code);
        fscanf(in, "%[^,],", pub);
        fscanf(in, "%[^,],", title);
        fscanf(in, "%[^\n]\n", price);// scans and saves each piece of information of the comic
        make_comic(&com, date, code, pub, title, price);// uses that info to make the comic
        add_comic(list, com);// add the comic to your comic list
    }
    fclose(in);

}

/*
adds comics to a buy list
*/
void buy(struct Comic_List* buy_list, struct Comic_List* comic_list, int index)
{
    struct Comic com;
    if ( comic_list->count >= index && index > 0)// makes sure the index is valid
    {
        
        make_comic(&com, comic_list->list[index].date, comic_list->list[index].code
            , comic_list->list[index].publisher, comic_list->list[index].title
            , comic_list->list[index].cost);//makes a copy of a comic to add to the buy list
        add_comic(buy_list, com);// adds to buy list
    }

}
/*
displays all info of comics in buy list and find the price
*/
void checkout(struct Comic_List* buy_list, FILE * out)
{
    double sub = 0;
    double tax = 0;
    double total = 0;//variables for the different prices
    display(buy_list,out);// displays all items in buylist
    for( int i = 0; i < buy_list->count; i++)
    {
        sub = sub + atof(buy_list->list[i].cost + 1);//makes all the string prices into ints and finds the subtotal
    }
    tax = sub * 0.05;//finds now much tax will cost
    total = sub + tax;//finds total
    fprintf(out, "Subtotal:  $%f\n", sub);//prints subtotal
    fprintf(out, "Tax:  $%f\n", tax);// prints tax
    fprintf(out, "Total:  $%f\n", total);// prints total

}

/*
displays the comics in a list and their information
*/
void display(struct Comic_List* list, FILE * out)
{
    if (list->count == 0)
    {
        fprintf(out, "List is currently empty.\n");// prints message if invalid input
    }
    for ( int i = 0; i < list->count; i++)//loop through all comics
    {
        fprintf(out, "Comic Number: %d\n", i + 1);// prints the comic's number
        display_comic(list->list[i], out);// prints the other information about the comic
    }
}

/*
makes a new file and writes out the information of the list
*/
void save(struct Comic_List* list, FILE * out)
{
    fprintf(out, "DATE,CODE,PUBLISHER,TITLE,PRICE\n"); // print header
    for (int i = 0; i < list->count; i++)//loop through all items in list
    {
        fprintf(out, "%s,%s,%s,%s,%s\n", list->list[i].date,
            list->list[i].code,list->list[i].publisher, 
            list->list[i].title, list->list[i].cost );// prints all the information of the comic
    }
fclose(out);
    
}

/*
finds the comic at a certain location and prints ints information
*/
void find(struct Comic_List* list, FILE * out, int index)
{
    if ( list->count >= index)//determines if index is valid
    {
        display_comic(list->list[index], out);//prints information of the comic
    }
    else
    {
        fprintf(out, "There is no comic at index #%d in the list.\n" , index);
    }// prints message if invalid input

}
/*
removes a comic from the list
*/
void remove_comic(struct Comic_List* list, int index, FILE * out)
{
    if (list->count > index)// determines if index is valid
    {
        free_comic(list->list[index]);// frees a comic
        for ( int i = index; i < list->count - 1; i++)// loops through needed comics
        {
            list->list[i] = list->list[i + 1];// moves the comic to correct position
        }
        list->count--;// decrease total comic count

        fprintf(out, "Comic at index %d successfully removed\n" , index);
    }
    else
    {
        fprintf(out, "Comic at index %d was not removed\n", index);
    }// prints message if invalid input
}
/*
clears all comics from a list
*/
void clear(struct Comic_List* list)
{
    for(int i = 0; i < list->count; i++)//loop through all comics
    {
        free_comic(list->list[i]);// free the comic
    }
    list->count = 0;// deduce total comic count
}
/*
sets up a comic list
*/
void initialize( struct Comic_List* list, int size)
{
    list->list = calloc(size, sizeof(struct Comic));// sets the memory of the list
    list->size = size;// sets the capacity
    list->count = 0;// sets the amount of comics it has aka 0
}
/*
displays one comic and its information
*/
void display_comic(struct Comic c, FILE* out )
{

    fprintf(out, "Date: %s\n", c.date);
    fprintf(out, "Code: %s\n", c.code);
    fprintf(out, "Publisher: %s\n", c.publisher);
    fprintf(out, "Title: %s\n", c.title);
    fprintf(out, "Cost: %s\n", c.cost);// prints all the information of the comic
    
}

/*
adds a comic to the list
*/
void add_comic( struct Comic_List *list, struct Comic c )
{
    if ( list->count == list->size)// determines if there is enough capacity
    {
        list->size = list->size * 2;// incease capacity
        list->list = realloc(list->list, list->size * sizeof(struct Comic));// changes size in the memory

    }
  
    list->list[list->count] = c;// adds comic to the back of the list
    list->count++;// increase amount of comics in list
}

/*
sets up the information of a comic
*/
void make_comic(struct Comic *c, char *date, char *code, char* pub, char* title, char *price)
{
    c->date = calloc(strlen(date) + 1, sizeof(char));
    strcpy(c->date, date);// sets up date
    c->code = calloc(strlen(code) + 1, sizeof(char));
    strcpy(c->code, code);// sets up code
    c->publisher = calloc(strlen(pub) + 1, sizeof(char));
    strcpy(c->publisher, pub);// sets up publisher
    c->title = calloc(strlen(title) + 1, sizeof(char));
    strcpy(c->title, title);// sets up title
    c->cost = calloc(strlen(price) + 1, sizeof(char));
    strcpy(c->cost, price);// sets up price
}

/*
frees a comic
*/
void free_comic( struct Comic c )
{
    free(c.date);
    free(c.code);
    free(c.publisher);
    free(c.title);
    free(c.cost);// frees all information of the comic
}

