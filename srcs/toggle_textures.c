/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:33:17 by mnascime          #+#    #+#             */
/*   Updated: 2023/12/09 15:50:32 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_color(t_cub3d *cub, int type, int tex_x, int tex_y)
{
	int		color;
	int		offset;

	offset = tex_y * cub->txtrs[type]->line_length[cub->level \
	% (cub->txtrs[type]->levels)] + tex_x \
	* (cub->txtrs[type]->bpp[cub->level \
	% (cub->txtrs[type]->levels)] / 8);
	color = *(int *)(cub->txtrs[type]->addrs[cub->level \
	% (cub->txtrs[type]->levels)] + offset);
	return (color);
}

void	draw_txtrs(t_cub3d *cub, t_ray *ray, t_vector *vec, int type)
{
	double	step;
	double	texture_pos;
	int		texture_y;
	int		color;
	int		y;

	step = 1.0 * cub->txtrs[type]->height[cub->level \
		% (cub->txtrs[type]->levels)] / (vec->yf - vec->yi);
	if ((ray->side == 0 && ray->dir_x < 0) || \
	(ray->side == 1 && ray->dir_y > 0))
		ray->x_txtr = cub->txtrs[type]->width[cub->level \
	% cub->txtrs[type]->levels] - ray->x_txtr - 1;
	texture_pos = (vec->yi - (double)WHEI / 2 + (vec->yf - vec->yi) / 2) * step;
	y = vec->yi;
	while (y < vec->yf)
	{
		texture_y = (int)texture_pos;
		if (y >= 0 && y < WHEI)
		{
			color = get_color(cub, type, ray->x_txtr, texture_y);
			my_mlx_pixel_put(cub, vec->xi, y, color);
		}
		texture_pos += step;
		y++;
	}
}

void	change_txtrs(t_cub3d *cub, int y, int x)
{
	if (cub->map->map[y][x] == DOOR)
		cub->level++;
	else
		return ;
	if (cub->level < 0)
		cub->level = cub->max_level;
}

void	register_elem(t_cub3d *cub, int type)
{
	int	elems;

	elems = cub->elems;
	if (type == F)
		elems |= (1 << (F + 1));
	else if (type == C)
		elems |= (1 << (C + 1));
	else if (type == NO)
		elems |= (1 << (NO + 1));
	else if (type == SO)
		elems |= (1 << (SO + 1));
	else if (type == EA)
		elems |= (1 << (EA + 1));
	else if (type == WE)
		elems |= (1 << (WE + 1));
	else if (type == DO)
		elems |= (1 << (DO + 1));
	else if (type == SP)
		elems |= (1 << (SP + 1));
	cub->elems = elems;
}
