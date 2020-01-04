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
ECHO = printf "\e[1A\r%s %s %s                                          \n" $V
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
BUILD_BRANCH			=	$$(git symbolic-ref HEAD 2>/dev/null | cut -d"/" -f 3)
BUILD_RELEASE			=	$$(awk 'NR==3 {print $$3}' $(BUILD_FILE))
BUILD_VERSION			=	$$(awk 'NR==4 {print $$3}' $(BUILD_FILE))
BUILD_PATCH			=	$$(awk 'NR==5 {print $$3}' $(BUILD_FILE))
DEFAULT_BUILD_FILE		=	"Build information, patch level is incremented at \
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
JOBC		=	jobcontrol/
SIGNALS		=	signals/
DB			=	db/
BUILTINS	=	builtins/
BLT_FC		=	builtins/fc/
REDIRS		=	redirections/
COMMANDLINE	=	command_line/
AC		=	command_line/auto_completion/
AK		=	command_line/action_keys/
HISTORY		=	command_line/history/
PROMPT		=	command_line/prompt/
EXEC		=	exec/
LEXER		= 	lexer_parser_analyzer/lexer/
PARSER		= 	lexer_parser_analyzer/parser/
ANALYZER	= 	lexer_parser_analyzer/analyzer/
EXPANSIONS	= 	expansions/
MISC		=	misc/
HASH		=	$(EXEC)hash_map/

# Add previous custom dir with $(O_PATH){custom dir} to PATH varriable

PATHS		+=	$(B_PATH)
PATHS		+=	$(O_PATH)
PATHS		+=	$(O_PATH)$(JOBC)
PATHS		+=	$(O_PATH)$(SIGNALS)
PATHS		+=	$(O_PATH)$(BUILTINS)
PATHS		+=	$(O_PATH)$(BLT_FC)
PATHS		+=	$(O_PATH)$(COMMANDLINE)
PATHS		+=	$(O_PATH)$(AC)
PATHS		+=	$(O_PATH)$(AK)
PATHS		+=	$(O_PATH)$(HISTORY)
PATHS		+=	$(O_PATH)$(CORE)
PATHS		+=	$(O_PATH)$(DB)
PATHS		+=	$(O_PATH)$(EXEC)
PATHS		+=	$(O_PATH)$(EXEC)$(REDIRS)
PATHS		+=	$(O_PATH)$(LEXER)
PATHS		+=	$(O_PATH)$(PARSER)
PATHS		+=	$(O_PATH)$(ANALYZER)
PATHS		+=	$(O_PATH)$(EXPANSIONS)
PATHS		+=	$(O_PATH)$(HASH)
PATHS		+=	$(O_PATH)$(MISC)
PATHS		+=	$(O_PATH)$(PROMPT)

# Files

SRC		+=	$(S_PATH)$(PROMPT)prompt.c
SRC		+=	$(S_PATH)$(PROMPT)check_subprompt.c
SRC		+=	$(S_PATH)$(PROMPT)check_backslash.c
SRC		+=	$(S_PATH)$(PROMPT)sub_prompt.c

SRC		+=	$(S_PATH)$(EXPANSIONS)expansion.c
SRC		+=	$(S_PATH)$(EXPANSIONS)math_expansion.c
SRC		+=	$(S_PATH)$(EXPANSIONS)cmd_subs_expansion.c
SRC		+=	$(S_PATH)$(EXPANSIONS)param_expansion.c
SRC		+=	$(S_PATH)$(EXPANSIONS)tilde_expansion.c


SRC			+=	$(S_PATH)$(COMMANDLINE)init_termcaps.c
SRC			+=	$(S_PATH)$(COMMANDLINE)term_config.c
SRC			+=	$(S_PATH)$(COMMANDLINE)utils.c
SRC			+=	$(S_PATH)$(COMMANDLINE)xfunctions.c

SRC		+=	$(S_PATH)lexer_parser_analyzer/lexer_parser_analyzer.c
SRC		+=	$(S_PATH)lexer_parser_analyzer/tmp_debug.c

