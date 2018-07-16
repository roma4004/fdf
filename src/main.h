/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/16 21:13:33 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define WIN_OFFSET 150
# define WIN_SCALE 12
# define WIN_NAME "I_am_mlx"
# define DEF_COLOR 0x009100FF


typedef struct	s_px
{
	double	x;
	double	y;
	double	z;
	int		color;
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

#endif
