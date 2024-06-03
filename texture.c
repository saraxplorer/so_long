/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 17:45:31 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/05/28 16:12:22 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img *player_tx(mlx_t *mlx, t_img *image)
{
	mlx_texture_t *player;
	
	player = mlx_load_png("images/player1.png");
	if (player == NULL)
		error_exit("cannot load wall");
	image->player = mlx_texture_to_image(mlx, player);
	if (image->player == NULL)
		error_exit("cannot view wall");
	mlx_delete_texture(player);
	return (image);
}

t_img *exit_tx(mlx_t *mlx, t_img *image)
{
	mlx_texture_t *exit;
	
	exit = mlx_load_png("images/exit1.png");
	if (exit == NULL)
		error_exit("cannot load wall");
	image->exit = mlx_texture_to_image(mlx, exit);
	if (image->exit == NULL)
		error_exit("cannot view wall");
	mlx_delete_texture(exit);
	return (image);
}

t_img *collectable_tx(mlx_t *mlx, t_img *image)
{
	mlx_texture_t *Geld;
	
	Geld = mlx_load_png("images/treasure.png");
	if (Geld == NULL)
		error_exit("cannot load wall");
	image->geld = mlx_texture_to_image(mlx, Geld);
	if (image->geld == NULL)
		error_exit("cannot view wall");
	mlx_delete_texture(Geld);
	return (image);
}

t_img *wall_tx(mlx_t *mlx, t_img *image)
{
	mlx_texture_t *wall;
	
	wall = mlx_load_png("images/wall1.png");
	if (wall == NULL)
		error_exit("cannot load wall");
	image->wall = mlx_texture_to_image(mlx, wall);
	if (image->wall == NULL)
		error_exit("cannot view wall");
	mlx_delete_texture(wall);
	return (image);
}

t_img *background_tx(mlx_t *mlx, t_img *image)
{
	mlx_texture_t *background;
	
	background = mlx_load_png("images/grass.png");
	if (background == NULL)
		error_exit("cannot load background");
	image->background = mlx_texture_to_image(mlx, background);
	if (image->background == NULL)
		error_exit("cannot view background");
	mlx_delete_texture(background);
	return (image);
}