SRC		+=	$(S_PATH)$(LEXER)assign_token.c
SRC		+=	$(S_PATH)$(LEXER)init_lexer.c
SRC		+=	$(S_PATH)$(LEXER)lexer.c
SRC		+=	$(S_PATH)$(LEXER)name_token.c
SRC		+=	$(S_PATH)$(LEXER)io_nbr_nwl_token.c
SRC		+=	$(S_PATH)$(LEXER)operator_token.c
SRC		+=	$(S_PATH)$(LEXER)expansion_token.c
SRC		+=	$(S_PATH)$(LEXER)expansion_token_bis.c
SRC		+=	$(S_PATH)$(LEXER)tmp_debug.c

SRC		+=	$(S_PATH)$(PARSER)parser.c
SRC		+=	$(S_PATH)$(PARSER)graph.c

SRC		+=	$(S_PATH)$(ANALYZER)analyze.c
SRC		+=	$(S_PATH)$(ANALYZER)analyzer_name.c
SRC		+=	$(S_PATH)$(ANALYZER)analyzer_assign.c
SRC		+=	$(S_PATH)$(ANALYZER)analyzer_memory.c
SRC		+=	$(S_PATH)$(ANALYZER)analyzer_job.c
SRC		+=	$(S_PATH)$(ANALYZER)analyzer_process.c
SRC		+=	$(S_PATH)$(ANALYZER)analyzer_redir.c
SRC		+=	$(S_PATH)$(ANALYZER)printanalyze.c
SRC		+=	$(S_PATH)$(ANALYZER)init_analyzer.c
SRC		+=	$(S_PATH)$(ANALYZER)init_analyzer_bis.c


SRC			+=	$(S_PATH)dev.c

SRC			+=	$(S_PATH)$(JOBC)background.c
SRC			+=	$(S_PATH)$(JOBC)continue.c
SRC			+=	$(S_PATH)$(JOBC)foreground.c
SRC			+=	$(S_PATH)$(JOBC)job_utils.c
SRC			+=	$(S_PATH)$(JOBC)launch_process.c
#SRC			+=	$(S_PATH)$(JOBC)launch_job.c
SRC			+=	$(S_PATH)$(JOBC)notifications.c
SRC			+=	$(S_PATH)$(JOBC)wait_job.c

SRC			+=	$(S_PATH)$(HISTORY)save_history.c
SRC			+=	$(S_PATH)$(HISTORY)search_in_history.c
SRC			+=	$(S_PATH)$(HISTORY)history_expansions.c
SRC			+=	$(S_PATH)$(HISTORY)check_hst_expansions.c

SRC			+=	$(S_PATH)$(AK)check_caps.c
SRC			+=	$(S_PATH)$(AK)del_keys.c
SRC			+=	$(S_PATH)$(AK)insert_in_buffer.c
SRC			+=	$(S_PATH)$(AK)move_cursor.c
SRC			+=	$(S_PATH)$(AK)keys_comb.c

SRC			+=	$(S_PATH)$(AC)auto_completion.c
SRC			+=	$(S_PATH)$(AC)ac_current_dir.c
SRC			+=	$(S_PATH)$(AC)ac_buffer.c
SRC			+=	$(S_PATH)$(AC)ac_bin.c
SRC			+=	$(S_PATH)$(AC)ac_directories.c
SRC			+=	$(S_PATH)$(AC)ac_tools.c

SRC			+=	$(S_PATH)$(DB)get_opt.c
SRC			+=	$(S_PATH)$(DB)set_env.c
SRC			+=	$(S_PATH)$(DB)fetch_db.c
SRC			+=	$(S_PATH)$(DB)env_updates.c
SRC			+=	$(S_PATH)$(DB)set_updates.c
SRC			+=	$(S_PATH)$(DB)db_tools.c
SRC			+=	$(S_PATH)$(DB)history.c
SRC			+=	$(S_PATH)$(DB)version.c
SRC			+=	$(S_PATH)$(DB)special_vars.c
SRC			+=	$(S_PATH)$(DB)process_vars.c

