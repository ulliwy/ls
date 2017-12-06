/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/20 11:42:01 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	dir_init(t_dir *arr)
{
	arr->cur = 0;
	arr->max = MAX_LEN;
	arr->blk = 0;
	arr->is_arg = 0;
	arr->files = (t_file *)malloc((sizeof(t_file)) * arr->max);
	(arr->info).links = 0;
	(arr->info).username = 0;
	(arr->info).group = 0;
	(arr->info).nbytes = 0;
	(arr->info).maj = 0;
	(arr->info).min = 0;
}

t_file	*pcpy(t_file *dst, t_file *src, int n)
{
	t_file	*ret;

	ret = dst;
	while (n > 0)
	{
		*dst = *src;
		dst++;
		src++;
		n--;
	}
	return (ret);
}

void	append_names(t_dir *arr, char *name)
{
	t_file	*new_arr;

	if (arr->cur == arr->max)
	{
		new_arr = (t_file *)malloc((sizeof(t_file)) * arr->max * 2);
		new_arr = pcpy(new_arr, arr->files, arr->max);
		free(arr->files);
		arr->files = new_arr;
		arr->max = arr->max * 2;
	}
	arr->files[arr->cur].name = ft_strdup(name);
	arr->cur++;
}

void	append(t_dir *arr, char *name, struct stat s_file_stat, t_opt opts)
{
	t_file	*new_arr;

	if (!(getpwuid(s_file_stat.st_uid)) && opts.l)
		return ;
	if (arr->cur == arr->max)
	{
		new_arr = (t_file *)malloc((sizeof(t_file)) * arr->max * 2);
		new_arr = pcpy(new_arr, arr->files, arr->max);
		free(arr->files);
		arr->files = new_arr;
		arr->max = arr->max * 2;
	}
	arr->files[arr->cur].name = ft_strdup(name);
	if (opts.u)
		arr->files[arr->cur].t = s_file_stat.st_atimespec;
	else
		arr->files[arr->cur].t = s_file_stat.st_mtimespec;
	arr->cur++;
	update_info(s_file_stat, arr);
}

void	free_filenames(t_dir *dir)
{
	int i;

	i = 0;
	while (i < dir->cur)
	{
		free((dir->files[i]).name);
		i++;
	}
}
