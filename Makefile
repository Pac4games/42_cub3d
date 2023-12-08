$(VERBOSE).SILENT:

NAME = cub3D
SRCS_PATH = srcs
OBJS_PATH = objs
LIBFT = libft
CC = cc 
CFLAGS = -Wall -Wextra -Werror -O3 -g #-fsanitize=address

MLX_INC = -I/usr/include -Imlx_linux
MLX_LIB = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
INC_LIBS = -Ilibft/ -Llibft/ -lft $(MLX_INC)

SRCS = main.c init_structs.c fill_structs.c fill_structs_utils.c destroy_structs.c \
       str_utils.c cub_util_prints.c cub_validate_map.c main_display.c \
	   draw_minimap.c find_sqr_coord.c  draw_player.c calc_player_movs.c \
	   define_keys.c toggle_movs.c  toggle_textures.c pixel_drawing_func.c \
	   check_colisions.c cub_raycasting.c cub_raycasting_utils.c cub_map.c \
	   cub_map_closed.c other_utils.c color_parsing.c mouse_utils.c \
	   destroy_cub.c
PATH_AND_SRCS = $(addprefix $(SRCS_PATH)/,$(SRCS))
OBJS = $(patsubst $(SRCS_PATH)/%.c,$(OBJS_PATH)/%.o,$(PATH_AND_SRCS))

all: $(NAME)

$(NAME) : $(OBJS)
	@cd mlx_linux && ./configure
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(INC_LIBS) -o $(NAME) $(MLX_LIB)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	@make clean -C $(LIBFT)
	rm -rf $(OBJS)
	@if [ -d "$(OBJS_PATH)" ]; then \
        rm -rf $(OBJS_PATH); \
    fi

fclean: clean
	rm -rf $(NAME)
	rm -rf libft/libft.a

re: fclean all

.PHONY: all clean fclean re
