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

# Progress bar with on line output printing. This script get the maximum
# lines , then expr a compilation percentage.

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
LNAME = shared_libft.a
#TNAME =

# Build information that can be added the predefines buffer at compilation

BUILD_FILE			=	.build
BUILD_DATE			=	$$(date +'%Y%m%d')
BUILD_BRANCH		=	$$(git symbolic-ref HEAD 2>/dev/null | cut -d"/" -f 3)
BUILD_RELEASE		=	$$(awk 'NR==3 {print $$3}' $(BUILD_FILE))
BUILD_VERSION		=	$$(awk 'NR==4 {print $$3}' $(BUILD_FILE))
BUILD_PATCH			=	$$(awk 'NR==5 {print $$3}' $(BUILD_FILE))
DEFAULT_BUILD_FILE	=	"Build information, patch level is incremented at \
compilation.\n\nRELEASE\t=\t0\nVERSION\t=\t0\nPATCH\t=\t0"

# Dir/Files Path

S_PATH = srcs/
H_PATH += includes/
H_PATH += shared_libft/includes/
B_PATH = build/
O_PATH = build/objs/
L_PATH = shared_libft/

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
HDR += shared_libft.h

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

# Compilation core

$(NAME): $(OBJ) $(BUILD_FILE)
	@$(ECHO) $(GCFIL) $(NAME)
	@$(CMPLO) $(NAME) $(OBJ) $(LIB)
	@$(GCSUC)
	@echo "---\nCFLAG\t- =$(B_C)\t$(CFLAG)$(RESET_C)\n---"
	@echo "\n$(G_C)[$(BUILD_BRANCH)] $(RESET_C)$@ \
	v.$(BUILD_RELEASE)_$(BUILD_VERSION)_$(BUILD_PATCH)_$(BUILD_DATE) is ready !"
	@cp $(NAME) \
	$(B_PATH)$(NAME)_$(BUILD_RELEASE)_$(BUILD_VERSION)_$(BUILD_PATCH)_$(BUILD_DATE)

$(OBJ): $(O_PATH)%.o: $(S_PATH)%.c $(HDR)
	@$(CMPLC) -DBUILDR=$(BUILD_RELEASE) -DBUILDV=$(BUILD_VERSION) \
	-DBUILDP=$(BUILD_PATCH) -DDATE=$(BUILD_DATE) $< -o $@
	@$(ECHO) $(GCFIL) $<

# Check if .build exist, then incremente patch level each compilation.
# If not exist, create it with default values

$(BUILD_FILE): $(OBJ)
	@if ! test -f $(BUILD_FILE); \
	then echo $(DEFAULT_BUILD_FILE) > $(BUILD_FILE); fi
	@sed -i '.bak' "5s/$(BUILD_PATCH)/$$(echo $$(($(BUILD_PATCH) + 1)))/g" \
	$(BUILD_FILE)
	@rm $(BUILD_FILE).bak

$(PATHS):
	@$(MKDIR) $(PATHS)
	@$(foreach var,$(PATHS), $(ECHO) $(MKSHW) $(var);)

norme:
	@$(NORMR)
	@$(NORME) $(SRC) $(H_PATH)$(HNAME)
	@$(NORMD)

clean: libco
	@for i in $(OBJ); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	@$(CLSUC)

fclean: libc
	@for i in $(OBJ); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	@for i in $(PATHS); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	@$(RM_RF) $(NAME)
	@$(ECHO) $(RMSHW) $(NAME)
	@$(CLSUC)

# Libc rules

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
