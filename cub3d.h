/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:14:40 by izouf             #+#    #+#             */
/*   Updated: 2022/10/02 18:50:13 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# define W 1024
# define H 512


typedef struct s_info
{
	char			*n;
	char			*s;
	char			*e;
	char			*w;
	char			*d;
	char			*c;
	char			*f;
	char			*s1;
	unsigned int	cc;
	unsigned int	fc;
	int				test[256];
}
					t_info;
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct  player
{
	int		xp;
	int		yp;
	int		radius;
	int		checker;
	int		turnDirection;
	int		walkDirectionx;
	int		walkDirectiony;
	double	rotationangl;
	float	movespeed;
	float	movestep;
	float	rotationspeed;
}				t_player;

typedef struct rays
{
	double			fovangle;
	int				wallstrip;
	int				numrays;
	double			rayangle;
	int				colid;
	double			wallhitx;
	double			wallhity;
	double			distance;
	bool				downdirect;
	bool				updirect;
	bool				leftdirect;
	bool				rightdirect;
}					t_rays;

typedef struct drawrays
{
	double			departx;
	double			departy;
	double			finx; 
	double			finy;
	struct drawrays	*next;
}				t_drawrays;

typedef struct s_cub
{
	char			**map;
	void			*mlx;
	void			*mlx_win;
	t_data			*img;
	int				w;
	int				h;
	double			posx;
	double			posy;
	int				xp;
	int				yp;
	int				topy;
	int				topx;
	int				i;
	int				j;
	int				k;
	double			pscreenx;
	double			pscreeny;
	double 			minix;
	double 			miniy;
	char			P;
	float			dirx;
	float			diry;
	int				checker;
	int				sizemy;
	float			ang;
	double			distancexx;
	double			distanceyy;
	int				compteur;
	t_info			info;
	t_player		*p;
	t_rays			*ray;
	t_drawrays		*node;
}	t_cub;


typedef struct s_pos
{
	double	x;
	double	y;
}			t_pos;

typedef struct glpos
{
	t_pos	intercept;
	t_pos	player;
	t_pos	step;
	t_pos	po;
	t_pos	hori;
	t_pos	verti;
	double 	hori_d;
	double 	verti_d;
	double 	nbr;
	bool hori_f; 
	bool verti_f;
}				t_glpos;
/*************************************************/

int				str_len(const char *s, char c);
void			free_tab(char **t);
int				count_world(const char *s, char c);
char			*str_cpy(const char *s, int size);
char			**ft_split(char *s, char c);
size_t			ft_strlen(char *s);
void			ft_concta(char *dest, char *src);
char			*ft_strjoin(int size, char **strs, char *sep);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strdup(const char *s);
int				ft_atoi(char *nptr);
int				check_file(char *t);
int				ft_strcmp(char *s1, char c);
char			*read_map(int fd);
int				cont_line(char *t);
void			ft_ifspace(char *line, int *i);
void			get_res(t_cub *all, char *line);
char			*check_texr(char *line, char *op);
void			ft_firstcheck(t_cub *all, char c);
unsigned int	get_rgb(char *line);
void			ft_parsing_line(t_cub *all, char *line, int i);
char			**fil_tab(int line, int fd, t_cub *all);
void			get_width_height(char **map, int *width, int *height);
int				ft_check_map_horizontal(char **map, int height);
int				ft_check_map_vertical(char **map, int width, int height);
void			ft_remplir_map(char **map, int width, int height);
void			ft_check(char **s);
void			ft_pars(t_cub *all, int width, int height);
void			big_parss1(t_cub *all, char c);
int				big_parss(int ac, char *av[], t_cub *all, char c);
void			check_b(t_cub *a);
void			check_charb(t_cub *a, char c);
void			check_m(t_cub *a);
void			check_charm(t_cub *a, char c);
int				ft_isdigit(char c);
void			if_digit(char *s);

/*************************************************/
void			*ft_memset(void *s, int c, size_t n);
void			replace_nl_with_null(char *str);
void			free_parsing(t_cub *parsing);
int				check_file_name(char *str);
int				skip_spaces(char *tmpline);
int				assign_floor(t_cub *parsing, int i);
int				assign_ceiling(t_cub *parsing, int i);
int				assign_vars_two(t_cub *parsing, int i);
int				assign_vars_three(t_cub *parsing, int i);
int				assign_vars(t_cub *parsing);
void			init_parsing(t_cub *parsing, char *argv[]);
void			parsing_directions_colors_two(t_cub *parsing);
int				parsing_directions_colors(t_cub *parsing, \
		char *argv[], int argc);
int				skip_newlines(t_cub *parsing);
void			parse_map(t_cub *parsing, size_t i);
int				check_fist_last_line(t_cub *parsing);
int				check_first_indexes(t_cub *parsing);
int				check_map(t_cub *parsing, int i, int j);
void			parse_map_assign_two(t_cub *parsing, size_t *i);
void			parse_map_assign(t_cub *parsing, size_t i);
void			replace_spc_wall(t_cub *parsing);
int				search_for_player(t_cub *parsing, int i, int j, int count);
int				search_for_player2(t_cub *parsing, int i, int j, int count);
void			ft_bzero(void *s, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
int				contains_newline(char const *s1);
char			*first_line(char *str);
char			*second_part(char *str);
char			*get_next_line(int fd);
int				check_colors(char *str);
void			main_parse(int ac, char **av, t_cub *parsing, int mode);
int				ft_error(char *str);
/***************************************************************/

void		ft_display(t_cub *all);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		affichminimap(t_cub *all, int ch);
void		pixelcarre(t_cub *all, int pi, t_data *img, int color);
void		raycasting(t_cub *all);
int			keyrelease(int key, t_cub *all);
int			keypressed(int key, t_cub *all);
int			moveplayer(t_cub *all);
int			closewin(int key, t_cub *all);
void		drawingray(t_cub *all, double x0, double y0, double x1, double y1);
t_drawrays 	*lstnew(double x, double y, double a, double b);
void		lstaddback(t_drawrays **header, t_drawrays *new);
void		drawimg(t_cub *all, int ch);
void		pixelmap(t_data *img, int color);
int	checkplayer(t_cub *all, int ch);
t_player	*iniatialiserp(t_cub *all);
void	detectang(t_cub *all);

void	drawingline(t_cub *all);
 void	paintplayer(t_cub *all, int ch);
int	checkwall(t_cub *all);
void	moveleft(t_cub *all);
void	moveright(t_cub *all);
void	moveup(t_cub *all);
void	movedown(t_cub *all);
void	moveraytleft(t_cub *all);
void	moveraytright(t_cub *all);
void	updat_data(t_cub **all);
void	freenode(t_cub *all);
void	paintmap(t_cub *all, t_data *img, int ch);
void	conserveangle(t_cub *all);
double	calculdistance(double x, double y, double a, double b);
void	raydirection(t_cub *all);
int	checkwall_ray(t_cub *all, double xr, double yr);
void	hintercept(t_cub *all, double angle, t_glpos *glpos);
t_drawrays *lstnew(double x, double y, double a, double b);
void	initialrayvar(t_cub *all);
void	paintceiling(t_cub *all, int top);
void	paintfloor(t_cub *all, int bottom);
void	renderthreeD(t_cub *all);
void	fovminimap(t_cub *all);
int	ft_strleny(char **str);
//void	init_gl(t_glpos *gl, t_cub *all);
#endif
