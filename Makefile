FILES_C = src/main.c src/read.c src/utils.c src/coors.c src/draw.c src/matrices.c
FILES_O = main.o read.o coors.o utils.o draw.o matrices.o
NAME = fdf
FLAGS = -Wall -Wextra -Werror
FRAMEWORKS = -framework OpenGL -framework AppKit

all: $(NAME)

lft:
	@make -C libft/ all

$(NAME): lft
	@echo "\033[0;5;33mMaking minilibx\033[0m"
	@make -C minilibx/ all
	@echo "\033[0;32mFinished making \033[97;40mminilibx\033[0m"
	@cp minilibx/libmlx.a ./
	@cp libft/libft.a ./
	@echo "\033[0;5;33mCompiling and building\033[0m"
	@gcc -c $(FLAGS) $(FILES_C) -I ./includes -I ./minilibx
	@gcc -o $(NAME) $(FLAGS) $(FILES_O) -I ./includes -I ./minilibx $(FRAMEWORKS) -L . -lft -lmlx
	@echo "\033[0;32mFinished building \033[40;97m$(NAME)\033[0m"

clean:
	@/bin/rm -f $(FILES_O) $(FILES_O)
	@make -C libft/ clean
	@make -C minilibx/ clean

fclean:
	@/bin/rm -f $(FILES_O) $(FILES_O)
	@/bin/rm -f $(NAME)
	@/bin/rm -f libft.a
	@/bin/rm -f libmlx.a
	@make -C libft/ fclean
	@make -C minilibx/ clean

re:	fclean all

test:
	@echo "\033[0;34mRemaking for test\033[0m"
	@rm fdf
	@gcc -c $(FLAGS) $(FILES_C) -I ./includes -I ./minilibx
	@gcc -o $(NAME) $(FLAGS) $(FILES_O) -I ./includes -I ./minilibx $(FRAMEWORKS) -L . -lft -lmlx

retest: test
