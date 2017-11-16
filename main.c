/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/16 14:14:35 by iprokofy         ###   ########.fr       */
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

void	print_names(t_dir *arr)
{
	int i = 0;

	if (!arr)
		return ;

	printf("cur: %d\n", arr->cur);
	while (i < arr->cur)
	{
		printf("%s\n", (arr->files[i]).name);
		i++;
	}
}

void	ls_files(t_dir fls)
{
	int i;

	i = 0;
	while (i < fls.cur)
	{
		printf("%d: %s\n", i, fls.files[i].name);
		i++;
	}
}

void	ft_ls(char *name)
{
	printf("%s:\n", name);
}



t_file	*pcpy(t_file *dst, t_file *src, size_t n)
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

void	append(t_dir *arr, char *name)
{
	t_file	*new_arr;

	if (arr->cur == arr->max)
	{
		new_arr = (t_file *)malloc((sizeof(t_file)) * arr->max * 2);
		pcpy(new_arr, arr->files, arr->max);
		free(arr->files);
		arr->files = new_arr;
		arr->max = arr->max * 2;
	}  
	(arr->files[arr->cur]).name = name;
	arr->cur++;
}

void	append_stat(t_dir *arr, char *name, struct stat s_file_stat)
{
	t_file	*new_arr;

	if (arr->cur == arr->max)
	{
		new_arr = (t_file *)malloc((sizeof(t_file)) * arr->max * 2);
		pcpy(new_arr, arr->files, arr->max);
		free(arr->files);
		arr->files = new_arr;
		arr->max = arr->max * 2;
	}  
	(arr->files[arr->cur]).name = name;
	(arr->files[arr->cur]).s_stat = s_file_stat;
	arr->cur++;
}

void	dir_init(t_dir *arr)
{
	arr->cur = 0;
	arr->max = MAX_LEN;
	arr->files = (t_file *)malloc((sizeof(t_file)) * arr->max);
}

int 	pre_ls(t_dir arr, t_opt opts)
{
	int			i;
	struct stat	s_file_stat;
	t_dir		fls;
	t_dir		dir;
	
	i = 0;
	dir_init(&fls);
	dir_init(&dir);
	while (i < arr.cur)
	{
		if (stat((arr.files[i]).name, &s_file_stat) < 0)
		{
			ft_putstr("ft_ls: ");
			perror((arr.files[i]).name);
		}
		else if (S_ISDIR(s_file_stat.st_mode))
			append_stat(&dir, (arr.files[i]).name, s_file_stat);
		else
			append_stat(&fls, (arr.files[i]).name, s_file_stat);
		i++;
	}
	//ls_files(fls);
	free(fls.files);
	i = 0;
	ls_files(dir);
	print_parameters(opts);

	free(dir.files);
	return (0);
}

int		main(int argc, char **argv)
{
	t_dir	args;
	t_opt	opts;
	int		i;
	int 	is_op;
	int 	parsed_opt;

	dir_init(&args);
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
			append(&args, argv[i]);
		}
		i++;
	}
	if (!args.cur || opts.cur_dir)
		append(&args, ".");
	
	sort_files(args.files, args.cur);
	//print_names(&args);
	pre_ls(args, opts);
	free(args.files);
	return (0);
}
