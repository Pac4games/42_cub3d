/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:51:34 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/31 16:07:23 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <math.h>
# include "mlx_linux/mlx.h"
# include "./libft/libft.h"

# define WWID 1920
# define WHEI 1080
# define ESC 65307
# define FRONT 119
# define BACK 115
# define TOLEFT 97
# define TORIGHT 100

typedef struct s_node	t_node;

typedef struct s_node
{
	int				*symbol;
	int				tot_cols;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	int		tot_rows;
}	t_list;

typedef struct s_map
{
	int	**map;
	int	tot_rows;
	int	tot_cols;
}	t_map;

enum e_map_txt
{
	ZERO = '0',
	WALL = '1',
	SPACE = ' ',
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
	UP_DOOR_AT_UP = 'U',
	UP_DOOR_AT_DOWN = 'D',
	UP_DOOR_AT_LEFT = 'L',
	UP_DOOR_AT_RIGHT = 'R',
	DOWN_DOOR_AT_UP = 'u',
	DOWN_DOOR_AT_DOWN = 'd',
	DOWN_DOOR_AT_LEFT = 'l',
	DOWN_DOOR_AT_RIGHT = 'r',
};

enum e_map_num
{
	NZERO,
	NWALL,
	NSPACE,
	NNORTH,
	NSOUTH,
	NEAST,
	NWEST,
	NUP_DOOR_AT_UP,
	NUP_DOOR_AT_DOWN,
	NUP_DOOR_AT_LEFT,
	NUP_DOOR_AT_RIGHT,
	NDOWN_DOOR_AT_UP,
	NDOWN_DOOR_AT_DOWN,
	NDOWN_DOOR_AT_LEFT,
	NDOWN_DOOR_AT_RIGHT,
};

enum e_texture
{
	NO,
	SO,
	EA,
	WE,
	UP,
	DOWN,
	F,
	C,
	TOT,
};

typedef struct s_txtrs
{
	char	**path;
	int		*color;
	int		type;
	int		levels;
}	t_txtrs;

typedef struct s_all_txtrs
{
	t_txtrs		*textures;
	int			tot_txtrs;
}	t_all_txtrs;

typedef struct s_minimap
{
	int			**mapx;
	int			**mapy;
}	t_minimap;

typedef struct s_vector
{
	int	xi;
	int	yi;
	int	xf;
	int	yf;
}	t_vector;

typedef struct s_cub3d
{
	t_map		*map;
	t_minimap	*minimap;
	t_vector	*player;
	t_all_txtrs	*all_txtrs;
	int			map_cols;
}	t_cub3d;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			go;
	t_cub3d		*cub;
}	t_data;

# define PRT_NORTH "NO"
# define PRT_SOUTH "SO"
# define PRT_EAST "EA"
# define PRT_WEST "WE"
# define PRT_FLOOR "F"
# define PRT_CEIL "C"
# define PRT_UP "UP"
# define PRT_LOW "LO"

// CONV_ENUMS
int			conv_to_map_num(char c);
char		*conv_to_txtr_text(char c);

// DISPLAY
void		display_in_canvas(t_cub3d *cub3d);
void		draw_line(t_data *data, t_vector *vector, int color);

// DRAW COORD
void		begin_coord(t_vector *vector, int x, int y);
void		end_coord(t_vector *vector, int x, int y);

// DRAW DOORS
void		draw_doors(t_data *img, t_map *map);

// DRAW LINES
void		draw_paralell_hlines(t_data *img, \
t_vector *vec, int beg, int color);
void		draw_paralell_vlines(t_data *img, \
t_vector *vec, int beg, int color);
void		get_h_vector(t_data *img, t_vector *vec, int x, int y);
void		get_v_vector(t_data *img, t_vector *vec, int x, int y);
void		draw_minimap(t_data *img, t_map *map);

// DRAW PLAYER
void		draw_player_lines(t_data *img, t_vector vec, int dist, int color);
void		draw_player(t_data *img, t_map *map);
void		move_player(t_data *img, int key);
t_vector	*get_player_pos(t_cub3d *cub);

// END STRUCTURES
void		destroy_split(char ***split_location);
void		destroy_list(t_list *list);
void		destroy_cub(t_cub3d *cub);
void		destroy_txtrs_list(t_all_txtrs *txtrs);
void		destroy_matrix(int **mat, int tot_rows);

// HANDLE KEYS
int			in_key(t_data *img);
int			key_press(int key_pressed, void *param);
int			key_release(int key_pressed, void *param);

//INIT STRUCTURES
t_node		*init_node(void);
void		init_list(t_list *list);
int			init_cub(t_cub3d *cub);
t_all_txtrs	*init_txtrs(void);
void		init_minimap(t_cub3d *cub);

// INSERT NODES
void		init_matrix(t_cub3d *cub, int tot_rows, int tot_cols);
void		insert_map_tail(t_list *list, int *data, int len);
void		list_to_map(t_list *list, t_cub3d *cub);
void		insert_txtrs(t_cub3d **cub, char *line, int txtr_type);

// MINIMAP
int			**update_display_x(int rows, int cols, int y, int x);
int			**update_display_y(int rows, int cols, int y, int x);
int			get_sqr_size(t_cub3d *cub);
void		sqr_adjustments(int **map, int rows, int cols);

// UTILITY PRINTS
void		print_map(t_map *map, int cols);
void		print_txtrs(t_all_txtrs *txtrs);
void		print_matrix(int **mat, int rows, int cols);

// UTILITIES
int			ft_isspace(int c);
int			is_only_spaces(char *str);
int			ft_str_end_trim(char *line);
int			**solo_matrix(int rows, int cols);

// VALIDATE MAP
int			map_line_is_valid(char *line);
int			is_valid_elem(char *line);

// MAIN
int			*fill_line_of_list(char *line);
int			fill_in_cub(t_cub3d *cub, int fd);
void		display_in_canvas(t_cub3d *cub);

#endif
