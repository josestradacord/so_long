/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:46:35 by joestrad          #+#    #+#             */
/*   Updated: 2023/03/29 18:21:42 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

/**
 * @brief 	This function checks if the program has leaks or not
 * 
 */
void	ft_leaks(void)
{
	system("leaks -q so_long_bonus");
}

/**
 * @brief 			This function checks if the name of the map that is given
 * 					in the command line is correct or not (its extension must
 * 					be .ber)
 * 
 * @param str 		The name of the map, including its extension
 * @param ext 		The extension to check
 * @return int 		The return value, 1 if it is correct, 0 otherwise
 */
int	ft_check_name(char *str, char *ext)
{
	int	len_n;
	int	len_e;
	int	index1;
	int	index2;

	len_n = ft_strlen(str);
	len_e = ft_strlen(ext);
	index1 = len_n - len_e;
	index2 = 0;
	while (index1 <= len_n)
	{
		if (str[index1++] != ext[index2++])
			return (0);
	}
	return (1);
}

/**
 * @brief 			This function initializes the main structure of the
 * 					program, that manages all the game options and features
 * 
 * @param str 		The name of the map, which is given from the command line
 * @param game 		A pointer to the main structure of the program
 * @return t_game* 	The return value, a pointer to the main structure of the
 * 					program
 */
t_game	*ft_init_game(char *str, t_game *game)
{
	game->sprite_w = SPRITE_SZ;
	game->sprite_h = SPRITE_SZ;
	game->map_w = 0;
	game->map_h = 0;
	game->map_nr = 0;
	game->map_nc = 0;
	game->n_c = 0;
	game->n_e = 0;
	game->n_p = 0;
	game->n_en = 0;
	game->pos_ply_x = 0;
	game->pos_ply_y = 0;
	game->ene_x = 0;
	game->ene_y = 0;
	game->n_moves = 0;
	game->mlx = NULL;
	game->wall_i = NULL;
	game->ground_i = NULL;
	game->player_i = NULL;
	game->exit_i = NULL;
	game->score_i = NULL;
	game->enemy_i0 = NULL;
	game->enemy_i1 = NULL;
	game->map_name = ft_strdup(str);
	return (game);
}

/**
 * @brief			Main function of the program 
 * 
 * @param argc 		The number of arguments in the command line, including
 * 					the name of the program
 * @param argv 		An array of each of the arguments on the command line
 * @return int 		The return value of the function
 */
int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_putstr_fd("ERROR\nUsage: ./so_long_bonus <maps/map.ber>\n", 2);
		exit(1);
	}
	else if (!ft_check_name(argv[1], ".ber"))
	{
		ft_putstr_fd("ERROR\nMap name is invalid\n", 2);
		exit(1);
	}
	game = (t_game *) malloc(sizeof(t_game));
	ft_init_game(argv[1], game);
	ft_map_valid(game);
	ft_start_game(game);
	ft_free(game);
	return (0);
}
