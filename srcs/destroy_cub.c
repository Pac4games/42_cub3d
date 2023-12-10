/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:21:43 by paugonca          #+#    #+#             */
/*   Updated: 2023/12/10 10:48:29 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	destroy_txtr_imgs(t_cub3d *cub, int i)
{
	int	f;

	if (cub->txtrs[i]->width)
		free(cub->txtrs[i]->width);
	if (cub->txtrs[i]->height)
		free(cub->txtrs[i]->height);
	if (cub->elem_imgs >> (i + 1) & 1)
	{
		if (cub->elem_allocs >> (i + 1) & 1)
		{
			f = -1;
			while (++f < cub->txtrs[i]->levels)
				mlx_destroy_image(cub->mlx, cub->txtrs[i]->imgs[f]);
		}
		free(cub->txtrs[i]->imgs);
		if (cub->txtrs[i]->addrs)
			free(cub->txtrs[i]->addrs);
		if (cub->txtrs[i]->bpp)
			free(cub->txtrs[i]->bpp);
		if (cub->txtrs[i]->line_length)
			free(cub->txtrs[i]->line_length);
		if (cub->txtrs[i]->endian)
			free(cub->txtrs[i]->endian);
	}
	free(cub->txtrs[i]);
}

static void	destroy_txtrs(t_cub3d *cub, int i)
{
	int	f;

	if (cub->elems >> (i + 1) & 1)
	{
		if (cub->txtrs[i]->path)
		{
			f = -1;
			while (++f <= cub->txtrs[i]->levels)
				free(cub->txtrs[i]->path[f]);
			free(cub->txtrs[i]->path);
		}
		if (i == F || i == C)
		{
			if (cub->txtrs[i]->floor)
				free(cub->txtrs[i]->floor);
			if (cub->txtrs[i]->ceiling)
				free(cub->txtrs[i]->ceiling);
			free(cub->txtrs[i]);
		}
		else
			destroy_txtr_imgs(cub, i);
	}
}

void	destroy_cub(t_cub3d *cub)
{
	int	i;

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
	i = -1;
	while (++i < TOT)
		destroy_txtrs(cub, i);
}
