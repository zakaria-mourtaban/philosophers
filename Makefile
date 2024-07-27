NAME = philo
CFLAGS = -Wall -Werror -Wextra -g
SRCS = philosrc/philo.c philosrc/initphilos.c philosrc/timeutils.c philosrc/handleinput.c
OBJS = $(SRCS:%.c=%.o)

# Paths to ft_printf, libft, and MinilibX directories
LIBFT_DIR = ./libft

# Library files
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Targets
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(LIBFT_DIR)/*.c
	gcc $(CFLAGS) -o $(NAME) $(OBJS) -Iphilosrc -L$(LIBFT_DIR) -lft -pthread

%.o: philosrc/%.c philosrc/philo.h
	gcc $(CFLAGS) -c $< -o $@

$(PRINTF_LIB):
	@make -C $(PRINTF_DIR)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re