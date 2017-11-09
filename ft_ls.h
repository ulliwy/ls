/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:13:38 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/09 15:31:09 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft/libft.h"

typedef struct	s_opt
{
	int			l;
	int			R;
	int			a;
	int			r;
	int			t;
	int			cur_dir;
}				t_opt;

#endif
