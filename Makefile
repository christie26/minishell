# all file
SRCS_EXEC		=	mini_exec.c \
					get_path.c \
					utils.c \
					child_parent.c \
					heredoc.c

SRCS_PARSE		=	readline.c \
					pipeline_list_utils.c \
					redirect_list_utils.c

SRCS_BUILT		=	built_in.c

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


NAME		= ./mini
LIBFT		= ./libft/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LDFLAGS		= -fsanitize=address
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
