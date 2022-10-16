/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momayaz <momayaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:54:05 by ygbouri           #+#    #+#             */
/*   Updated: 2022/10/10 09:41:53 by momayaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void getmapheight(t_cub *all)
{
	int i;

	i = 0;
	while (all->map[i])
		i++;
	all->info.mapheight = i;
}

void getmapwidth(t_cub *all)
{
	int i;

	i = 0;
	while (all->map[0][i])
		i++;
	all->info.mapwidth = i;
}

float	ft_abs(float value)
{
	if (value < 0)
		return (-value);
	return (value);
}


void	ft_checkdoor(char **map, float x, float y)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{	
			if (map[i][j] == 'D' && (ft_abs(i - y) < 2 && ft_abs(j - x) < 2))
			{
				map[i][j] = 'O';
			}
			if (map[i][j] == 'O' && (ft_abs(i - y) >= 2 || ft_abs(j - x) >= 2))
				map[i][j] = 'D';
		}
	}
}


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
	double offSETX;
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
	while (i < bottomofwall)
	{
		if (all->hitV){
			offSETX = all->pos->po.y / 16;
		}
		else
			offSETX = all->pos->po.x / 16;
		offSETX -= floor(offSETX);
		offSETX *= all->texture[all->l7aj].w;
		int d = i + (wallstripheight / 2) - (H / 2);
		int offSETY = d * ((float) all->texture[all->l7aj].w / wallstripheight);
		if (all->l7aj >= 0 && all->l7aj < 6){
			int txtColl = (int)all->texture[all->l7aj].data[(all->texture[all->l7aj].h * offSETY) + (int)offSETX];
			my_mlx_pixel_put(all->img, all->ray->colid, i, txtColl);
		}
		i++;
	}
	all->l7aj = -1;
}

void	fovminimap(t_cub *all)
{
	double 		inc_angle;
	t_glpos		glpos;

	inc_angle = all->ray->fovangle / W;
	//init_gl(&glpos, all);
	initialrayvar(all);
	//all->compteur = 0;
	calcTuxter(all);
	ft_checkdoor(all->map, all->posx / 16, all->posy / 16);
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
	randringsprite(all);
	mlx_put_image_to_window(all->mlx, all->mlx_win, all->img->img, 0, 0);
}


