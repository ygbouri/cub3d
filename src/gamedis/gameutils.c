/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:02:01 by ygbouri           #+#    #+#             */
/*   Updated: 2022/10/02 12:56:40 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"





void	hintercept(t_cub *all, double angle)
{
	t_pos	intercept;
	t_pos	player;
	t_pos	step;
	t_pos	po;
	t_pos  hori;
	t_pos  verti;
	double hori_d;
	double verti_d;
	double nbr;
	bool hori_f; 
	bool verti_f;

	hori_f = false;
 	verti_f = false;
	int	len = ft_strleny(all->map);
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	all->ray->downdirect = (angle >= 0 && angle <= M_PI);
	all->ray->updirect = !all->ray->downdirect;
	
	all->ray->rightdirect = ((angle < (0.5 * M_PI)) || (angle > (1.5 * M_PI)));
	all->ray->leftdirect = !all->ray->rightdirect;
	// horizontal
	player.x = all->pscreenx;
	player.y = all->pscreeny;
	intercept.y = floor(player.y / 16) * 16;
	if (all->ray->downdirect)
		intercept.y += 16;
	intercept.x = player.x + (intercept.y - player.y) / tan(angle);
	step.y = 16;
	if (all->ray->updirect)
		step.y *= -1;
	step.x = step.y / tan(angle);
	if (all->ray->leftdirect && step.x > 0)
		step.x *= -1;
	if (all->ray->rightdirect && step.x < 0)
		step.x *= -1;
	while ((((int)(intercept.y / 16) >= 0) 
			&& (int)(intercept.y / 16) < len) 
			&& ((int)(intercept.x / 16)>= 0) 
			&& ((int)(intercept.x / 16)< (int)ft_strlen(all->map[(int)intercept.y / 16]) * 16))
	{
		nbr = intercept.y;
		if (all->ray->updirect)
			nbr--;
		if (checkwall_ray(all, intercept.x, nbr))
		{
			intercept.x += step.x;
			intercept.y += step.y;
		}
		else
		{
			hori_f = true;
			hori.x = intercept.x;
			hori.y = intercept.y;
			break;
		}
	}
	// vertical
	intercept.x = floor(player.x / 16) * 16;
	if (all->ray->rightdirect)
		intercept.x += 16;
	intercept.y = player.y + (intercept.x - player.x) * tan(angle);

	step.x = 16;
	if (all->ray->leftdirect)
		step.x *= -1;
	step.y = step.x * tan(angle);
	if (all->ray->updirect && step.y > 0)
		step.y *= -1;
	if (all->ray->downdirect && step.y < 0)
		step.y *= -1;

	while ((((int)(intercept.y / 16) >= 0) 
			&& (int)(intercept.y / 16) < len) 
			&& ((int)(intercept.x / 16) >= 0)
			&& ((int)(intercept.x / 16) < (int)ft_strlen(all->map[(int)intercept.y / 16]) * 16))
	{
		nbr = intercept.x;
		if (all->ray->leftdirect)
			nbr--;
		if (checkwall_ray(all, nbr, intercept.y))
		{
			intercept.x += step.x;
			intercept.y += step.y;
		}
		else
		{
			verti_f = true;
			verti.x = intercept.x;
			verti.y = intercept.y;
			break;
		}
	}
	if (verti_f)
		verti_d = calculdistance(player.x, player.y, verti.x, verti.y);
	else 
		verti_d = 1e30;
	if (hori_f)
		hori_d = calculdistance(player.x, player.y, hori.x, hori.y);
	else 
		hori_d = 1e30;
	
	if (hori_d < verti_d)
	{
		po.x = hori.x ;
		po.y = hori.y;
		all->ray->distance = hori_d;
	}
	else
	{
		po.x = verti.x;
		po.y = verti.y;
		all->ray->distance = verti_d;
	}
	double departx = player.x - all->distancexx;
	double departy = player.y - all->distanceyy;
	double    finx 	= po.x - all->distancexx;
	double    finy 	= po.y - all->distanceyy;
	lstaddback(&(all->node), lstnew(departx, departy, finx, finy));
}




