// CS 344 PROGRAM 2

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

#define PREFIX "movie_"

// parse data


// largest file, this function is based on an example code of stat_example on Canvas
void largestFile(){
	// open dir
	DIR* 	currDir = opendir(".");
	struct 	dirent *aDir;
	struct 	stat dirStat;
	off_t	fSize;
	char 	entryName[256];
	int 	i = 0;

	// loop through all files
	while((aDir = readdir(currDir)) != NULL){
		
		// find matching prefix
		if(strncmp(aDir->d_name, PREFIX, strlen(PREFIX)) == 0){
			printf("%s\n", aDir->d_name);				
			// check for .csv files
//			if(){		

				// get meta-data of current file
				stat(aDir->d_name, &dirStat);
			
				// check sizes for tied file name
//			}
		}
	}
	
	// find the largest file
	
		// if true 

	// parse the data	

	// close the dir	
	closedir(currDir);
	
}

// process user options
void file_process(){
	int user = 0;
	bool exit = false;

	while(exit == false){
		printf("Which file you want to process?\n");
		printf("Enter 1 to pick the largest file\n");
		printf("Enter 2 to pick the smallest file\n");
		printf("Enter 3 to specify the name of a file\n");
		printf("Enter a choice from 1 to 3: ");
		scanf("%i", &user);
		if(user == 1){
			// find the largest file
			largestFile();			
			exit = true;
		}else if (user == 2){
			// find the smallest file
		
			exit = true;
		}else if(user == 3){
			// find the specific file

			exit = true;
		}
	}
}

int main(){
	
	int user = 0;

	// loop until user quit the program
	while(user != 2){
		printf("1. Select file to process\n");
		printf("2. Exit the program\n");
		printf("Enter a choice 1 or 2: ");
		scanf("%i", &user);
	
		if(user == 1){
			// call file process function
			file_process();
		}else if(user != 2){
			printf("wrong input, please try again. \n\n");
		}

	}
	return 0;
}
