# so_long

1. General Guide
2. Development steps of the actual code with some expalanations

***GENERAL GUIDE/Try First***
This is a step by step tutorial for beginners to learn using the MLX42 library. 

**Step 1: Download and build the library MLX42**

Google MLX42 and download from github.+ make

**Step 2: Opening a window**


#X window system: commonly known as X11 or simply X, is a windowing system that provides a graphical user interface for Unix-based operating systems, allowing users to interact with programs through graphical elements like windows, buttons, and menus.
#data types: The data types we are seeing here like mlx_t, mlx_image_t are structs defined inside the library. in the location MLX42/include/MLX42
/MLX42.h a million things are defined there. 
```c
typedef struct mlx_image
{
	const uint32_t	width;
	const uint32_t	height;
	uint8_t*		pixels;
	mlx_instance_t*	instances;
	size_t			count;
	bool			enabled;
	void*			context;
}	mlx_image_t;
```
#MLX_INIT
The mlx_t* mlx_init(int32_t width, int32_t height, const char* title, bool resize) 

Initializes a new MLX42 Instance.

Parameters:
width – The width of the window.
height – The height of the window.
title – The title of the window.
resize – Enable window resizing.

Returns:
Ptr to the MLX handle or null on failure.

This function sets up a connection between our program and the X window system. This connection is necessary for our program to be able to interact with the windowing system and display graphical elements on the screen. Once the connection is established, our program can create windows, handle user input, and perform other graphical operations using the functions provided by the mlx library. mlx_init() returns a pointer to an opaque structure that represents the connection. That pointer can then be passed to other MLX42 functions that require a connection to the X server. They'll know exactly what window instance they should be working with.


#MLX_LOOP
The void mlx_loop(mlx_t* mlx) function only takes a pointer to our window connection and starts an infinite loop that continuously waits for events to occur in the X window system. 

``` c
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 500
#define HEIGHT 500

int32_t main(void)
{
	mlx_t	*mlx; //mlx_t * is a pointer to the window we open
	mlx = mlx_init(WIDTH, HEIGHT, "GAME", true);// Init mlx with a canvas size of 500x500 and the ability to resize the window.
	if (!mlx)
		exit(EXIT_FAILURE);
	mlx_loop(mlx);// Run the main loop and terminate on quit. 
	mlx_terminate(mlx);
}
```
compile with:

cc main.c MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm
./a.out 

it will open a window
MLX42 is dependent on a few other libraries, when you are using Linux you should also link the libraries required. With the following command.
-ldl -lglfw -lm -lpthread
dl -> Dynamically loaded (DL)
glfw -> Graphics Library Framework
m -> Math library

**Step 3: Making an image inside the window**

