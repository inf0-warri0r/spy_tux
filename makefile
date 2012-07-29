#Author :Tharindra Galahena
#Project:spy_tux - keylogger for linux
#Date   :29/07/2012

CC    = gcc
FILES = spy_tux.c
FLAGS = -lpthread

all:	
	$(CC) -o spy_tux $(FILES) $(FLAGS) $(GTK_LIBS) $(GTK_FLAGS) 
