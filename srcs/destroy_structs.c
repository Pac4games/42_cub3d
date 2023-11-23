/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/15 12:40:05 by paugonca         ###   ########.fr       */
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

void	destroy_txtrs_list(t_all_txtrs *txtrs)
{
	int	i;

	if (!txtrs)
		return ;
	i = 0;
	while (txtrs->textures[i].path)
		free_mtx(txtrs->textures[i++].path);
	free(txtrs->textures);
	free(txtrs);
}

void	destroy_cub(t_cub3d *cub)
{
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
	if (cub->all_txtrs)
		destroy_txtrs_list(cub->all_txtrs);
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