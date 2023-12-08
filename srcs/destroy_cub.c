/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:21:43 by paugonca          #+#    #+#             */
/*   Updated: 2023/12/08 22:25:42 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_cub(t_cub3d *cub)
{
	int	i;
	int	f;

	if (!cub)
		return ;
	if (cub->minimap)
	{
		free(cub->minimap->x_vals);
		free(cub->minimap->y_vals);
		if (cub->player)
			free(cub->player);
		free(cub->minimap);
	}
	if (cub->map)
	{
		destroy_matrix(cub->map->map, cub->map->tot_rows);
		free(cub->map);
	}
	i = 0;
	while (cub->tot_txtrs > 0 && (cub->elems >> i & 1))
	{
		if (cub->txtrs[i]->floor)
			free(cub->txtrs[i]->floor);
		if (cub->txtrs[i]->ceiling)
			free(cub->txtrs[i]->ceiling);
		if (cub->txtrs[i]->width)
			free(cub->txtrs[i]->width);
		if (cub->txtrs[i]->height)
			free(cub->txtrs[i]->height);
		if (cub->txtrs[i]->path)
		{
			f = -1;
			while (++f <= cub->txtrs[i]->levels)
				free(cub->txtrs[i]->path[f]);
			free(cub->txtrs[i]->path);
		}
		if (i == F || i == C)
		{
			free(cub->txtrs[i]);
			continue ;
		}
		else
			continue ;
		if (cub->txtrs[i]->imgs)
		{
			f = -1;
			free(cub->txtrs[i]->imgs);
		}
		if (cub->txtrs[i]->addrs)
		{
			f = -1;
			free(cub->txtrs[i]->addrs);
		}
		if (cub->txtrs[i]->bpp)
			free(cub->txtrs[i]->bpp);
		if (cub->txtrs[i]->line_length)
			free(cub->txtrs[i]->line_length);
		if (cub->txtrs[i]->endian)
			free(cub->txtrs[i]->endian);
		free(cub->txtrs[i]);
	}
	free(cub->txtrs);
}
