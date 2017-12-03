/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/20 11:42:01 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	opt_init(t_opt *opts)
{
	opts->l = 0;
	opts->R = 0;
	opts->a = 0;
	opts->r = 0;
	opts->t = 0;
	opts->g = 0;
	opts->u = 0;
	opts->d = 0;
	opts->sort = 1;
	opts->cur_dir = 0;
}

int 	additional_opts(char *op, t_opt *opts)
{
	int 	ret;

	ret = 1;
	if (*op == 'l')
		opts->l = 1;
	else if (*op == 'R')
		opts->R = 1;
	else if (*op == 'a')
		opts->a = 1;
	else if (*op == 'r')
		opts->r = 1;
	else if (*op == 't')
		opts->t = 1;
	else if (*op == 'u')
		opts->u = 1;
	else if (*op == 'd')
		opts->d = 1;
	else if (*op == 'g')
	{
		opts->g = 1;
		opts->l = 1;
	}
	else
		ret = 0;
	return (ret);
}

int		parse_opts(char *op, t_opt *opts, int *is_op)
{
	if (*is_op && *op == '-' && !(*(op + 1)))
	{
		*is_op = 0;
		opts->cur_dir = 1;
		return (1);
	}
	while (*op)
	{
		if (additional_opts(op, opts))
			;
		else if (*op == '1')
		{
			opts->one = 1;
			opts->l = 0;
		}
		else if (*op == 'f')
		{
			opts->a = 1;
			opts->sort = 0;
		}
		else
			return (put_opt_error(*op));
		op++;
	}
	return (1);
}
