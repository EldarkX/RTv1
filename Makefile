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

OBJ = ft_printf.o  ft_atoi.o  ft_bzero.o  ft_isalnum.o  ft_isalpha.o  ft_isascii.o  ft_isdigit.o \
      ft_isprint.o  ft_itoa.o  ft_lstadd.o  ft_lstdel.o  ft_lstdelelem.o  ft_lstdelone.o  ft_lstiter.o  ft_lstmap.o \
      ft_lstnew.o  ft_memalloc.o  ft_memccpy.o  ft_memchr.o  ft_memcpy.o  ft_memdel.o  ft_memmove.o  ft_memset.o \
      ft_putchar.o  ft_putchar_fd.o  ft_putendl.o  ft_putendl_fd.o  ft_putnbr.o  ft_putnbr_fd.o  ft_putstr.o \
      ft_putstr_fd.o  ft_str_is_alpha.o  ft_str_is_lowercase.o  ft_str_is_numeric.o  ft_str_is_uppercase.o \
      ft_str_to_lower.o  ft_str_to_upper.o  ft_strcat.o  ft_strchr.o  ft_strclr.o  ft_strcmp.o  ft_strcpy.o \
      ft_strdel.o  ft_strdup.o  ft_strequ.o  ft_striter.o  ft_striteri.o  ft_strjoin.o  ft_strlcat.o  ft_strlen.o \
      ft_strmap.o  ft_strmapi.o  ft_strncat.o  ft_strncpy.o  ft_strncmp.o  ft_strnequ.o  ft_strnew.o  ft_strnstr.o \
      ft_strrchr.o  ft_strsplit.o  ft_strstr.o  ft_strsub.o  ft_strtrim.o  ft_swap.o  ft_tolower.o  ft_toupper.o \
      ft_memcmp.o ft_struct_filler.o functions.o ft_display_string.o ft_display_int.o ft_display_char.o ft_display_other.o \
      ft_putstr_unicode.o ft_putchar_unicode.o ft_display_float.o functions_2.o ft_manage_pointer.o get_next_line.o \


RTV1_SRC = src/main.c src/vector3d.c src/constructors_objects.c src/draw.c src/controller.c src/intersects.c \
	src/ray_tracing_proccess.c src/lighting.c src/normal.c src/parser.c
RTV1_OBJ = main.o vector3d.o constructors_objects.o draw.o controller.o intersects.o \
	ray_tracing_proccess.o lighting.o normal.o parser.o

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

$(OBJ): $(SRC)
	@gcc $(FLAGS) -c $(SRC) $(LIBFT_INC)

$(RTV1_OBJ): $(RTV1_SRC)
	@gcc $(FLAGS) -c $(RTV1_SRC) $(RTV1_INC)

clean:
	@rm -f $(OBJ)
	@rm -f $(RTV1_OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_NAME)

re: fclean all