SRC			+=	$(S_PATH)$(BUILTINS)set.c
SRC			+=	$(S_PATH)$(BUILTINS)unset.c
SRC			+=	$(S_PATH)$(BUILTINS)export.c
SRC			+=	$(S_PATH)$(BUILTINS)exit.c
SRC			+=	$(S_PATH)$(BUILTINS)cd.c
SRC			+=	$(S_PATH)$(BUILTINS)echo.c
SRC			+=	$(S_PATH)$(BUILTINS)pwd.c
SRC			+=	$(S_PATH)$(BUILTINS)type.c

#SRC			+=	$(S_PATH)$(BLT_FC)fc.c
#SRC			+=	$(S_PATH)$(BLT_FC)fc_edit.c
#SRC			+=	$(S_PATH)$(BLT_FC)fc_reverse.c
#SRC			+=	$(S_PATH)$(BLT_FC)fc_specifier.c
#SRC			+=	$(S_PATH)$(BLT_FC)fc_listing.c

SRC			+=	$(S_PATH)$(MISC)errors.c
SRC			+=	$(S_PATH)$(MISC)abs_path.c
SRC			+=	$(S_PATH)$(MISC)ft_access.c
SRC			+=	$(S_PATH)$(MISC)recall.c
SRC			+=	$(S_PATH)$(MISC)check_args.c
SRC			+=	$(S_PATH)$(MISC)is_a_dir.c
SRC			+=	$(S_PATH)$(MISC)quit_shell.c

SRC			+=	$(S_PATH)$(SIGNALS)sigint.c
SRC			+=	$(S_PATH)$(SIGNALS)init_signals.c

SRC			+=	$(S_PATH)$(EXEC)task_master.c
SRC			+=	$(S_PATH)$(EXEC)status_handler.c
SRC			+=	$(S_PATH)$(EXEC)exec_process.c
SRC			+=	$(S_PATH)$(EXEC)dispatcher.c
SRC			+=	$(S_PATH)$(EXEC)call_bin.c
SRC			+=	$(S_PATH)$(EXEC)call_builtin.c
SRC			+=	$(S_PATH)$(EXEC)get_bin.c
SRC			+=	$(S_PATH)$(EXEC)set_envp.c
SRC			+=	$(S_PATH)$(EXEC)$(REDIRS)exec_redirs.c
SRC			+=	$(S_PATH)$(EXEC)$(REDIRS)redirs.c
SRC			+=	$(S_PATH)$(EXEC)$(REDIRS)redirs_tools.c


SRC			+=	$(S_PATH)$(HASH)add_hash_map.c
SRC			+=	$(S_PATH)$(HASH)fetch_hash_db.c
SRC			+=	$(S_PATH)$(HASH)get_hash.c
SRC			+=	$(S_PATH)$(HASH)locate_hash.c
SRC			+=	$(S_PATH)$(HASH)resize_hash_map.c


SRC			+=	$(S_PATH)$(CORE)42sh.c
SRC			+=	$(S_PATH)$(CORE)init_shell.c
SRC			+=	$(S_PATH)$(CORE)load_prompt.c
SRC			+=	$(S_PATH)$(CORE)load_noi_mode.c
SRC			+=	$(S_PATH)$(CORE)output.c
SRC			+=	$(S_PATH)$(CORE)free_handler.c

# Headers

HDR			+=	sh42.h
HDR			+=	define.h
HDR			+=	expansion.h
HDR			+=	struct.h
HDR			+=	lexer_parser_analyzer.h
HDR			+=	command_line.h
HDR			+=	shared_libft.h
###############################################################################
#                                                                             #
###############################################################################

# Objects

OBJ = $(patsubst $(S_PATH)%.c, $(O_PATH)%.o, $(SRC))

# Comment -no-pie flag if an error occured
LIB = $(L_PATH)$(LNAME) -ltermcap #-no-pie
vpath %.h $(H_PATH)

# Variables

C_GCC = clang $(CFLAG)
IFLAGS += $(addprefix -I, $(H_PATH))
CMPLC = $(C_GCC) -c $(IFLAGS)
CMPLO = $(C_GCC) -o
BUILD = $(PATHS)
AR_RC = ar rc
RANLI = ranlib
CFLAG = -Wall -Wextra -Werror -g
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
	CFLAG = -Wall -Wextra -Werror -g
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
