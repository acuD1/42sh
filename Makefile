define MSG
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile for 42sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By arsciand fcatusse guvillat                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#                                                      #+#    #+#              #
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

# Build information that can be added the predefines buffer at compilation

BUILD_FILE			=	.build
BUILD_DATE			=	$$(date +'%Y%m%d')
BUILD_BRANCH		=	$$(git symbolic-ref HEAD 2>/dev/null | cut -d"/" -f 3)
BUILD_RELEASE		=	$$(awk 'NR==3 {print $$3}' $(BUILD_FILE))
BUILD_VERSION		=	$$(awk 'NR==4 {print $$3}' $(BUILD_FILE))
BUILD_PATCH			=	$$(awk 'NR==5 {print $$3}' $(BUILD_FILE))
DEFAULT_BUILD_FILE	=	"Build information, patch level is incremented at \
compilation.\n\nRELEASE\t=\t0\nVERSION\t=\t0\nPATCH\t=\t0"

# Dir/Files Path (Do not modify)

S_PATH = srcs/
H_PATH += includes/
H_PATH += shared_libft/includes/
B_PATH = build/
O_PATH = build/objs/
L_PATH = shared_libft/

###############################################################################
#                               Modifications                                 #
###############################################################################

# Add custom dir for .o

CORE		=	core/
DB			=	db/
BUILTINS	=	builtins/
COMMANDLINE	=	command_line/
EXEC		=	exec/

# Add previous custom dir with $(O_PATH){custom dir} to PATH varriable

PATHS		+=	$(B_PATH)
PATHS		+=	$(O_PATH)
PATHS		+=	$(O_PATH)$(BUILTINS)
PATHS		+=	$(O_PATH)$(COMMANDLINE)
PATHS		+=	$(O_PATH)$(CORE)
PATHS		+=	$(O_PATH)$(DB)
PATHS		+=	$(O_PATH)$(EXEC)

# Files

#SRC			+=	$(S_PATH)$(BUILTINS)check_builtins.c
#SRC			+=	$(S_PATH)$(BUILTINS)exit.c
#SRC			+=	$(S_PATH)$(BUILTINS)history.c

SRC			+=	$(S_PATH)$(COMMANDLINE)check_caps.c
SRC			+=	$(S_PATH)$(COMMANDLINE)del_keys.c
SRC			+=	$(S_PATH)$(COMMANDLINE)insert_in_buffer.c
SRC			+=	$(S_PATH)$(COMMANDLINE)move_cursor.c
SRC			+=	$(S_PATH)$(COMMANDLINE)prompt.c
SRC			+=	$(S_PATH)$(COMMANDLINE)save_history.c
SRC			+=	$(S_PATH)$(COMMANDLINE)auto_completion.c
SRC			+=	$(S_PATH)$(COMMANDLINE)auto_complete_current_dir.c
SRC			+=	$(S_PATH)$(COMMANDLINE)auto_complete_buffer.c
SRC			+=	$(S_PATH)$(COMMANDLINE)auto_complete_bin.c
SRC			+=	$(S_PATH)$(COMMANDLINE)init_termcaps.c
SRC			+=	$(S_PATH)$(COMMANDLINE)term_config.c
SRC			+=	$(S_PATH)$(COMMANDLINE)check_quotes.c
SRC			+=	$(S_PATH)$(COMMANDLINE)multiline.c

SRC		+=	$(S_PATH)$(CORE)42sh.c
SRC		+=	$(S_PATH)$(CORE)load_prompt.c
SRC		+=	$(S_PATH)$(CORE)output.c
SRC		+=	$(S_PATH)$(CORE)free_handler.c

SRC		+=	$(S_PATH)$(DB)init_shell.c
SRC		+=	$(S_PATH)$(DB)get_opt.c
SRC		+=	$(S_PATH)$(DB)set_env.c
SRC		+=	$(S_PATH)$(DB)fetch_db.c
SRC		+=	$(S_PATH)$(DB)get_tokens.c

SRC		+=	$(S_PATH)$(EXEC)exec_process.c
SRC		+=	$(S_PATH)$(EXEC)exec_handler.c
SRC		+=	$(S_PATH)$(EXEC)get_bin.c
SRC		+=	$(S_PATH)$(EXEC)set_envp.c

SRC		+=	$(S_PATH)dev.c
# Headers

HDR			+=	sh42.h
HDR			+=	define.h
HDR			+=	struct.h
HDR			+=	builtins.h
HDR			+=	command_line.h
HDR			+=	shared_libft.h
###############################################################################
#                                                                             #
###############################################################################

# Objects

OBJ = $(patsubst $(S_PATH)%.c, $(O_PATH)%.o, $(SRC))
LIB = $(L_PATH)$(LNAME) -ltermcap -no-pie
vpath %.h $(H_PATH)

# Variables

C_GCC = gcc $(CFLAG)
IFLAGS += $(addprefix -I, $(H_PATH))
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
else ifeq ($(DEBUG), dev)
	CFLAG =
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

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
$(BUILD_FILE): $(OBJ)
	@if ! test -f $(BUILD_FILE); \
	then echo $(DEFAULT_BUILD_FILE) > $(BUILD_FILE); fi
	@sed -i '.bak' "5s/$(BUILD_PATCH)/$$(echo $$(($(BUILD_PATCH) + 1)))/g" \
	$(BUILD_FILE)
	@rm $(BUILD_FILE).bak
else
$(BUILD_FILE): $(OBJ)
	@if ! test -f $(BUILD_FILE); \
	then echo $(DEFAULT_BUILD_FILE) > $(BUILD_FILE); fi
	@sed -i "5s/$(BUILD_PATCH)/$$(echo $$(($(BUILD_PATCH) + 1)))/g" \
	$(BUILD_FILE)
endif

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
