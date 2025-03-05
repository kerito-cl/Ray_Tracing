NAME	:= miniRT
LIBFT_DIR	:= libft
LIBFT_LIB	:= $(LIBFT_DIR)/libft.a
CFLAGS	:= -Wunreachable-code -Ofast
LIBMLX	:= ./MLX42
LIB_URL := https://github.com/codam-coding-college/MLX42
HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT_DIR)
LIBS	:= $(LIBMLX)/build/libmlx42.a

OBJ_DIR	:= obj
SRCS	:= src/main.c src/error.c src/parse.c src/arena.c src/utils.c \
			src/assign_geo_objects.c src/camera.c \
			src/vec3/vec_methods.c src/vec3/vec_methods2.c src/vec3/vec_methods3.c src/vec3/vec_methods4.c src/vec3/vec_methods5.c \
		  gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS	:= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
LIBFT	:= -L$(LIBFT_DIR) -lft

all: libmlx libft $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/src/vec3 $(OBJ_DIR)/gnl $(OBJ_DIR)/src

libft:
	@echo "building libft"
	@make -C $(LIBFT_DIR) 

libmlx: $(LIBS)

$(LIBS): $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBMLX):
	@git clone $(LIB_URL) $(LIBMLX)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS) $(LIBS)
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -ldl -lglfw -pthread -lm -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft

