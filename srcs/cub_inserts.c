/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_inserts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/26 16:27:47 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	insert_map_tail(t_list *list, int *data, int len)
{
	t_node	*new_node;

	new_node = init_node();
	if (!new_node)
		return ;
	new_node->symbol = data;
	new_node->tot_cols = len;
	if (list->tail)
	{
		new_node->prev = list->tail;
		list->tail->next = new_node;
	}
	else
		list->head = new_node;
	list->tail = new_node;
	(list->tot_rows)++;
}

void	insert_txtrs_tail(t_all_txtrs *txtrs, char *data, int txtr_type)
{
	t_txtr	*new_txtr;

	new_txtr = init_single_txtr();
	if (!new_txtr)
		return ;
	new_txtr->type = txtr_type;
	new_txtr->path = data;
	if (txtrs->tail)
	{
		new_txtr->prev = txtrs->tail;
		txtrs->tail->next = new_txtr;
	}
	else
		txtrs->head = new_txtr;
	txtrs->tail = new_txtr;
	(txtrs->tot_txtrs)++;
}

t_map	*list_to_map(t_list **list, int map_cols)
{
	t_map	*map;
	t_node	*cur;
	int		i;
	int		f;

	map = init_matrix((*list)->tot_rows, map_cols);
	cur = (*list)->head;
	i = 0;
	while (i < map->tot_rows)
	{
		map->map[i] = cur->symbol;
		f = cur->tot_cols;
		while (f < map_cols)
		{
			map->map[i][f] = NSPACE;
			f++;
		}
		cur->symbol = NULL;
		cur = cur->next;
		i++;
	}
	destroy_list(list);
	return (map);
}

void	insert_txtrs(t_cub3d **cub3d, char *line, int txtr_type)
{
	t_txtr	*new_txtr;
	char	**split;
	int		i;

	i = 0;
	split = ft_split_spaces(line);
	if (!split)
		return ;
	while (split[++i])
	{
		insert_txtrs_tail((*cub3d)->textures, split[i], txtr_type);
		if ((*cub3d)->cur_txtrs)
		{
			new_txtr = (*cub3d)->cur_txtrs->head;
			while (new_txtr)
			{
				if (new_txtr->type == txtr_type)
				{
					destroy_split(&split);
					return ;
				}
				new_txtr = new_txtr->next;
			}
			insert_txtrs_tail((*cub3d)->cur_txtrs, split[i], txtr_type);
		}
		else
			insert_txtrs_tail((*cub3d)->cur_txtrs, split[i], txtr_type);
	}
	destroy_split(&split);
}
