NAME = philo
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread
SRCS = philosrc/philo.c philosrc/timeutils.c philosrc/handling.c philosrc/initphilos.c philosrc/observerroutine.c philosrc/philoroutine.c
OBJS = $(SRCS:%.c=%.o)

# Paths to libft directory
LIBFT_DIR = ./libft

# Library files
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Targets
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	clang $(CFLAGS) -o $(NAME) $(OBJS) -Iphilosrc -L$(LIBFT_DIR) -lft -pthread

# Rule to build object files from source files
%.o: philosrc/%.c philosrc/philo.h
	clang $(CFLAGS) -c $< -o $@

# Rule to build the libft library
$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

# Clean object files and libft
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Clean everything and remove executable
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
