/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/26 00:56:20 by mnascime         ###   ########.fr       */
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

t_cub3d	*init_cub(void)
{
	t_cub3d	*cub;

	cub = malloc(sizeof(*cub));
	if (!cub)
		return (NULL);
	cub->textures = init_txtrs();
	if (!cub->textures)
	{
		free(cub);
		return (NULL);
	}
	cub->map = NULL;
	cub->map_cols = 0;
	return (cub);
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

t_map	*init_matrix(int tot_rows, int tot_cols)
{
	t_map	*map;

	map = malloc(sizeof(*map));
	if (!map)
		return (NULL);
	map->tot_rows = tot_rows;
	map->tot_cols = tot_cols;
	map->map = malloc(sizeof(*(map->map)) * tot_rows);
	if (!map->map)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

void	destroy_list(t_list **list)
{
	t_node	*del;
	t_node	*next;

	if (!list || !(*list))
		return ;
	next = NULL;
	del = (*list)->head;
	while (del)
	{
		next = del->next;
		free(del);
		del = next;
	}
	free(*list);
	*list = NULL;
}

static void	destroy_txtrs_list(t_all_txtrs **txtrs)
{
	t_txtr	*del;
	t_txtr	*next;

	if (!txtrs || !(*txtrs))
		return ;
	next = NULL;
	del = (*txtrs)->head;
	while (del)
	{
		next = del->next;
		free(del);
		del = next;
	}
	free(*txtrs);
	*txtrs = NULL;
}

void	destroy_cub(t_cub3d **cub)
{
	t_map	*matrix;
	int		i;

	if (cub || !(*cub))
		return ;
	if (*cub && (*cub)->map)
	{
		matrix = (*cub)->map;
		i = -1;
		while (++i < matrix->tot_rows)
			free(matrix->map[i]);
		free(matrix);
		matrix = NULL;
		free((*cub)->map);
		(*cub)->map = NULL;
	}
	destroy_txtrs_list(&(*cub)->textures);
	free((*cub));
}
