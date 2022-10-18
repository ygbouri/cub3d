/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils13.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momayaz <momayaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:38:17 by momayaz           #+#    #+#             */
/*   Updated: 2022/10/17 18:39:06 by momayaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	initialiserinter(t_glpos *gl)
{
	gl->intercept.x = 0;
	gl->intercept.y = 0;
	gl->player.x = 0;
	gl->player.y = 0;
	gl->step.x = 0;
	gl->step.y = 0;
	gl->po.x = 0;
	gl->po.y = 0;
	gl->hori.x = 0;
	gl->hori.y = 0;
	gl->verti.x = 0;
	gl->verti.y = 0;
	gl->nbr = 0;
	gl->hori_d = 0;
	gl->verti_d = 0;
	gl->hori_f = false;
 	gl->verti_f = false;
}

void	calculhoridis(t_cub *all, t_glpos *glpos, int len)
{
	while ((((int)(glpos->intercept.y / 16) >= 0) 
			&& (int)(glpos->intercept.y / 16) < len) 
			&& ((int)(glpos->intercept.x / 16) >= 0) 
			&& ((int)(glpos->intercept.x / 16) < (int)ft_strlen(all->map[(int)glpos->intercept.y / 16]) * 16))
	{
		glpos->nbr = glpos->intercept.y;
		if (all->ray->updirect)
			glpos->nbr--;
		if (checkwall_ray(all, glpos->intercept.x, glpos->nbr))
		{
			glpos->hori_f = false;
			glpos->intercept.x += glpos->step.x;
			glpos->intercept.y += glpos->step.y;
		}
		else
		{
			glpos->hori_f = true;
			glpos->hori.x = glpos->intercept.x;
			glpos->hori.y = glpos->intercept.y;
			break;
		}
	}
}

void	ft_frame(t_cub *all)
{
	static int	frame;
	static int	i;

	if (frame <= 2)
	{
		frame++;
		if (frame == 2)
		{
			frame = 0;
			i++;
			all->st = i;
		}
		if (i == 14)
			i = 0;
	}
}