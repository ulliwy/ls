/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:13:38 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/17 15:51:45 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//1lRartfgu

#ifndef FT_LS_H
# define FT_LS_H

#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/acl.h>

# define MAX_LEN 5
# define N_COL 4
# define COL_SIZE 16

typedef struct	s_opt
{
	int			one;
	int			l;
	int			R;
	int			a;
	int			r;
	int			t;
	int 		g;
	int 		u;
	int			cur_dir;
	int 		sort;
}				t_opt;

typedef struct	s_file
{
	char	*name;
	long	mtime;
}				t_file;

typedef struct	s_merge
{
	int			l;
	int			r;
	int			m;
	int			k;
	int			rev;
}				t_merge;

typedef struct	s_info
{
	int		links;
	int		username;
	int		group;
	int		nbytes;
	int		maj;
	int		min;
}				t_info;

typedef struct 	s_dir
{
	int			cur;
	int 		max;
	int			blk;
	int			is_arg;
	t_file		*files;
	t_info		info;
}				t_dir;

int		sort_files(t_file *arr, int n, int r);
void	sort_dates(t_file *arr, int n, t_opt opts);
void	merge_sort(t_file *arr, int l, int r, int rev);

void 	pre_ls(t_dir arr, t_opt opts, int need_dir_name);
void	ft_ls(char *d, t_opt opts, int need_dir_name);
char	*create_path(char *outer, char *inner);
void	put_file_error(char *d);

void	dir_init(t_dir *arr);
void	append_names(t_dir *arr, char *name);
void	append(t_dir *arr, char *name, struct stat s_file_stat, int atime);
void	free_filenames(t_dir *dir);

int 	ft_numlen(int n);
int 	get_username_length(struct stat f_stat);
int 	get_group_length(struct stat f_stat);
void	update_info(struct stat f_stat, t_dir *arr);

int		ls_files(t_dir fls, t_opt opts, char *dir_name);
void	regular_output(t_dir fls);
void	long_output(t_dir fls, char *dir_name, t_opt opts);

void	print_mode(struct stat f_stat);
void	print_perm(struct stat f_stat);
void	print_username(struct stat f_stat, int len);
void	print_groupname(struct stat f_stat, int len);
void	print_extattr(char *path);
void	print_time(struct stat f_stat, int atime);

#endif
