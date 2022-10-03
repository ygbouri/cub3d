/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:45:40 by ygbouri           #+#    #+#             */
/*   Updated: 2022/10/03 13:41:12 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	paintplayer(t_cub *all, int ch)
{
	int			i;
	t_drawrays	*tmp;

	(void)ch;
	i = 0;
	tmp = all->node;
	my_mlx_pixel_put(all->img, 64, 64, 0xFD1700);
	while (tmp->next)
	{
		
		drawingray(all, tmp->departx, tmp->departy, tmp->finx, tmp->finy);
		tmp = tmp->next;
	}
	drawingray(all, tmp->departx, tmp->departy, tmp->finx, tmp->finy);
}

int	checkwall(t_cub *all)
{
	int	x;
	int	y;
	int	x_line;

	x = floor(all->posx / 16);
	y = floor(all->posy / 16);
	
	if (y < 0 && y > ft_strleny(all->map))
		return (0);
	if (all->map[y] != NULL)
		x_line = ft_strlen(all->map[y]);
	else
		return (0);
	if (x < 0 && x > x_line)
		return (0);
	if (all->map[y][x] == '1' || all->map[y][x] == ' ' || all->map[y][x] == 0)
		return (0);
	return (1);
}

void	moveraytright(t_cub *all)
{
	all->p->rotationangl -= 0.05;
	if (all->p->rotationangl <= 0)
		all->p->rotationangl += 2 * M_PI;
}

void	updat_data(t_cub **all)
{
	double step;

	step = (*all)->p->walkDirectiony * 2;
	(*all)->p->rotationangl += (*all)->p->turnDirection * (2 * M_PI / 180);
	(*all)->p->rotationangl = fmod((*all)->p->rotationangl, 2 * M_PI);
	if ((*all)->p->rotationangl < 0)
		(*all)->p->rotationangl +=  2 * M_PI;
	else if ((*all)->p->rotationangl > 2 * M_PI)
		(*all)->p->rotationangl -=  2 * M_PI;
	(*all)->posx += cos((*all)->p->rotationangl) * step;
	(*all)->posy += sin((*all)->p->rotationangl) * step;
	if (checkwall(*all) == 1)
	{
		(*all)->pscreenx = (*all)->posx;
		(*all)->pscreeny = (*all)->posy;
	}
	step = (*all)->p->walkDirectionx * 2;
	(*all)->posx -= sin((*all)->p->rotationangl) * step;
	(*all)->posy += cos((*all)->p->rotationangl) * step;
	if (checkwall(*all) == 1)
	{
		(*all)->pscreenx = (*all)->posx;
		(*all)->pscreeny = (*all)->posy;
	}
}

int keyrelease(int key, t_cub *all)
{
	if (key == 124)
		all->p->turnDirection = 0;
	else if (key == 123)
		all->p->turnDirection = 0;
	if (key == 0)
		all->p->walkDirectionx = 0;
	else if (key == 2)
		all->p->walkDirectionx = 0;
	else if (key == 1)
		all->p->walkDirectiony = 0;
	else if (key == 13)
		all->p->walkDirectiony = 0;
	return (0);
}