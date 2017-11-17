/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/16 17:08:25 by iprokofy         ###   ########.fr       */
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

void	dir_init(t_dir *arr)
{
	arr->cur = 0;
	arr->max = MAX_LEN;
	arr->files = (char **)malloc((sizeof(char *)) * arr->max);
}

void	print_names(t_dir *arr)
{
	int i = 0;

	if (!arr)
		return ;

	printf("cur: %d\n", arr->cur);
	while (i < arr->cur)
	{
		printf("%s\n", arr->files[i]);
		i++;
	}
}

void	ls_files(t_dir fls, t_opt opts)
{
	int i;

	opt_init(&opts);
	i = 0;
	while (i < fls.cur)
	{
		printf("%d: %s\n", i, fls.files[i]);
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

// void	append_stat(t_dir *arr, char *name, struct stat s_file_stat)
// {
// 	t_file	*new_arr;

// 	if (arr->cur == arr->max)
// 	{
// 		new_arr = (t_file *)malloc((sizeof(t_file)) * arr->max * 2);
// 		pcpy(new_arr, arr->files, arr->max);
// 		free(arr->files);
// 		arr->files = new_arr;
// 		arr->max = arr->max * 2;
// 	}  
// 	(arr->files[arr->cur]).name = name;
// 	(arr->files[arr->cur]).s_stat = s_file_stat;
// 	arr->cur++;
// }

// char	*ft_addpath(char const *s1, char const *s2)
// {
// 	char			*new;
// 	char			*new_start;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	if (!(new = (char *)malloc(sizeof(char) *
// 		(ft_strlen(s1) + ft_strlen(s2) + 1 + 1))))
// 		return (NULL);
// 	new_start = new;
// 	while (*s1)
// 	{
// 		*new = *s1;
// 		new++;
// 		s1++;
// 	}
// 	*new = '/';
// 	new++;
// 	while (*s2)
// 	{
// 		*new = *s2;
// 		new++;
// 		s2++;
// 	}
// 	*new = '\0';
// 	return (new_start);
// }

void	append(t_dir *arr, char *name)
{
	char	**new_arr;

	if (arr->cur == arr->max)
	{
		new_arr = (char **)malloc((sizeof(char *)) * arr->max * 2);
		pcpy(new_arr, arr->files, arr->max);
		free(arr->files);
		arr->files = new_arr;
		arr->max = arr->max * 2;
	}  
	arr->files[arr->cur] = name;
	arr->cur++;
}

// void	ft_ls(char *d, t_opt opts)
// {
// 	DIR 			*dir;
// 	struct dirent 	*dp;
// 	t_dir 			items;
// 	struct stat		s_file_stat;
// 	int i;
// 	char *new;

// 	dir_init(&items);
// 	if (!(dir = opendir(d)))
// 	{
// 		ft_putstr("ft_ls: ");
// 		perror(d);
// 	}
// 	while ((dp = readdir(dir)))
// 	{
// 		if (ft_strcmp(dp->d_name, ".") && ft_strcmp(dp->d_name, ".."))
// 		{
// 			stat(dp->d_name, &s_file_stat);
// 			append(&items, dp->d_name);
// 		}
// 	}
// 	ls_files(items, opts);
// 	i = 0;
// 	if (opts.R)
// 	{
// 		while (i < items.cur)
// 		{
// 			if (!stat(items.files[i].name, &s_file_stat))
// 				if (S_ISDIR(s_file_stat.st_mode) && ft_strcmp(items.files[i].name, ".")
// 					&& ft_strcmp(items.files[i].name, ".."))
// 				{
// 					new = ft_addpath(dp->d_name, items.files[i]);
// 					//free()
// 					//printf("dir: %s\n", items.files[i].name);
// 					ft_ls(, opts);
// 				}
// 			i++;
// 		}
// 	}
// 	free(items.files);
// }



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
		if (stat(arr.files[i], &s_file_stat) < 0)
		{
			ft_putstr("ft_ls: ");
			perror(arr.files[i]);
		}
		else if (S_ISDIR(s_file_stat.st_mode))
			append(&dir, arr.files[i]);
		else
			append(&fls, arr.files[i]);
		i++;
	}
	ls_files(fls, opts);
	i = 0;
	while (i < dir.cur)
	{
		//ft_ls(dir.files[i], opts);
		i++;
	}
	free(fls.files);
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
	// print_parameters(opts);
	//print_names(&args);
	pre_ls(args, opts);
	free(args.files);
	return (0);
}
