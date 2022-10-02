/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:45:47 by ygbouri           #+#    #+#             */
/*   Updated: 2022/10/02 12:52:11 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	conserveangle(t_cub *all)
{
	all->ray->rayangle /= (2 * M_PI);
	if (all->ray->rayangle < 0)
		all->ray->rayangle += (2 * M_PI);
}

double	calculdistance(double x, double y, double a, double b)
{
	return (sqrt(pow((a - x), 2) + pow((b - y), 2)));
}

void	raydirection(t_cub *all)
{
	if (all->ray->rayangle >= 0 && all->ray->rayangle <= M_PI)
		all->ray->downdirect = 1;
	else
		all->ray->updirect = 1;
	if ((all->ray->rayangle < (0.5 * M_PI)) || (all->ray->rayangle > (1.5 * M_PI)))
		all->ray->rightdirect = 1;
	else
		all->ray->leftdirect = 1;
}

void	drawingray(t_cub *all, double x0, double y0, double x1, double y1)
{
	int		dx;
	int		dy;
	int		i;
	int		step;
	float	x;
	float	y;
	float	incx;
	float	incy;

	i = 0;
	dx = x1 - x0 ;
	dy = y1 - y0;
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	incx = dx / (float)step;
	incy = dy / (float)step;
	x = x0;
	y = y0;
	while (i < step && x <= 128 && y <= 128)
	{
		my_mlx_pixel_put(all->img, round(x), round(y),0xeb4034);
		x += incx;
		y += incy;
		i++;
	}
}

int	checkwall_ray(t_cub *all, double xr, double yr)
{
	int	x;
	int	y;
	int	x_line;

	x = floor(xr / 16);
	y = floor(yr / 16);
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
