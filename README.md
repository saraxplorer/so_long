# so_long

**Step 1: Download and build the library MLX42**

Google MLX42 and download from github.+ make

**Step 2: Opening a window**

#X window system: commonly known as X11 or simply X, is a windowing system that provides a graphical user interface for Unix-based operating systems, allowing users to interact with programs through graphical elements like windows, buttons, and menus.
#data types: The data types we are seeing here like mlx_t, mlx_image_t are structs defined inside the library. For example, in the location MLX42/include/MLX42
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
The mlx_t* mlx_init(int32_t width, int32_t height, const char* title, bool resize) function sets up a connection between our program and the X window system. This connection is necessary for our program to be able to interact with the windowing system and display graphical elements on the screen. Once the connection is established, our program can create windows, handle user input, and perform other graphical operations using the functions provided by the mlx library. mlx_init() returns a pointer to an opaque structure that represents the connection. That pointer can then be passed to other MLX42 functions that require a connection to the X server. They'll know exactly what window instance they should be working with.
Because mlx_init returns a pointer to the window instance, that will be used by other MLX42 functions.

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

**Step 3: Making a image inside the window**

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
	memset(g_img->pixels, 255, g_img->width * g_img->height *sizeof(int));//lot going on
	mlx_image_to_window(mlx, g_img, 0, 0);// Draw the image at coordinate (0, 0).
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return(EXIT_SUCCESS);
}
``` c

memset(void *memset(void *ptr, int value, size_t num);
ptr: A pointer to the memory block to be filled.
value: The value to be set. This is an integer, typically represented as an unsigned char. 
So, when using memset, you provide the pointer to the memory block (g_img->pixels), the value you want to set (255), and the number of bytes (we calculate) to be set to that value.
In MLX42, the mlx_image_t is defined.
g_img->width * g_img->height *sizeof(int): we input height, width through mlx_new_image function.

