/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:59:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/26 01:03:41 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_map	*list_to_map(t_list **list, int tot_cols)
{
	t_map	*map;
	t_node	*cur;
	int		i;

	map = init_matrix((*list)->tot_rows, tot_cols);
	cur = (*list)->head;
	i = 0;
	while (i < map->tot_rows)
	{
		map->map[i] = cur->symbol;
		cur->symbol = NULL;
		cur = cur->next;
		i++;
	}
	return (map);
}

static int	ft_str_end_trim(char *line)
{
	int		i;

	if (!line)
		return (0);
	i = ft_strlen(line);
	while (line[i] && line[i] == ' ')
		i--;
	return (i);
}

static char	*fill_line_of_list(char *line)
{
	char	*map_line;
	int		len;
	int		i;

	len = ft_str_end_trim(line);
	map_line = malloc(sizeof(map_line) * (len + 1));
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

static int	map_line_is_valid(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != ZERO && line[i] != WALL && line[i] != SPACE &&
		line[i] != NORTH && line[i] != SOUTH && line[i] != EAST &&
		line[i] != WEST && line[i] != UP_DOOR_AT_UP && line[i] != UP_DOOR_AT_DOWN \
		&& line[i] != UP_DOOR_AT_LEFT && line[i] != UP_DOOR_AT_RIGHT \
		&& line[i] != DOWN_DOOR_AT_UP && line[i] != DOWN_DOOR_AT_DOWN \
		&& line[i] != DOWN_DOOR_AT_LEFT && line[i] != DOWN_DOOR_AT_RIGHT)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_isspace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

static int	is_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid_elem(char *line)
{
	if (ft_strnstr(line, PRT_NORTH, ft_strlen(PRT_NORTH)) \
	&& line[ft_strlen(PRT_NORTH)] == ' ')
		return (NO);
	else if (ft_strnstr(line, PRT_SOUTH, ft_strlen(PRT_SOUTH)) \
	&& line[ft_strlen(PRT_SOUTH)] == ' ')
		return (SO);
	else if (ft_strnstr(line, PRT_EAST, ft_strlen(PRT_EAST)) \
	&& line[ft_strlen(PRT_EAST)] == ' ')
		return (EA);
	else if (ft_strnstr(line, PRT_WEST, ft_strlen(PRT_WEST)) \
	&& line[ft_strlen(PRT_WEST)] == ' ')
		return (WE);
	else if (ft_strnstr(line, PRT_UP, ft_strlen(PRT_UP)) \
	&& line[ft_strlen(PRT_UP)] == ' ')
		return (UP);
	else if (ft_strnstr(line, PRT_LOW, ft_strlen(PRT_LOW)) \
	&& line[ft_strlen(PRT_LOW)] == ' ')
		return (DOWN);
	else if (ft_strnstr(line, PRT_FLOOR, ft_strlen(PRT_FLOOR)) \
	&& line[ft_strlen(PRT_FLOOR)] == ' ')
		return (F);
	else if (ft_strnstr(line, PRT_CEIL, ft_strlen(PRT_CEIL)) \
	&& line[ft_strlen(PRT_CEIL)] == ' ')
		return (C);
	else if (line[0] == '1')
		return (TOT);
	return (0);
}

static void	insert_txtrs(t_cub3d **cub3d, char *line, int txtr_type)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split_spaces(line);
	if (!split)
		return ;
	while (split[++i])
		insert_txtrs_tail((*cub3d)->textures, split[i], txtr_type);
	destroy_split(&split);
}

static t_cub3d	*fill_in_cub(int fd)
{
	t_cub3d	*cub3d;
	t_list	*list;
	char	*line;
	int		i;

	cub3d = init_cub();
	list = init_list();
	if (!list)
	{
		free(cub3d);
		return (NULL);
	}
	line = (char *)1;
	while (line)
	{
		line = get_next_line(fd);
		if (line && !is_only_spaces(line) && ft_strlen(line) > 0)
		{
			i = 0;
			while (ft_isspace(line[i]))
				i++;
			if (line[i] && is_valid_elem(&line[i]) > 0 && is_valid_elem(&line[i]) != TOT)
				insert_txtrs(&cub3d, &line[i], is_valid_elem(&line[i]));
			else if (line[i] && is_valid_elem(&line[i]) == TOT && map_line_is_valid(line))
			{
				insert_map_tail(list, fill_line_of_list(line));
				if (ft_str_end_trim(line) > cub3d->map_cols)
					cub3d->map_cols = ft_str_end_trim(line);
			}
			else
			{
				free(line);
				destroy_list(&list);
				if (cub3d)
					destroy_cub(&cub3d);
				return (NULL);
			}
		}
		free(line);
	}
	if (list && cub3d)
	{
		cub3d->map = list_to_map(&list, cub3d->map_cols);
		destroy_list(&list);
	}
	return (cub3d);
}

void	print_map(t_map *map)
{
	int	i;

	i = -1;
	while (map->map && map->map[++i])
		printf("%s", map->map[i]);
}

int	main(int ac, char *av[])
{
	t_cub3d	*cub3d;
	int		fd;

	if (ac == 2 && ft_strnstr(&av[1][ft_strlen(av[1]) \
	- 4], ".cub", ft_strlen(av[1])))
	{
		fd = open(av[1], O_RDONLY, 0777);
		if (fd <= 0)
			return (0);
		cub3d = fill_in_cub(fd);
		close(fd);
		//print_map(cub3d->map);
		//display_in_canvas(cub3d);
		print_map(cub3d->map);
		if (cub3d)
			destroy_cub(&cub3d);
	}
	return (0);
}
