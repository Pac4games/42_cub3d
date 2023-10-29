/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_inits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/29 16:09:03 by mnascime         ###   ########.fr       */
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
	return (1);
}

void	init_minimap(t_cub3d *cub)
{
	cub->minimap = malloc(sizeof(*cub->minimap));
	if (!cub->minimap)
		return ;
	cub->minimap->mapxi = \
	update_display_x(cub->map->tot_rows, cub->map_cols, -1, -1);
	if (!cub->minimap->mapxi)
	{
		free(cub->minimap);
		return ;
	}
	cub->minimap->mapyi = \
	update_display_y(cub->map->tot_rows, cub->map_cols, -1, -1);
	if (!cub->minimap->mapyi)
	{
		destroy_matrix(cub->minimap->mapxi, cub->map->tot_rows);
		free(cub->minimap);
		return ;
	}
	cub->minimap->mapxf = \
	update_display_x(cub->map->tot_rows, cub->map_cols, -1, -1);
	if (!cub->minimap->mapxf)
	{
		destroy_matrix(cub->minimap->mapxi, cub->map->tot_rows);
		destroy_matrix(cub->minimap->mapyi, cub->map->tot_rows);
		free(cub->minimap);
		return ;
	}
	calc_sqr_end(cub->minimap->mapxf, cub->map->tot_rows, cub->map_cols);
	cub->minimap->mapyf = \
	update_display_y(cub->map->tot_rows, cub->map_cols, -1, -1);
	if (!cub->minimap->mapyf)
	{
		destroy_matrix(cub->minimap->mapxi, cub->map->tot_rows);
		destroy_matrix(cub->minimap->mapxf, cub->map->tot_rows);
		destroy_matrix(cub->minimap->mapyi, cub->map->tot_rows);
		free(cub->minimap);
		return ;
	}
	calc_sqr_end(cub->minimap->mapyf, cub->map->tot_rows, cub->map_cols);
}
