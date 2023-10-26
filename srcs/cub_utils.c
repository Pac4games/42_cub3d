/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:51:12 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/26 00:49:02 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_split(char ***split_location)
{
	int		i;
	char	**split;

	split = *split_location;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	*split_location = NULL;
}

void	insert_map_tail(t_list *list, char *data)
{
	t_node	*new_node;

	new_node = init_node();
	if (!new_node)
		return ;
	new_node->symbol = data;
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

double	**solo_matrix(int rows, int cols)
{
	int		i;
	double	**mat;

	mat = malloc(sizeof(*mat) * rows);
	if (!mat)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		mat[i] = malloc(sizeof(*(mat[i])) * cols);
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
	return (mat);
}

void	free_blocks(int rows, double **blockx, double **blocky)
{
	int	x;

	x = 0;
	while (x < rows)
	{
		free(blockx[x]);
		free(blocky[x]);
		x++;
	}
	free(blockx);
	free(blocky);
}
