//------------------------------------------------------------------------
// NAME: Petar Damianov
// CLASS: XIb
// NUMBER: 21
// PROBLEM: #1
// FILE NAME: ls.c
// FILE PURPOSE: Program that implements shell interpreter
//------------------------------------------------------------------------

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

// GOD DAMN MAN PAGE IS INSANE

char* get_proper_error_message(const char* open_msg, const char* filename_msg){
	// Proper error message = ls: cannot access aa
	// or ls: cannot open directory forbidden/
	char* error_message = malloc(strlen(open_msg) + strlen(filename_msg));
	strcpy(error_message, open_msg);
	strcat(error_message, filename_msg);

	return error_message;
}

char* get_permissions(struct stat* statbuf){
	char* permissions = (char*) malloc(sizeof(char) * 10);
	memset(permissions, '-', 9);
	permissions[9] = '\0';

	if(statbuf->st_mode & S_IRUSR){permissions[0] = 'r';}
	if(statbuf->st_mode & S_IWUSR){permissions[1] = 'w';}
	if(statbuf->st_mode & S_IXUSR){permissions[2] = 'x';}
	if(statbuf->st_mode & S_IRGRP){permissions[3] = 'r';}
	if(statbuf->st_mode & S_IWGRP){permissions[4] = 'w';}
	if(statbuf->st_mode & S_IXGRP){permissions[5] = 'x';}
	if(statbuf->st_mode & S_IROTH){permissions[6] = 'r';}
	if(statbuf->st_mode & S_IWOTH){permissions[7] = 'w';}
	if(statbuf->st_mode & S_IXOTH){permissions[8] = 'x';}

	return permissions;
}

void print_file_info(const char* pathname){
	struct stat* statbuf = (struct stat*) malloc(sizeof(struct stat));

	if ((stat(pathname, statbuf)) == -1){
		const char* open_msg = "ls: cannot access ";
		char* error_message = get_proper_error_message(open_msg, pathname);
		perror(error_message);
		free(error_message);
		exit(-1);
	}
	// Get permissions 
	char* p = get_permissions(statbuf);
	printf("%s ", p);
	free(p);

	// Get hardlinks
	printf("%ld ", statbuf->st_nlink);

	// StackOverflow to be alive
	// Get file owner and group
	struct passwd *pw;
	pw = getpwuid(statbuf->st_uid);

    struct group  *gr;
    gr = getgrgid(statbuf->st_gid);

    printf("%s %s ", pw->pw_name, gr->gr_name);

	// Get blocks allocated size
	printf("%ld ", statbuf->st_size);

	// And lastly gat file last modification data
	// I need no more than 30 characters displaing timestamp
	char time_buffer[100];

	time_t ttime = statbuf->st_mtim.tv_sec;

	//magic lmao
	strftime(time_buffer, 100, "%b %d %R", localtime(&ttime));
	printf("%s", time_buffer);

	free(statbuf);
}

