/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_coord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:41:33 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/05 11:49:45 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	begin_coord(t_vector *vector, int x, int y)
{
	vector->xi = x;
	vector->yi = y;
}

void	end_coord(t_vector *vector, int x, int y)
{
	vector->xf = x;
	vector->yf = y;
}

void	minimap_scale_down(t_vector *vec, float scale, int dist)
{
	vec->xi = vec->xi * scale + dist;
	vec->xf = vec->xf * scale + dist;
	vec->yi = vec->yi * scale + dist;
	vec->yf = vec->yf * scale + dist;
}

void	player_scaled_down(t_cub3d *cub, float scale, int dist)
{
	t_vector	vec;

	vec.xi = cub->player->xi * scale + dist;
	vec.xf = cub->player->xf * scale + dist;
	vec.yi = cub->player->yi * scale + dist;
	vec.yf = cub->player->yf * scale + dist;
	draw_player_lines(cub, vec, \
	(int)ceilf(cub->sqr_size * 0.5 * cub->scale), 0x44FF24);
}

void	gaze_scale_down(t_cub3d *cub, float x, float y, int dist)
{
	x = x * cub->scale + dist;
	y = y * cub->scale + dist;
	my_mlx_pixel_put(cub, x, y, 0x44FF24);
}
