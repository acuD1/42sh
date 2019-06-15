define MSG
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile for 42sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/14 19:23:44 by arsciand          #+#    #+#              #
#                                                     ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
endef

# Progress bar

ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL = make
%:
	  @$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
	  -nrRf $(firstword $(MAKEFILE_LIST)) \
	  ECHO="OutputPrintable" | grep -c "OutputPrintable")
N := x
C = $(words $N)$(eval N := x $N)
V = "`expr "   [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
ECHO = printf "\e[1A\r%s %s %s                        \n" $V
endif

# Color

RESET_C = \033[m
B_C = \033[0;34m
Y_C = \033[0;33m
G_C = \033[0;32m
R_C = \033[0;31m
M_C = \033[0;35m
C_C = \033[0;36m

# Programms names

NAME = 42sh
LNAME = libft.a
#TNAME =

# Version

BUILD_NUMBER_FILE = .build-number
BUILD_DATE = $$(date +'%Y%m%d')
BUILD_BRANCH = $$(git symbolic-ref HEAD 2>/dev/null | cut -d"/" -f 3)
BUILD_VERSION = $$(cat .version)
BUILD_PATCH = $$(cat $(BUILD_NUMBER_FILE))
BUILD_RELEASE = $$(cat .release)

# Dir/Files Path

S_PATH = srcs/
H_PATH += includes/
H_PATH += libft/includes/
B_PATH = build/
O_PATH = build/objs/
L_PATH = libft/

CR_PATH = build/objs/core/

PATHS = $(B_PATH) $(O_PATH) $(CR_PATH)

OBJP = "$(O_PATH){core}*.o"

# Files

SRC += $(S_PATH)core/42sh.c

#SRC += $(S_PATH)dev.c

# Objects and Headers

HDR += sh42.h
HDR += define.h
HDR += struct.h
HDR += libft.h

OBJ = $(patsubst $(S_PATH)%.c, $(O_PATH)%.o, $(SRC))
LIB = $(L_PATH)$(LNAME)
vpath %.h $(H_PATH)

# Variables

C_GCC = gcc $(CFLAG)
IFLAGS = $(addprefix -I, $(H_PATH))
CMPLC = $(C_GCC) -c $(IFLAGS)
CMPLO = $(C_GCC) -o
BUILD = $(PATHS)
AR_RC = ar rc
RANLI = ranlib
CFLAG = -Wall -Wextra -Werror
RM_RF = /bin/rm -rf
MKDIR = mkdir -p
NORME = norminette
SLEEP = sleep 0.01
GCFIL = "	- >	Compiling		-"
RMSHW = "	- -	Removing		-"
MKSHW = "	- +	Creating		-"
GCSUC = echo "$(G_C)==========>\tSUCCESS$(RESET_C)"
CLSUC = echo "$(R_C)==========>\tDONE$(RESET_C)"
NORMD = echo "$(G_C)==========>\tDONE$(RESET_C)"

.PHONY: all norme clean fclean re test

DEBUG =

ifeq ($(DEBUG), g)
	CFLAG = -g
else ifeq ($(DEBUG), fsanitize)
	CFLAG = -fsanitize=address
else
	CFLAG = -Wall -Wextra -Werror
endif

# Rules
make:
	$(MSG)
	@$(MAKE) --no-print-directory all

all: libm $(BUILD) $(NAME)

$(NAME): $(OBJ) $(BUILD_NUMBER_FILE)
	@$(ECHO) $(GCFIL) $(NAME)
	@$(CMPLO) $(NAME) $(OBJ) $(LIB)
	@$(GCSUC)
	@echo "---\nCFLAG\t- =$(B_C)\t$(CFLAG)$(RESET_C)\n---"
	@echo "\n$(G_C)[$(BUILD_BRANCH)] $(RESET_C)$@ v.$(BUILD_RELEASE)_$(BUILD_VERSION)_$(BUILD_PATCH)_$(BUILD_DATE) is ready !"
	@cp $(NAME) $(B_PATH)$(NAME)_$(BUILD_RELEASE)_$(BUILD_VERSION)_$(BUILD_PATCH)_$(BUILD_DATE)

$(OBJ): $(O_PATH)%.o: $(S_PATH)%.c $(HDR)
	@$(CMPLC) -DBUILDR=$(BUILD_RELEASE) -DBUILDV=$(BUILD_VERSION) -DBUILDP=$(BUILD_PATCH) -DDATE=$(BUILD_DATE) $< -o $@
	@$(ECHO) $(GCFIL) $<

$(BUILD_NUMBER_FILE): $(OBJ)
	@if ! test -f $(BUILD_NUMBER_FILE); then echo 0 > $(BUILD_NUMBER_FILE); fi
	@echo $$(($$(cat $(BUILD_NUMBER_FILE)) + 1)) > $(BUILD_NUMBER_FILE)

$(PATHS):
	@$(MKDIR) $(PATHS)
	@$(foreach var,$(PATHS), $(ECHO) $(MKSHW) $(var);)

norme:
	@$(NORMR)
	@$(NORME) $(SRC) $(H_PATH)$(HNAME)
	@$(NORMD)

test:
	@$(GCRUN)

clean: libco
	@for i in $(OBJ); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	@$(CLSUC)

fclean: libc
	@for i in $(OBJ); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	@for i in $(PATHS); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	@$(RM_RF) $(NAME)
	@$(ECHO) $(RMSHW) $(NAME)
	@$(CLSUC)

libm:
	@make -C $(L_PATH)
	@printf "\n"

libco:
	@make clean -C $(L_PATH)

libc:
	@make fclean -C $(L_PATH)

re:
	$(MSG)
	@$(MAKE) --no-print-directory fclean all

endif
