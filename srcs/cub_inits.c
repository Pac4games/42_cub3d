/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_inits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/26 16:24:02 by mnascime         ###   ########.fr       */
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

t_list	*init_list(void)
{
	t_list	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->tot_rows = 0;
	return (list);
}

t_txtr	*init_single_txtr(void)
{
	t_txtr	*txtr;

	txtr = malloc(sizeof(*txtr));
	if (!txtr)
		return (NULL);
	txtr->path = NULL;
	txtr->color = 0;
	txtr->type = 0;
	txtr->next = NULL;
	txtr->prev = NULL;
	return (txtr);
}

t_all_txtrs	*init_txtrs(void)
{
	t_all_txtrs	*txtrs;

	txtrs = malloc(sizeof(*txtrs));
	if (!txtrs)
		return (NULL);
	txtrs->head = NULL;
	txtrs->tail = NULL;
	txtrs->tot_txtrs = 0;
	txtrs->tot_lvls = 0;
	return (txtrs);
}

t_cub3d	*init_cub(void)
{
	t_cub3d	*cub;

	cub = malloc(sizeof(*cub));
	if (!cub)
		return (NULL);
	cub->textures = init_txtrs();
	cub->cur_txtrs = init_txtrs();
	if (!cub->textures)
	{
		free(cub);
		return (NULL);
	}
	cub->map = NULL;
	cub->map_cols = 0;
	return (cub);
}
