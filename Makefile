SRC = src/main.c src/vector3d.c src/constructors.c src/draw.c src/controller.c src/intersects.c src/ray_tracing_proccess.c \
		src/lighting.c src/get_normals.c
OBJ = src/main.o src/vector3d.o src/constructors.o src/draw.o src/controller.o src/intersects.o src/ray_tracing_proccess.o \
	src/lighting.o src/get_normals.o
LIB = `sdl2-config --libs` -L/usr/lib -lSDL2_image

NAME = rtv1

FLAGS = -Wall -Wextra -pthread

all:
	@gcc $(FLAGS) $(SRC) $(LIB) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
