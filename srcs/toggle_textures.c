/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:33:17 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/26 20:37:21 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_color(t_cub3d *cub, int type, int tex_x, int tex_y)
{
	int		color;
	int		offset;

	offset = tex_y * cub->textures[type]->line_length[cub->level \
	% (cub->textures[type]->levels)] + tex_x \
	* (cub->textures[type]->bits_per_pixel[cub->level \
	% (cub->textures[type]->levels)] / 8);
	color = *(int *)(cub->textures[type]->addrs[cub->level \
	% (cub->textures[type]->levels)] + offset);
	return (color);
}

void	draw_txtrs(t_cub3d *cub, t_ray *ray, t_vector *vec, int type)
{
	double	step;
	double	texture_pos;
	int		texture_y;
	int		color;
	int		y;

	step = 1.0 * cub->textures[type]->height[cub->level \
		% (cub->textures[type]->levels)] / (vec->yf - vec->yi);
	texture_pos = (vec->yi - WHEI / 2 + (vec->yf - vec->yi) / 2) * step;
	y = vec->yi;
	while (y < vec->yf)
	{
		texture_y = (int)texture_pos & (cub->textures[type]->height[cub->level \
		% (cub->textures[type]->levels)] - 1);
		color = get_color(cub, type, ray->x_txtr, texture_y);
		my_mlx_pixel_put(cub, vec->xi, y, color);
		texture_pos += step;
		y++;
	}
}

void	change_textures(t_cub3d *cub, int y, int x)
{
	static int	lastx = 0;
	static int	lasty = 0;

	if (cub->map->map[y][x] != cub->map->map[lasty][lastx])
	{
		if (cub->map->map[y][x] == DOOR_UP)
			cub->level++;
		else if (cub->level > 0)
			cub->level--;
		else
			return ;
		if (cub->level < 0)
			cub->level = cub->tot_txtrs;
		lasty = y;
		lastx = x;
	}
}

void	register_elem(t_cub3d *cub, int type)
{
	int	elems;

	elems = cub->elems;
	if (type == NO)
		elems |= (1 << (NO + 1));
	else if (type == SO)
		elems |= (1 << (SO + 1));
	else if (type == EA)
		elems |= (1 << (EA + 1));
	else if (type == WE)
		elems |= (1 << (WE + 1));
	else if (type == UP)
		elems |= (1 << (UP + 1));
	else if (type == DO)
		elems |= (1 << (DO + 1));
	else if (type == F)
		elems |= (1 << (F + 1));
	else if (type == C)
		elems |= (1 << (C + 1));
	cub->elems = elems;
}
