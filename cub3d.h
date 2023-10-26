/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:51:34 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/26 00:49:12 by mnascime         ###   ########.fr       */
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

# define WWID 1080
# define WHEI 720
# define ESC 65307

typedef struct s_node	t_node;

typedef struct s_node
{
	char			*symbol;
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
	char	**map;
	int		tot_rows;
	int		tot_cols;
}	t_map;

enum e_map
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

typedef struct s_txtr
{
	char			*path;
	int				color;
	int				type;
	struct s_txtr	*next;
	struct s_txtr	*prev;
}	t_txtr;

typedef struct s_all_txtrs
{
	struct s_txtr	*head;
	struct s_txtr	*tail;
	int		tot_txtrs;
	int		tot_lvls;
}	t_all_txtrs;

enum e_texture
{
	NO = 1,
	SO,
	EA,
	WE,
	UP,
	DOWN,
	F,
	C,
	TOT,
};

typedef struct s_cub3d
{
	/*
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	*/
	t_map		*map;
	t_all_txtrs	*textures;
	int			map_cols;
}	t_cub3d;

typedef struct s_vector
{
	int	xi;
	int	yi;
	int	xf;
	int	yf;
}	t_vector;

# define PRT_NORTH "NO"
# define PRT_SOUTH "SO"
# define PRT_EAST "EA"
# define PRT_WEST "WE"
# define PRT_FLOOR "F"
# define PRT_CEIL "C"
# define PRT_UP "UP"
# define PRT_LOW "LO"
/*
// Blocks
int			smlnum(int rows, int cols);
void		corr_blocky(int rows, int cols, double **blocky);
double		**creat_blocky(t_matrix *matrix, int y, int x);
void		corr_blockx(int rows, int cols, double **blockx);
double		**creat_blockx(t_matrix *matrix, int y, int x);

// Display
int			quits(t_data *img);
int			read_keys(int key_pressed, void *param);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		draw_line(t_data *data, t_vector *vector, int zi, int zf);
void		display_in_canvas(t_matrix *matrix);

// Draw utils
void		begin_coord(t_vector *vector, int x, int y);
void		end_coord(t_vector *vector, int x, int y);
void		corr_blockz(int tab, int rows, int cols, double **blockz);
int			max_z(int rows, int cols, double **blockz);
int			min_z(int rows, int cols, double **blockz);

// Draw
void		draw_midlines(t_data *img, t_matrix *mat, double **bx, double **by);
int			recolor(int zi, int rf, int gf, int bf);
void		colorize(t_matrix *matrix);
void		draw_hedges(t_data *img, t_matrix *mat, double **bx, double **by);
void		draw_vedges(t_data *img, t_matrix *mat, double **bx, double **by);
*/
// Init_End
t_node		*init_node(void);
t_list		*init_list(void);
t_cub3d		*init_cub(void);
t_all_txtrs	*init_txtrs(void);
t_txtr		*init_single_txtr(void);
t_map		*init_matrix(int tot_rows, int tot_cols);
void		destroy_list(t_list **list);
void		destroy_cub(t_cub3d **cub);
/*
// Scale
void		corr_b(int rows, int cols, double corr, double **block);
void		rescale(t_matrix *mat, double **bx, double **by);
int			bignum(int first, int second);
*/
// Utils
void		insert_map_tail(t_list *list, char *data);
void		insert_txtrs_tail(t_all_txtrs *txtrs, char *data, int txtr_type);
void		destroy_split(char ***split_location);
double		**solo_matrix(int rows, int cols);
void		free_blocks(int rows, double **blockx, double **blocky);
/*
// main
t_matrix	*list_to_matrix(t_list **list);
t_list		*file_to_dll(int fd);
*/
#endif
