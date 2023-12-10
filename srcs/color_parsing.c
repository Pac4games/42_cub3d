/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:44:35 by paugonca          #+#    #+#             */
/*   Updated: 2023/12/10 12:38:31 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	insert_colors(t_cub3d *cub, char **split, int type, int i)
{
	if (type == F)
		cub->txtrs[type]->floor[i] = (ft_atoi(split[0]) << 16 \
		| ft_atoi(split[1]) << 8 | ft_atoi(split[2]));
	else if (type == C)
		cub->txtrs[type]->ceiling[i] = (ft_atoi(split[0]) << 16 \
		| ft_atoi(split[1]) << 8 | ft_atoi(split[2]));
}

//The "c" variable here stands for "color split", it's name was shortened to
//abide by the norm.
static int	parse_colors_utils(t_cub3d *cub, char **split, int i, int type)
{
	int		f;
	char	**c;

	while (++i < cub->txtrs[type]->levels)
	{
		c = ft_split(split[i], ',');
		if (!c)
		{
			free_mtx(split);
			print_err_cub("failed to allocate memory", cub);
		}
		f = -1;
		while (++f <= 2)
		{
			if (ft_atoi(c[f]) < 0 || ft_atoi(c[f]) > 255 || !str_isdigit(c[f]))
			{
				free_mtx(split);
				free_mtx(c);
				return (print_err_ret("incorrect color formatting"));
			}
		}
		insert_colors(cub, c, type, i);
		free_mtx(c);
	}
	return (1);
}

int	parse_colors(t_cub3d *cub, char *line, int type)
{
	int		i;
	int		check;
	char	**split;

	split = ft_split_spaces(&line[2]);
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
	check = parse_colors_utils(cub, split, i, type);
	if (!check)
		return (check);
	free_mtx(split);
	return (1);
}
