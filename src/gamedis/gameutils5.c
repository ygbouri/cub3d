/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momayaz <momayaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:45:44 by ygbouri           #+#    #+#             */
/*   Updated: 2022/10/04 17:44:49 by momayaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


static void	ft_left(t_cub *all, int x, int pos)
{
	if (x > pos)
	{
		(all)->p->rotationangl +=  (2 * M_PI / 180);
        (all)->p->rotationangl = fmod((all)->p->rotationangl, 2 * M_PI);
        if ((all)->p->rotationangl < 0)
            (all)->p->rotationangl +=  2 * M_PI;
	}
}

static void	ft_right(t_cub *all, int x, int pos)
{
	if (x < pos)
	{
		(all)->p->rotationangl +=  -1 * (2 * M_PI / 180);
        (all)->p->rotationangl = fmod((all)->p->rotationangl, 2 * M_PI);
        if ((all)->p->rotationangl < 0)
            (all)->p->rotationangl +=  2 * M_PI;
	}
}

int	ft_mouse(int x, int y, t_cub *game)
{
	static int	pos;

	mlx_clear_window(game->mlx, game->mlx_win);
	ft_left(game, x, pos);
	ft_right(game, x, pos);
	pos = x;
    moveplayer(game);
	return (y);
}