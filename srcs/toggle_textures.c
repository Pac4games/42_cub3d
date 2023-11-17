/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:33:17 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/17 16:17:42 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


static int	get_color(t_cub3d *cub, int type, int tex_x, int tex_y)
{
	int		color;
	int		offset;
	
	offset = tex_y * cub->all_txtrs->textures[type].line_length + tex_x \
	* (cub->bits_per_pixel / 8);
	color = *(int *)(cub->all_txtrs->textures[type].addr + offset);
	return (color);
}

void	draw_txtrs(t_cub3d *cub, t_ray *ray, t_vector *vec, int type)
{
	double	step;
	double	texture_pos;
	int		texture_y;
	int		color;
	int		y;

	step = 1.0 * cub->all_txtrs->textures[type].height / (vec->yf - vec->yi);
	texture_pos = (vec->yi - WHEI / 2 + (vec->yf - vec->yi) / 2) * step;
	y = vec->yi;
	cub->all_txtrs->textures[type].img = mlx_xpm_file_to_image(cub->mlx, \
	cub->all_txtrs->textures[type].path[cub->level \
	% (cub->all_txtrs->textures[type].levels)], \
	&cub->all_txtrs->textures[type].width, &cub->all_txtrs->textures[type].height);
	cub->all_txtrs->textures[type].addr = mlx_get_data_addr(cub->all_txtrs->textures[type].img, \
	&cub->bits_per_pixel, &cub->all_txtrs->textures[type].line_length, &cub->endian);
	while (y < vec->yf)
	{
		texture_y = (int)texture_pos & (cub->all_txtrs->textures[type].height - 1);
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
		if (cub->map->map[y][x] == DOOR_UP \
		|| cub->map->map[y][x] == DOOR_DOWN)
			cub->level++;
		else if (cub->level > 0)
			cub->level--;
		else
			return ;
		if (cub->level < 0)
			cub->level = cub->all_txtrs->tot_txtrs;
		printf("%s\n", cub->all_txtrs->textures[SO].path[cub->level \
		% (cub->all_txtrs->textures[SO].levels)]);
		lasty = y;
		lastx = x;
	}
}
