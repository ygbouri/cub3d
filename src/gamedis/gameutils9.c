/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:56:43 by ygbouri           #+#    #+#             */
/*   Updated: 2022/10/02 12:56:56 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_drawrays *lstnew(double x, double y, double a, double b)
{
	t_drawrays	*element;

	element = (t_drawrays *)malloc(sizeof(t_drawrays));
	if (!element)
		return (NULL);
	element->departx = x;
	element->departy = y;
	element->finx = a;
	element->finy = b;
	element->next = NULL;
	return (element);
}

void	lstaddback(t_drawrays **header, t_drawrays *new)
{
	t_drawrays	*p;

	p = NULL;
	if (header)
	{
		if ((*header) == NULL)
			(*header) = new;
		else
		{
			p = *header;
			while (p->next != NULL)
				p = p->next;
			p->next = new;
		}
	}
}

void	initialrayvar(t_cub *all)
{
	all->ray->colid = 0;
	all->ray->fovangle = 60 * (M_PI / 180);
	all->ray->wallstrip = 1;
	all->ray->numrays = W / all->ray->wallstrip;
	all->ray->rayangle = all->p->rotationangl - (all->ray->fovangle / 2);
	all->ray->distance = 0;
	all->ray->wallhitx = 0;
	all->ray->wallhity = 0;
	all->ray->downdirect = false;
	all->ray->updirect = false;
	all->ray->leftdirect = false;
	all->ray->rightdirect = false;
}
