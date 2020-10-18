/*************************************************************    
 * Program Filename: movie.h
 * Author: YanYan Lee
 * Date: 10/17/2020
 * Description: h file that contains movie structs and libraries
 * 		for main.c file
 * Input: None
 * Output : None
 * **************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define PREFIX "movies_"
#define EXT	".csv"

// struct for movies
struct movie{
        char    *title;
        int     year;
        char    **lang;
        float   rating;
        struct  movie  *next;
};


