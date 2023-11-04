/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_conv_enums.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:10:17 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/04 18:20:37 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	conv_to_map_num_door(char c)
{
	if (c == UP_DOOR_AT_UP)
		return (NUP_DOOR_AT_UP);
	else if (c == UP_DOOR_AT_DOWN)
		return (NUP_DOOR_AT_DOWN);
	else if (c == UP_DOOR_AT_LEFT)
		return (NUP_DOOR_AT_LEFT);
	else if (c == UP_DOOR_AT_RIGHT)
		return (NUP_DOOR_AT_RIGHT);
	else if (c == DOWN_DOOR_AT_UP)
		return (NDOWN_DOOR_AT_UP);
	else if (c == DOWN_DOOR_AT_DOWN)
		return (NDOWN_DOOR_AT_DOWN);
	else if (c == DOWN_DOOR_AT_LEFT)
		return (NDOWN_DOOR_AT_LEFT);
	else if (c == DOWN_DOOR_AT_RIGHT)
		return (NDOWN_DOOR_AT_RIGHT);
	return (0);
}

int	conv_to_map_num(char c)
{
	if (c == ZERO)
		return (NZERO);
	else if (c == WALL)
		return (NWALL);
	else if (c == SPACE)
		return (NSPACE);
	else if (c == NORTH)
		return (NNORTH);
	else if (c == SOUTH)
		return (NSOUTH);
	else if (c == EAST)
		return (NEAST);
	else if (c == WEST)
		return (NWEST);
	else if (conv_to_map_num_door(c))
		return (conv_to_map_num_door(c));
	else
		return (0);
}

char	*conv_to_txtr_text(char c)
{
	if (c == NO)
		return (PRT_NORTH);
	else if (c == SO)
		return (PRT_SOUTH);
	else if (c == EA)
		return (PRT_EAST);
	else if (c == WE)
		return (PRT_WEST);
	else if (c == F)
		return (PRT_FLOOR);
	else if (c == C)
		return (PRT_CEIL);
	else if (c == UP)
		return (PRT_UP);
	else
		return (PRT_LOW);
}
