/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:13:38 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/15 15:54:34 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

typedef struct	s_opt
{
	int			l;
	int			R;
	int			a;
	int			r;
	int			t;
	int			cur_dir;
}				t_opt;

typedef struct	s_dir
{
	char		*name;
	struct stat	s_stat;
}				t_dir;

typedef struct 	s_darr
{
	int			cur;
	int			max;
	char		**names;
}				t_darr;

int		sort_names(char **arr, int n);

#endif
