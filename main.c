/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/14 16:42:21 by iprokofy         ###   ########.fr       */
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

void	append(t_darr *arr, char *name)
{
	//char	**new_arr;

	//printf("%p\n", new_arr);
	char **new_arr = malloc(5);
	free(new_arr);
	printf("%s\n", name);
	if (arr->cur >= arr->max)
	{
		printf("this %d\n", arr->max);
		
		//
		//new_arr = (char *)malloc(sizeof(int));
		//printf("%s\n", arr->names[0]);
		//new = ft_memcpy(new, arr->names, arr->max);
		//printf("%s\n", arr->names[0]);
		return ;
	}  
	arr->names[arr->cur] = name;
		//printf("%s\n", arr->names[arr->cur]);
	arr->cur++;

	//printf("%d\n", arr->cur);
	//printf("%d\n", arr->max);
}

void	names_init(t_darr *arr)
{
	arr->cur = 0;
	arr->max = 5;
	arr->names = (char **)malloc(arr->max);
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
	//print_parameters(opts);
	//print_names(&names);
	//process printing
	return (0);
}
