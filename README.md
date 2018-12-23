![title](https://github.com/roma4004/fdf/raw/master/images/title.png)
# fdf is about creating a simplified graphic representation of a relief landscape, linking various points (x, y, z) via segments with algorithm of [Bresenham](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm). 
The coordinates of this landscape are stored in a file passed as a parameter to your program.
raw map example 42.fdf:
```
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```
Each number corresponds to a point in space:

	• The horizontal position corresponds to its axis.
	• The vertical position corresponds to its ordinate.
	• The value corresponds to its altitude


**Mandatory part:**

We cannot use global variables, must follow the [Norm](https://github.com/roma4004/fdf/blob/master/documentation/norme.en.pdf), **this explains many unobvious decisions solutions that I applied, like function in 25 row, or only 4 argument in function**).

We have to handle errors carefully. In no way can quit my program in an unexpected
manner (Segmentation fault, bus error, double free, etc).
	
   We are alowed to use the following functions:
	
   	• open, read, write, close, malloc, free, perror, strerror, exit	
	• All the functions defined in the math library
	• All the functions defined in the miniLibX library

**Bonus part:** (plus = already implemented, minus = decided not to implement)
	
	- Fill the boxes with a color according to altitude
	  (green at the bottom, then brown, then white on top for ex.).
	+ Specify the color spectrum in parameter.
	+ Manage correctly the hidden surfaces.
	+ Change types of projection.
	
**My own bonus:**
	
	Choiceing the different style of the connecting dots(pixels) on the map:
		+ new visual effects, eg "|", "/", "-", "\" 
		  (You can also animate the switching of these styles by holding the Enter key).
		  *separated visual example of vertical, horizontal, backslash and slash connecting of dots: 
![raw map-file example](https://github.com/roma4004/fdf/raw/master/images/4%20basic%20styles.png)
		  *for example, which gives a combination of vertical + horizontal + slash, and a separate backslash: 
![raw map-file example](https://github.com/roma4004/fdf/raw/master/images/effect_combination.png)

		+ Standard way of connecting, that named "fdf".		
		+ Ability to disconnect the connection between layers, that named "layer".		
		+ Display just dots wireframe of the map (non connected style), effects named "dot" .		
		* All effects can be superimposed on each other, that is, simultaneously turn on.
	Rotating maps on all axis (X,Y,Z) relative to their center. 
		*That would create the illusion of a 3D object on a 2D screen.
	Moveing maps on the screen.
	Zoom maps on all axis and zoom only on Z axis, which is give you ability to change maps altitude.
	Ability to disable or enable the interface.
	Ability to quickly to reset the scaling, moving and rotating the current map's angel.
	
	
Examples:

Classical simple implementation of fdf looks like this:
![classic_fdf](https://github.com/roma4004/fdf/raw/master/images/fdf_demo_classic.png)
or basic valid variant:
![classic_fdf](https://github.com/roma4004/fdf/raw/master/images/classic_fdf.jpg)

My implementation of classic fdf:
![my_classic_fdf](https://github.com/roma4004/fdf/raw/master/images/my_classic_fdf.png)

Effect with disconnected layers fdf:
![my_fdf_with_disconnected_layers](https://github.com/roma4004/fdf/raw/master/images/my_fdf_with_disconnected_layers.png)
	
Maps can be more interesting with fractal or terrain (if the color on the card is set it will be read and displayed):
![julia](https://github.com/roma4004/fdf/raw/master/images/julia.png)
![mandelbrot](https://github.com/roma4004/fdf/raw/master/images/mandelbrot.png)
![landscape1](https://github.com/roma4004/fdf/raw/master/images/landscape1.png)
![Z_scale](https://github.com/roma4004/fdf/raw/master/images/with_interface/pylone/Z_scale.png)
![Z_scale2](https://github.com/roma4004/fdf/raw/master/images/with_interface/pylone/Z_scale2.png)
![layer_style](https://github.com/roma4004/fdf/raw/master/images/with_interface/pylone/layer_style.png)
![dot_style](https://github.com/roma4004/fdf/raw/master/images/with_interface/pylone/dot_style.png)
![Z_scale_rotated](https://github.com/roma4004/fdf/raw/master/images/with_interface/pylone/Z_scale_rotated.png)
![layer_rotated](https://github.com/roma4004/fdf/raw/master/images/with_interface/pylone/Z_scale_layer_rotated.png)
![layer_rotated](https://github.com/roma4004/fdf/raw/master/images/with_interface/pylone/Z_scale_dot_rotated.png)
![layer_rotated2](https://github.com/roma4004/fdf/raw/master/images/with_interface/pylone/Z_scale_layer_rotated2.png)
![dot_rotated2](https://github.com/roma4004/fdf/raw/master/images/with_interface/pylone/Z_scale_dot_rotated2.png)

many other cool screenshot img of my fdd can be found in [./img](https://github.com/roma4004/fdf/blob/master/images/)
