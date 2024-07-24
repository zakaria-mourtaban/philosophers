NAME = philo

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
SRCS = philosrc/*.c
OBJS = $(SRCS:%.c=%.o)

# Paths to ft_printf, libft, and MinilibX directories
# PRINTF_DIR = ./ft_printf
LIBFT_DIR = ./libft
# MINILIBX_DIR = ./minilibx_linux

# Library files
# PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a
# MINILIBX_LIB = $(MINILIBX_DIR)/libmlx.a

# Targets
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) #$(PRINTF_LIB) $(MINILIBX_LIB) $(PRINTF_DIR)/*.c $(LIBFT_DIR)/*.c $(MINILIBX_DIR)/*.c
	gcc $(CFLAGS) -o $(NAME) $(OBJS) -lpthreads

%.o: philosrc/%.c philo/philo.h
	gcc $(CFLAGS) -c $< -o $@

# $(PRINTF_LIB):
# 	@make -C $(PRINTF_DIR)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

# $(MINILIBX_LIB):
# 	@make -C $(MINILIBX_DIR)

clean:
	rm -f $(OBJS)
	# $(MAKE) -C $(PRINTF_DIR) clean
	# $(MAKE) -C $(LIBFT_DIR) clean
	# $(MAKE) -C $(MINILIBX_DIR) clean

fclean: clean
	rm -f $(NAME)
	# $(MAKE) -C $(PRINTF_DIR) fclean
	# $(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re