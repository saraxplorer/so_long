/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_image.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/06 17:26:02 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/05/28 15:35:30 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img *struct_image(t_game *game)
{
	t_img *texture;
	
	texture = (t_img*)ft_calloc(1, sizeof(t_img));
	if (texture == NULL)
		error_exit("Memory allocation failed");
	texture = background_tx(game->mlx, texture);
	texture = wall_tx(game->mlx, texture);
	texture = exit_tx(game->mlx, texture);
	texture = collectable_tx(game->mlx, texture);
	texture = player_tx(game->mlx, texture);
	return(texture);
}
