# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/18 00:55:10 by fstadelw          #+#    #+#              #
#    Updated: 2019/04/26 02:24:38 by fstadelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@ ./test.sh

fast:
	@ NOVALGRIND='yes' ./test.sh

clean:
	@ $(MAKE) -C sig clean > /dev/null 2> /dev/null; exit 0
	@ rm -Rf tmp/ res/

.PHONY: all fast clean
