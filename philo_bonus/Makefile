NAME = philo_bonus

#CFLAGS----------------------------------------------------------------------------------

CC 	= cc
CFLAGS 	= -Wall -Wextra -Werror -I ./include
RM	= rm -rf
NOPRINT = --no-print-directory

#COLOURS---------------------------------------------------------------------------------

GREEN := \033[1;32m
RED := \033[1;31m
RESET := \033[0m

#FILES------------------------------------------------------------------------------------

SRCS = ./src/main.c ./src/init.c ./src/simulation.c ./src/utils.c \
	./src/philo_routine.c ./src/table_routine.c ./src/semaphores.c

	
#OBJS--------------------------------------------------------------------------------------

OBJS = $(SRCS:.c=.o)

#Make---------------------------------------------------------------------------------------

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread -lrt
	@echo "[100%] $(GREEN)(Philosophers) Compilation successful!$(RESET)"

clean:
	$(RM) $(OBJS)
	@echo "[100%] $(RED)(Philosophers) Cleaning up objects...$(RESET)"

fclean:
	$(RM) $(OBJS) $(NAME)
	@echo "[100%] $(RED)(Philosophers) Cleaning up executable...$(RESET)"

re: fclean all bonus

#RULES-------------------------------------------------------------------------------------

.PHONY:	all clean fclean re bonus

.SILENT:
