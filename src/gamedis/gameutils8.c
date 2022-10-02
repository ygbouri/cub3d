/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:54:05 by ygbouri           #+#    #+#             */
/*   Updated: 2022/10/02 18:23:19 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	paintceiling(t_cub *all, int top)
{
	int	i;

	i = 0;
	while (i < top)
	{
		my_mlx_pixel_put(all->img, all->ray->colid, i, all->info.cc);
		i++;
	}
}

void	paintfloor(t_cub *all, int bottom)
{
	int	i;

	i = bottom;
	while (i < H)
	{
		my_mlx_pixel_put(all->img, all->ray->colid, i, all->info.fc);
		i++;
	}
}

void	renderthreeD(t_cub *all)
{
	int		i;
	int		wallstripheight;
	int		topofwall;
	int		bottomofwall;
	double	correctdistance;
	double	distoprojectionplane;
	double	wallheight;

	i = 0;
	correctdistance = 0;
	correctdistance = all->ray->distance * cos(all->ray->rayangle - all->p->rotationangl);
	distoprojectionplane = (W / 2.0) / tan(all->ray->fovangle / 2.0);
	wallheight = (16 / correctdistance) * distoprojectionplane;
	wallstripheight = (int)wallheight;
	topofwall = (H / 2.0) - (wallstripheight / 2.0);
	bottomofwall = (H / 2.0) + (wallstripheight / 2.0);
	if (topofwall < 0 || topofwall > H)
		topofwall = 0;
	if (bottomofwall > H || bottomofwall < 0)
		bottomofwall = H;
	i = topofwall;
	paintceiling(all, topofwall);
	paintfloor(all, bottomofwall);
	while (i < bottomofwall)
	{
		my_mlx_pixel_put(all->img, all->ray->colid, i, 0x3A3845);
		i++;
	}
}

void	fovminimap(t_cub *all)
{
	double 		inc_angle;
	t_glpos		glpos;

	inc_angle = all->ray->fovangle / W;
	//init_gl(&glpos, all);
	initialrayvar(all);
	//all->compteur = 0;
	while (all->ray->colid < all->ray->numrays)
	{
		hintercept(all, all->ray->rayangle, &glpos);
		renderthreeD(all);
		all->ray->rayangle += inc_angle;
		all->ray->colid++;
		//all->compteur += 1;
	}
	//printf("rays %d compteur%d\n", all->ray->numrays,all->ray->colid);
}


void	affichminimap(t_cub *all, int ch)
{
	int	x;
	int	y;
	all->node = NULL;
	checkplayer(all, ch);
	x = all->pscreenx - 64;
	y = all->pscreeny - 64;
	all->distancexx = x;
	all->distanceyy = y;
	all->posx = all->pscreenx;
	all->posy = all->pscreeny;
	if(ch == 0)
	{
		all->p = iniatialiserp(all);
		detectang(all);
	}
	fovminimap(all);
	paintmap(all, all->img, ch);
	paintplayer(all, ch);
	mlx_put_image_to_window(all->mlx, all->mlx_win, all->img->img, 0, 0);
}