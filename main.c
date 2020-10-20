// CS 344 PROGRAM 2

#include "movie.h" 

// function to parse data
// This function copy from Assignment 1 createMovie function in main.c and sample code for assignment 1 on Canvas
struct movie *createMovie(char *currLine){
		
	struct movie *currMovie = malloc(sizeof(struct movie));

	// pointer for using strtok_r
	char *ptr;

	// total number of languages
	int langSize = 5;

	// token for title
	char *token = strtok_r(currLine, ",", &ptr);
	currMovie->title = calloc(strlen(token)+1, sizeof(char));
	strcpy(currMovie->title, token);

	// token for year
	token = strtok_r(NULL, ",", &ptr);
	currMovie->year = atoi(token);

	// token for languages
	token = strtok_r(NULL, ",", &ptr);

	// allocate dynamic array for languages 
	currMovie->lang = (char**)calloc(langSize ,sizeof(char*));
	
	// dynamic array for languages
	int i;
	for(i = 0; i < langSize; i++){
		currMovie->lang[i] = (char*)calloc(strlen(token)+1 ,sizeof(char));
		char *token2 = strtok_r(NULL, "[,]", &token);
	
		// fill the empty language with string
		if(token2 == NULL){
			strcpy(currMovie->lang[i], "NULL");

		}else{
			strcpy(currMovie->lang[i], token2);
		}
		
	}	

	// token for rating
	token = strtok_r(NULL, ",", &ptr);
	currMovie->rating = strtod(token, NULL);

	// set the next node to null
	currMovie->next = NULL;
	return currMovie;	
}

// reads file and splits data per line
// This function copy from assignment 1 file process fucntion in main.c and sample code for assignment 1 on Canvas
struct movie* file_process(char fPath[]){
	// read file
	FILE *movieFile = fopen(fPath, "r");
	char *currLine = NULL;
	size_t len = 0;
	size_t nread;
	char *token;

	// head and tail of the linked list
	struct movie *head = NULL;
	struct movie *tail = NULL;

	// skip the first line of the csv file
	getline(&currLine, &len, movieFile);
		
	// readfile line by line until the end of the file
	while((nread = getline(&currLine ,&len, movieFile)) != -1){
		
		// call function to input data
		struct movie *newNode = createMovie(currLine);
		if(head == NULL){
			head = newNode;
			tail = newNode;
		}else{
			tail->next = newNode;
			tail = newNode;
		}

	}
	free(currLine);
	fclose(movieFile);
	return head;
}

// create new dir and return the dir name
char* createNewDir(){
	int n;
	int status;
	char dirName[50];
	char nStr[10];

	// format of the new dir
	memset(dirName, '\0', sizeof(dirName));
	strcpy(dirName,"leeya.movies.");
	
	// convert random number to string
	n = rand()%100000;
	sprintf(nStr, "%i", n);

	// concatenate two strings
	strcat(dirName, nStr);
	 	
	// create new dir
	status = mkdir(dirName, 0750);

	// return dir name	
	char * name = calloc(strlen(dirName)+1,sizeof(char));
	name = dirName;
	printf("Created directory with the name: %s\n", name);
	return name;
}

// create new movie file, part of this function use the sample code from week 3 file on Canvas
void newFile(struct movie *list, char newDir[]){
	// create sub-directory path
	char dir[50] = "./";
	strcat(dir,newDir);
	strcat(dir, "/");

	// open sub-directory
	DIR*	currDir = opendir("dir");

	// open new file
	int file_descriptor;
	char fName[50];
	struct movie *m = list;
	
	// loop through the movie linked list
	while(m != NULL){ 

		// create file path
		memset(fName, '\0', sizeof(fName));

		// convert year into file string name
		sprintf(fName, "%i", m->year);
		strcat(fName, ".txt");

		strcat(dir, fName);
		
		// open file
		file_descriptor = open(dir, O_RDWR | O_CREAT | O_APPEND, 0640);
		if(file_descriptor == -1){
			printf("Unable to open %s\n", dir);
			exit(1);
		}

		// write title to the file
		write(file_descriptor, m->title, strlen(m->title));
		write(file_descriptor, "\n", sizeof(char));
		close(file_descriptor);
		
		// clean up the file path
		memset(dir, '\0', sizeof(dir));
		strcat(dir,"./");
		strcat(dir,newDir);
		strcat(dir, "/");

		m = m->next;
	}
	closedir(currDir);
}


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
				
			// check for .csv extensions	
			if(strncmp(&aDir->d_name[strlen(aDir->d_name)-4], EXT, strlen(EXT)) == 0){						

				// get meta-data of current file
				stat(aDir->d_name, &dirStat);

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
	
	//call create new dir function
	char *	newDir = createNewDir();
	char dir[50];
	memset(dir, '\0',sizeof(dir));
	strcpy(dir, newDir);

	//call parse data function
	struct movie * list = file_process(entryName);

	// generate file
	newFile(list, dir);

	// close the dir	
	closedir(currDir);	
}

// find the specific file
bool specFile(){
	
	// open current directory
	DIR* currDir = opendir(".");
	struct dirent *aDir;
	char entryName[256]; 
	char fName[256];
	bool exist = false;

	printf("Enter the complete file name: ");
	scanf("%s", &fName);

	//loop through dir
	while((aDir = readdir(currDir)) !=NULL){	

		// if file name is valid, use bool value to either print error messages or continue to process the file
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

	// error message, file not found
	if(exist == false){
		printf("The file %s was not found. Try again\n\n", fName);
	}else{		
		// continue the file processing
		printf("Now processing the chosen file named: %s\n\n",entryName);

		// create new directory function
		char *newDir = createNewDir();
		char dir[50];
		memset(dir, '\0', sizeof(dir));
		strcpy(dir, newDir);

		// call file process function
		struct movie * list = file_process(entryName);
		
		// generate files
		newFile(list, dir);
	}
	return exist;
}

// handling user options
void user_options(){
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
	srand(time(NULL));	
	
	struct movie *list;
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
			user_options();
		}else if(user != 2){
			printf("Wrong input, please try again. \n\n");
		}

	}
	return 0;
}
