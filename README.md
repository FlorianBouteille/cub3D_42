# CUB3D 

A big project in the 42 Common core involving and old and fun technology : raycasting. 

Inspired from the classic "3D" game Wolfenstein, the idea is to take a 2D representation of a map with walls, doors and empty spaces and simulate a 3D view from it by casting a set of rays from the position of the player and drawing the environment in real time. 

As usual, this project starts with a lot of parsing, as every 42 project is always thouroughly tested by peers and should never behave unexpectedly in case of errors. So we took our time trying to foresee every possible error case while opening the file map and in the map itself. 
Then, we could start the actual core of the project, calculating the view. We started by drawing a simple minimap and tracing a single vector from the player, making sure the segment stopped when it encountered an obstacle. From that, we were able do determine a field of view and drawing one vector per pixel in the width of the rendering screen. This involved some basic trigonometry, as every vector needs to be cast according to the player position and orientation in the map. We then built textures for all 4 types of walls (north, south, east and west) and implemented a method do find out which wall needed to be drawn according to the vector direction and player position. The height of each wall segment is then drawn according to the vector length, the smaller the vector, the bigger the wall, and each pixel was selected vertically in the texture to get the final result. 

As a bonus, we built a system for opening doors, a minimap, some light animation and a "fast run" option. 

This was a really fun project and we're happy with the final product ! 
