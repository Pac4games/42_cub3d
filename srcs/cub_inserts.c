/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_inserts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/09 11:35:36 by paugonca         ###   ########.fr       */
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
			cub->map->map[i][f] = SPACE;
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
	char		**split;
	int			i;
	static int	f = 0;

	i = 0;
	if (f > TOT - 1)
		return ;
	i += ft_strlen(conv_to_txtr_text(txtr_type));
	split = ft_split_spaces(&line[i]);
	if (!split)
		return ;
	i = 0;
	while (split[i])
		i++;
	if (!(*cub)->all_txtrs)
		(*cub)->all_txtrs = init_txtrs();
	(*cub)->all_txtrs->textures[f].path = split;
	(*cub)->all_txtrs->textures[f].type = txtr_type;
	(*cub)->all_txtrs->textures[f].levels = i;
	(*cub)->all_txtrs->textures[f].color = 0;
	f++;
}
