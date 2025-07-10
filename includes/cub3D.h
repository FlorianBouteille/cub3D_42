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
}		e_directions;

typedef struct s_ray
{
	float				vector_len;
	float				wall_x;
	int 				direction;
}						t_ray;

typedef struct s_texture
{
	int 	height;
	int 	width;
	char 	*path;
	void 	*img;
	int 	*pixels;
}						t_texture;


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

typedef struct s_wallinfo
{
	int					x;
	int					y;
	struct s_wallinfo	*next;
}						t_wallinfo;

typedef struct s_mapinfo
{
	int					map_scale;
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
	char				*floor_color;
	char				*ceiling_color;
	int					floor_color_int;
	int					ceiling_color_int;
	char				**map;
	float				*vector_lens;
	t_texture 			*north;
	t_texture 			*south;
	t_texture 			*east;
	t_texture 			*west;
	t_ray				*ray_info;
	t_img_buffer		minimap;
	t_img_buffer		frame;
	t_data				*data;
	t_wallinfo			*wall;
}						t_mapinfo;

// parse.c
char					**parse_map(char *file);
t_mapinfo				*get_mapinfo(char **parsed);

// test.c
void					print_tab(char **tab);
void					print_mapinfo(t_mapinfo *info);
void					print_wallinfo(t_wallinfo *wall);

// exit.c
void					exit_clean(char *message, t_mapinfo *info,
							char **parsed);
int						exit_clean_null(t_mapinfo *info);
void					free_mapinfo(t_mapinfo *info);

// init.c
t_mapinfo				*init_mapinfo(void);
t_data					*init_data(void);
t_wallinfo				*init_wallinfo(int x, int y, t_wallinfo *head);
void					init_img_buffer(t_mapinfo *info,
							t_img_buffer *img_buffer, int width, int height);

// check_mapinfo.c
void					check_mapinfo(t_mapinfo *info);

// check_map.c
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

// get_wall_info.c
t_wallinfo				*get_wall_info(char **map);

// loop.c
void					loop(t_mapinfo *info);

// my_pixel_put.c
void					my_pixel_put(t_img_buffer *img_buffer, int x, int y,
							int color);

// vector_len.c
float					get_vector_len(float x1, float y1, float x2, float y2);

// draw_frame.c
void					draw_frame(t_mapinfo *info);

// open_img.c
void					load_img(t_mapinfo *info);

// get_pixel.c
int						get_pixel(t_mapinfo *info, int y, int x, int len);

// free.c
void					ft_free_int_tab(int **tab);

#endif
