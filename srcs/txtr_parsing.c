/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txtr_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:44:35 by paugonca          #+#    #+#             */
/*   Updated: 2023/11/26 15:40:38 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	insert_colors(t_cub3d *cub, char **split, int type, int i)
{
	if (type == F)
		cub->textures[type]->floor[i] = (ft_atoi(split[0]) << 16 \
		| ft_atoi(split[1]) << 8 | ft_atoi(split[2]));
	else if (type == C)
		cub->textures[type]->ceiling[i] = (ft_atoi(split[0]) << 16 \
		| ft_atoi(split[1]) << 8 | ft_atoi(split[2]));
}

int	parse_colors(t_cub3d *cub, char *line, int type)
{
	int		i;
	int		f;
	char	**split;
	char	**color_split;

	split = ft_split(&line[2], ' ');
	if (!split)
		print_err_cub("failed to allocate memory", cub);
	i = -1;
	while (split[++i])
	{
		if (ft_strlen(split[i]) < 5 || ft_strlen(split[i]) > 11 + 1)
		{
			free_mtx(split);
			return (print_err_ret("incorrect color formatting"));
		}
	}
	i = -1;
	while (++i < cub->textures[type]->levels)
	{
		color_split = ft_split(split[i], ',');
		if (!color_split)
		{
			free_mtx(split);
			print_err_cub("failed to allocate memory", cub);
		}
		f = -1;
		while (++f <= 2)
		{
			if (ft_atoi(color_split[f]) < 0 || ft_atoi(color_split[f]) > 255
				|| !str_isdigit(color_split[f]))
			{
				free_mtx(split);
				free_mtx(color_split);
				return (print_err_ret("incorrect color formatting"));
			}
		}
		insert_colors(cub, color_split, type, i);
		free_mtx(color_split);
	}
	free_mtx(split);
	return (1);
}
/*
int	parse_textures(t_cub3d *cub, char *line, int type)
{
	int		i;
	int		*fds;
	void	**tmp;
	char	**split;

	split = ft_split(&line[3], ' ');
	if (!split)
		print_err_cub("failed to allocate memory", cub);
	fds = malloc(mtx_len(split) * sizeof(int));
	i = -1;
	while (split[++i])
	{
		fds[i] = open(split[i], O_RDONLY);
		if (fds[i] == -1)
			print_err_cub("error opening file", cub);
	}
}
*/
