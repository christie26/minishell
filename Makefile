# all file
SRCS_EXEC		=	mini_exec.c \
					get_path.c \
					execute_utils.c \
					child_parent.c \
					redirection.c \
					heredoc.c \
					new_error.c

SRCS_PARSE		=	readline.c \
					parse_simple_check.c \
					parse_token.c \
					parse_expand.c \
					parse_quote_remove.c \
					parse_tree.c \
					pipeline_list_utils.c \
					redirect_list_utils.c \
					token_list_utils.c \
					signals.c

SRCS_BUILT		=	builtin_center.c \
					builtin_export.c \
					builtin_unset.c \
					builtin_env.c \
					builtin_cd.c \
					builtin_others.c \
					builtin_utils.c

# add path as their usage
DIR_EXEC		= execute/
DIR_PARSE		= parse/
DIR_BUILT		= built_in/

SRCS_EXEC		:= $(addprefix $(DIR_EXEC), $(SRCS_EXEC))
SRCS_PARSE		:= $(addprefix $(DIR_PARSE), $(SRCS_PARSE))
SRCS_BUILT		:= $(addprefix $(DIR_BUILT), $(SRCS_BUILT))

SRCS			= $(SRCS_EXEC) $(SRCS_PARSE) $(SRCS_BUILT)

# add "./src" directory
SRC_DIR			= ./src/
SRCS			:= $(addprefix $(SRC_DIR), $(SRCS))

# make object files
OBJS			:= $(SRCS:%.c=%.o)


NAME		= ./minishell
LIBFT		= ./libft/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LDFLAGS		= -fsanitize=address -g
RM			= rm -f

all:		${NAME}

.c.o:
			$(CC) $(CFLAGS) -Ilibft/includes -c $< -o $@

$(NAME): 	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -lreadline -o $(NAME)

$(LIBFT):
			make -j3 -C ./libft all

clean:
			${RM} ${OBJS}
			@make -C ./libft clean

fclean:		clean
			${RM} ${LIBFT}
			${RM} ${NAME}

re:			fclean all


.PHONY:		all clean fclean re
