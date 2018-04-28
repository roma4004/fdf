/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/04/21 19:10:14 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define WIN_HEIHGT 768
# define WIN_WIDTH 1024
# define WIN_NAME I_am_mlx

typedef struct	s_px
{
	double	x;
	double	y;
	double	z;
	int		color;
}				t_px;

typedef struct	s_win
{
	t_px	**map;
	int		len;
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
