// CS 344 PROGRAM 2

#include "movie.h" 

// function to parse data
// part of this function is based on Assignment 1 createMovie function and main.c


// find the largest or smallest file, this function is based on an example code of stat_example in exploration on Canvas
void pickFile(int user){
	// open dir
	DIR* 	currDir = opendir(".");
	struct 	dirent *aDir;
	struct 	stat dirStat;
	off_t	fSize = 0;
	char 	entryName[256];
	int 	i = 0;
	bool	sizeCmp = true;

	// loop through all files
	while((aDir = readdir(currDir)) != NULL){
		
		// find matching prefix
		if(strncmp(aDir->d_name, PREFIX, strlen(PREFIX)) == 0){
//			printf("%s %i %c\n", aDir->d_name, strlen(aDir->d_name), aDir->d_name[18]);				
			// check for .csv extensions	
			if(strncmp(&aDir->d_name[strlen(aDir->d_name)-4], EXT, strlen(EXT)) == 0){						
				//printf("files that matches prefix and ext: ");
				//printf("%s \n", aDir->d_name);

				// get meta-data of current file
				stat(aDir->d_name, &dirStat);

//				printf("size: %i\n",dirStat.st_size);
				
				// deside if do option 1 or option 2 comparison
				if(user == 1){
					sizeCmp = dirStat.st_size > fSize;
				}else if (user == 2){
					sizeCmp = dirStat.st_size < fSize;
				}

				// find file
				if( i == 0 || sizeCmp){
						fSize = dirStat.st_size;
						memset(entryName, '\0', sizeof(entryName));
						strcpy(entryName, aDir->d_name);		
				}i++;
			}
		}
	}
	// print final result
	printf("Now processing the chosen file named: %s\n\n" ,entryName);
	
	// parse data

	// close the dir	
	closedir(currDir);	
}

// find the specific file
bool specFile(){
	DIR* currDir = opendir(".");
	struct dirent *aDir;
	char entryName[256]; 
	char fName[256];
	bool exist = false;

	printf("Enter the complete file name: ");
	scanf("%s", &fName);

	//loop through dir
	while((aDir = readdir(currDir)) !=NULL){	
		//printf("input: %s, file in dir: %s\n", fName, aDir->d_name);	
		//printf("length result: %i\n", strcmp(fName, aDir->d_name));	
		// file validation
		if(strncmp(fName, aDir->d_name, strlen(aDir->d_name)) == 0){	
			exist = true;
			memset(entryName, '\0', sizeof(entryName));
			strcpy(entryName, aDir->d_name);
			break;	
		}else{
			exist = false;
		}	

	}

	// close dir
	closedir(currDir);
	if(exist == false){
		printf("The file %s was not found. Try again\n\n", fName);
	}else{		
		printf("Now processing the chosen file named: %s\n\n",entryName);
	}
	return exist;
}

// handling user options
void file_process(){
	int 	user = 0;
	bool	exit = false;

	while(exit == false){
		printf("Which file you want to process?\n");
		printf("Enter 1 to pick the largest file\n");
		printf("Enter 2 to pick the smallest file\n");
		printf("Enter 3 to specify the name of a file\n\n");
		printf("Enter a choice from 1 to 3: ");
		scanf("%i", &user);
//		printf("\n");
		if(user == 1 || user == 2){
			
			// pick file according to integer
			pickFile(user);			
			exit = true;

		}else if(user == 3){
			// find the specific file
			exit = specFile();
		}else{
			printf("Wrong input, please try again\n\n");;	
		}
	}
}

int main(){
	
	int user = 0;

	// loop until user quit the program
	while(user != 2){
		printf("1. Select file to process\n");
		printf("2. Exit the program\n\n");
		printf("Enter a choice 1 or 2: ");
		scanf("%i", &user);
		printf("\n");	
		if(user == 1){
			// call file process function
			file_process();
		}else if(user != 2){
			printf("Wrong input, please try again. \n\n");
		}

	}
	return 0;
}
