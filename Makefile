
define MSG
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile for 42sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By arsciand fcatusse guvillat mpivet-p         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#                                                      #+#    #+#              #
#                                                     ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
endef

# Progress bar with on line output printing. This script get the maximum
# lines , then expr a compilation percentage.

ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL		=	make
%:
	  @$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
T					:=	$(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
	  -nrRf $(firstword $(MAKEFILE_LIST)) \
	  ECHO="OutputPrintable" | grep -c "OutputPrintable")
N					:=	x
C					=	$(words $N)$(eval N := x $N)
V					=	"`expr "   [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
ECHO				=	printf "\e[1A\r%s %s %s                                          \n" $V
endif

# Color

RESET_C				=	\033[m
B_C					=	\033[0;34m
Y_C					=	\033[0;33m
G_C					=	\033[0;32m
R_C					=	\033[0;31m
M_C					=	\033[0;35m
C_C					=	\033[0;36m
F_C					=	\033[35;5;108m

# Programms names

NAME				=	42sh
LNAME				=	shared_libft.a

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

S_PATH				=	srcs/
H_PATH				+=	includes/
H_PATH				+=	shared_libft/includes/
B_PATH				=	build/
O_PATH				=	build/objs/
L_PATH				=	shared_libft/

###############################################################################
#                               Modifications                                 #
###############################################################################

# Add custom dir for .o

BUILTINS			=	builtins/
CD					=	$(BUILTINS)cd/
FC					=	$(BUILTINS)fc/
HASH				=	$(BUILTINS)hash/
CMDLINE				=	cmdline/
AC					=	$(CMDLINE)auto_c/
AK					=	$(CMDLINE)action_keys/
CLIPBOARD			=	$(CMDLINE)clipboard/
HISTORY				=	$(CMDLINE)history/
HST_EXP				=	$(HISTORY)exp/
PROMPT				=	$(CMDLINE)prompt/
SUB_PROMPT			=	$(CMDLINE)sub_prompt/
CMDLINE_UTILS		=	$(CMDLINE)utils/
CORE				=	core/
DB					=	db/
EXEC				=	exec/
REDIRS				=	$(EXEC)redirections/
EXPANSIONS			=	exp/
LEXER_EXP			=	$(EXPANSIONS)lexer_exp/
PARAM_EXP			=	$(EXPANSIONS)param_exp/
JOBC				=	jobcontrol/
LPA					=	LPA/
LEXER				=	$(LPA)lexer/
PARSER				=	$(LPA)parser/
ANALYZER			=	$(LPA)analyzer/
MISC				=	misc/
SIGNALS				=	signals/

# Add previous custom dir with $(O_PATH){custom dir} to PATH varriable

PATHS				+=	$(B_PATH)
PATHS				+=	$(O_PATH)
PATHS				+=	$(O_PATH)$(BUILTINS)
PATHS				+=	$(O_PATH)$(FC)
PATHS				+=	$(O_PATH)$(CD)
PATHS				+=	$(O_PATH)$(HASH)
PATHS				+=	$(O_PATH)$(CMDLINE)
PATHS				+=	$(O_PATH)$(CMDLINE_UTILS)
PATHS				+=	$(O_PATH)$(AC)
PATHS				+=	$(O_PATH)$(AK)
PATHS				+=	$(O_PATH)$(CLIPBOARD)
PATHS				+=	$(O_PATH)$(HISTORY)
PATHS				+=	$(O_PATH)$(HST_EXP)
PATHS				+=	$(O_PATH)$(PROMPT)
PATHS				+=	$(O_PATH)$(SUB_PROMPT)
PATHS				+=	$(O_PATH)$(CORE)
PATHS				+=	$(O_PATH)$(DB)
PATHS				+=	$(O_PATH)$(EXEC)
PATHS				+=	$(O_PATH)$(REDIRS)
PATHS				+=	$(O_PATH)$(EXPANSIONS)
PATHS				+=	$(O_PATH)$(LEXER_EXP)
PATHS				+=	$(O_PATH)$(PARAM_EXP)
PATHS				+=	$(O_PATH)$(JOBC)
PATHS				+=	$(O_PATH)$(LPA)
PATHS				+=	$(O_PATH)$(LEXER)
PATHS				+=	$(O_PATH)$(PARSER)
PATHS				+=	$(O_PATH)$(ANALYZER)
PATHS				+=	$(O_PATH)$(MISC)
PATHS				+=	$(O_PATH)$(SIGNALS)

# Files

SRC					+=	$(S_PATH)$(BUILTINS)bg.c
SRC					+=	$(S_PATH)$(BUILTINS)echo.c
SRC					+=	$(S_PATH)$(BUILTINS)exit.c
SRC					+=	$(S_PATH)$(BUILTINS)export.c
SRC					+=	$(S_PATH)$(BUILTINS)fg.c
SRC					+=	$(S_PATH)$(BUILTINS)jobs.c
SRC					+=	$(S_PATH)$(BUILTINS)path_tests.c
SRC					+=	$(S_PATH)$(BUILTINS)pwd.c
SRC					+=	$(S_PATH)$(BUILTINS)set.c
SRC					+=	$(S_PATH)$(BUILTINS)test.c
SRC					+=	$(S_PATH)$(BUILTINS)type.c
SRC					+=	$(S_PATH)$(BUILTINS)unset.c

SRC					+=	$(S_PATH)$(CD)cd_change_dir.c
SRC					+=	$(S_PATH)$(CD)cd_check_path.c
SRC					+=	$(S_PATH)$(CD)cd_home.c
SRC					+=	$(S_PATH)$(CD)cd_oldpwd.c
SRC					+=	$(S_PATH)$(CD)cd_update_pwd.c
SRC					+=	$(S_PATH)$(CD)cd_use_cd_path.c
SRC					+=	$(S_PATH)$(CD)cd.c

SRC					+=	$(S_PATH)$(FC)fc_edit.c
SRC					+=	$(S_PATH)$(FC)fc_launcher.c
SRC					+=	$(S_PATH)$(FC)fc_listing.c
SRC					+=	$(S_PATH)$(FC)fc_print.c
SRC					+=	$(S_PATH)$(FC)fc_specifier.c
SRC					+=	$(S_PATH)$(FC)fc_tools.c
SRC					+=	$(S_PATH)$(FC)fc.c

SRC					+=	$(S_PATH)$(HASH)hash_dispatcher.c
SRC					+=	$(S_PATH)$(HASH)fill_hash_map.c
SRC					+=	$(S_PATH)$(HASH)fetch_hash_db.c
SRC					+=	$(S_PATH)$(HASH)get_hash.c
SRC					+=	$(S_PATH)$(HASH)hash_handler.c
SRC					+=	$(S_PATH)$(HASH)hash_key_remover.c
SRC					+=	$(S_PATH)$(HASH)hash_opt_tools.c
SRC					+=	$(S_PATH)$(HASH)hash_opt.c
SRC					+=	$(S_PATH)$(HASH)hash.c
SRC					+=	$(S_PATH)$(HASH)locate_hash.c
SRC					+=	$(S_PATH)$(HASH)resize_hash_map.c

SRC					+=	$(S_PATH)$(CMDLINE)init_termcaps.c
SRC					+=	$(S_PATH)$(CMDLINE)term_config.c

SRC					+=	$(S_PATH)$(CMDLINE_UTILS)get_var_value.c
SRC					+=	$(S_PATH)$(CMDLINE_UTILS)utils.c

SRC					+=	$(S_PATH)$(AK)check_caps.c
SRC					+=	$(S_PATH)$(AK)del_keys.c
SRC					+=	$(S_PATH)$(AK)insert_in_buffer.c
SRC					+=	$(S_PATH)$(AK)keys_comb.c
SRC					+=	$(S_PATH)$(AK)move_cursor.c
SRC					+=	$(S_PATH)$(AK)move_in_column.c
SRC					+=	$(S_PATH)$(AK)tab_key.c

SRC					+=	$(S_PATH)$(CLIPBOARD)select_text.c
SRC					+=	$(S_PATH)$(CLIPBOARD)ak_clipboard.c

SRC					+=	$(S_PATH)$(AC)auto_completion.c
SRC					+=	$(S_PATH)$(AC)ac_check_type.c
SRC					+=	$(S_PATH)$(AC)ac_display.c
SRC					+=	$(S_PATH)$(AC)ac_get_dir.c
SRC					+=	$(S_PATH)$(AC)ac_bin.c
SRC					+=	$(S_PATH)$(AC)ac_file.c
SRC					+=	$(S_PATH)$(AC)ac_var.c
SRC					+=	$(S_PATH)$(AC)ac_parser.c
SRC					+=	$(S_PATH)$(AC)ac_tilde.c
SRC					+=	$(S_PATH)$(AC)ac_tools.c

SRC					+=	$(S_PATH)$(HISTORY)save_history.c
SRC					+=	$(S_PATH)$(HISTORY)search_in_history.c
SRC					+=	$(S_PATH)$(HISTORY)walking_history.c

SRC					+=	$(S_PATH)$(HST_EXP)check_hst_exp.c
SRC					+=	$(S_PATH)$(HST_EXP)history_expansions.c
SRC					+=	$(S_PATH)$(HST_EXP)replace_buffer.c

SRC					+=	$(S_PATH)$(PROMPT)prompt.c

SRC					+=	$(S_PATH)$(SUB_PROMPT)check_backslash.c
SRC					+=	$(S_PATH)$(SUB_PROMPT)check_subprompt.c
SRC					+=	$(S_PATH)$(SUB_PROMPT)heredoc.c
SRC					+=	$(S_PATH)$(SUB_PROMPT)sub_prompt.c
SRC					+=	$(S_PATH)$(SUB_PROMPT)subprompt_tools.c
SRC					+=	$(S_PATH)$(SUB_PROMPT)subprompt_loader.c

SRC					+=	$(S_PATH)$(CORE)free_handler.c
SRC					+=	$(S_PATH)$(CORE)init_shell.c
SRC					+=	$(S_PATH)$(CORE)main.c
SRC					+=	$(S_PATH)$(CORE)shell_loader.c

SRC					+=	$(S_PATH)$(DB)db_tools.c
SRC					+=	$(S_PATH)$(DB)env_updates.c
SRC					+=	$(S_PATH)$(DB)fetch_db.c
SRC					+=	$(S_PATH)$(DB)get_opt.c
SRC					+=	$(S_PATH)$(DB)history.c
SRC					+=	$(S_PATH)$(DB)process_vars.c
SRC					+=	$(S_PATH)$(DB)ps_x.c
SRC					+=	$(S_PATH)$(DB)set_env.c
SRC					+=	$(S_PATH)$(DB)set_updates.c
SRC					+=	$(S_PATH)$(DB)special_vars.c
SRC					+=	$(S_PATH)$(DB)version.c

SRC					+=	$(S_PATH)$(EXEC)call_bin.c
SRC					+=	$(S_PATH)$(EXEC)call_builtin.c
SRC					+=	$(S_PATH)$(EXEC)launch_job.c
SRC					+=	$(S_PATH)$(EXEC)exec_process.c
SRC					+=	$(S_PATH)$(EXEC)get_bin.c
SRC					+=	$(S_PATH)$(EXEC)set_envp.c
SRC					+=	$(S_PATH)$(EXEC)status_handler.c
SRC					+=	$(S_PATH)$(EXEC)task_master.c

SRC					+=	$(S_PATH)$(REDIRS)exec_redirs.c
SRC					+=	$(S_PATH)$(REDIRS)redirs_tools.c
SRC					+=	$(S_PATH)$(REDIRS)redirs.c

SRC					+=	$(S_PATH)$(LEXER_EXP)lexer_exp.c
SRC					+=	$(S_PATH)$(LEXER_EXP)lexer_param_cmds_exp.c
SRC					+=	$(S_PATH)$(LEXER_EXP)lexer_tilde_math_exp.c

SRC					+=	$(S_PATH)$(PARAM_EXP)get_brace_param.c
SRC					+=	$(S_PATH)$(PARAM_EXP)launch_param.c
SRC					+=	$(S_PATH)$(PARAM_EXP)other_format.c
SRC					+=	$(S_PATH)$(PARAM_EXP)param_exp_tools.c
SRC					+=	$(S_PATH)$(PARAM_EXP)pos_vars.c
SRC					+=	$(S_PATH)$(PARAM_EXP)prefix_suffixe_format.c

SRC					+=	$(S_PATH)$(EXPANSIONS)assign_envp_tools.c
SRC					+=	$(S_PATH)$(EXPANSIONS)machine_expansion.c
SRC					+=	$(S_PATH)$(EXPANSIONS)expansion.c
SRC					+=	$(S_PATH)$(EXPANSIONS)quotes_backslash.c
SRC					+=	$(S_PATH)$(EXPANSIONS)inhibiteurs.c
SRC					+=	$(S_PATH)$(EXPANSIONS)tilde_cmds_math_exp.c
SRC					+=	$(S_PATH)$(EXPANSIONS)expansion_tok.c

SRC					+=	$(S_PATH)$(JOBC)background.c
SRC					+=	$(S_PATH)$(JOBC)continue.c
SRC					+=	$(S_PATH)$(JOBC)foreground.c
SRC					+=	$(S_PATH)$(JOBC)get_job.c
SRC					+=	$(S_PATH)$(JOBC)get_signal.c
SRC					+=	$(S_PATH)$(JOBC)job_utils.c
SRC					+=	$(S_PATH)$(JOBC)jobc_id.c
SRC					+=	$(S_PATH)$(JOBC)launch_process.c
SRC					+=	$(S_PATH)$(JOBC)mark_process_status.c
SRC					+=	$(S_PATH)$(JOBC)free_job_from_list.c
SRC					+=	$(S_PATH)$(JOBC)mark_job_as_stopped.c
SRC					+=	$(S_PATH)$(JOBC)notifications.c
SRC					+=	$(S_PATH)$(JOBC)wait_job.c
SRC					+=	$(S_PATH)$(JOBC)are_jobs_done.c
SRC					+=	$(S_PATH)$(JOBC)rebuild_job_command.c
SRC					+=	$(S_PATH)$(JOBC)get_last_stop_status.c
SRC					+=	$(S_PATH)$(JOBC)split_job.c

SRC					+=	$(S_PATH)$(LPA)lexer_parser_analyzer.c

SRC					+=	$(S_PATH)$(ANALYZER)analyze.c
SRC					+=	$(S_PATH)$(ANALYZER)analyzer_assign.c
SRC					+=	$(S_PATH)$(ANALYZER)analyzer_heredoc.c
SRC					+=	$(S_PATH)$(ANALYZER)analyzer_job.c
SRC					+=	$(S_PATH)$(ANALYZER)analyzer_memory.c
SRC					+=	$(S_PATH)$(ANALYZER)analyzer_name.c
SRC					+=	$(S_PATH)$(ANALYZER)analyzer_process.c
SRC					+=	$(S_PATH)$(ANALYZER)analyzer_redir.c
SRC					+=	$(S_PATH)$(ANALYZER)init_analyzer_bis.c
SRC					+=	$(S_PATH)$(ANALYZER)init_analyzer.c
SRC					+=	$(S_PATH)$(ANALYZER)analyzer_subpts.c
SRC					+=	$(S_PATH)$(ANALYZER)token_to_tab.c

SRC					+=	$(S_PATH)$(LEXER)assign_token.c
SRC					+=	$(S_PATH)$(LEXER)init_lexer.c
SRC					+=	$(S_PATH)$(LEXER)io_nbr_nwl_token.c
SRC					+=	$(S_PATH)$(LEXER)lexer.c
SRC					+=	$(S_PATH)$(LEXER)name_token.c
SRC					+=	$(S_PATH)$(LEXER)operator_token.c

SRC					+=	$(S_PATH)$(PARSER)graph.c
SRC					+=	$(S_PATH)$(PARSER)parser.c

SRC					+=	$(S_PATH)$(MISC)abs_path_tools.c
SRC					+=	$(S_PATH)$(MISC)abs_path.c
SRC					+=	$(S_PATH)$(MISC)check_args.c
SRC					+=	$(S_PATH)$(MISC)errors.c
SRC					+=	$(S_PATH)$(MISC)ft_access.c
SRC					+=	$(S_PATH)$(MISC)is_a_dir.c
SRC					+=	$(S_PATH)$(MISC)output.c
SRC					+=	$(S_PATH)$(MISC)quit_shell.c
SRC					+=	$(S_PATH)$(MISC)recall.c
SRC					+=	$(S_PATH)$(MISC)free_process_link.c

SRC					+=	$(S_PATH)$(SIGNALS)init_signals.c
SRC					+=	$(S_PATH)$(SIGNALS)sigint.c

# Headers

HDR					+=	sh42.h
HDR					+=	define.h
HDR					+=	expansion.h
HDR					+=	struct.h
HDR					+=	lexer_parser_analyzer.h
HDR					+=	command_line.h
HDR					+=	enum.h
HDR					+=	shared_libft.h

###############################################################################
#                                                                             #
###############################################################################

# Objects

OBJ					=	$(patsubst $(S_PATH)%.c, $(O_PATH)%.o, $(SRC))
LIB					=	$(L_PATH)$(LNAME) -ltermcap
vpath %.h $(H_PATH)

# Variables

DEBUG				=
CFLAGS				=	-Wall -Wextra -Werror
ifeq ($(DEBUG), g)
	CFLAGS			=	-g
else ifeq ($(DEBUG), fsanitize)
	CFLAGS			=	-fsanitize=address -g3
else ifeq ($(DEBUG), hard)
	CFLAGS			+=	-Wall -Weverything -fsanitize=address,undefined -Wno-cast-qual
	CFLAGS			+=	-Wno-missing-noreturn -Wno-disabled-macro-expansion
else ifeq ($(DEBUG), dev)
	CFLAGS			=
endif
CC					=	clang $(CFLAGS)
IFLAGS				+=	$(addprefix -I, $(H_PATH))
CMPLC				=	$(CC) -c $(IFLAGS)
CMPLO				=	$(CC) -o
BUILD				=	$(PATHS)
AR_RC				=	ar rc
RANLI				=	ranlib
RM_RF				=	/bin/rm -rf
MKDIR				=	mkdir -p
NORME				=	norminette
SLEEP				=	sleep 0.01
GCFIL				=	"- > Compiling	-"
RMSHW				=	"- - Removing	-"
MKSHW				=	"- + Creating	-"
GCSUC				=	echo "$(G_C)=====>     SUCCESS$(RESET_C)"
CLSUC				=	echo "$(R_C)=====>     DONE$(RESET_C)"
NORMD				=	echo "$(G_C)=====>     DONE$(RESET_C)"

.PHONY: all norme clean fclean re test

# Rules
make:
	echo "# **************************************************************************** #"
	echo "#                                                                              #"
	echo "#                                                         :::      ::::::::    #"
	echo "#    Makefile for 42sh                                  :+:      :+:    :+:    #"
	echo "#                                                     +:+ +:+         +:+      #"
	echo "#    By arsciand fcatusse guvillat mpivet-p         +#+  +:+       +#+         #"
	echo "#                                                 +#+#+#+#+#+   +#+            #"
	echo "#                                                      #+#    #+#              #"
	echo "#                                                     ###   ########.fr        #"
	echo "#                                                                              #"
	echo "# **************************************************************************** #"
	$(MAKE) --no-print-directory all

all: libm $(BUILD) $(NAME)

# Compilation core

ifneq ("$(wildcard $(L_PATH)$(LNAME))","")
TEST				=	shared_libft/shared_libft.a
else
TEST				=
endif

$(NAME): $(OBJ) $(BUILD_FILE) $(TEST)
	$(ECHO) $(GCFIL) $(NAME)
	$(CMPLO) $(NAME) $(OBJ) $(LIB)
	$(GCSUC)
	echo "---\nCFLAGS - =$(B_C) $(CFLAGS)$(RESET_C)\n---"
	echo "\n$(G_C)[$(BUILD_BRANCH)] $(RESET_C)$@ $(F_C) \
	v.$(BUILD_RELEASE)_$(BUILD_VERSION)_$(BUILD_PATCH)_$(BUILD_DATE) $(RESET_C) is ready !"
	cp $(NAME) \
	$(B_PATH)$(NAME)_$(BUILD_RELEASE)_$(BUILD_VERSION)_$(BUILD_PATCH)_$(BUILD_DATE)

$(OBJ): $(O_PATH)%.o: $(S_PATH)%.c $(HDR)
	$(CMPLC) -DBUILDR=$(BUILD_RELEASE) -DBUILDV=$(BUILD_VERSION) \
	-DBUILDP=$(BUILD_PATCH) -DDATE=$(BUILD_DATE) $< -o $@
	$(ECHO) $(GCFIL) $<

# Check if .build exist, then incremente patch level each compilation.
# If not exist, create it with default values

UNAME_S				:=	$(shell uname -s)

ifeq ($(UNAME_S), Darwin)
$(BUILD_FILE): $(OBJ)
	if ! test -f $(BUILD_FILE); \
	then echo $(DEFAULT_BUILD_FILE) > $(BUILD_FILE); fi
	sed -i '.bak' "5s/$(BUILD_PATCH)/$$(echo $$(($(BUILD_PATCH) + 1)))/g" \
	$(BUILD_FILE)
	rm $(BUILD_FILE).bak
else
$(BUILD_FILE): $(OBJ)
	if ! test -f $(BUILD_FILE); \
	then echo $(DEFAULT_BUILD_FILE) > $(BUILD_FILE); fi
	sed -i "5s/$(BUILD_PATCH)/$$(echo $$(($(BUILD_PATCH) + 1)))/g" \
	$(BUILD_FILE)
endif

$(PATHS):
	$(MKDIR) $(PATHS)
	$(foreach var,$(PATHS), $(ECHO) $(MKSHW) $(var);)

norme:
	$(NORMR)
	$(NORME) $(SRC) $(H_PATH)$(HNAME)
	$(NORMD)

clean: libco
	for i in $(OBJ); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	$(CLSUC)

fclean: libc
	for i in $(OBJ); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	for i in $(PATHS); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	$(RM_RF) $(NAME)
	$(ECHO) $(RMSHW) $(NAME)
	$(CLSUC)

# Libc rules

libm:
	make -C $(L_PATH)
	printf "\n"

libco:
	make clean -C $(L_PATH)

libc:
	make fclean -C $(L_PATH)

help:
	echo "Makefile for 42sh"
	echo "usage : make [VERBOSE=1] [DEBUG=g|fsanitize|hard|dev] [all|clean|fclean|re|libm|libco|libc|help]"

re:
	$(MAKE) --no-print-directory fclean all

ifndef VERBOSE
.SILENT:
endif

endif
