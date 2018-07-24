/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:59:52 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/23 14:59:53 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "math.h"

void    rotate_y(t_win *win, size_t y, size_t x, int new_angle)
{
    double tmp_y;
    double tmp_x;
    double tmp_z;
    double angle;

    if (!win)
		return ;
    win->map[y][x].x = win->map[y][x].x - win->centr_x;
	win->map[y][x].y = win->map[y][x].y - win->centr_y;
    angle = new_angle * PI / 180;
	tmp_x = win->map[y][x].x;
	tmp_y = win->map[y][x].y * cos(angle) + win->map[y][x].z * sin(angle);
	tmp_z = -win->map[y][x].y * sin(angle) + win->map[y][x].z * cos(angle);
	tmp_x = tmp_x + win->centr_x;
	tmp_y = tmp_y + win->centr_y;
    win->map[y][x].x = tmp_x;
    win->map[y][x].y = tmp_y;
    win->map[y][x].z = tmp_z;
}

void    rotate_x(t_win *win, size_t y, size_t x, int new_angle)
{
    double tmp_y;
    double tmp_x;
    double tmp_z;
    double angle;

    if (!win)
		return ;
    win->map[y][x].x = win->map[y][x].x - win->centr_x;
	win->map[y][x].y = win->map[y][x].y - win->centr_y;
    angle = new_angle * PI / 180;
	tmp_x = win->map[y][x].x * cos(angle) + win->map[y][x].z * sin(angle);
	tmp_y = win->map[y][x].y;
	tmp_z = -win->map[y][x].x * sin(angle) + win->map[y][x].z * cos(angle);
	tmp_x = tmp_x + win->centr_x;
	tmp_y = tmp_y + win->centr_y;
    win->map[y][x].x = tmp_x;
    win->map[y][x].y = tmp_y;
    win->map[y][x].z = tmp_z;
 }

void    rotate_z(t_win *win, size_t y, size_t x, int new_angle)
{
    double tmp_y;
    double tmp_x;
    double tmp_z;
    double angle;

    if (!win)
		return ;
    win->map[y][x].x = win->map[y][x].x - win->centr_x;
	win->map[y][x].y = win->map[y][x].y - win->centr_y;
    angle = new_angle * PI / 180;
    tmp_x = win->map[y][x].x * cos(angle) - win->map[y][x].y * sin(angle);
    tmp_y = win->map[y][x].x * sin(angle) + win->map[y][x].y * cos(angle);
    tmp_z = win->map[y][x].z;
    tmp_x = tmp_x + win->centr_x;
	tmp_y = tmp_y + win->centr_y;
    win->map[y][x].x = tmp_x;
    win->map[y][x].y = tmp_y;
    win->map[y][x].z = tmp_z;
}

void    angle_reset(t_win *win)
{
    size_t	y;
	size_t	x;

    if (!win)
		return ;
         
    y = - 1;
	while (++y < win->map_rows)
    {
        x = - 1;
		while (++x < win->map_cols)
        {
            win->map[y][x].y = y;
            win->map[y][x].x = x;
            win->map[y][x].z = win->map[y][x].z_orig;
        }
    }
    draw_map(win);
}

void    rotate_map(t_win *win, char axis, int new_angle)
{
    size_t	y;
	size_t	x;

    if (!win )
		return ;
    y = - 1;
	while (++y < win->map_rows)
    {
        x = - 1;
		while (++x < win->map_cols)
        {
            if (axis == 'x' || axis == 'a') rotate_x(win, y, x, new_angle);    
            if (axis == 'y' || axis == 'a') rotate_y(win, y, x, new_angle);   
            if (axis == 'z' || axis == 'a') rotate_z(win, y, x, new_angle);
        }
    }
    draw_map(win);
}