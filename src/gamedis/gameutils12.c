/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils12.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momayaz <momayaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:36:25 by momayaz           #+#    #+#             */
/*   Updated: 2022/10/17 18:36:53 by momayaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

void getwaltex(t_cub *all)
{
	if (all->ray->updirect && all->pos->hori_f)
		all->l7aj = 0;
	else if (all->ray->downdirect && all->pos->hori_f)
		all->l7aj = 3;
	else if (all->ray->leftdirect && all->pos->verti_f)
		all->l7aj = 2;
	else if (all->ray->rightdirect && all->pos->verti_f)
		all->l7aj = 1;
	if(all->map[(int)(all->pos->po.y / 16)][(int)(all->pos->po.x / 16)] == 'D')
		all->l7aj = 4;
	if((all->ray->updirect && all->pos->hori_f) && all->map[(int)((all->pos->po.y) / 16) - 1][(int)(all->pos->po.x / 16)] == 'D')
		all->l7aj = 4;
	if((all->ray->leftdirect && all->pos->verti_f) && all->map[(int)((all->pos->po.y) / 16)][(int)(all->pos->po.x / 16) - 1] == 'D')
		all->l7aj = 4;
}

void paintwalltex(t_cub *all, int i, int bottomofwall, double wallheight)
{
	double offSETX;
	int d;
	int offSETY;
	int txtColl;

	while (i < bottomofwall)
	{
		if (all->hitV){
			offSETX = all->pos->po.y / 16;
		}
		else
			offSETX = all->pos->po.x / 16;
		offSETX -= floor(offSETX);
		offSETX *= all->texture[all->l7aj].w;
		d = i + (wallheight / 2) - (H / 2);
		offSETY = d * ((float) all->texture[all->l7aj].w / wallheight);
		if (all->l7aj >= 0 && all->l7aj < 6){
			txtColl = (int)all->texture[all->l7aj].data[(all->texture[all->l7aj].w * offSETY) + (int)offSETX];
			my_mlx_pixel_put(all->img, all->ray->colid, i, txtColl);
		}
		i++;
	}
	all->l7aj = 0;
}

void	renderthreeD(t_cub *all)
{
	int		i;
	int		wallstripheight;
	int		topofwall;
	int		bottomofwall;
	double	correctdistance;
	double	wallheight;

	i = 0;
	correctdistance = 0;
	correctdistance = all->ray->distance * cos(all->ray->rayangle - all->p->rotationangl);
	all->distoprojectionplane = (W / 2) / tan(all->ray->fovangle / 2);
	wallheight = (16 / correctdistance) * all->distoprojectionplane;
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
	getwaltex(all);
	paintwalltex(all, i, bottomofwall, wallheight);
}