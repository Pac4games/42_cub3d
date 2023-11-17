/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:07:44 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/13 11:37:53 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rot_raycaster(t_cub3d *cub, double rot)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = cub->dir_x;
	old_planex = cub->plane_x;
	cub->dir_x = cub->dir_x * cosf(rot) - cub->dir_y * sinf(rot);
	cub->dir_y = old_dirx * sinf(rot) + cub->dir_y * cosf(rot);
	cub->plane_x = cub->plane_x * cosf(rot) - cub->plane_y * sinf(rot);
	cub->plane_y = old_planex * sinf(rot) + cub->plane_y * cosf(rot);
}

void	init_raycaster(t_cub3d *cub)
{
	if (cub->direction == NORTH)
	{
		cub->dir_y = -1;
		cub->plane_x = 0.6;
	}
	else if (cub->direction == EAST)
	{
		cub->dir_x = 1;
		cub->plane_y = 0.6;
	}
	else if (cub->direction == SOUTH)
	{
		cub->dir_y = 1;
		cub->plane_x = -0.6;
	}
	else
	{
		cub->dir_x = -1;
		cub->plane_y = -0.6;
	}
}

static int	real_distance_calc(t_cub3d *cub, t_ray *ray)
{
	int		hit;
	char	sqr;

	hit = 0;
	while (hit == 0)
	{
		if (ray->dist_x < ray->dist_y)
		{
			ray->dist_x += ray->delta_x;
			ray->x += ray->xstep;
			ray->side = 0;
		}
		else
		{
			ray->dist_y += ray->delta_y;
			ray->y += ray->ystep;
			ray->side = 1;
		}
		sqr = cub->map->map[get_sqr_coord(cub, ray->y, \
		ray->x, 0)][get_sqr_coord(cub, ray->y, ray->x, 1)];
		if (sqr == WALL || sqr == DOOR_UP || sqr == DOOR_DOWN)
			hit = 1;
	}
	return (sqr);
}

static void	raycast_step_calc(t_cub3d *cub, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->xstep = -1;
		ray->dist_x = (cub->player_x - ray->x) * ray->delta_x;
	}
	else
	{
		ray->xstep = 1;
		ray->dist_x = (ray->x + 1.0 - cub->player_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->ystep = -1;
		ray->dist_y = (cub->player_y - ray->y) * ray->delta_y;
	}
	else
	{
		ray->ystep = 1;
		ray->dist_y = (ray->y + 1.0 - cub->player_y) * ray->delta_y;
	}
}

static void	raycast_draw_walls(t_cub3d *cub, t_ray *ray, char sqr, int i)
{
	int			line_height;
	int			color;
	t_vector	vec;

	if (ray->side == 0)
		ray->real_dist = (ray->dist_x - ray->delta_x);
	else
		ray->real_dist = (ray->dist_y - ray->delta_y);
	line_height = (int)(WHEI / ray->real_dist);
	vec.xi = i;
	vec.xf = i;
	vec.yi = -line_height / 2 + WHEI / 2;
	if (vec.yi < 0 || line_height < 0)
		vec.yi = 0;
	vec.yf = line_height / 2 + WHEI / 2;
	if (vec.yf >= WHEI || line_height < 0)
		vec.yf = WHEI - 1;
	if (sqr == DOOR_UP)
		color = 0x00FFFF;
	else if (sqr == DOOR_DOWN)
		color = 0xFF00FF;
	else
		color = 0X00ff00 / 2;
	draw_line(cub, &vec, color);
}

void	raycasting(t_cub3d *cub)
{
	int		i;
	char	sqr;
	double	camera_ray;
	t_ray	ray;

	i = 0;
	while (i < WWID)
	{
		ray.x = get_player_sqr(cub, 1);
		ray.y = get_player_sqr(cub, 0);
		camera_ray = 2 * i / (double) WWID - 1;
		ray.dir_x = cub->dir_x + cub->plane_x * camera_ray;
		ray.dir_y = cub->dir_y + cub->plane_y * camera_ray;
		ray.delta_x = fabs(1 / ray.dir_x);
		ray.delta_y = fabs(1 / ray.dir_y);
		raycast_step_calc(cub, &ray);
		sqr = real_distance_calc(cub, &ray);
		raycast_draw_walls(cub, &ray, sqr, i);
		//dda_side_selector(mlx, &ray, player, info);
		i++;
	}
}
