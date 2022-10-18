/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momayaz <momayaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:57:21 by momayaz           #+#    #+#             */
/*   Updated: 2022/10/18 09:56:54 by momayaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcTuxter(t_cub *all){
	t_data info;
	
	all->texture[0].img = mlx_xpm_file_to_image(all->mlx, all->info.n, &all->texture[0].w, &all->texture[0].h);
	if (!all->texture[0].img)
		exit(1);
	all->texture[0].data = (unsigned int*) mlx_get_data_addr(all->texture[0].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->texture[1].img = mlx_xpm_file_to_image(all->mlx, all->info.s, &all->texture[1].w, &all->texture[1].h);
	if (!all->texture[1].img)
		exit(1);
	all->texture[1].data = (unsigned int*) mlx_get_data_addr(all->texture[1].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->texture[2].img = mlx_xpm_file_to_image(all->mlx, all->info.e, &all->texture[2].w, &all->texture[2].h);
	if (!all->texture[2].img)
		exit(1);
	all->texture[2].data = (unsigned int*) mlx_get_data_addr(all->texture[2].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->texture[3].img = mlx_xpm_file_to_image(all->mlx, all->info.w, &all->texture[3].w, &all->texture[3].h);
	if (!all->texture[3].img)
		exit(1);
	all->texture[3].data = (unsigned int*) mlx_get_data_addr(all->texture[3].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->texture[4].img = mlx_xpm_file_to_image(all->mlx, "./pics/images_64x64.xpm", &all->texture[4].w, &all->texture[4].h);
	if (!all->texture[4].img)
		exit(1);
	all->texture[4].data = (unsigned int*) mlx_get_data_addr(all->texture[4].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
}


int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

int	ft_isdigit(char c)
{
	if ((c >= '0' && c <= '9') || c == ',')
		return (1);
	return (0);
}

void	if_digit(char *s)
{
	int	i;

	i = 0;
	s = ft_strtrim(s, "\n");
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			ft_error("rgb error1\n");
		i++;
	}
}

void	ft_pars(t_cub *all, int width, int height)
{
	int	j;

	j = 0;
	get_width_height(all->map, &width, &height);
	ft_remplir_map(all->map, width, height);
	if (ft_check_map_horizontal(all->map, height) == 0
		&& ft_check_map_vertical(all->map, width, height) == 0)
		return ;
	else
		ft_error("pars error \n");
}

void	big_parss1(t_cub *all, char c)
{
	int	i;
	int	width;
	int	height;

	i = 0;
	width = 0;
	height = 0;
	while (all->map[i])
		free(all->map[i++]);
	free(all->map);
	all->map = ft_split(all->info.s1, '\n');
	free(all->info.s1);
	ft_pars(all, width, height);
	if (c == 'm')
		check_m(all);
	else if (c == 'b')
		check_b(all);
}

int	big_parss(int ac, char *av[], t_cub *all, char c)
{
	int		line;
	int		fd;

	int x = 0;
	while (x < 256)
		all->info.test[x++] = 0;
	if (ac != 2)
		return (printf("cub3d take just 1 arg"), 0);
	if (!check_file(av[1]))
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (printf("file not found or permission denied "), 0);
	for (size_t i = 0; i < 256; i++)
	{
		all->info.test[i] = 0;
	}
	
	line = cont_line(av[1]);
	all->map = fil_tab(line, fd, all);
	line = 0;
	while (all->map[line])
		line++;
	all->info.s1 = ft_strjoin(line, all->map, "\n");
	big_parss1(all, c);
	return (0);
}

int main(int ac, char **av)
{
	t_cub	all;

	all.checker = 0;
	all.ray = (t_rays *)malloc(sizeof(t_rays));
	big_parss(ac, av, &all, 'b');
	all.spritecount = calculspritenumber(&all);
	all.sprite = malloc(sizeof(t_sprite) * all.spritecount);
	all.st = -1;
	locateSprite(&all);
	ft_display(&all);

}