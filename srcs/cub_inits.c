/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_inits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/27 16:05:28 by mnascime         ###   ########.fr       */
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

int	init_cub(t_cub3d *cub)
{
	cub->textures = NULL;
	cub->cur_txtrs = NULL;
	cub->map = NULL;
	cub->map_cols = 0;
	return (1);
}

/*
int	init_cub(t_cub3d *cub)
{
	cub = malloc(sizeof(*cub));
	if (!cub)
		return (1);
	cub->textures = init_txtrs();
	if (!cub->textures)
	{
		free(cub);
		return (1);
	}
	cub->cur_txtrs = init_txtrs();
	if (!cub->cur_txtrs)
	{
		free(cub);
		free(cub->textures);
		return (1);
	}
	cub->map = NULL;
	cub->map_cols = 0;
	return (0);
}
*/
