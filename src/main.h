/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/17 20:20:23 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define WIN_OFFSET 150
# define WIN_OFFSET_Y 150
# define WIN_OFFSET_X 400
# define WIN_SCALE 12
# define WIN_NAME "I_am_mlx"
# define DEF_COLOR 0x009100FF

# include <stdio.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "get_next_line.h"

typedef struct	s_px
{
	double	x;
	double	y;
	double	z;
	int		col;
	int		alp;
}				t_px;

//enum error
//
typedef struct	s_line
{
	double	start_x;
	double	start_y;
	double	end_x;
	double	end_y;
	double	len_y;
	double	len_x;
	double	len;
	double	dy;
	double	dx;
	double	y1;
	double	x1;
	double	y2;
	double	x2;
	double	y3;
	double	x3;
	double	d;
}				t_line;

typedef struct	s_win
{
	t_px	**map;
	size_t	map_rows;
	size_t	map_cols;
	int		width;
	int		height;
	int		offset_x;
	int		offset_y;
	int		sc_x;
	int		sc_y;
	int		sc_z;
	void	*mlx_ptr;
	void	*win_ptr;
	int		frame_cnt;
	int		con_on;
	int		ver_on;
	int		sla_on;
	int		hor_on;
	int		bsl_on;
	int		fdf_on;
}				t_win;

void	draw_map(t_win *win);

void	draw_line_map(t_win *win);
void	init_win(t_win *win);
void	init_line(t_line *line);

int		exit_x(void *par);
void    map_offset(t_win *win, int offset_y, int offset_x);
void    zoom_offset(t_win *win, int zoom_offset);
void    numpads(t_win *win, int key);
void    animate(t_win *win);

int     toggle_param(int *param);
int		deal_key(int key, t_win *win);

int		is_hex(char ch);
int		ch2int(char ch);
int		parse_color(char *hex, size_t *i, size_t max_i);

void	convert_map(t_win *win, t_list *lst);
void	set_map_size(t_win *win, t_list *lst);
t_win	*parse_map(char *file_name, t_win *win);

void	destroy_lst(t_list *lst);
int		lst_append(t_list **lst, char *buf, int size);
long long	i_atoi(const char *str, size_t *i, size_t max_i);
size_t	cnt_words(char *str, size_t max_i, char ch);

double	ft_abs(double num);
double	ft_max(double first, double second);
void	draw_px_by_coord(t_win *win, double y, double x, int color);
void	draw_px_by_map(t_win *win, size_t y, size_t x);
void	line(t_win *win, t_line *line, double y, double x, int color);

void	draw_map_vertical(t_win *win, int offset_y, int offset_x, int con);
void	draw_map_backslash(t_win *win, int offset_y, int offset_x, int con);
void	draw_map_horizontal(t_win *win, int offset_y, int offset_x, int con);
void	draw_map_slash(t_win *win, int offset_y, int offset_x, int con);
void	draw_map_fdf(t_win *win, int offset_y, int offset_x, int con);

void	free_map(t_win *win);
void 	print_map(t_win *win);
void	print_content_lst(t_list *lst);

void	multi_init_line(t_line *l1, t_line *l2, t_line *l3, t_line *l4);
void	set_start_if_max(t_line *line, double new_y, double new_x);
void	set_end_if_max  (t_line *line, double new_y, double new_x);
void	set_start_if_min(t_line *line, double new_y, double new_x);
void	set_end_if_min  (t_line *line, double new_y, double new_x);
void	set_start_if_max_y	(t_line *line, double new);
void	set_start_if_max_x	(t_line *line, double new);
void	set_end_if_max_y	(t_line *line, double new);
void	set_end_if_max_x	(t_line *line, double new);
void	set_start_if_min_y 	(t_line *line, double new);
void	set_start_if_min_x	(t_line *line, double new);
void	set_end_if_min_y	(t_line *line, double new);
void	set_end_if_min_x	(t_line *line, double new);
void	get_top_line(t_line *line, double new_y, double new_x);
void	get_bottom_line(t_line *line, double new_y, double new_x);
void	get_left_line(t_line *line, double new_y, double new_x);
void	get_right_line(t_line *line, double new_y, double new_x);
void	print_map_frame(t_win *win);

#endif
