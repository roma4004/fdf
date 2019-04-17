/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/17 15:24:48 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define WIN_WIDTH		1920
# define WIN_HEIGHT		1080
# define DEF_OFFSET_Y	200
# define DEF_OFFSET_X	100
# define DEF_SCALE		1
# define TITLE			"FDF by dromanic (@Dentair)"
# define DEF_COLOR		0x009100FF
# define PI				3.14159265359
# define WIDTH_ERR_SKIP	0

# define MSG_MOVE		"move            : arrows left, up, down, right"
# define MSG_ZOOM_A		"zoom all        : -, + or mouse scroll"
# define MSG_ZOOM_Z		"zoom only Z     : 9, 0 or numpad +, -"
# define MSG_INTERF		"interface       : 8 or numpad 8"
# define MSG_ROTATE		"rotate X,Y,Z(+-): QA, WS, ED"
# define MSG_ANIMATE	"next style      : enter (hold to animate)"
# define MSG_RESET		"reset           : R"
# define MSG_STYLE		"set visual style: 1..7 (|, /, -, \\, fdf, layer, dot)"
# define MSG_EXIT		"exit the program: esc or hit (x) at the corner window"

# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

typedef struct	s_uint32_point
{
	uint64_t	x;
	uint64_t	y;
}				t_ui_pt;

typedef struct	s_sint32_point
{
	int64_t		x;
	int64_t		y;
}				t_si_pt;

typedef struct	s_double_2point
{
	double		x;
	double		y;
}				t_db_2pt;

typedef struct	s_double_3point
{
	double		x;
	double		y;
	double		z;
}				t_db_3pt;

typedef struct	s_sint32_3point
{
	int64_t		x;
	int64_t		y;
	int64_t		z;
}				t_si_3pt;

typedef struct	s_px
{
	t_db_3pt	pt;
	double		z_orig;
	int			color;
}				t_px;

typedef struct	s_line
{
	int			color;
	t_si_pt		end;
	t_si_pt		len;
	t_si_pt		delt;
	t_si_pt		offset;
	int64_t		len_max;
	int64_t		d;
}				t_line;

typedef struct	s_param
{
	uint32_t	width;
	uint32_t	height;
	t_si_pt		move;
	t_si_3pt	scale;
	t_db_2pt	center;
	size_t		rows;
	size_t		cols;
	int			frame_cnt;
}				t_param;

typedef struct	s_flags
{
	int			interface_on;
	int			fdf_on;
	int			con_on;
	int			ver_on;
	int			sla_on;
	int			hor_on;
	int			bsl_on;
	int			dot_on;
	int			error_code;
}				t_flags;

typedef struct	s_enviroments
{
	t_px		**map;
	t_param		param;
	t_flags		flags;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*buffer;
}				t_env;

enum			e_keys
{
	NUM_1 = 83, ONE = 18,
	NUM_2 = 84, TWO = 19,
	NUM_3 = 85, THREE = 20,
	NUM_4 = 86, FOUR = 21,
	NUM_5 = 87, FIVE = 23,
	NUM_6 = 88, SIX = 22,
	NUM_7 = 89, SEVEN = 26,
	NUM_8 = 91, EIGHT = 28,
	NUM_MINUS = 78, NINE = 25,
	NUM_PLUS = 69, ZERO = 29,
	Q = 12, W = 13, E = 14,
	A = 0, S = 1, D = 2,
	R = 15, ENTER = 36, ESC = 53,
	ARROW_UP = 126, ARROW_DOWN = 125,
	ARROW_LEFT = 123, ARROW_RIGHT = 124,
	MOUSE_SCROLL_UP = 4, MINUS = 27,
	MOUSE_SCROLL_DOWN = 5, PLUS = 24,
};

enum			e_errors
{
	MAP_INVALID = 404,
	WIDTH_ERR = 405,
	READ_ERR = 406,
	COLOR_ERR = 407,
	ITS_A_DIRECTORY = 21
};

int				parse_map(t_env *e, char *file_name);

void			draw_line(int *buffer, t_line *l, int64_t x, int64_t y);
void			draw_map(t_env *e, t_px **map, int *buf, t_param param);

void			conn_vertical(t_px **map, int *buffer, t_param p, int c);
void			conn_backslash(t_px **map, int *buffer, t_param p, int c);
void			conn_horizontal(t_px **map, int *buffer, t_param p, int c);
void			conn_slash(t_px **map, int *buffer, t_param p, int c);
void			conn_fdf(t_px **map, int *buffer, t_param p, int c);

void			redraw_img(t_env *e);

int				deal_keyboard(int key, t_env *e);
int				deal_mouse(int key, int x, int y, t_env *env);

int				exit_x(t_env *e);

void			rotate_map(t_env *e, t_px **map, char axis, double angle);
void			reset(t_env *e);

#endif
