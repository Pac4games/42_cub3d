# Cub3D
> Yeah, your setup looks great, but can it ***run doom though?***

This project is a 3D first-person game written in C, where we achieve a three-dimensional perspective through the use
of [Raycasting](https://en.wikipedia.org/wiki/Ray_casting) and the [miniLibX](https://github.com/42Paris/minilibx-linux) 
graphical library.

In this game you are free to walk around and explore the maps provided by us, customize them to your liking or even make
your own maps from scratch!

### But how do .cub maps work?
- The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
orientation.
This is a simple valid map:
```
111111
100101
101001
1100N1
111111
```
- The map must be closed/surrounded by walls
- Except for the map content, each type of element can be separated by one or
more empty line(s).
- Except for the map content which always has to be the last, each type of
element can be set in any order in the file.
- Except for the map, each type of information from an element can be separated
by one or more space(s).
- The map will be parsed as it looks in the file. Spaces are a valid part of the
map and handled as empty space.
- Each element (except the map) first information is the type identifier (composed by one or two character(s)),
followed by all specific informations for each object in a strict order such as

  - North texture:

    `NO ./path_to_the_north_texture`

    · identifier: NO
    
    · path to the north texure
    
  - South texture:

    `SO ./path_to_the_south_texture `
  
    · identifier: SO
  
    · path to the south texure

  - West texture:
  
    `WE ./path_to_the_west_texture`
  
    · identifier: WE
  
    · path to the west texure
  
  - East texture:
  
    `EA ./path_to_the_east_texture`
  
    · identifier: EA
  
    · path to the east texure

  - Floor color:
  
    `F 220,100,0`
  
    · identifier: F
  
    · R,G,B colors in range [0,255]: 0, 255, 255

  - Ceiling color:

    `C 225,30,0`
    
    · identifier: C
    
    · R,G,B colors in range [0,255]: 0, 255, 255

Example of a minimalist valid .cub map:

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```
