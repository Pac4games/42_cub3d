/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/23 12:06:24 by paugonca         ###   ########.fr       */
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

t_all_txtrs	*init_txtrs(void)
{
	t_all_txtrs	*txtrs;

	txtrs = malloc(sizeof(t_all_txtrs));
	if (!txtrs)
		return (NULL);
	txtrs->tot_txtrs = TOT;
	txtrs->textures = malloc(txtrs->tot_txtrs * sizeof(t_txtrs));
	txtrs->textures->floor = malloc(sizeof(t_color));
	txtrs->textures->ceiling = malloc(sizeof(t_color));
	if (!txtrs->textures)
	{
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
	cub->all_txtrs = NULL;
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
	return (1);
}

void	init_matrix(t_cub3d *cub, int tot_rows, int tot_cols)
{
	cub->map = malloc(sizeof(*cub->map));
	cub->map->tot_rows = tot_rows;
	cub->map->tot_cols = tot_cols;
	cub->map->map = solo_matrix(tot_rows, tot_cols);
	if (!cub->map->map)
	{
		free(cub->map);
		return ;
	}
}
