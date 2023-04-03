/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:03:55 by joestrad          #+#    #+#             */
/*   Updated: 2023/03/27 19:02:58 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

/**
 * @brief 			This function locates the enemy's position in the map,
 * 					that is the row and the column where the enemy is
 * 
 * @param game 		A pointer to the main structure of the program
 * @param e_r  		A pointer to the row where the enemy is
 * @param e_c  		A pointer to the column where the enemy is
 */
void	ft_locate_enemy(t_game *game)
{
	while (game->ene_x < game->map_nr)
	{
		game->ene_y = 0;
		while (game->ene_y < game->map_nc)
		{
			if (game->map[game->ene_x][game->ene_y] == 'B')
			{
				game->ene_x = game->ene_x;
				game->ene_y = game->ene_y;
				break ;
			}
			game->ene_y++;
		}
		if (game->map[game->ene_x][game->ene_y] == 'B')
		{
			game->ene_x = game->ene_x;
			game->ene_y = game->ene_y;
			break ;
		}
		game->ene_x++;
	}
}

/**
 * @brief 			This function displays the a message that indicates that
 * 					the player has lost the game and it finished the program
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_game_over(t_game *game)
{
	ft_putendl_fd("Game Over\nYou have lost", 1);
	ft_free(game);
	exit(1);
}

/**
 * @brief 			This function draws the map and the number of moves
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_draw(t_game *game)
{
	ft_draw_map(game);
	ft_print_score(game);
}

/**
 * @brief 			This function moves the enemy horizontaly in the game
 * 
 * @param param 	A param passed to the function, in this case is a pointer
 * 					to the game structure
 */
void	ft_move_enemy(void *param)
{
	static int	dir = 1;
	static int	delta_t = 0;
	t_game		*game;

	game = param;
	if (delta_t++ == 5)
	{
		if (game->n_en > 0)
		{
			ft_locate_enemy(game);
			if (game->map[game->ene_x][game->ene_y - (1 * dir)] == '0')
			{
				game->map[game->ene_x][game->ene_y - (1 * dir)] = 'B';
				game->map[game->ene_x][game->ene_y] = '0';
			}	
			else if (game->map[game->ene_x][game->ene_y - (1 * dir)] == 'P')
			{
				ft_game_over(game);
			}
			else
				dir *= -1;
			ft_draw(game);
		}
		delta_t = 0;
	}
}

/**
 * @brief 			This function writes the number of moves on the game's
 * 					windows
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_print_score(t_game *game)
{
	char	*score;

	score = ft_itoa(game->n_moves);
	mlx_delete_image(game->mlx, game->score_i);
	game->score_i = mlx_put_string(game->mlx, score, 15, 14);
	free(score);
}
