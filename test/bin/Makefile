# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/18 00:55:10 by fstadelw          #+#    #+#              #
#    Updated: 2019/04/26 02:12:38 by fstadelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	= $(wildcard *.c)
PRG	= $(SRC:.c=.bin)

all: $(PRG)

%.bin: %.c
	$(CC) $< -o $@

clean:
	rm $(PRG)

re: clean all

exec:
	@ for file in `echo $(PRG) | tr ' ' '\n' | sort -g` ; do \
		/bin/echo -n [$$file]' :	' ; \
		echo "./$$file" | tcsh ; \
		echo ; \
	done

test:
	@ for file in `echo $(PRG) | tr ' ' '\n' | sort -g` ; do \
		/bin/echo -n [$$file]' :	' ; \
		echo "./$$file" | ../../minishell ; \
		echo ; \
	done
