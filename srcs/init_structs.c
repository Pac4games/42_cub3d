/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/12/07 16:39:29 by paugonca         ###   ########.fr       */
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

static t_txtrs	*init_txtrs_utils(t_txtrs *txtrs, int times)
{
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
	return (init_txtrs_utils(txtrs, times));
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
