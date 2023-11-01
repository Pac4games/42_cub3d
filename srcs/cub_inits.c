/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_inits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/01 16:21:59 by mnascime         ###   ########.fr       */
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
	if (!txtrs->textures)
	{
		free(txtrs);
		return (NULL);
	}
	return (txtrs);
}

int	init_cub(t_cub3d *cub)
{
	cub->all_txtrs = NULL;
	cub->minimap = NULL;
	cub->map = NULL;
	cub->map_cols = 0;
	cub->player = NULL;
	cub->move = 0;
	return (1);
}

void	init_minimap(t_cub3d *cub)
{
	cub->minimap = malloc(sizeof(*cub->minimap));
	if (!cub->minimap)
		return ;
	cub->minimap->mapx = \
	update_display_x(cub->map->tot_rows, cub->map_cols, -1, -1);
	if (!cub->minimap->mapx)
	{
		free(cub->minimap);
		return ;
	}
	sqr_adjustments(cub->minimap->mapx, cub->map->tot_rows, cub->map_cols);
	cub->minimap->mapy = \
	update_display_y(cub->map->tot_rows, cub->map_cols, -1, -1);
	if (!cub->minimap->mapy)
	{
		destroy_matrix(cub->minimap->mapx, cub->map->tot_rows);
		free(cub->minimap);
		return ;
	}
	sqr_adjustments(cub->minimap->mapy, cub->map->tot_rows, cub->map_cols);
}
