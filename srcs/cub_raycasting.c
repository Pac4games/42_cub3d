/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:07:44 by mnascime          #+#    #+#             */
/*   Updated: 2023/12/07 15:44:47 by paugonca         ###   ########.fr       */
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

static char	real_distance_calc(t_cub3d *cub, t_ray *ray)
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
		if (sqr == WALL || sqr == DOOR)
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

static void	select_img_n_side(t_cub3d *cub, t_ray *ray, t_vector *vec, char sqr)
{
	double	wall_x;
	int		type;

	if (ray->side == 0)
		wall_x = cub->player_y + ray->real_dist * ray->dir_y;
	else
		wall_x = cub->player_x + ray->real_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	if (sqr == DOOR)
		type = DO;
	else if (ray->side == 0 && ray->dir_x > 0)
		type = EA;
	else if (ray->side == 0 && ray->dir_x < 0)
		type = WE;
	else if (ray->side == 1 && ray->dir_y > 0)
		type = SO;
	else if (ray->side == 1 && ray->dir_y < 0)
		type = NO;
	else
		return ;
	ray->x_txtr = (int)(wall_x * \
	cub->txtrs[type]->width[cub->level % cub->txtrs[type]->levels]);
	ray->x_txtr = cub->txtrs[type]->width[cub->level \
	% cub->txtrs[type]->levels] - ray->x_txtr - 1;
	draw_txtrs(cub, ray, vec, type);
}

static void	raycast_draw_walls(t_cub3d *cub, t_ray *ray, char sqr, int i)
{
	int			line_height;
	t_vector	vec;
	int			counter;

	counter = -1;
	if (ray->side == 0)
		ray->real_dist = (ray->dist_x - ray->delta_x);
	else
		ray->real_dist = (ray->dist_y - ray->delta_y);
	line_height = (int)(WHEI / ray->real_dist);
	vec.xi = i;
	vec.xf = i;
	vec.yi = -line_height / 2 + WHEI / 2;
	vec.yf = line_height / 2 + WHEI / 2;
	while (++counter < vec.yi)
		my_mlx_pixel_put(cub, vec.xi, counter, \
		cub->txtrs[C]->ceiling[cub->level % (cub->txtrs[C]->levels)]);
	counter = vec.yf - 1;
	while (++counter < WHEI)
		my_mlx_pixel_put(cub, vec.xi, counter, \
		cub->txtrs[F]->floor[cub->level % (cub->txtrs[F]->levels)]);
	select_img_n_side(cub, ray, &vec, sqr);
}

void	raycasting(t_cub3d *cub)
{
	int		i;
	char	sqr;
	double	camera_ray;
	t_ray	ray;

	i = 0;
	ft_memset(&ray, 0, sizeof(ray));
	while (i < WWID)
	{
		ray.x = get_player_sqr(cub, 1);
		ray.y = get_player_sqr(cub, 0);
		camera_ray = 1.7 * WWID / WHEI * i / (double) WWID - 0.85 * WWID / WHEI;
		ray.dir_x = cub->dir_x + cub->plane_x * camera_ray;
		ray.dir_y = cub->dir_y + cub->plane_y * camera_ray;
		ray.delta_x = fabs(1 / ray.dir_x);
		ray.delta_y = fabs(1 / ray.dir_y);
		raycast_step_calc(cub, &ray);
		sqr = real_distance_calc(cub, &ray);
		raycast_draw_walls(cub, &ray, sqr, i);
		i++;
	}
}
