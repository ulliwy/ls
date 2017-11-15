/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/15 15:54:20 by iprokofy         ###   ########.fr       */
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

void	print_parameters(t_opt opts)
{
	printf("options: \n");
	printf("   R: %d\n", opts.R);
	printf("   a: %d\n", opts.a);
	printf("   l: %d\n", opts.l);
	printf("   r: %d\n", opts.r);
	printf("   t: %d\n", opts.t);
}

void	print_names(t_darr *arr)
{
	int i = 0;

	if (!arr)
		return ;

	printf("cur: %d\n", arr->cur);
	while (i < arr->cur)
	{
		printf("%s\n", arr->names[i]);
		i++;
	}
}

char	**pcpy(char **dst, char **src, size_t n)
{
	while (n > 0)
	{
		*dst = *src;
		dst++;
		src++;
		n--;
	}
	return (dst);
}

void	append(t_darr *arr, char *name)
{
	char	**new_arr;

	if (arr->cur == arr->max)
	{
		new_arr = (char **)malloc((sizeof(char *)) * arr->max * 2);
		pcpy(new_arr, arr->names, arr->max);
		free(arr->names);
		arr->names = new_arr;
		arr->max = arr->max * 2;
	}  
	arr->names[arr->cur] = name;
	arr->cur++;
}

void	names_init(t_darr *arr)
{
	arr->cur = 0;
	arr->max = 5;
	arr->names = (char **)malloc((sizeof(char *)) * arr->max);
}

void	ls_files(t_darr fls)
{
	int i;

	i = 0;
	while (i < fls.cur)
	{
		printf("%d: %s\n", i, fls.names[i]);
		i++;
	}
}

void	ft_ls(char *name)
{
	printf("%s:\n", name);
}

int 	pre_ls(t_darr arr, t_opt opts)
{
	int			i;
	struct stat	s_file_stat;
	t_darr		dir;
	t_darr		fls;

	i = 0;
	names_init(&dir);
	names_init(&fls);
	while (i < arr.cur)
	{
		if (stat(arr.names[i], &s_file_stat) < 0)
		{
			ft_putstr("ft_ls: ");
			perror(arr.names[i]);
		}
		else if (S_ISDIR(s_file_stat.st_mode))
			append(&dir, arr.names[i]);
		else
			append(&fls, arr.names[i]);
		i++;
	}
	ls_files(fls);
	free(fls.names);
	i = 0;
	while (i < dir.cur)
	{
		ft_putstr("\n");
		ft_ls(dir.names[i]);
		i++;
	}
	print_parameters(opts);

	free(dir.names);
	return (0);
}

int		main(int argc, char **argv)
{
	t_darr	names;
	t_opt	opts;
	int		i;
	int 	is_op;
	int 	parsed_opt;

	names_init(&names);
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
			append(&names, argv[i]);
		}
		i++;
	}
	if (!names.cur || opts.cur_dir)
		append(&names, ".");
	sort_names(names.names, names.cur);

	pre_ls(names, opts);
	free(names.names);
	return (0);
}
