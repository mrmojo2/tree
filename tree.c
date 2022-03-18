#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int depth=-1;

void readd(char *dir){
	int errno=0;
	struct dirent *de;
        DIR *d;
	char path[2048];

        if((d=opendir(dir))==NULL){
                perror("opendir error");
		return;
		//printf("   %s\n",dir);
        }
	depth++;
		
        while((de=readdir(d))!=NULL){	
		if((strncmp(".",de->d_name,1)==0)||(strcmp("..",de->d_name)==0)){ continue;}
		for(int i=0;i<depth;i++){ printf("\t");}
		printf("%s\n",de->d_name);	
		
		if((de->d_type)&DT_DIR){
			snprintf(path,sizeof(path),"%s/%s",dir,de->d_name);
			readd(path);
		}
	}
	if(errno!=0){
		printf("couldn't open directory\n");
	}else{
		closedir(d);
		depth--;
	}
	return;
}

void main(int argc,char *argv[]){
	readd(argv[1]);
}
