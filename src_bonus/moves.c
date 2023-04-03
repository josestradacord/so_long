/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:44:44 by joestrad          #+#    #+#             */
/*   Updated: 2023/03/27 17:38:44 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

/**
 * @brief 			This function checks if the player has collected all
 * 					the collectable objects and can exit the game, if he can't
 * 					a message is shown
 * 
 * @param game 		A pointer to the main structure of the program
 * @param x 		The x position in the map
 * @param y 		The y position in the map
 */
void	ft_check_exit(t_game *game, int x, int y)
{
	if (game->n_c == 0)
	{
		game->map[x][y] = '0';
		game->n_moves++;
		game->n_e--;
		game->pos_ply_x = x;
		game->pos_ply_y = y;
	}
	else
		ft_putendl_fd("There are some collectable objects in the map", 1);
}

/**
 * @brief 			This function
 * 
 * @param game 		A pointer to the main structure of the program
 * @param x 		The x position in the map
 * @param y 		The y position in the map
 */
void	ft_check_coll(t_game *game, int x, int y)
{
	if (game->map[x][y] == 'C')
			game->n_c--;
		game->map[game->pos_ply_x][game->pos_ply_y] = '0';
		game->pos_ply_x = x;
		game->pos_ply_y = y;
		game->map[game->next_pos_ply_x][game->next_pos_ply_y] = 'P';
		game->n_moves++;
}

/**
 * @brief 			This function does the player's movement in the game's
 * 					window
 * 
 * @param game 		A pointer to the main structure of the program
 */
void	ft_make_move(t_game *game)
{
	int	moves;
	int	x;
	int	y;

	moves = game->n_moves;
	x = game->next_pos_ply_x;
	y = game->next_pos_ply_y;
	if (game->map[x][y] == '0' || game->map[x][y] == 'C')
		ft_check_coll(game, x, y);
	else if (game->map[x][y] == 'E')
		ft_check_exit(game, x, y);
	ft_draw_map(game);
	if (game->n_moves > moves)
		ft_print_score(game);
	ft_game_win(game);
}

/**
 * @brief 			This function checks if the game has finished (if there
 * 					are not more collectable objects in the map) and shows a
 * 					message
 * 
 * @param game		A pointer to the main structure of the program 
 */
void	ft_game_win(t_game *game)
{
	if (game->n_e == 0)
	{
		ft_putendl_fd("Congratulations, you win!", 1);
		ft_putstr_fd("Number of moves: ", 1);
		ft_putnbr_fd(game->n_moves, 1);
		ft_putendl_fd("", 1);
		exit(0);
	}
}

/**
 * @brief 			This function catches the key that has been pressed to
 * 					make the player's movement in the game's window
 * 
 * @param keydata 	A structure with information about the key that has been
 * 					pressed
 * @param param 	A pointer to the main structure of the program
 */
void	ft_player_mov(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	game->next_pos_ply_x = game->pos_ply_x;
	game->next_pos_ply_y = game->pos_ply_y;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		game->next_pos_ply_x--;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		game->next_pos_ply_y--;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		game->next_pos_ply_y++;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		game->next_pos_ply_x++;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		exit(0);
	ft_make_move(game);
}
