#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comic.h"
/**
 * “As a Hokie, I will conduct myself with honor and integrity at all times. I will not lie, cheat, or steal, nor will I accept the actions of those who do.”
 * */

/*
the main method of the program
*/
int main(int argc, char *argv[])
{
    //displays message if not ran with enough inputs
    if ( argc != 3 )
	{
		fprintf(stderr, "Usage: vectors <input-file> <output-file>\n");
		exit(1);
	}

    FILE* in;
	in = fopen(argv[1], "r");//makes the input file
	FILE* out;
	out = fopen(argv[2], "w");// makes the output file

    char command[2000];// variable for the commands types
    char command2[2000];// variable for the string commands
    int command3 = 0;// variable for the int commands
    struct Comic_List list;
    initialize(&list, 10);// makes the list for all the comics
    struct Comic_List buy_list;
    initialize(&buy_list, 10);// makes the list for the comics you want to buy
    


    fscanf(in, "%s", command);// scanes the first word on the first line
    
    while (!feof(in))// loops until end of file
    {
        if (strcmp(command, "load") == 0)// determines if command is set as load
        {
            fgetc(in); // skips space before the command
            fscanf(in, "%s\n", command2);// scans the filename
            fprintf(out, "Command: load %s\n", command2);// prints "Command: load" and the name of it
            load(&list, command2);// calls appropriate method
            fprintf(out, "Number of comics: %d\n", list.count); // prints number of comics in the list
        }
        else if (strcmp(command, "buy") == 0)// determines if command is set as buy
        {
            fgetc(in);// skips space before the command
            fscanf(in, "%d\n", &command3);// scans the buy
            fprintf(out, "Command: buy %d\n", command3);// prints "Command: buy " and the name of it
            buy(&buy_list, &list, command3);// calls appropriate method
            fprintf(out, "Comic #%d added to purchase list\n", command3);//prints statement that the comic has been added


        }
        else if (strcmp( command, "checkout") == 0)// determines if command is set as checkout
        {
            fprintf(out, "Command: checkout\n");// prints "Command: checkout" 
            checkout(&buy_list, out);// calls appropriate method
            fgetc(in);//skips to next line


        }
        else if (strcmp( command, "display") == 0)// determines if command is set as display
        {
            fprintf(out, "Command: display\n");// prints "Command: display" 
            display(&list, out);// calls appropriate method
            fgetc(in); // skips to next line


        }
        else if (strcmp( command, "save") == 0)// determines if command is set as save
        {
            fgetc(in);// skips space before the command
            fscanf(in, "%s\n", command2);// scans the place
            FILE * saveFile = fopen(command2, "w");
            fprintf(out, "Command: save %s\n", command2);// prints "Command: save " and the name of it
            save(&list, saveFile);// calls appropriate method


        }
        else if (strcmp( command, "clear") == 0)// determines if command is set as clear
        {
            fprintf(out, "Command: clear\n");// prints "Command: clear"
            clear(&list);// calls appropriate method
            fgetc(in);//skips to next line


        }
        else if (strcmp( command, "find") == 0)// determines if command is set as find
        {
            fgetc(in);// skips space before the command
            fscanf(in, "%d\n", &command3);// scans the find
            fprintf(out, "Command: find %d\n", command3);// prints "Command: find " and the name of it
            find(&list, out, command3);// calls appropriate method


        }
        else if (strcmp( command, "remove") == 0)// determines if command is set as remove
        {
            fgetc(in);// skips space before the command
            fscanf(in, "%d\n", &command3);// scans the remove
            fprintf(out, "Command: remove %d\n", command3);// prints "Command: remove " and the name of it
            remove_comic(&list, command3, out);// calls appropriate method


        }
        
        fscanf(in, "%s", command);// sets command as the first word of the next line
    }
      
clear(&list);
clear(&buy_list);
free(list.list);
free(buy_list.list);// free all used objects

    fclose(in);
    fclose(out);
    
    return 0;
}
