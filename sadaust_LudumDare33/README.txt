This program was made as part of the Ludum Dare 33 game jam, it is provided in an as is state and no garantes are made that it will not cause damage to your computer from use.

Options file format:
0.45f //mouse x sensitivity
0.15f //mouse y sensitivity
map.txt //what map to load


Map system notes:
map load has no error checking so be careful
game supports 200 creatures and 100 buildings
players always start at 0,0,0
players start at size 1
players only need to be as large as a creature to eat it
players have to be bigger than buildings to eat them
game ends when all things are eaten

Map file format:
-2000 2000 -2000 2000 //left, right, back, and front edges of the world
c 10 0 4 //letter designates type c for creatures b for buildings, x positon, y position, size
c 5 5 2
c -10 0 8
c -10 10 16
b 200 0 10