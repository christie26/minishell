
#####

SRCS_EXEC		=	main_exec.c \
					mini_echo.c

SRCS_PARSE		=	testfile.c

#####

DIR_EXEC		= execute/
DIR_PARSE		= parse/

SRCS_EXEC		:= $(addprefix $(DIR_EXEC), $(SRCS_EXEC))
SRCS_PARSE		:= $(addprefix $(DIR_PARSE), $(SRCS_PARSE))

SRCS			= $(SRCS_EXEC) $(SRCS_PARSE)
OBJS			:= $(SRCS:%.c=%.o)

#####

SRC_DIR			= ./src/
SRCS			:= $(addprefix $(SRC_DIR), $(SRCS))

OBJ_DIR 		= ./obj/
OBJS			:= $(addprefix $(OBJ_DIR), $(OBJS))

NAME		= ./mini
LIBFT		= ./libft/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LDFLAGS		= -fsanitize=address
RM			= rm -f

all:		${NAME}

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)
			mkdir -p $(OBJ_DIR)$(DIR_EXEC)
			mkdir -p $(OBJ_DIR)$(DIR_PARSE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -Ilibft -c $< -o $@

$(NAME): 	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

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
