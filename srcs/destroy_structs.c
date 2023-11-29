/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/28 17:16:33 by paugonca         ###   ########.fr       */
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
	if (cub->txtrs)
	{
		while (++i < cub->tot_txtrs)
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
			if (cub->txtrs[i]->addrs)
			{
				f = -1;
				free(cub->txtrs[i]->addrs);
			}
			else
				continue ;
			if (cub->txtrs[i]->bpp)
				free(cub->txtrs[i]->bpp);
			if (cub->txtrs[i]->line_length)
				free(cub->txtrs[i]->line_length);
			if (cub->txtrs[i]->endian)
				free(cub->txtrs[i]->endian);
			if (cub->txtrs[i]->imgs)
			{
				f = -1;
				while (++f <= cub->txtrs[i]->levels - 1)
					mlx_destroy_image(cub->mlx, cub->txtrs[i]->imgs[f]);
				free(cub->txtrs[i]->imgs);
			}
			free(cub->txtrs[i]);
		}
		free(cub->txtrs);
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
