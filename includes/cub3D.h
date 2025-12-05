/* ************************************************************************** */
/*                                                                          */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:45:04 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/19 16:24:19 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include_libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>

# define PI 3.141593

typedef enum directions
{
	NO,
	SO,
	EA,
	WE
}						t_directions;

typedef enum door_states
{
	CLOSED,
	OPENING,
	OPEN
}						t_door_states;

typedef struct s_door
{
	int					x;
	int					y;
	int					state;
	int					anim_frame;
	double				anim_time;
	struct s_door		*next;
}						t_door;

typedef struct s_ray
{
	float				vector_len;
	float				wall_x;
	int					direction;
	t_door				*door;
}						t_ray;

typedef struct s_texture
{
	int					height;
	int					width;
	int					size_line;
	char				*path;
	void				*img;
	int					*pixels;
}						t_texture;

typedef struct s_door_texture
{
	t_texture			*open;
	t_texture			*closed;
	t_texture			*anim_1;
	t_texture			*anim_2;
	t_texture			*anim_3;
	t_texture			*anim_4;
	t_texture			*anim_5;
}						t_door_texture;

typedef struct s_color
{
	int					red;
	int					green;
	int					blue;
}						t_color;

typedef struct s_data
{
	void				*mlx;
	void				*win;
}						t_data;

typedef struct s_img_buffer
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_img_buffer;

typedef struct s_mapinfo
{
	int					doors_opening;
	int					map_scale;
	int					ms;
	int					width;
	int					height;
	int					tiles_x;
	int					tiles_y;
	float				player_x_mini;
	float				player_y_mini;
	int					player_speed;
	float				player_direction;
	int					key_w;
	int					key_s;
	int					key_a;
	int					key_d;
	int					look_left;
	int					look_right;
	int					mouse_left;
	int					mouse_right;
	char				*floor_color;
	char				*ceiling_color;
	int					floor_color_int;
	int					ceiling_color_int;
	char				**map;
	float				*vector_lens;
	t_door				*doors;
	t_texture			**door_textures;
	t_texture			**lizard_textures;
	t_texture			*north;
	t_texture			*south;
	t_texture			*east;
	t_texture			*west;
	t_ray				*ray_info;
	t_img_buffer		minimap;
	t_img_buffer		frame;
	t_data				*data;
}						t_mapinfo;

// parse.c
char					**parse_map(char *file);
t_mapinfo				*get_mapinfo(char **parsed);
char					check_line(char *line);

// test.c
void					print_tab(char **tab);
void					print_mapinfo(t_mapinfo *info);

// exit.c
void					exit_clean(char *message, t_mapinfo *info,
							char **parsed);
int						exit_clean_null(t_mapinfo *info);
void					free_mapinfo(t_mapinfo *info);
void					free_texture(t_mapinfo *info, t_texture *texture);
void					free_north_and_exit(t_mapinfo *info, char *msg);

// init.c
t_mapinfo				*init_mapinfo(void);
t_data					*init_data(t_mapinfo *info);
void					init_img_buffer(t_mapinfo *info,
							t_img_buffer *img_buffer, int width, int height);

// check_mapinfo.c
void					check_mapinfo(t_mapinfo *info);

// check_map.c
int						count_lines(char *file);
void					check_map(t_mapinfo *info);
int						get_map_width(char **map);
int						get_map_height(char **map);

// check_walls.c
int						check_walls(char **map, t_mapinfo *info);

// keyhooks.c
int						handle_keyup(int keycode, t_mapinfo *info);
int						handle_keydown(int keycode, t_mapinfo *info);
void					hook_handler(t_mapinfo *info);

// minimap.c
void					draw_minimap(t_mapinfo *info, int display);

// move_player.c
int						update(t_mapinfo *info);
void					move_player(t_mapinfo *info, float delta_y,
							float delta_x);

// draw_line.c
void					draw_line(t_mapinfo *info, float angle_diff);
void					draw_until_wall(t_mapinfo *info, float angle_diff,
							int index);
void					draw_vectors(t_mapinfo *info, int width, float fov);

// loop.c
void					loop(t_mapinfo *info);

// my_pixel_put.c

static inline void	my_pixel_put(t_img_buffer *img_buffer, int x, int color,
		int line_position)
{
	char	*dst;

	dst = img_buffer->addr + (line_position + x * (img_buffer->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}
// vector_len.c
float					get_vector_len(float x1, float y1, float x2, float y2);

// draw_frame.c
void					draw_frame(t_mapinfo *info);

// open_img.c
void					load_img(t_mapinfo *info);
t_texture				*load_texture(t_mapinfo *info, t_texture *texture,
							char *path);

// get_pixel.c
int						get_pixel_2(t_mapinfo *info, int y, int x, int len);

static inline t_texture	*find_texture(t_mapinfo *info, int x)
{
	t_texture	*texture;

	if (info->ray_info[x].door != NULL)
		texture = info->door_textures[info->ray_info[x].door->anim_frame];
	else if (info->ray_info[x].direction == NO)
		texture = info->north;
	else if (info->ray_info[x].direction == SO)
		texture = info->south;
	else if (info->ray_info[x].direction == EA)
		texture = info->east;
	else
		texture = info->west;
	return (texture);
}

static inline int	get_pixel(t_mapinfo *info, int y, int x, int len)
{
	int			x1;
	int			y1;
	int			draw_start;
	t_texture	*texture;

	texture = find_texture(info, x);
	draw_start = (info->height - len) / 2;
	x1 = info->ray_info[x].wall_x * texture->width;
	if (x1 < 0)
		x1 = 0;
	else if (x1 >= texture->width)
		x1 = texture->width - 1;
	if (len == 0)
		len = 1;
	y1 = ((y - draw_start) * texture->height) / len;
	if (y1 >= texture->height)
		y1 = texture->height - 1;
	return (texture->pixels[y1 * texture->size_line + x1]);
}

// free.c
void					ft_free_int_tab(int **tab);
void					free_door(t_door *door);
void					free_extra_textures(t_mapinfo *info);
void					free_door_textures(t_mapinfo *info);

// doors.c
t_door					*new_door(int x, int y);
t_door					*get_door_at(t_door *doors, int x, int y);
void					add_door(t_mapinfo *info, int x, int y);

// doors2.c
void					open_door(t_mapinfo *info);
void					animate_door(t_mapinfo *info);

// open_textures.c
void					load_extra_textures(t_mapinfo *info);

// animate_wall.c
void					animate_wall(t_mapinfo *info);

#endif
