# fdf its a study project,
and is about creating a simplified graphic representation of a relief landscape,
linking various points (x, y, z) via segments. 
The coordinates of this landscape are stored in a file passed as a parameter to your program.

![raw map-file example](https://github.com/roma4004/fdf/raw/master/img/map_example.png)

Each number corresponds to a point in space:

	• The horizontal position corresponds to its axis.

	• The vertical position corresponds to its ordinate.

	• The value corresponds to its altitude


Mandatory part:

	We cannot use global variables, must follow the Norm
	(see Norm.pdf, this explains many unobvious decisions solutions that I applied).
  
	We have to handle errors carefully. In no way can quit my program in an unexpected
  	manner (Segmentation fault, bus error, double free, etc).
  
	We are alowed to use the following functions:

	- open, read, write, close, malloc, free, perror, strerror, exit
	
	- All the functions defined in the math library
	
	- All the functions defined in the miniLibX library
	

Bonus part: (plus = already implemented, minus = decided not to implement)
  
	- Fill the boxes with a color according to altitude (green at the bottom, then brown,
	  then white on top for ex.)

	+ Specify the color spectrum in parameter.

	+ Manage correctly the hidden surfaces.

	+ Change types of projection.

My own bonus:

	Choiceing the different style of the connecting dots(pixels) on the map:
		+ new visual effects, eg "|", "/", "-", "\" 
		  (You can also animate the switching of these styles by holding the Enter key).
		  
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
	
	
	
