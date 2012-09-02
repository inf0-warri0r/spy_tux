#Author :Tharindra Galahena
#Project:spy_tux - keylogger for linux
#Date   :29/07/2012

#     Copyright 2012 Tharindra Galahena
#
# This file is part of spy_tux.

# spy_tux is free software: you can redistribute it and/or modify it under the terms of 
# the GNU General Public License as published by the Free Software Foundation, either 
# version 3 of the License, or any later version. spy_tux is distributed in the hope 
# that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
# Public License for more details.
#
# You should have received a copy of the GNU General Public License along with spy_tux. 
# If not, see http://www.gnu.org/licenses/.
# 

CC    = gcc
FILES = spy_tux.c
FLAGS = -lpthread

all:	
	$(CC) -o spy_tux $(FILES) $(FLAGS) $(GTK_LIBS) $(GTK_FLAGS) 
