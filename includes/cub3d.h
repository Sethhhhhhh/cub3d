/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:16:23 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/13 14:16:32 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define FORWARD         		119
# define DOWN            		115
# define ROTATE_LEFT			100
# define ROTATE_RIGHT			97
# define ECHAP				6553

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_fpos
{
	double		x;
	double		y;
}				t_fpos;

typedef struct	s_size
{
	int			w;
	int			h;
}				t_size;

typedef struct	s_fsize
{
	double		w;
	double		h;
}				t_fsize;

typedef struct	s_parse
{
	t_size		size;
	char		**map;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sprite;
	int			floor;
	int			ceiling;
	int			size_grid_y;
	int			count_sprite;
}				t_parse;

typedef struct	s_player
{
	t_fpos		pos;
	double		speed;
	double		r_speed;
	int			forward;
	int			back;
	int			r_left;
	int			r_right;

}				t_player;

typedef struct	s_texture
{
	char		*path;
	void		*ptr;
	int			*data;
	int			bits;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct	s_ray
{
	t_fpos		dir;
	t_fpos		plane;
	t_fpos		ray_dir;
	t_fpos		side_dist;
	t_fpos		delta_dist;
	t_pos		map;
	t_pos		step;
	double		*z_buffer;
	double		camera;
	double		perp_wall_dist;
	int			side;
	int			pole;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct	s_sprite
{
	t_fpos		transform;
	t_size		size;
	t_pos		texture;
	t_pos		pos;
	t_pos		draw_start;
	t_pos		draw_end;
	double		inv_det;
	int			dist;
	int			screen;
	int			color;
}				t_sprite;

typedef struct	s_bmp
{
	char		*header;
	int			fd;
	int			color;
}				t_bmp;

typedef struct	s_img
{
	void		*ptr;
	int			*data;
	int			bits;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	t_ray		ray;
	t_img		img;
	t_player	player;
	t_texture	texture[5];
	t_sprite	*sprites;
	int			save;
}				t_mlx;

typedef struct	s_g
{
	t_parse		parse;
	t_mlx		mlx;
}				t_g;

void			s_parse(t_g *g, int fd);
int				s_parse_map(t_g *g, char *line, int *count, int *ml);

int				s_init_image(t_g *g);
int				s_close(t_g *g);
int				s_is_map_parsing(t_g *g);
void			s_destroy_image(t_g *g);

void			s_draw_pixel(t_g *g, int x, int y, int color);
void			s_draw_column(t_g *g, int col, int color);
void			s_draw_sprite(t_g *g, int sprite_id, int i);

int				s_get_start_pos(t_g *g);
void			s_move_and_rotate(t_g *g);

int				s_keypress(int keycode, t_g *g);
int				s_keyrelease(int keycode, t_g *g);
void			s_move(t_g *g);
void			s_rotate_left(t_g *g);
void			s_rotate_right(t_g *g);

int				s_raycast(t_g *g);

void			s_get_path_to_set(t_g *g);
void			s_get_texture_pos(t_g *g, int col, int texture);

void			s_get_sprites(t_g *g);
void			s_draw_sprites(t_g *g);
void			s_get_screen_sprite_pos(t_g *g, int sprite_id);

void			s_error(t_g *g, char *error);
void			s_check_resolution(t_g *g);

void			s_free(t_g *g);

void			s_bmp(t_g *g);

#endif
