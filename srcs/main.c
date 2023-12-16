/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:59:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/12/13 18:59:31 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	*fill_line_of_list(char *line)
{
	int	*map_line;
	int	len;
	int	i;

	len = ft_str_end_trim(line);
	map_line = malloc(sizeof(map_line) * len);
	if (!map_line)
		return (0);
	i = 0;
	while (i < len)
	{
		map_line[i] = line[i];
		i++;
	}
	map_line[i] = '\0';
	return (map_line);
}

static int	insert_line(t_cub3d *cub, t_list *list, char *line, int *check)
{
	int		i;
	int		result;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] && is_valid_elem(&line[i]) != TOT)
	{
		if (*check == 2)
			return (print_err_ret("invalid element line"));
		result = insert_txtrs(cub, &line[i], is_valid_elem(&line[i]));
		if (result)
			*check = 1;
		return (result);
	}
	else if (line[i] && is_valid_elem(&line[i]) == TOT)
	{
		insert_map_tail(list, fill_line_of_list(line), ft_str_end_trim(line));
		if (ft_str_end_trim(line) > cub->map_cols)
			cub->map_cols = ft_str_end_trim(line);
		*check = 2;
	}
	else
		return (print_err_ret("invalid map formatting"));
	return (1);
}

static int	fill_in_cub_utils(t_cub3d *cub, int fd, char *line, t_list *list)
{
	int	check;
	int	result;

	check = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (line && !is_only_spaces(line) && ft_strlen(line) > 0 \
		&& line[0] != '\n')
		{
			result = insert_line(cub, list, line, &check);
			if (check == 3 || !result)
			{
				free(line);
				destroy_list(list);
				if (cub)
					destroy_cub(cub);
				return (result);
			}
		}
		else if (check == 2)
			check = 3;
		free(line);
	}
	return (1);
}

int	fill_in_cub(t_cub3d *cub, int fd)
{
	t_list	list;
	char	*line;

	init_list(&list);
	line = (char *)1;
	if (!fill_in_cub_utils(cub, fd, line, &list))
		return (0);
	if (list.head && cub)
		list_to_map(&list, cub);
	return (1);
}

int	main(int ac, char **av)
{
	t_cub3d	cub;
	int		fd;

	if (ac == 2)
	{
		if (!ft_strnstr(&av[1][ft_strlen(av[1]) - 4], ".cub", ft_strlen(av[1])))
			return (print_err_ret("invalid map format") + 1);
		fd = open(av[1], O_RDONLY);
		if (fd <= 0)
			return (print_err_ret("failed to open map") + 1);
		ft_memset(&cub, 0, sizeof(cub));
		if (!fill_in_cub(&cub, fd) || close(fd) == -1 \
		|| !cub.map || !check_map(cub.map->map, (cub.elems >> (DO + 1) & 1)))
		{
			if (cub.map)
				destroy_cub(&cub);
			return (EXIT_FAILURE);
		}
		cub.sqr_size = get_sqr_size();
		init_player_pos(&cub, -1, -1);
		init_raycaster(&cub);
		display_in_canvas(&cub);
	}
	return (0);
}
