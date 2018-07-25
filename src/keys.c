/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/22 15:22:31 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	deal_keyboard3(int key, t_win *win)
{
	if (!win)
		return (1);
	if (key == Q)
		rotate_map(win, 'y', 2);
	else if (key == W)
		rotate_map(win, 'x', 2);
	else if (key == E)
		rotate_map(win, 'z', 2);
	else if (key == A)
		rotate_map(win, 'y', -2);
	else if (key == S)
		rotate_map(win, 'x', -2);
	else if (key == D)
		rotate_map(win, 'z', -2);
	else if (key == R)
		reset(win);
	return (0);
}

static int	deal_keyboard2(int key, t_win *win)
{
	if (!win)
		return (1);
	if (key == NUM_1 || key == ONE)
		toggles(win, 1);
	else if (key == NUM_2 || key == TWO)
		toggles(win, 2);
	else if (key == NUM_3 || key == THREE)
		toggles(win, 3);
	else if (key == NUM_4 || key == FOUR)
		toggles(win, 4);
	else if (key == NUM_5 || key == FIVE)
		toggles(win, 5);
	else if (key == NUM_6 || key == SIX)
		toggles(win, 6);
	else if (key == NUM_7 || key == SEVEN)
		toggles(win, 7);
	else if (key == NUM_8 || key == EIGHT)
		toggles(win, 8);
	else
		deal_keyboard3(key, win);
	return (0);
}

int			deal_keyboard(int key, t_win *win)
{
	if (!win)
		return (1);
	if (key == ARROW_LEFT)
		map_offset(win, -10, 0);
	else if (key == ARROW_UP)
		map_offset(win, 0, -10);
	else if (key == ARROW_DOWN)
		map_offset(win, 0, 10);
	else if (key == ARROW_RIGHT)
		map_offset(win, 10, 0);
	else if (key == NUM_MINUS || key == NINE)
		zoom_offset(win, -1, 1);
	else if (key == NUM_PLUS || key == ZERO)
		zoom_offset(win, +1, 1);
	else if (key == ENTER)
		animate(win);
	else if (key == MINUS)
		zoom_offset(win, -1, 0);
	else if (key == PLUS)
		zoom_offset(win, 1, 0);
	else
		deal_keyboard2(key, win);
	return (0);
}

int			deal_mouse(int key, int x, int y, t_win *win)
{
	if (!win)
		return (1);
	y++;
	x++;
	if (key == MOUSE_SCROLL_UP)
		zoom_offset(win, -1, 0);
	else if (key == MOUSE_SCROLL_DOWN)
		zoom_offset(win, 1, 0);
	return (0);
}
