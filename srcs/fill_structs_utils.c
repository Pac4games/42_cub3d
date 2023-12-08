/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:19 by paugonca          #+#    #+#             */
/*   Updated: 2023/12/08 22:11:54 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	fill_txtrs_utils1(t_cub3d *cub, int type, int i)
{
	cub->txtrs[type]->endian = malloc(sizeof(int) * i);
	if (!cub->txtrs[type]->endian)
	{
		free(cub->txtrs[type]->imgs);
		free(cub->txtrs[type]->line_length);
		free(cub->txtrs[type]->bpp);
		return (0);
	}
	cub->txtrs[type]->addrs = malloc(sizeof(char *) * (i + 1));
	if (!cub->txtrs[type]->addrs)
	{
		free(cub->txtrs[type]->endian);
		free(cub->txtrs[type]->line_length);
		free(cub->txtrs[type]->bpp);
		return (0);
	}
	return (1);
}

int	fill_txtrs_utils2(t_cub3d *cub, int type, int i)
{
	int	counter;

	counter = -1;
	while (++counter < i)
	{
		cub->txtrs[type]->imgs[counter] = mlx_xpm_file_to_image(cub->mlx, \
		cub->txtrs[type]->path[counter], \
		&cub->txtrs[type]->width[counter], \
		&cub->txtrs[type]->height[counter]);
		if (!cub->txtrs[type]->imgs[counter])
			return (print_err_ret("one or more invalid textures"));
	}
	counter = -1;
	while (++counter < i)
		cub->txtrs[type]->addrs[counter] = \
	mlx_get_data_addr(cub->txtrs[type]->imgs[counter], \
	&cub->txtrs[type]->bpp[counter], &cub->txtrs[type]->line_length[counter], \
	&cub->txtrs[type]->endian[counter]);
	cub->txtrs[type]->addrs[counter] = NULL;
	return (1);
}

void	insert_txtrs_utils(t_cub3d *cub, int txtr_type, char *line, int i)
{
	if (i > cub->max_level)
		cub->max_level = i;
	cub->tot_txtrs++;
	register_elem(cub, txtr_type);
	if (txtr_type == F || txtr_type == C)
	{
		if (!parse_colors(cub, line, txtr_type))
		{
			free(line);
			destroy_cub(cub);
			exit(EXIT_FAILURE);
		}
	}
}
