#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * “As a Hokie, I will conduct myself with honor and integrity at all times. I will not lie, cheat, or steal, nor will I accept the actions of those who do.”
 * */

struct Comic_List
{
    struct Comic* list;
    int size;
    int count;
};

struct Comic
{
    char* date;
    char* code;
    char* publisher;
    char* title;
    char *cost;
};

/*
the names and parameters of all the functions used in comic.c
*/
void load(struct Comic_List* list, char * filename);
void buy(struct Comic_List* buy_list, struct Comic_List* comic_list, int index);
void checkout(struct Comic_List* buy_list, FILE * out);
void display(struct Comic_List* list, FILE * out);
void save(struct Comic_List* list, FILE * out);
void find(struct Comic_List* list, FILE * out, int index);
void remove_comic(struct Comic_List* list, int index, FILE * out);
void clear(struct Comic_List* list);
void initialize( struct Comic_List* list, int size);
void display_comic(struct Comic c, FILE* out );
void add_comic( struct Comic_List *list, struct Comic c );
void make_comic(struct Comic* c, char *date, char *code, char* pub, char *title, char *price);
void free_comic( struct Comic c );