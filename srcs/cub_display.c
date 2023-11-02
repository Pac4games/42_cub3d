/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:15:22 by margarida         #+#    #+#             */
/*   Updated: 2023/11/02 14:41:29 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	quits(t_cub3d *cub)
{
	mlx_do_key_autorepeaton(cub->mlx);
	mlx_destroy_image(cub->mlx, cub->img);
	mlx_destroy_window (cub->mlx, cub->mlx_win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	destroy_cub(cub);
	exit(EXIT_SUCCESS);
}

static int	read_keys(int key_pressed, t_cub3d *cub)
{
	if (key_pressed == ESC)
		quits(cub);
	else if (key_pressed == 119 || key_pressed == 115 \
	|| key_pressed == 97 || key_pressed == 100)
		key_press(key_pressed, cub);
	return (0);
}

void	my_mlx_pixel_put(t_cub3d *cub, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && x < WWID && y < WHEI)
	{
		dst = cub->addr + (y * cub->line_length + \
		x * (cub->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_cub3d *cub, t_vector *vector, int color)
{
	double	dx;
	double	dy;
	double	pxx;
	double	pxy;
	int		pxs;

	pxx = vector->xi;
	pxy = vector->yi;
	dx = vector->xf - vector->xi;
	dy = vector->yf - vector->yi;
	pxs = sqrt((dx * dx) + (dy * dy));
	dx /= pxs;
	dy /= pxs;
	pxx = vector->xi;
	pxy = vector->yi;
	while (pxs)
	{
		my_mlx_pixel_put(cub, pxx, pxy, color);
		pxx += dx;
		pxy += dy;
		--pxs;
	}
}

void	display_in_canvas(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, WWID, WHEI, "cub3D");
	cub->img = mlx_new_image(cub->mlx, WWID, WHEI);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel, \
	&cub->line_length, &cub->endian);
	draw_minimap(cub, cub->map);
	draw_doors(cub, cub->map);
	draw_player_lines(cub, *cub->player, \
	cub->sqr_size * 0.5, 0x44FF24);
	my_mlx_pixel_put(cub, cub->gaze_x, cub->gaze_y, 0x44FF24);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img, 0, 0);
	mlx_hook(cub->mlx_win, 2, (1L << 0), read_keys, cub);
	mlx_hook(cub->mlx_win, 3, (1L << 1), key_release, cub);
	mlx_hook(cub->mlx_win, 17, (1L << 1), quits, cub);
	mlx_do_key_autorepeatoff(cub->mlx);
	mlx_loop_hook(cub->mlx, in_key, cub);
	mlx_loop(cub->mlx);
}
