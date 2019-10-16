CFILE= srcs/main.c srcs/stack_char.c srcs/stack_int.c srcs/function.c srcs/help_function.c
NAME= eval_expr
all:
	@gcc $(CFILE) -o $(NAME) -I ./includes
clean:
	@rm -f $(NAME)
fclean: clean
	@rm -f $(NAME)
.PHONY: all clean fclean
