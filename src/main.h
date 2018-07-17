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
# define WIN_SCALE 100
# define WIN_NAME "I_am_mlx"
# define DEF_COLOR 0x809100FF

# include <stdio.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "get_next_line.h"

typedef struct	s_px
{
	double	x;
	double	y;
	double	z;
	int		color;
	int		color_alpha;
}				t_px;

//enum error
//
typedef struct	s_line
{
	double	start_y;
	double	start_x;
	double	end_x;
	double	end_y;
	double	len_y;
	double	len_x;
	double	len;
	double	step;
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
	int		scale_x;
	int		scale_y;
	int		scale_z;
	void	*mlx_ptr;
	void	*win_ptr;
}				t_win;

int		exit_x(void *par);

int		is_hex(char ch);
int		ch2int(char ch);
int		parse_color(char *hex, size_t *i, size_t max_i);
void	destroy_lst(t_list *lst);
int		lst_append(t_list **lst, char *buf, int size);
void	convert_map(t_win *win, t_list *lst);
void	print_content_lst(t_list *lst);
void	set_map_size(t_win *win, t_list *lst);
t_win	*parse_map(char *file_name, t_win *win);

long long	i_atoi(const char *str, size_t *i, size_t max_i);
size_t	cnt_words(char *str, size_t max_i, char ch);

double	ft_abs(double num);
double	ft_max(double first, double second);
void	draw_px_by_coord(t_win *win, double y, double x);
void	draw_px_by_map(t_win *win, size_t y, size_t x);
void	draw_line(t_win *win, t_line *line);

void 	print_map(t_win *win);
#endif