``` c
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 500
#define HEIGHT 500

mlx_image_t	*g_img; //initialize the image outside the function(global variable?)!

int32_t main(void)
{
	mlx_t	*mlx;
	mlx = mlx_init(WIDTH, HEIGHT, "GAME", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 230, 230);//Create a 230x230 image.
	memset(g_img->pixels, 255, g_img->width * g_img->height *sizeof(int));
	mlx_image_to_window(mlx, g_img, 0, 0);// Draw the image at coordinate (0, 0).
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return(EXIT_SUCCESS);
}
```
memset(void *memset(void *ptr, int value, size_t num);
ptr: A pointer to the memory block to be filled.
value: The value to be set. This is an integer, typically represented as an unsigned char. 
So, when using memset, you provide the pointer to the memory block (g_img->pixels), the value you want to set (255), and the number of bytes (we calculate) to be set to that value.
In MLX42, the mlx_image_t is defined.
g_img->width * g_img->height *sizeof(int): we input height, width through mlx_new_image function.

**Step 4: make a texture in the window**

we will need a .png file with the texture. I downloaded it from github. i am using mlx_load_png and mlx_texture_to_image functions for it.
```c
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 500
#define HEIGHT 500

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t main(void)
{
	mlx_t	*mlx;
	mlx = mlx_init(WIDTH, HEIGHT, "GAME", true);
	if (!mlx)
		error();
	mlx_texture_t *texture = mlx_load_png("./images/Grass.png");// Try to load the file
	if (!texture)
		error();
	mlx_image_t	*img = mlx_texture_to_image(mlx, texture);// Convert texture to a displayable image
	if (!img)
		error();
	mlx_image_to_window(mlx, img, 0, 0);// Display the image
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);//to avoid memory leaks, possibly
	mlx_delete_texture(texture);//to avoid memory leaks, possibly
	mlx_terminate(mlx);
}
```

The name and location need to be precise.

**Step 5: Make the whole background**

Making the whole background needs to repeatedly use the texture for the whole WIDTH and HEGHT. Here's how we can achieve it.

```c
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 500
#define HEIGHT 500

void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t main(void)
{
	mlx_t	*mlx;
	mlx = mlx_init(WIDTH, HEIGHT, "GAME", true);
	if (!mlx)
		error();
	mlx_texture_t *texture = mlx_load_png("./images/Grass.png");
	if (!texture)
		error();
	mlx_image_t	*img = mlx_texture_to_image(mlx, texture);
	if (!img)
		error();
	int textureWidth = texture->width;//the width of the .png image
	int textureHeight = texture->height;//the height of the .png image
	
	int y = 0;
	while (y < HEIGHT) //y will loop untill HEIGHT
	{
		int x = 0;
		while (x < WIDTH)
		{
			mlx_image_to_window(mlx, img, x, y);
			x = x + textureWidth;
		}
		y = y + textureHeight;
	}
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);
	mlx_terminate(mlx);
}
```

Development steps:
1. Make sure if there is a map inputted and only one map
2. Make sure that the map is .ber and not in other format
3. read the map with get_next_line function. For this we need open function. This function returns a unique fd(starting from 3). We keep readind line by line and store it as a pointer to char. we have now the map as a str.
4. Now we check if there is an empty line in the string by checking for either a newline at the very beginning or two consecutive newlines(meaning one empty line)
5.  Check contents and their numbers according to subject requirements. Use ft_strchr to find the first occurance of an unwanted/invalid char in the map
6.  Use ft_split to break the string map at the newline char into array of strings(or map lines in this case). now we have pointer to pointer to the lines. They can be used as grid(x, y)!
7.  Make sure map shape is rectangular and while we are at it we can get the height cause it will be the number of lines!
8.  Make sure the path is correct for playing i.e. walls not surrounding player/collectable/exit. for this, we make a temporary struct. This struct will be same as game struct. Members of the struct are- collectables, height, weidth, grid, player_x position player_y position ans exit_x position. To make a copy of the map in the temporary struct, we allocate memory for "height" numbers because it is the number of lines.Then we populate it line by line with ft_strdup. All othe r variables need to be assigned using functions like element_position and collectables_num.
9.  Now we do the path check from the temp map. Here comes a new concept of 2D path checking(similar to flood fill) which I will describe. example map:
```c
11111
100C1
1P0E1
11111
```
and this is the relevant code
```c
void	check_path_all(t_game *temp, int y, int x)
{
	if (temp->grid[y][x] == '1')
		return ;
	if (temp->grid[y][x] == 'E')
		temp->exit_x = 1;
	if (temp->grid[y][x] == 'C')
		temp->geld--;
	temp->grid[y][x] = '1';
	check_path_all(temp, y + 1, x);
	check_path_all(temp, y - 1, x);
	check_path_all(temp, y, x + 1);
	check_path_all(temp, y, x - 1);
}

void	check_path(char **map, int height)
{
	t_game	temp;

	temp = temp_game(map, height);
	check_path_all(&temp, temp.player_y, temp.player_x);
	if (temp.exit_x != 1 || temp.geld != 0)
	{
		free_map(map, height);
		free_map(temp.grid, temp.height);
		error_exit("path not valid");
	}
	free_map(temp.grid, temp.height);
}
```
9.1. Start at the position of the player (marked as 'P').

9.2. Move down if possible (if the position below is not a wall '1').

9.3. If the position below is clear ('0'), mark it as visited ('1') and move to that position.

9.4. Repeat steps 2-3 recursively until reaching the bottom or hitting a wall.

9.5. If there are no more positions to move downward, move upward if possible (if the position above is not a wall '1').

9.6. Repeat steps 3-5 recursively until reaching the top or hitting a wall.

9.7. Once vertical movements are exhausted, move right if possible (if the position to the right is not a wall '1').

9.8. Repeat steps 3-7 recursively until reaching the rightmost edge or hitting a wall.

9.9. Once rightward movements are exhausted, move left if possible (if the position to the left is not a wall '1').

9.10. Repeat steps 3-9 recursively until reaching the leftmost edge or hitting a wall.

9.11. During each step, check if the current position contains a special marker:
	a. If it's the exit ('E'), set a flag to indicate that the exit has been found.
	b. If it's a coin ('C'), decrement the coin count.
 
9.12. Continue until all reachable positions have been visited.
Lets' put some visualizations in. 

Initial Map:

```C
11111
100C1
1P0E1
11111
```
Step 1: Go downward from 'P' until blocked by a wall or bottom.

```C
11111
100C1
110E1
11111
```
Step 2: Go upward from the last visited position until blocked by a wall or top.

```C
11111
110C1
110E1
11111
```
Step 3: Go rightward from the last visited position until blocked by a wall or edge.

```C
11111
111C1
110E1
11111
```
Step 4: Go leftward from the last visited position until blocked by a wall or edge.

```C
11111
111C1
110E1
11111
```
Step 5: Backtrack to the previous position, explore downward until blocked by a wall or bottom.

```C
11111
111C1
111E1
11111
```
Step 6: Backtrack to the previous position, explore upward until blocked by a wall or top.

```C
11111
11111
111E1
11111
```
Step 7: Recursion completes, all reachable positions marked as '1'.

```C
11111
11111
11111
11111
```
10. Initialize game like we did for temp
11. Check walls
12.  mlx_t *mlx_init(int32_t width, int32_t height, const char *title, bool resize)

**Initializes a new MLX42 Instance /environment**

Parameters:
width – The width of the window.
height – The height of the window.
title – name of the game.
resize – Enable window resizing.


Returns:
Ptr to the MLX handle or null on failure.

13. mlx_texture_t *mlx_load_png(const char *path)

**load a PNG file into a buffer.**

Parameters:
path – Path to the PNG file.

Returns:
If successful the texture data is returned, else NULL.

14. mlx_image_t *mlx_texture_to_image(mlx_t *mlx, mlx_texture_t *texture)
**Converts a given texture to an image**

Parameters:
mlx – The MLX instance handle.
texture – The texture to use to create the image from.

Returns:
mlx_image_t* The image created from the texture.

15. void mlx_delete_texture(mlx_texture_t *texture)
**Deletes a texture by freeing its allocated data.**

Parameters:
texture – The texture to free.

16. int32_t mlx_image_to_window(mlx_t *mlx, mlx_image_t *img, int32_t x, int32_t y)
**Draws a new (instance of) an image, it will then share the same pixel buffer as the image. NOTE: Keep in mind that the instance array gets reallocated, try to store the return value to the instance! NOT the pointer! It will become invalid! WARNING: Try to display as few images on the window as possible, drawing too many images will cause a loss in performance!

Parameters:
mlx – The MLX instance handle.
img – The image to draw on the screen.
x – The X position.
y – The Y position.

Returns:
Index to the instance, or -1 on failure.

17. void mlx_key_hook(mlx_t *mlx, mlx_keyfunc func, void *param)
**This function sets the key callback, which is called when a key is pressed on the keyboard. Useful for single keypress detection.**

Parameters:
mlx – The MLX instance handle.
func – The keypress callback function(!)
param – An additional optional parameter.

mlx_keyfunc is === mlx_key_data_t in my code
typedef struct mlx_key_data 
mlx_key_data_t
Key function callback data. Data related to the mlx_key_hook function

Parameters:
key – The key that was pressed.
action – The action that was done with the key.
os_key – The os_key is unique for every key, and will have a different value/keycode depending on the platform. They may be consistent on different platforms.
modifier – The modifier key that was pressed, 0 if no key was pressed.
