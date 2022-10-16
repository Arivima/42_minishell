NAME				= minishell

LIB_DIR				= ./lib
LIBFT_DIR			= $(LIB_DIR)/libft
LIBFT_A				= $(LIBFT_DIR)/libft.a
LIB_A				= $(LIBFT_A)

BIN_BUILTIN_DIR		= ./bin

HEAD_DIR			= ./include

FILES				= \
						main.c\
						init.c\
						error.c\
						exit.c\
						# _testing.c\

PARSING_FILES		= \
						parsing_tokenizing_1.c\
						parsing_tokenizing_2.c\
						parsing_expansion_1.c\
						parsing_expansion_2.c\
						parsing_expansion_word.c\
						parsing_expansion_quote.c\

PARSING				= $(addprefix parsing/, $(PARSING_FILES))

EXECUTION_FILES		= \
						execve_bin/execution_bin_cmd.c\
						execve_bin/execution_bin_cmd_path.c\
						execve_bin/execution_bin_cmd_path2.c\
						execve_bin/execution_bin_our_exec_builtins.c\
						execution/execution_1.c\
						execution/execution_2.c\
						execution/execution_pipe_1.c\
						execution/execution_pipe_2.c\
						execution/execution_redirections_1.c\
						execution/execution_redirections_2.c\
						execution/execution_redirections_heredoc_1.c\
						execution/execution_redirections_heredoc_2.c\
						signal.c\

EXECUTION			= $(addprefix execution/, $(EXECUTION_FILES))

BUILTIN_FILES       = \
						cd.c\
						cd_2.c\
						env.c\
						pwd.c\
						echo.c\
						export.c\
						export_print.c\
						unset.c\
						exit_cmd.c\

BUILTIN             = $(addprefix execution/builtin/, $(BUILTIN_FILES))

UTILS_FILES			= \
						utils_lists_data_1.c\
						utils_lists_data_2.c\
						utils_lists_files_1.c\
						utils_lists_files_2.c\
						utils_lists_param_1_1.c\
						utils_lists_param_1_2.c\
						utils_lists_param_2.c\
						utils_parsing.c\
						utils_exec.c\
						utils_other.c\

UTILS				= $(addprefix utils/, $(UTILS_FILES))

SRCS_DIR			=	./srcs
SRCS				= \
						$(addprefix $(SRCS_DIR)/,$(FILES))\
						$(addprefix $(SRCS_DIR)/,$(PARSING))\
						$(addprefix $(SRCS_DIR)/,$(EXECUTION))\
						$(addprefix $(SRCS_DIR)/,$(BUILTIN))\
						$(addprefix $(SRCS_DIR)/,$(UTILS))\

OBJS_DIR			=	./objs
OBJS				= $(patsubst $(SRCS_DIR)%,$(OBJS_DIR)%,$(SRCS:.c=.o))

INCLUDES			= -I $(LIBFT_DIR) -I $(BIN_BUILTIN_DIR) -I $(HEAD_DIR)
CFLAGS 				= -Wall -Wextra -Werror $(INCLUDES) -g #-fsanitize=address

GREEN 				= \033[01;32m
RESET 				= \033[00m

all:				$(NAME)

$(NAME):			libraries $(OBJS) bin_builtins
					@gcc -g $(CFLAGS) $(OBJS) $(LIB_A) -o $(NAME) -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include -lreadline -ltermcap
					@echo "$(GREEN)$(NAME) successfully compiled $(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
					@mkdir -p $(@D)
					@gcc -c -g $(CFLAGS) $< -o $@

$(OBJS): 			| $(OBJS_DIR)

$(OBJS_DIR):
					@mkdir $(OBJS_DIR)

libraries:			
					@printf "Making libft..." && make -C $(LIBFT_DIR)

bin_builtins:
					@printf "Making bin builtins..." && make -C $(BIN_BUILTIN_DIR)

clean:				
					@make clean -C $(LIBFT_DIR)
					@make clean -C $(BIN_BUILTIN_DIR)
					@rm -f $(OBJS)
					@rm -f "minishell_heredoc.tmp"
					@echo "$(GREEN)Successfully cleaned objects - $(NAME)$(RESET)"

fclean: 			clean
					@make fclean -C $(LIBFT_DIR)
					@make fclean -C $(BIN_BUILTIN_DIR)
					@rm -f $(OBJS)
					@rm -f $(NAME)
					@rm -rf $(OBJS_DIR)
					@echo "$(GREEN)Successfully forced cleaned - $(NAME)$(RESET)"

bis:				
					@rm -f $(OBJS)
					@rm -f $(NAME)
					@rm -rf $(OBJS_DIR)
					@echo "$(GREEN)Successfully cleaned binary and objects  - $(NAME)$(RESET)"
					@make

run:				bis
					@./minishell
					@echo "$(GREEN)Successfully executed $(NAME)$(RESET)"


re: 				fclean all
.PHONY: 			all clean fclean re libraries builtins bis run
