CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fPIE

INCLUDES = -I/usr/include -Ilibft -Iget_next_line -Ilibprintf -Iparssing

PRINTDIR = libprintf/
PRINT = $(PRINTDIR)libftprintf.a

LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a

NAME = minishell

GNL = get_next_line/
GNL_SRC = get_next_line.c get_next_line_utils.c

SRCDIR = built-ins/
SRC = built-ins/ft_pwd.c ft_env.c ft_cd.c ft_export.c ft_unset.c ft_echo.c
PARSDIR = parssing/
PRC = parssing/minishellnorm.c process_quotes.c utils.c init_tokenz.c

#BONUSDIR = bonus/
#BONUS = bonus/

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)) $(notdir $(PRC:.c=.o)))
GNL_OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(GNL_SRC:.c=.o)))
#OBJECT_BONUS = $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_SRC:.c=.o)))

all: $(NAME)

#bonus: $(NAME_BONUS)

$(NAME): $(LIBFT) $(OBJECTS) $(GNL_OBJECTS) $(PRINT)
	$(CC) $(CFLAGS) $(OBJECTS) $(GNL_OBJECTS) -o $(NAME) $(LIBFT) $(PRINT) -lreadline -pie

# Bonus
#$(NAME_BONUS): $(LIBFT) $(OBJECT_BONUS) $(GNL_OBJECTS) $(PRINT)
#	$(CC) $(CFLAGS) $(OBJECT_BONUS) $(GNL_OBJECTS) -o $(NAME_BONUS) $(LIBFT) $(PRINT)

# Libft compiling
$(LIBFT): $(LIBFTDIR)
	@$(MAKE) -C $(LIBFTDIR) --quiet

$(OBJ_DIR)/%.o: $(SRCDIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR)/%.o: $(PARSDIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

#PRINTF compiling
$(PRINT): $(PRINTDIR)
	@$(MAKE) -C $(PRINTDIR) --quiet

# Bonus object
#$(OBJ_DIR)/%.o: $(BONUSDIR)%.c
#	mkdir -p $(OBJ_DIR)
#	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

# GNL
$(OBJ_DIR)/%.o: $(GNL)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

