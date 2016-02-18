CC= gcc
FLAGS= -Wall -Wextra -g
SRC_ASM = src_asm/main.c \
		  src_asm/reader.c \
		  src_asm/lexer.c \
		  src_asm/parser.c \
		  src_asm/parser_token.c \
		  src_asm/parser_label.c \
		  src_asm/parser_utils.c \
		  src_asm/lexer_op.c \
		  src_asm/process_op.c \
		  src_asm/check_section.c \
		  src_asm/check_section_utils.c \
		  src_asm/print_token.c \
		  src_asm/utils.c \
		  src_asm/free_files.c \
		  src_asm/process_op_utils.c \
		  src_asm/process_op_utils_2.c \
		  src_asm/error_util.c \
		  src_common/op.c \
		  src_common/swap_bytes.c

SRC_COREWAR=

OBJ_ASM= $(SRC_ASM:.c=.o)
OBJ_COREWAR= $(SRC_COREWAR:.c=.o)

NAME_ASM=asm
NAME_COREWAR=corewar
LIB=-L./libft -lft_core -lft_list -lft_printf
DIR_LFT=./libft
INCLUDES=./libft/includes -I ./src_asm  -I ./src_common

.PHONY: clean fclean re all

.SILENT:

all: $(NAME_ASM) #$(NAME_COREWAR)

$(NAME_ASM): $(OBJ_ASM)
	(cd $(DIR_LFT) ; make )
	$(CC) -o $(NAME_ASM) $(OBJ_ASM) $(LIB) $(FLAGS)
	echo "\t\xF0\x9F\x8F\x81   Compiling \033[35m$(NAME_ASM) \033[0mDONE!"

$(NAME_COREWAR): $(OBJ_COREWAR)
	(cd $(DIR_LFT) ; make)
	$(CC) -o $(NAME_COREWAR) $(OBJ_COREWAR) $(LIB) $(FLAGS)
	echo "\t\xF0\x9F\x8F\x81   Compiling \033[35m$(NAME_COREWAR) \033[0mDONE!"

%.o: %.c
	echo "\t\xF0\x9F\x94\xA7   Building \033[34m $@ \033[0m"
	$(CC) -c $(FLAGS) -o $@ $< -I $(INCLUDES)

clean:
	(cd $(DIR_LFT) ; make clean)
	echo "\t\xF0\x9F\x92\xA3   Cleaning"
	rm -rf $(OBJ_ASM)
	rm -rf $(OBJ_COREWAR)

fclean: clean
	(cd $(DIR_LFT) ; make fclean)
	echo "\t\xF0\x9F\x9A\xBD   Full Clean"
	rm -rf $(NAME_ASM)
	rm -rf $(NAME_COREWAR)

re: fclean all
