# all file
SRCS_EXEC		=	#main_exec.c \
					built_in.c	\
					execute_center.c \
					utils.c

SRCS_PARSE		=	testfile.c \
					parse_utils.c \
					readline.c

# add path as their usage
DIR_EXEC		= execute/
DIR_PARSE		= parse/

SRCS_EXEC		:= $(addprefix $(DIR_EXEC), $(SRCS_EXEC))
SRCS_PARSE		:= $(addprefix $(DIR_PARSE), $(SRCS_PARSE))

SRCS			= $(SRCS_EXEC) $(SRCS_PARSE)

# add "./src" directory
SRC_DIR			= ./src/
SRCS			:= $(addprefix $(SRC_DIR), $(SRCS))

# make object files
OBJS			:= $(SRCS:%.c=%.o)
# OBJS_PARSE		:= $(SRCS_PARSE:%.c=%.o)


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
# $(NAME): 	$(OBJS_PARSE) $(LIBFT)
# $(CC) $(CFLAGS) $(OBJS_PARSE) -L./libft -lft -lreadline -o $(NAME)

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
