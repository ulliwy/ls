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

# define MAX_LEN 5
# define N_COL 4
# define COL_SIZE 16

typedef struct	s_opt
{
	int			o;
	int			l;
	int			R;
	int			a;
	int			r;
	int			t;
	int			cur_dir;
}				t_opt;

typedef struct	s_file
{
	char	*name;
	long	mtime;
}				t_file;

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

int		sort_files(t_file *arr, int n, t_opt opts);
void	sort_dates(t_file *arr, int n, t_opt opts);

#endif
