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




void    rotate_x(t_win *win, size_t y, size_t x, long z)
{
    int sh_y;
    int sh_x;
    int sh_z;

   // int c_y;
    //int c_x;
   // int c_z;

    if (!win)
		return ; 
    sh_y = win->height / 2;
    sh_x = win->width / 2;
    sh_z = win->map[y][x].z / 2;

    win->map[y][x].x = x;
    win->map[y][x].y = y * cos(win->angle_x) + z * -sin(win->angle_x);
    win->map[y][x].z = y * sin(win->angle_x) + z * cos(win->angle_x);
    printf("\nreset Y:%zu X:%zu y=%f, x=%f, z=%f\n", y, x, win->map[y][x].y, win->map[y][x].x, win->map[y][x].z);
}

void    rotate_y(t_win *win, size_t y, size_t x, long z)
{
    int sh_y;
    int sh_x;
    int sh_z;

    if (!win)
		return ; 
    sh_y = win->height / 2;
    sh_x = win->width / 2;
    sh_z = win->map[y][x].z / 2;
    win->map[y][x].x = x * cos(win->angle_y) + z * sin(win->angle_y);
    win->map[y][x].z = x * -sin(win->angle_y) + z * cos(win->angle_y);
    printf("\nreset Y:%zu X:%zu y=%f, x=%f, z=%f\n", y, x, win->map[y][x].y, win->map[y][x].x, win->map[y][x].z);
}

void    rotate_z(t_win *win, size_t y, size_t x, long z)
{
    int sh_y;
    int sh_x;
    int sh_z;

    if (!win)
		return ; 
    sh_y = win->map_rows / 2;
    sh_x = win->map_cols / 2;
    sh_z = win->map[y][x].z / 2;
    win->map[y][x].x = x  * cos(win->angle_z) - y * sin(win->angle_z);
    win->map[y][x].y = x * sin(win->angle_z) + y * cos(win->angle_z);
    z++;
    printf("\nreset Y:%zu X:%zu y=%f, x=%f, z=%f\n", y, x, win->map[y][x].y, win->map[y][x].x, win->map[y][x].z);
}

void    rotate_map_px(t_win *win, size_t y, size_t x, long z)
{
    int sh_x;
    int sh_y;
    int sh_z;

    if (!win)
		return ; 
    sh_y = win->height / 2;
    sh_x = win->width / 2;
    sh_z = win->map[y][x].z / 2;
    win->map[y][x].y = sh_y + (y - sh_y) * cos(win->angle_x) + (sh_z - z) * sin(win->angle_x);
    win->map[y][x].z = sh_z + (y - sh_y) * sin(win->angle_x) + (z - sh_z) * cos(win->angle_x);


    win->map[y][x].x = sh_x + (x - sh_x) * cos(win->angle_y) + (z - sh_z) * sin(win->angle_y);
    win->map[y][x].y = y;
    win->map[y][x].z = sh_z + (sh_x - x) * sin(win->angle_y) + (z - sh_z) * cos(win->angle_y);

    win->map[y][x].x = sh_x + (x - sh_x) * cos(win->angle_z) + (sh_y - y) * sin(win->angle_z);
    win->map[y][x].y = sh_y + (x - sh_x) * sin(win->angle_z) + (y - sh_y) * cos(win->angle_z);
    win->map[y][x].z = z;
    /*printf("\nreset Y:%zu X:%zu y=%f, x=%f, z=%f\n", y, x, win->map[y][x].y, win->map[y][x].x, win->map[y][x].z);
    win->map[y][x].x = x;
    win->map[y][x].y =  y * cos(win->angle_y) + win->map[y][x].z_orig * sin(win->angle_y);
    win->map[y][x].z = -y * sin(win->angle_y) + win->map[y][x].z_orig * cos(win->angle_y);
    //printf("\nreset Y:%zu X:%zu y=%f, x=%f, z=%f\n", y, x, win->map[y][x].y, win->map[y][x].x, win->map[y][x].z);
    win->map[y][x].x = win->map[y][x].x * cos(win->angle_x) + z * sin(win->angle_x);
    win->map[y][x].y = win->map[y][x].y;
    win->map[y][x].z = -win->map[y][x].x * sin(win->angle_x) - z * cos(win->angle_x);
    //printf("\nreset Y:%zu X:%zu y=%f, x=%f, z=%f\n", y, x, win->map[y][x].y, win->map[y][x].x, win->map[y][x].z);
    win->map[y][x].x = win->map[y][x].x * cos(win->angle_z) + win->map[y][x].y * sin(win->angle_z);
    win->map[y][x].y = win->map[y][x].x * sin(win->angle_z) + win->map[y][x].y * cos(win->angle_z);
    win->map[y][x].z = win->map[y][x].z;*/
}


void    angle_reset(t_win *win)
{
    if (!win)
		return ;
    mlx_clear_window(win->mlx_ptr, win->win_ptr);       
    win->angle_y = 0;
    win->angle_x = 0;
    win->angle_z = 0;
    
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
            win->map[y][x].y = y;
            win->map[y][x].x = x;
            win->map[y][x].z = win->map[y][x].z_orig;
        }
    }
    printf("reset angle_y=%f, angle_x=%f, angle_z=%f\n", win->angle_y, win->angle_x, win->angle_z);
    draw_map(rotate_map(win, 'a'));
}

t_win   *rotate_map(t_win *win, char axis)
{
    size_t	y;
	size_t	x;

    if (!win )
		return (NULL);
    y = - 1;
	while (++y < win->map_rows)
    {
        x = - 1;
		while (++x < win->map_cols)
        {
            //rotate_map_px(win, y, x, win->map[y][x].z_orig);
        //axis++;
         if (axis == 'x' || axis == 'a') rotate_x(win, y, x, win->map[y][x].z_orig);    
         if (axis == 'y' || axis == 'a') rotate_y(win, y, x, win->map[y][x].z_orig);   
         if (axis == 'z' || axis == 'a') rotate_z(win, y, x, win->map[y][x].z_orig); 
        }
    }

    return(win);
}

void   angle_change(t_win *win, char axis, int offset_angle)
{
    if (!win)
		return ;
    mlx_clear_window(win->mlx_ptr, win->win_ptr);   
    if (axis == 'y')
        win->angle_y += offset_angle * 0.1;
    if (axis == 'x')
        win->angle_x += offset_angle * 0.1;
    if (axis == 'z')
        win->angle_z += offset_angle * 0.1;
        printf("angle_y=%f, angle_x=%f, angle_z=%f\n", win->angle_y, win->angle_x, win->angle_z);
    rotate_map(win, axis);
    draw_map(win);
}
