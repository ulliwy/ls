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
