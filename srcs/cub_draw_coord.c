/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_coord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:41:33 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/28 12:59:15 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	begin_coord(t_vector *vector, int x, int y)
{
	vector->xi = x;
	vector->yi = y;
}

void	end_coord(t_vector *vector, int x, int y)
{
	vector->xf = x;
	vector->yf = y;
}
