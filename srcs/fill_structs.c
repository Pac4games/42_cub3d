/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/22 16:30:37 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**solo_matrix(int rows, int cols)
{
	int		i;
	char	**mat;

	mat = malloc((sizeof(char *) + 1) * rows);
	if (!mat)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		mat[i] = malloc((sizeof(char) + 1) * cols);
		if (!mat[i])
		{
			i = -1;
			while (mat[++i])
				free(mat[i]);
			free(mat);
			return (NULL);
		}
		i++;
	}
	mat[i] = NULL;
	return (mat);
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
			cub->map->map[i][f++] = SPACE;
		cub->map->map[i][f] = '\0';
		free(cur->symbol);
		cur->symbol = NULL;
		cur = cur->next;
		i++;
	}
	destroy_list(list);
}

int	parse_colors(t_cub3d *cub, char *line, int type)
{
	int		i;
	char	**split;

	if (ft_strlen(&line[2]) < 5 || ft_strlen(&line[2]) > 11)
		return (print_err_ret("incorrect color formatting"));
	split = ft_split(&line[2], ',');
	if (!split || mtx_len(split) != 3)
		return (print_err_ret("incorrect color formatting"));
	i = -1;
	while (++i <= 2)
		if (ft_atoi(split[i]) < 0 || ft_atoi(split[i]) > 255)
			return (print_err_ret("incorrect color formatting"));	
	if (type == F)
	{
		cub->all_txtrs->textures->floor->r = ft_atoi(split[0]);
		cub->all_txtrs->textures->floor->g = ft_atoi(split[1]);
		cub->all_txtrs->textures->floor->b = ft_atoi(split[2]);
	}
	else if (type == C)
	{
		cub->all_txtrs->textures->ceiling->r = ft_atoi(split[0]);
		cub->all_txtrs->textures->ceiling->g = ft_atoi(split[1]);
		cub->all_txtrs->textures->ceiling->b = ft_atoi(split[2]);
	}
	return (1);
}

void	insert_txtrs(t_cub3d **cub, char *line, int txtr_type)
{
	char		**split;
	int			i;
	static int	f;

	i = 0;
	if (txtr_type == F || txtr_type == C)
		if (!parse_colors(*cub, line, txtr_type))
			return ;
	printf("Floor:\nR: %d\nG: %d\nB: %d\n\n",
			(*cub)->all_txtrs->textures->floor->r,
			(*cub)->all_txtrs->textures->floor->g,
			(*cub)->all_txtrs->textures->floor->b);
	printf("Ceiling:\nR: %d\nG: %d\nB: %d\n",
			(*cub)->all_txtrs->textures->ceiling->r,
			(*cub)->all_txtrs->textures->ceiling->g,
			(*cub)->all_txtrs->textures->ceiling->b);
	if (f > TOT - 1)
		return ;
	i += ft_strlen(conv_to_txtr_text(txtr_type));
	split = ft_split_spaces(&line[i]);
	if (!split)
		return ;
	i = mtx_len(split);
	if (!(*cub)->all_txtrs)
		(*cub)->all_txtrs = init_txtrs();
	(*cub)->all_txtrs->textures[f].path = split;
	(*cub)->all_txtrs->textures[f].type = txtr_type;
	(*cub)->all_txtrs->textures[f].levels = i;
	(*cub)->all_txtrs->textures[f].color = 0;
	f++;
}
