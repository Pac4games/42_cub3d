/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_conv_enums.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:10:17 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/09 11:46:28 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
