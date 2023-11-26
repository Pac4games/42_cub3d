/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:54:46 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/26 20:40:53 by mnascime         ###   ########.fr       */
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
	mat[i] = '\0';
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

void	fill_txtrs(t_cub3d *cub, int type, int i)
{
	int	counter;

	if (type == F || type == C || type == TOT)
		return ;
	cub->textures[type]->imgs = malloc(sizeof(void *) * i);
	if (!cub->textures[type]->imgs)
		return ;
	cub->textures[type]->bits_per_pixel = malloc(sizeof(int) * i);
	if (!cub->textures[type]->bits_per_pixel)
	{
		free(cub->textures[type]->imgs);
		return ;
	}
	cub->textures[type]->line_length = malloc(sizeof(int) * i);
	if (!cub->textures[type]->line_length)
	{
		free(cub->textures[type]->imgs);
		free(cub->textures[type]->bits_per_pixel);
		return ;
	}
	cub->textures[type]->endian = malloc(sizeof(int) * i);
	if (!cub->textures[type]->endian)
	{
		free(cub->textures[type]->imgs);
		free(cub->textures[type]->line_length);
		free(cub->textures[type]->bits_per_pixel);
		return ;
	}
	counter = -1;
	while (++counter < i)
		cub->textures[type]->imgs[counter] = mlx_xpm_file_to_image(cub->mlx, \
		cub->textures[type]->path[counter], \
		&cub->textures[type]->width[counter], \
		&cub->textures[type]->height[counter]);
	cub->textures[type]->addrs = malloc(sizeof(char *) * (i + 1));
	if (!cub->textures[type]->addrs)
	{
		free(cub->textures[type]->imgs);
		free(cub->textures[type]->endian);
		free(cub->textures[type]->line_length);
		free(cub->textures[type]->bits_per_pixel);
		return ;
	}
	counter = -1;
	while (++counter < i)
		cub->textures[type]->addrs[counter] = mlx_get_data_addr(cub->textures[type]->imgs[counter], \
	&cub->textures[type]->bits_per_pixel[counter], &cub->textures[type]->line_length[counter], \
	&cub->textures[type]->endian[counter]);
	cub->textures[type]->addrs[counter] = '\0';
}

void	insert_txtrs(t_cub3d *cub, char *line, int txtr_type)
{
	char		**split;
	int			i;

	i = 0;
	if (txtr_type > TOT - 1)
		return ;
	i += ft_strlen(conv_to_txtr_text(txtr_type));
	split = ft_split_spaces(&line[i]);
	if (!split)
		return ;
	i = mtx_len(split);
	if (!cub->textures)
	{
		cub->textures = malloc(TOT * sizeof(t_txtrs *));
		if (!cub->textures)
			return ;
	}
	cub->textures[txtr_type] = init_txtrs(i);
	cub->textures[txtr_type]->path = split;
	cub->textures[txtr_type]->type = txtr_type;
	cub->textures[txtr_type]->levels = i;
	cub->tot_txtrs++;
	register_elem(cub, txtr_type);
	if (txtr_type == F || txtr_type == C)
	{
		if (!parse_colors(cub, line, txtr_type))
			return ;
	}
}
