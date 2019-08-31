LIBFT_OBJ_DIR = ./libft/bin/
OBJ_DIR = ./bin/

SRC = libft/ft_printf/ft_printf.c libft/ft_atoi.c libft/ft_bzero.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c \
	  libft/ft_isprint.c libft/ft_itoa.c libft/ft_lstadd.c libft/ft_lstdel.c libft/ft_lstdelelem.c libft/ft_lstdelone.c libft/ft_lstiter.c libft/ft_lstmap.c \
	  libft/ft_lstnew.c libft/ft_memalloc.c libft/ft_memccpy.c libft/ft_memchr.c libft/ft_memcpy.c libft/ft_memdel.c libft/ft_memmove.c libft/ft_memset.c \
	  libft/ft_putchar.c libft/ft_putchar_fd.c libft/ft_putendl.c libft/ft_putendl_fd.c libft/ft_putnbr.c libft/ft_putnbr_fd.c libft/ft_putstr.c \
	  libft/ft_putstr_fd.c libft/ft_str_is_alpha.c libft/ft_str_is_lowercase.c libft/ft_str_is_numeric.c libft/ft_str_is_uppercase.c \
	  libft/ft_str_to_lower.c libft/ft_str_to_upper.c libft/ft_strcat.c libft/ft_strchr.c libft/ft_strclr.c libft/ft_strcmp.c libft/ft_strcpy.c \
	  libft/ft_strdel.c libft/ft_strdup.c libft/ft_strequ.c libft/ft_striter.c libft/ft_striteri.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlen.c \
	  libft/ft_strmap.c libft/ft_strmapi.c libft/ft_strncat.c libft/ft_strncpy.c libft/ft_strncmp.c libft/ft_strnequ.c libft/ft_strnew.c libft/ft_strnstr.c \
	  libft/ft_strrchr.c libft/ft_strsplit.c libft/ft_strstr.c libft/ft_strsub.c libft/ft_strtrim.c libft/ft_swap.c libft/ft_tolower.c libft/ft_toupper.c \
	  libft/ft_memcmp.c libft/ft_printf/ft_struct_filler.c libft/ft_printf/functions.c libft/ft_printf/ft_display_string.c libft/ft_printf/ft_display_int.c \
	  libft/ft_printf/ft_display_char.c libft/ft_printf/ft_display_other.c libft/ft_printf/ft_putchar_unicode.c libft/get_next_line.c \
	  libft/ft_printf/ft_putstr_unicode.c libft/ft_printf/ft_display_float.c libft/ft_printf/functions_2.c libft/ft_printf/ft_manage_pointer.c \

SRC_NAMES = $(SRC:libft/%=%)
SRC_NAMES2 = $(SRC_NAMES:ft_printf/%=%)
OBJ = $(addprefix $(LIBFT_OBJ_DIR), $(SRC_NAMES2:.c=.o))

RTV1_SRC = src/main.c src/vector3d.c src/constructors_objects.c src/draw.c src/controller.c src/intersects.c \
	src/ray_tracing_proccess.c src/lighting.c src/normal.c src/parser.c src/constructors_scene.c \
	src/parser_helper.c
RTV1_SRC_NAMES = $(RTV1_SRC:src/%=%)
RTV1_OBJ = $(addprefix $(OBJ_DIR), $(RTV1_SRC_NAMES:.c=.o))

LIBFT_INC = -I libft/includes/
RTV1_INC = -I inc/

NAME = rtv1
LIBFT_NAME = libftprintf.a

FRAMEWORK = `sdl2-config --libs` -L/usr/lib -lSDL2_image -lm -pthread

FLAGS = -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ) $(RTV1_OBJ)
	@ar rc $(LIBFT_NAME) $(OBJ)
	@ranlib $(LIBFT_NAME)
	@gcc $(FLAGS) $(RTV1_OBJ) $(LIBFT_NAME) $(FRAMEWORK) -o $(NAME)
	@echo "RTv1 compile done!"

$(OBJ): $(SRC) | $(LIBFT_OBJ_DIR)
	@echo "Libft compiling..."
	@gcc $(FLAGS) -c $(SRC) $(LIBFT_INC)
	@mv *.o $(LIBFT_OBJ_DIR)
	@echo "libft compile done!"
	
$(LIBFT_OBJ_DIR):
	@mkdir $(LIBFT_OBJ_DIR)

$(RTV1_OBJ): $(RTV1_SRC) | $(OBJ_DIR) 
	@echo "RTv1 compiling..."
	@gcc $(FLAGS) -c $(RTV1_SRC) $(RTV1_INC)
	@mv *.o $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -f $(OBJ)
	@rm -f $(RTV1_OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_NAME)

re: fclean all
