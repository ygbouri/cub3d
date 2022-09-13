/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:14:40 by izouf             #+#    #+#             */
/*   Updated: 2022/09/13 13:45:15 by ygbouri          ###   ########.fr       */
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
}					t_info;

typedef struct s_cub
{
	char	**map;
	t_info	info;
}	t_cub;



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

int				keypress(int keycode, t_key *key);
int				keyrelease(int keycode, t_key *key);
void			ft_herewego(t_game *game, t_cub parsing, int bonus);
void			ft_print(t_raycast *ray, t_win *win, char **map, int bonus);

void			ft_load(t_raycast *ray, void *mlx, t_cub parsing);
void			ft_init(t_raycast *ray, t_cub parsing, char **map, int bonus);

void			ft_init_key(t_key *key);
int				ft_nsprite(char **map);
void			ft_hitdoor(t_raycast *ray, char c);
void			ft_checkdoor(char **map, float x, float y);
int				ft_error(char *str);

unsigned int	getcolor(t_texture *t, int x, int y);
void			ft_swap(t_pair **sprites, int amount);
float			ft_abs(float value);
void			ft_put(t_win *win, unsigned int **buffer);

void			ft_init_v(t_raycast *ray, int x);
void			ft_init_dist(t_raycast *ray);
void			ft_wall_col(t_raycast *ray, char **map, int bonus);
void			ft_side(t_raycast *ray);
void			ft_init_c(t_raycast *ray, int x, int bonus);

int				ft_sprites(t_raycast *ray, char **map);

int				ft_move(t_game *game);

int				ft_mouse(int x, int y, t_game *game);

int				ft_minimap(t_raycast *ray, t_win *win, char **map);

void			ft_free(t_cub *parsing, t_game *game);
int				ft_close(void);

void			ft_frame(t_raycast *ray);

#endif