void print_all_files_type_from_directory(const char* pathname, int special_print, int hidden_files, int file_info, int recursive){
	struct dirent *d;
	DIR *ds = opendir(pathname);

	// for everythink in folder if partname is folder get info 
	if (ds == NULL){
		const char* open_msg = "ls: cannot open directory ";
		char* error_message = get_proper_error_message(open_msg, pathname);
		perror(error_message);
		free(error_message);
		exit(-1);
	}else{

		if (special_print){
			printf("%s:\n", pathname);
		}

		// Get the number of blocks occupied by all files in the directory if file_info= 1
		if(file_info){
			struct stat* statbuf = (struct stat*) malloc(sizeof(struct stat));
			if ((stat(pathname, statbuf)) == -1){
				const char* open_msg = "ls: cannot access ";
				char* error_message = get_proper_error_message(open_msg, pathname);
				perror(error_message);
				free(error_message);
				exit(-1);
			}
			printf("total %ld\n", statbuf->st_blocks / 2);
			free(statbuf);
		}
		// While there are entry in ther directory 
		while ((d = readdir(ds)) != NULL){

			// if file is hidden command is 0 or 1 logic for hiddent files
			if(!hidden_files && d->d_name[0] == '.'){
				continue;
			}else{
				if((strlen(d->d_name) == 2 && d->d_name[1] == '.') || (strlen(d->d_name) == 1 && d->d_name[0] == '.')){
					continue;
				} 
			}

			// Get files type using d_type from dirent structure
			//for readability
			// I need to rewrite filepath of files/folders or they wont work using stat function

			if(d->d_type == DT_REG){printf("-");}
			else if(d->d_type == DT_DIR){printf("d");}
			else if(d->d_type == DT_BLK){printf("b");}
			else if(d->d_type == DT_CHR){printf("c");}
			else if(d->d_type == DT_FIFO){printf("p");}
			else if(d->d_type == DT_LNK){printf("l");}
			else if(d->d_type == DT_SOCK){printf("s");}
			else if(d->d_type == DT_UNKNOWN){printf("Unknown");}
			else{printf("Error while finiding file type!");}

			// if -l command is used call print_file_info function after file type than print filename

			if(file_info){
				char *filename = (char*) malloc(strlen(pathname));
				strcpy(filename, pathname);
				if (pathname[strlen(pathname) - 1] == '/'){
					filename = (char*) realloc(filename, strlen(filename) + strlen(d->d_name));
				}else{
					filename = (char*) realloc(filename, strlen(filename) + strlen(d->d_name) + 1);
					strcat(filename, "/");
				}
				strcat(filename, d->d_name);
				print_file_info(filename);
				free(filename);
			}

			printf(" %s\n",d->d_name);
		}
		if (errno == EBADF){
			perror("Error while calling readdir()");
			exit(-1);
		}
	}

	if (closedir(ds) == -1){
		perror("Error while calling closedir()");
	}
}

void print_file_type(const char* pathname, int special_print, int hidden_files, int file_info, int recursive){
	struct stat* statbuf = (struct stat*) malloc(sizeof(struct stat));
	if ((stat(pathname, statbuf)) == -1){
		const char* open_msg = "ls: cannot access ";
		char* error_message = get_proper_error_message(open_msg, pathname);
		perror(error_message);
		free(error_message);
		exit(-1);
	}
	// Get files type using st_mode from stat structure and following mask values
	if (S_ISDIR(statbuf->st_mode)){
		// Use dir logic cuz there are more than one file 
		print_all_files_type_from_directory(pathname, special_print, hidden_files, file_info, recursive);

	}else{
		if(S_ISREG(statbuf->st_mode))printf("-");
		else if(S_ISBLK(statbuf->st_mode))printf("b");
		else if(S_ISCHR(statbuf->st_mode))printf("c");
		else if(S_ISFIFO(statbuf->st_mode))printf("p");
		else if(S_ISLNK(statbuf->st_mode))printf("l");
		else if(S_ISSOCK(statbuf->st_mode))printf("s");
		else{printf("Error while finiding file type!\n");}

		if(file_info){
			print_file_info(pathname);
		}

		printf(" %s\n", pathname);

	}
	free(statbuf);
}


int main(int argc, char* argv[]){
	// get commands from argv
	int opt, hidden_files=0, file_info=0, recursive=0;
	while((opt=getopt(argc, argv, "lAR?:"))!=-1) {
		switch(opt) {
			case 'A':hidden_files=1;break;
			case 'l':file_info=1;break;
			case 'R':recursive=1;break;
			default: break;
		}
	}

	//get files from argv and rum logic
	if (argc == 1){
		print_file_type(".", 0, hidden_files, file_info, recursive);
	}else if (argc == 2){
		if(argv[1][0] == '-'){
			print_file_type(".", 0, hidden_files, file_info, recursive);
		}else{
			print_file_type(argv[1], 0, hidden_files, file_info, recursive);
		}
	}
	else {
		// start logic functions for every command
		int commands_count = 0;
		for (int i = 1; i < argc; ++i) {
			if (argv[i][0] == '-'){
				commands_count++;
				if (commands_count == argc - 1){
					print_file_type(".", 0, hidden_files, file_info, recursive);
				}
				continue;
			}
			// if args > 2 than use special output when u have folder
			print_file_type(argv[i], 1, hidden_files, file_info, recursive);
			if (i != argc - 1){
				printf("\n");
			}
		}
	}

	return 0;
}