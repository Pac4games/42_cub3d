/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/27 14:08:14 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_list(t_list *list)
{
	t_node	*del;
	t_node	*next;

	if (!list)
		return ;
	next = NULL;
	del = list->head;
	while (del)
	{
		next = del->next;
		free(del->symbol);
		free(del);
		del = next;
	}
}

void	destroy_txtrs_list(t_txtrs *txtrs)
{
	int	i;

	if (!txtrs)
		return ;
	i = 0;
	while (txtrs[i].path)
		free_mtx(txtrs[i++].path);
	free(txtrs);
}

void	destroy_cub(t_cub3d *cub)
{
	int	i;
	int	f;

	i = -1;
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
	if (cub->textures)
	{
		while (++i < cub->tot_txtrs)
		{
			if (cub->textures[i]->floor)
				free(cub->textures[i]->floor);
			if (cub->textures[i]->ceiling)
				free(cub->textures[i]->ceiling);
			if (cub->textures[i]->width)
				free(cub->textures[i]->width);
			if (cub->textures[i]->height)
				free(cub->textures[i]->height);
			if (cub->textures[i]->path)
			{
				f = -1;
				while (++f <= cub->textures[i]->levels)
					free(cub->textures[i]->path[f]);
				free(cub->textures[i]->path);
			}
			if (i == F || i == C)
			{
				free(cub->textures[i]);
				continue ;
			}
			if (cub->textures[i]->bits_per_pixel)
				free(cub->textures[i]->bits_per_pixel);
			if (cub->textures[i]->line_length)
				free(cub->textures[i]->line_length);
			if (cub->textures[i]->endian)
				free(cub->textures[i]->endian);
			if (cub->textures[i]->addrs)
			{
				f = -1;
				free(cub->textures[i]->addrs);
			}
			if (cub->textures[i]->imgs)
			{
				f = -1;
				while (++f <= cub->textures[i]->levels - 1)
					mlx_destroy_image(cub->mlx, cub->textures[i]->imgs[f]);
				free(cub->textures[i]->imgs);
			}
			free(cub->textures[i]);
		}
		free(cub->textures);
	}
}

void	destroy_matrix(char **matrix, int tot_rows)
{
	int	i;

	i = -1;
	while (++i < tot_rows)
		free(matrix[i]);
	free(matrix);
	matrix = NULL;
}
