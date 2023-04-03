/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:09:27 by joestrad          #+#    #+#             */
/*   Updated: 2023/03/22 14:49:50 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * @brief 			This function draws the map's element given by elem in the
 * 					window's position given by x and y
 * 
 * @param g 		A pointer to the main structure of the program
 * @param elem 		The element that has to be drawn
 * @param y 		The y position
 * @param x 		The x position
 */
void	ft_draw_element(t_game *g, mlx_image_t *elem, int y, int x)
{
	mlx_image_to_window(g->mlx, elem, y * g->sprite_w, x * g->sprite_h);
}

/**
 * @brief 		This function draws the map in the game's window
 * 
 * @param g 	A pointer to the main structure of the program
 */
void	ft_draw_map(t_game *g)
{
	int	map_x;
	int	map_y;

	map_x = 0;
	while (map_x < g->map_nr)
	{
		map_y = 0;
		while (map_y < g->map_nc)
		{
			if (g->map[map_x][map_y] == '0')
				ft_draw_element(g, g->ground_i, map_y, map_x);
			else if (g->map[map_x][map_y] == '1')
				ft_draw_element(g, g->wall_i, map_y, map_x);
			else if (g->map[map_x][map_y] == 'P')
				ft_draw_element(g, g->player_i, map_y, map_x);
			else if (g->map[map_x][map_y] == 'C')
				ft_draw_element(g, g->collect_i, map_y, map_x);
			else
				ft_draw_element(g, g->exit_i, map_y, map_x);
			map_y++;
		}
		map_x++;
	}
}

/**
 * @brief 			This function creates the game's window, loads the
 * 					textures from the files and creates the images of them 
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_create_window(t_game *game)
{
	t_textures	imgs;

	game->mlx = mlx_init(game->map_w, game->map_h, "so_long", false);
	imgs.wall = mlx_load_png("textures/wall.png");
	imgs.ground = mlx_load_png("textures/floor.png");
	imgs.player = mlx_load_png("textures/player.png");
	imgs.exit = mlx_load_png("textures/exit.png");
	imgs.collect = mlx_load_png("textures/collect.png");
	game->wall_i = mlx_texture_to_image(game->mlx, imgs.wall);
	game->ground_i = mlx_texture_to_image(game->mlx, imgs.ground);
	game->player_i = mlx_texture_to_image(game->mlx, imgs.player);
	game->exit_i = mlx_texture_to_image(game->mlx, imgs.exit);
	game->collect_i = mlx_texture_to_image(game->mlx, imgs.collect);
	mlx_delete_texture(imgs.collect);
	mlx_delete_texture(imgs.wall);
	mlx_delete_texture(imgs.ground);
	mlx_delete_texture(imgs.exit);
	mlx_delete_texture(imgs.player);
}

/**
 * @brief 			This function start the game and it is called after the
 * 					map has been validated (and it is ok)
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_start_game(t_game *game)
{
	ft_create_window(game);
	ft_draw_map(game);
	mlx_key_hook(game->mlx, &ft_player_mov, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
