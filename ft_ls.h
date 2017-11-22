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
#include <errno.h>
#include <dirent.h>

# define MAX_LEN 5
# define N_COL 4
# define COL_SIZE 16

typedef struct	s_opt
{
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

typedef struct 	s_dir
{
	int			cur;
	int 		max;
	t_file		*files;
}				t_dir;

int		sort_files(t_file *arr, int n, t_opt opts);

#endif
