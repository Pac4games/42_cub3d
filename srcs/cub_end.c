/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/28 13:16:59 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_split(char ***split_location)
{
	int		i;
	char	**split;

	split = *split_location;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	*split_location = NULL;
}

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
	t_txtr	*del;
	t_txtr	*next;

	if (!txtrs)
		return ;
	next = NULL;
	del = txtrs->head;
	while (del)
	{
		next = del->next;
		free(del->path);
		free(del);
		del = next;
	}
	free(txtrs);
	txtrs = NULL;
}

void	destroy_cub(t_cub3d *cub)
{
	if (!cub)
		return ;
	if (cub->map)
	{
		destroy_matrix(cub->map->map, cub->map->tot_rows);
		free(cub->map);
	}
	if (cub->textures)
		destroy_txtrs_list(cub->textures);
	if (cub->cur_txtrs)
		destroy_txtrs_list(cub->cur_txtrs);
}

void	destroy_matrix(int **matrix, int tot_rows)
{
	int	i;

	i = -1;
	while (++i < tot_rows)
		free(matrix[i]);
	free(matrix);
	matrix = NULL;
}
