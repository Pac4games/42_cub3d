/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_inserts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/28 13:27:50 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	list->tot_rows++;
}

void	insert_txtrs_tail(t_all_txtrs *txtrs, char *data, int txtr_type)
{
	t_txtr	*new_txtr;
	size_t	i;

	new_txtr = init_single_txtr();
	if (!new_txtr)
		return ;
	new_txtr->type = txtr_type;
	new_txtr->path = malloc(sizeof(char) * (ft_strlen(data) + 1));
	if (!new_txtr->path)
		return ;
	i = -1;
	while (++i < ft_strlen(data))
		new_txtr->path[i] = data[i];
	new_txtr->path[i] = '\0';
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

void	list_to_map(t_list *list, t_cub3d *cub)
{
	t_node	*cur;
	int		i;
	int		f;

	init_matrix(cub, list->tot_rows, cub->map_cols);
	cur = list->head;
	i = 0;
	while (i < cub->map->tot_rows)
	{
		f = -1;
		while (++f < cur->tot_cols)
			cub->map->map[i][f] = cur->symbol[f];
		while (f < cub->map_cols)
		{
			cub->map->map[i][f] = NSPACE;
			f++;
		}
		free(cur->symbol);
		cur->symbol = NULL;
		cur = cur->next;
		i++;
	}
	destroy_list(list);
}

void	insert_txtrs(t_cub3d **cub, char *line, int txtr_type)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split_spaces(line);
	if (!split)
		return ;
	while (split[++i])
	{
		if (!(*cub)->textures)
			(*cub)->textures = init_txtrs();
		insert_txtrs_tail((*cub)->textures, split[i], txtr_type);
		if (i == 1)
		{
			if (!(*cub)->cur_txtrs)
				(*cub)->cur_txtrs = init_txtrs();
			insert_txtrs_tail((*cub)->cur_txtrs, split[i], txtr_type);
		}
	}
	destroy_split(&split);
}
