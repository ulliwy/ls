/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/09 15:31:02 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	opt_init(t_opt *opts)
{
	opts->l = 0;
	opts->R = 0;
	opts->a = 0;
	opts->r = 0;
	opts->t = 0;
	opts->cur_dir = 0;
}

void	put_opt_error(char opt)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(opt);
	ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
}

int		parse_opts(char *op, t_opt *opts, int *is_op)
{
	op++;
	if (*op == '-' && !(*(op + 1)))
	{
		is_op = 0;
		opts->cur_dir = 1;
		return (1);
	}
	while (*op)
	{
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
		else
		{
			put_opt_error(*op);
			return (0);
		}
		op++;
	}
	return (1);
}

void	print_parameters(t_opt opts, t_list *opendirs)
{
	printf("options: \n");
	printf("   R: %d\n", opts.R);
	printf("   a: %d\n", opts.a);
	printf("   l: %d\n", opts.l);
	printf("   r: %d\n", opts.r);
	printf("   t: %d\n", opts.t);
	while (opendirs)
	{
		
	}
}

int		main(int argc, char **argv)
{
	t_list	*opendirs;
	t_opt	opts;
	int		i;
	int 	is_op;
	int 	parsed_opt;

	opendirs = NULL;
	i = 1;
	is_op = 1;
	parsed_opt = 1;
	opt_init(&opts);
	while (i < argc && parsed_opt)
	{
		if (argv[i][0] == '-' && argv[i][1] && is_op)
			parsed_opt = parse_opts(argv[i], &opts, &is_op);
		else
		{
			is_op = 0;
			ft_lstadd(&opendirs, ft_lstnew(argv[i], sizeof(argv[i])));
		}
		i++;
	}
	if (!opendirs || opts.cur_dir)
		ft_lstadd(&opendirs, ft_lstnew(".", sizeof(".")));
	print_parameters(opts, opendirs);
	//process printing
	return (0);
}
