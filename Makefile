

NAME		= minishell

SRCS		= readline.c utils.c builtin/utils.c builtin/cd.c builtin/echo.c \
				builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c \
				builtin/unset.c binaries/main_bin.c binaries/path_utils.c \
				exit/exit.c env/env_init.c pipe/pipe.c pipe/pipe_utils.c \
				parsing/lexer/ft_split_tokens.c parsing/lexer/nbr_tokens.c parsing/lexer/which_type_is_it.c \
				parsing/lexer/nbr_words_quotes.c parsing/lexer/what_is_len.c \
				parsing/lexer/make_str_quotes.c parsing/lexer/make_str_simple_dollar_redir.c\
				parsing/parser/preparsing.c parsing/parser/tools_parser.c parsing/parser/fill_args_parser.c \
				parsing/parser/fill_redir_parser.c parsing/parser/verif_parsing.c\
				libft/ft_strjoin.c libft/ft_split.c file/file_open.c \
				file/file_utils.c builtin/export_utils.c builtin/cd_utils.c \
				signals/sig_handlers.c signals/set_signals.c \
				parsing/parser/parser_print.c parsing/parser/do_var_existe.c \
				parsing/parser/fill_args_parser_check.c parsing/parser/fill_redir_utils.c \
				file/heredoc_utils.c exit/malloc_error.c file/stream_utils.c



OBJS		= $(SRCS:.c=.o)

CC			= gcc

RM			= rm -rf

LFT			= ./libft

CFLAGS		= -Wall -Werror -Wextra -no-pie -g -I.

LIBS		= -lreadline -L ./libft -lft

MAKE_LIB	= ${MAKE} -C ${LFT}

all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE_LIB)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:		
			$(RM) $(OBJS)
			$(MAKE_LIB) clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE_LIB) fclean

re:		fclean $(NAME)

.PHONY:		all clean fclean re
