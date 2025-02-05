NAME = philo_bonus

#CFLAGS----------------------------------------------------------------------------------

CC 	= cc
CFLAGS 	= -Wall -Wextra -Werror -I ./include_b
RM	= rm -rf
NOPRINT = --no-print-directory

#COLOURS---------------------------------------------------------------------------------

GREEN := \033[1;32m
RED := \033[1;31m
RESET := \033[0m

#FILES------------------------------------------------------------------------------------

SRCS = ./src_b/main_bonus.c ./src_b/init_bonus.c ./src_b/threads_bonus.c ./src_b/utils_bonus.c \
	./src_b/philo_routine_bonus.c ./src_b/table_routine_bonus.c

	
#OBJS--------------------------------------------------------------------------------------

OBJS = $(SRCS:.c=.o)

#Make---------------------------------------------------------------------------------------

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline 
	@echo "[100%] $(GREEN)(Minishell) Compilation  | Minishell | successful!$(RESET)"

clean:
	$(RM) $(OBJS)
	@echo "[100%] $(RED)(Minishell) Cleaning up exept compilers ..$(RESET)"

fclean:
	$(RM) $(OBJS) $(NAME)
	@echo "[100%] $(RED)(Minishell) Cleaning up...$(RESET)"

re: fclean all bonus

#RULES-------------------------------------------------------------------------------------

.PHONY:	all clean fclean re bonus

.SILENT:
