/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:15:22 by margarida         #+#    #+#             */
/*   Updated: 2023/12/06 10:50:33 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_sprite(t_cub3d *cub)
{
	double		step;
	double		texture_pos;
	int			texture_y;
	int			x;
	int			y;
	t_vector	vec;

	vec.xi = WWID / 2 - cub->txtrs[SP]->width[cub->level % cub->txtrs[SP]->levels] / 2;
	vec.yi = WHEI - cub->txtrs[SP]->height[cub->level % cub->txtrs[SP]->levels];
	vec.xf = vec.xi + cub->txtrs[SP]->width[cub->level % cub->txtrs[SP]->levels];
	vec.yf = WHEI;
	step = 1.0 * cub->txtrs[SP]->height[cub->level \
		% (cub->txtrs[SP]->levels)] / (vec.yf - vec.yi);
	x = vec.xi;
	while (x < vec.xf)
	{
		y = vec.yi;
		texture_pos = (vec.yi - WHEI / 2 + (vec.yf - vec.yi) / 2) * step;
		while (y < vec.yf)
		{
			texture_y = (int)texture_pos;
			if (y >= 0 && y < WHEI && get_color(cub, SP, x, texture_y) != 0)
				my_mlx_pixel_put(cub, x, y, get_color(cub, SP, x, texture_y));
			texture_pos += step;
			y++;
		}
		x++;
	}
	if (cub->start >= 20)
		cub->start--;
	else if (cub->start < 0)
		cub->start++;
}

void	display_in_canvas(t_cub3d *cub)
{
	int	type;

	type = 0;
	cub->mlx = mlx_init();
	cub->img = mlx_new_image(cub->mlx, WWID, WHEI);
	while (++type <= cub->tot_txtrs)
	{
		if ((cub->elems >> type & 1))
			if (!fill_txtrs(cub, type - 1, cub->txtrs[type - 1]->levels))
				quits(cub);
	}
	cub->mlx_win = mlx_new_window(cub->mlx, WWID, WHEI, "cub3D");
	cub->addr = mlx_get_data_addr(cub->img, &cub->bpp, \
	&cub->line_length, &cub->endian);
	raycasting(cub);
	redraw_minimap(cub);
	draw_sprite(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img, 0, 0);
	mlx_hook(cub->mlx_win, 2, (1L << 0), read_keys, cub);
	mlx_hook(cub->mlx_win, 3, (1L << 1), key_release, cub);
	mlx_hook(cub->mlx_win, 17, (1L << 1), quits, cub);
	mlx_do_key_autorepeatoff(cub->mlx);
	mlx_loop_hook(cub->mlx, in_key, cub);
	mlx_loop(cub->mlx);
}
