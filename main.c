/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/17 14:44:26 by iprokofy         ###   ########.fr       */
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

// void	long_output(t_dir fls, t_opt opts, char *dir_name)
// {

// }

void	regular_output(t_dir fls, int hidden)
{
	int i;
	int j;

	i = 0;
	hidden = 0;
	while (i < fls.cur)
	{
		j = i;
		if (i)
			ft_printf("\n");
		while (j < fls.cur)
		{
			//printf("j: %d\n", j);
			ft_printf("%-*.15s", COL_SIZE, fls.files[j]);
			j = j + 1 + N_COL;
		}
		i = i + N_COL;
	}

	// while (i < N_COL)
	// {
	// 	j = i;
	// 	if (i)
	// 		ft_printf("\n");
	// 	while (j < fls.cur)
	// 	{
	// 		//printf("j: %d\n", j);
	// 		ft_printf("%-*.15s", COL_SIZE, fls.files[j]);
	// 		j = j + N_COL;
	// 	}
	// 	i++;
	// }
}


int		ls_files(t_dir fls, t_opt opts, char *dir_name, int need_dir_name)
{
	if (need_dir_name)
		ft_printf("%s:\n", dir_name);
	if (!opts.l)
		regular_output(fls, opts.a);
		//long_output(t_dir fls, opts, char *dir_name);		
	ft_printf("\n");
	return (1);
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

char	*create_path(char *outer, char *inner)
{
	char	*name;
	char	*ret;

	name = (char*)malloc(ft_strlen(outer) + ft_strlen(inner) + 2);
	ret = name;
	while (*outer)
		*name++ = *outer++;
	*name = 47;
	name++;
	while (*inner)
		*name++ = *inner++;
	*name = '\0';
	return (ret);
}

void	ft_ls(char *d, t_opt opts, int need_dir_name)
{
	DIR 			*dir;
	struct dirent 	*dp;
	t_dir 			items;
	struct stat		s_file_stat;
	int 			i;
	char			*name;

	dir_init(&items);
	if (!(dir = opendir(d)))
	{
		ft_putstr("ft_ls: ");
		perror(d);
		return ;
	}
	while ((dp = readdir(dir)))
	{
		stat(dp->d_name, &s_file_stat);
		append(&items, dp->d_name);
	}
	sort_files(items.files, items.cur, opts.r);
	ls_files(items, opts, d, need_dir_name);
	i = 0;
	if (opts.R)
	{
		while (i < items.cur)
		{

			name = create_path(d, items.files[i]);
			if (!stat(name, &s_file_stat) && S_ISDIR(s_file_stat.st_mode)
					&& ft_strcmp(items.files[i], ".")
					&& ft_strcmp(items.files[i], ".."))
			{
				ft_printf("\n");
				ft_ls(name, opts, 1);
			}
				
			free(name);
			i++;
		}
	}
	free(items.files);
}

int 	pre_ls(t_dir arr, t_opt opts, int need_dir_name)
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
	if (fls.cur > 0)
		ls_files(fls, opts, 0, 0);
	i = 0;
	while (i < dir.cur)
	{
		if (i)
			ft_printf("\n");
		ft_ls(dir.files[i], opts, need_dir_name);
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
	
	sort_files(args.files, args.cur, opts.r);
	pre_ls(args, opts, args.cur > 1 ? 1 : 0);
	free(args.files);
	return (0);
}
