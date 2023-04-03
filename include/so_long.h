/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:47:16 by joestrad          #+#    #+#             */
/*   Updated: 2023/03/27 17:22:34 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"

// Constants defines
# define SPRITE_SZ 	64
# define FILE_ERROR	11
# define ROW_ERROR	12
# define COL_ERROR	13
# define BOR_ERROR	14
# define PLY_ERROR	15
# define CLL_ERROR	16
# define EXT_ERROR	17
# define INV_ERROR	18
# define PTH_ERROR	19

// Data type to manage all the game options
typedef struct s_game
{
	int			sprite_w;
	int			sprite_h;
	int			map_w;
	int			map_h;
	int			map_nr;
	int			map_nc;
	int			n_c;
	int			n_e;
	int			n_p;
	int			pos_ply_x;
	int			pos_ply_y;
	int			next_pos_ply_x;
	int			next_pos_ply_y;
	int			n_moves;
	char		**map;
	char		**map_cp;
	char		*map_name;
	mlx_t		*mlx;
	mlx_image_t	*wall_i;
	mlx_image_t	*ground_i;
	mlx_image_t	*player_i;
	mlx_image_t	*exit_i;
	mlx_image_t	*collect_i;
}	t_game;

// Data type to manage the textures
typedef struct s_textures
{
	mlx_texture_t	*wall;
	mlx_texture_t	*ground;
	mlx_texture_t	*player;
	mlx_texture_t	*exit;
	mlx_texture_t	*collect;
}	t_textures;

// Manage maps
void	ft_map_valid(t_game *game);
void	ft_read_map(t_game *game, int fd);
int		ft_check_name(char *str, char *ext);
char	*ft_join_map(char *old_map, char *line);

// Manage map's check
void	ft_check_rows(t_game *game);
void	ft_check_cols(t_game *game);
int		ft_check_border(t_game *game);
void	ft_check_chars(t_game *game);
void	ft_check_elems(t_game *game);

// Manage map's path
void	ft_fill(t_game *game, int p_r, int p_c);
void	ft_flood_fill(t_game *game, int p_r, int p_c);
void	ft_locate_player(t_game *game, int *p_r, int *p_c);
void	ft_check_path(t_game *game);

// Manage players moves
void	ft_player_mov(mlx_key_data_t keydata, void *param);
void	ft_make_move(t_game *game);
void	ft_check_exit(t_game *game, int x, int y);
void	ft_check_coll(t_game *game, int x, int y);

// Manage errors and frees
void	ft_error(int error, t_game *game);
void	ft_free(t_game *game);

// Windows game functions
void	ft_start_game(t_game *game);
void	ft_draw_map(t_game *game);
void	ft_create_window(t_game *game);
void	ft_game_win(t_game *game);

#endif