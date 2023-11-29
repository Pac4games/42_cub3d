/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/28 12:57:48 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_node	*init_node(void)
{
	t_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->symbol = NULL;
	node->tot_cols = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	init_list(t_list *list)
{
	(*list).head = NULL;
	(*list).tail = NULL;
	(*list).tot_rows = 0;
}

t_txtrs	*init_txtrs(int times)
{
	t_txtrs	*txtrs;

	txtrs = malloc(sizeof(t_txtrs));
	if (!txtrs)
		return (NULL);
	txtrs->floor = malloc(sizeof(int) * times);
	if (!txtrs->floor)
	{
		free(txtrs);
		return (NULL);
	}
	txtrs->ceiling = malloc(sizeof(int) * times);
	if (!txtrs->ceiling)
	{
		free(txtrs->floor);
		free(txtrs);
		return (NULL);
	}
	txtrs->width = malloc(sizeof(int) * times);
	if (!txtrs->width)
	{
		free(txtrs->floor);
		free(txtrs->ceiling);
		free(txtrs);
		return (NULL);
	}
	txtrs->height = malloc(sizeof(int) * times);
	if (!txtrs->height)
	{
		free(txtrs->floor);
		free(txtrs->ceiling);
		free(txtrs->width);
		free(txtrs);
		return (NULL);
	}
	return (txtrs);
}

int	init_cub(t_cub3d *cub)
{
	cub->mlx = NULL;
	cub->mlx_win = NULL;
	cub->img = NULL;
	cub->addr = NULL;
	cub->txtrs = NULL;
	cub->minimap = NULL;
	cub->map = NULL;
	cub->map_cols = 0;
	cub->player = NULL;
	cub->move = 0;
	cub->direction = 0;
	cub->level = 0;
	cub->plane_x = 0;
	cub->plane_y = 0;
	cub->inverted = 1;
	cub->tot_txtrs = 0;
	cub->elems = 0;
	return (1);
}

void	init_matrix(t_cub3d *cub, int tot_rows, int tot_cols)
{
	cub->map = malloc(sizeof(*cub->map));
	if (!cub->map)
		return ;
	cub->map->tot_rows = tot_rows;
	cub->map->tot_cols = tot_cols;
	cub->map->map = solo_matrix(tot_rows, tot_cols);
	if (!cub->map->map)
	{
		free(cub->map);
		return ;
	}
}
