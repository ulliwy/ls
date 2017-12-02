/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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
	opts->sort = 1;
	opts->cur_dir = 0;
}

// void	print_names(t_dir *arr)
// {
// 	int i = 0;

// 	if (!arr)
// 		return ;

// 	printf("cur: %d\n", arr->cur);
// 	while (i < arr->cur)
// 	{
// 		printf("%ld : %s\n", arr->files[i].mtime, arr->files[i].name);
// 		i++;
// 	}
// }

int	put_opt_error(char opt)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(opt);
	ft_putstr("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
	return (0);
}

// int 	set_options(char op, t_opt *opts)
// {
// 	if (*op == 'l')
// 		opts->l = 1;
// 	else if (*op == 'R')
// 		opts->R = 1;
// 	else if (*op == 'a')
// 		opts->a = 1;
// 	else if (*op == 'r')
// 		opts->r = 1;
// 	else if (*op == 't')
// 		opts->t = 1;
// 	else if (*op == '1')
// 		opts->one = 1;
// 	else if (*op == 'f')
// 	{
// 		opts->a = 1;
// 		opts->sort = 0;
// 	}
// 	else
// 		return (put_opt_error(*op));
// }

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
		else if (*op == 'g')
		{
			opts->g = 1;
			opts->l = 1;
		}
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

int 	parse_args(char **argv, t_opt *opts, t_dir *args, int argc)
{
	int 	i;
	int 	parsed_opt;
	int 	is_op;

	i = 1;
	parsed_opt = 1;
	is_op = 1;
	while (i < argc && parsed_opt)
	{
		if (argv[i][0] == '-' && argv[i][1] && is_op)
			parsed_opt = parse_opts(argv[i] + 1, opts, &is_op);
		else
		{
			is_op = 0;
			opts->cur_dir = 0;
			append_names(args, argv[i]);
		}
		i++;
	}
	return (parsed_opt);
}

int		main(int argc, char **argv)
{
	t_dir	args;
	t_opt	opts;
	int 	parsed_opt;
	int 	ret;

	dir_init(&args);
	opt_init(&opts);
	ret = 0;
	parsed_opt = parse_args(argv, &opts, &args, argc);
	if (!args.cur || opts.cur_dir)
		append_names(&args, ".");
	if (opts.sort)
		sort_files(args.files, args.cur, 0);
	if (parsed_opt)
		pre_ls(args, opts, args.cur > 1 ? 1 : 0);
	free_filenames(&args);
	free(args.files);
	return (!parsed_opt);
}
