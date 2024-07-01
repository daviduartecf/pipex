CC = cc -g
NAME = pipex
FT_PRINTF = ft_printf/libftprintf.a
FLAGS = -Wall -Werror -Wextra
SRCS = parse-args.c free_functions.c parse_utils.c
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${FT_PRINTF}:
	@make --silent -C ft_printf

${NAME}: ${OBJS} ${FT_PRINTF}
	@echo "\033[0;32mCompiling program...\033[0m"
	@${CC} ${OBJS} ${FT_PRINTF} ${FLAGS} -o ${NAME}
	@echo "\033[0;32mpipex successfully compiled.\033[0m"

%.o: %.c
	@${CC} -c $< -o $@ -Wall -Werror -Wextra

clean:
	@rm -f ${OBJS}
	@make --no-print-directory -C ft_printf/ fclean

fclean:	clean
	@rm ${NAME}

re: fclean all


.PHONY : all clean fclean re
