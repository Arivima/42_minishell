CD					= our_cd
ECHO				= our_echo
ENV					= our_env
EXPORT				= our_export
PWD					= our_pwd
UNSET				= our_unset
EXIT				= our_exit

LIB_PATH			= ../lib/libft/
LIB					= $(LIB_PATH)libft.a

CD_SRCS				= bin_cd.c bin_cd_2.c $(UTILS_SRCS) bin_error.c
ECHO_SRCS			= bin_echo.c $(UTILS_SRCS) bin_error.c
ENV_SRCS			= bin_env.c $(UTILS_SRCS) bin_error.c
EXPORT_SRCS			= bin_export.c bin_export_print.c $(UTILS_SRCS) bin_error.c
PWD_SRCS			= bin_pwd.c $(UTILS_SRCS) bin_error.c
UNSET_SRCS			= bin_unset.c $(UTILS_SRCS) bin_error.c
EXIT_SRCS			= bin_exit_cmd.c bin_exit.c $(UTILS_SRCS) bin_error.c

UTILS_FILES			= \
						bin_utils_lists_data_1.c\
						bin_utils_lists_data_2.c\
						bin_utils_lists_files_1.c\
						bin_utils_lists_files_2.c\
						bin_utils_lists_param_1_1.c\
						bin_utils_lists_param_1_2.c\
						bin_utils_lists_param_2.c\
						bin_utils_parsing.c\
						bin_utils_other.c\

UTILS_SRCS			= $(addprefix ./utils/, $(UTILS_FILES))

CD_OBJS				= $(CD_SRCS:.c=.o)
ECHO_OBJS			= $(ECHO_SRCS:.c=.o)
ENV_OBJS			= $(ENV_SRCS:.c=.o)
EXPORT_OBJS			= $(EXPORT_SRCS:.c=.o)
PWD_OBJS			= $(PWD_SRCS:.c=.o)
UNSET_OBJS			= $(UNSET_SRCS:.c=.o)
EXIT_OBJS			= $(EXIT_SRCS:.c=.o)

CC					= gcc

CFLAGS				= -Wall -Wextra -Werror -g -I libft #-fsanitize=address

GREEN				= '\x1b[32m'
YELLOW				= '\x1b[33m'
RED					= '\x1b[31m'
MAGENTA				= '\x1b[35m'
CYAN				= '\x1b[36m'
GRAY				= '\x1b[2;37m'
CURSIVE				= '\x1b[3m'
RESET				= '\x1b[0m'

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:				subsystem $(CD) $(ECHO) $(ENV) $(EXPORT) $(PWD) $(UNSET) $(EXIT)

subsystem:
					@make all -C $(LIB_PATH)

$(CD):				$(CD_OBJS)
					@ $(CC) $(CFLAGS) -o $(CD) $(CD_OBJS) $(LIB)
					@echo $(GREEN)$(CURSIVE)"Cd has been compiled\n"$(RESET)

$(ECHO):			$(ECHO_OBJS)
					@ $(CC) $(CFLAGS) -o $(ECHO) $(ECHO_OBJS) $(LIB)
					@echo $(GREEN)$(CURSIVE)"Echo has been compiled\n"$(RESET)

$(ENV):				$(ENV_OBJS)
					@ $(CC) $(CFLAGS) -o $(ENV) $(ENV_OBJS) $(LIB)
					@echo $(GREEN)$(CURSIVE)"Env has been compiled\n"$(RESET)

$(EXPORT):			$(EXPORT_OBJS)
					@ $(CC) $(CFLAGS) -o $(EXPORT) $(EXPORT_OBJS) $(LIB)
					@echo $(GREEN)$(CURSIVE)"Export has been compiled\n"$(RESET)

$(PWD):				$(PWD_OBJS)
					@ $(CC) $(CFLAGS) -o $(PWD) $(PWD_OBJS) $(LIB)
					@echo $(GREEN)$(CURSIVE)"Pwd has been compiled\n"$(RESET)

$(UNSET):			$(UNSET_OBJS)
					@ $(CC) $(CFLAGS) -o $(UNSET) $(UNSET_OBJS) $(LIB)
					@echo $(GREEN)$(CURSIVE)"Unset has been compiled\n"$(RESET)

$(EXIT):			$(EXIT_OBJS)
					@ $(CC) $(CFLAGS) -o $(EXIT) $(EXIT_OBJS) $(LIB)
					@echo $(GREEN)$(CURSIVE)"Exit has been compiled\n"$(RESET)

clean:
					@make clean -C $(LIB_PATH)
					@rm -f $(CD_OBJS) $(ECHO_OBJS) $(ENV_OBJS) $(EXPORT_OBJS) $(PWD_OBJS) $(UNSET_OBJS) $(EXIT_OBJS)

fclean:				clean
					@make fclean -C $(LIB_PATH)
					@rm -f $(CD) $(ECHO) $(ENV) $(EXPORT) $(PWD) $(UNSET) $(EXIT)

re:					fclean all

.PHONY:				all subsystem clean fclean re
