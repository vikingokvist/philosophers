NAME = philo

#CFLAGS----------------------------------------------------------------------------------

CC 	= gcc
CFLAGS 	= -Wall -Wextra -Werror -I ./includes -g3 -fsanitize=thread
RM	= rm -rf
NOPRINT = --no-print-directory

#COLOURS---------------------------------------------------------------------------------

GREEN := \033[1;32m
RED := \033[1;31m
RESET := \033[0m

#FILES------------------------------------------------------------------------------------

SRCS = ./src/main.c ./src/init.c ./src/free_table.c \
	./src/create_threads.c ./src/utils.c ./src/do_routine.c

	
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
