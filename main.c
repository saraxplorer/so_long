/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/17 16:48:43 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/06/03 17:41:16 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void error_exit(char* str)
{
 ft_putstr_fd("Error\n", 2);
 ft_putendl_fd(str, 2);
 exit(EXIT_FAILURE);
}

void check_file_extension(char *name)
{
	size_t len;
	len = ft_strlen(name);
	if (len < 4 || ft_strncmp(&name [len - 4], ".ber", 4)!= 0) 
		error_exit("Please provide a .ber file");
}

int main(int argc, char **argv)
{
 
	t_game	game;
	
 	if (argc < 2)
 		error_exit("Please input one gaming map");
	if (argc > 2)
 		error_exit("Please input one file at a time");
	check_file_extension(argv[1]);
	game = map_to_data(argv[1]);
	 game.mlx = mlx_init((game.width * PIXELS), (game.height * PIXELS), "abc", true);
	if (!game.mlx)
		error_exit("GAME CANNOT INITIATE");
	game.img = struct_image(&game);
	background_to_window(&game);
	images_to_window(&game);
	mlx_key_hook(game.mlx, hook_moves, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_map(game.grid, game.height);
	free(game.img);
	return (EXIT_SUCCESS);
}
