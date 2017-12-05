/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/20 11:42:01 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_stat_err(char *name)
{
	ft_putstr("ft_ls: ");
	if (name[0])
		perror(name);
	else
		perror("fts_open");
}

void	create_link(char *path, struct stat	*s_file_stat_link)
{
	char	*linkname;

	linkname = (char *)malloc(1000);
	ft_bzero(linkname, 1000);
	readlink(path, linkname, 1000);
	lstat(linkname, s_file_stat_link);
	free(linkname);
}

void	split_args(t_dir arr, t_dir *fls, t_dir *dir, t_opt opts)
{
	struct stat	s_file_stat;
	struct stat	s_file_stat_link;
	int			i;

	i = 0;
	while (i < arr.cur)
	{
		if (lstat(arr.files[i].name, &s_file_stat) < 0)
			put_stat_err(arr.files[i].name);
		else if (S_ISDIR(s_file_stat.st_mode) && !(opts.d))
			append(dir, arr.files[i].name, s_file_stat, opts.u);
		else if (S_ISLNK(s_file_stat.st_mode) && !(opts.l) && !(opts.d))
		{
			create_link(arr.files[i].name, &s_file_stat_link);
			if (S_ISDIR(s_file_stat_link.st_mode))
				append(dir, arr.files[i].name, s_file_stat_link, opts.u);
			else
				append(fls, arr.files[i].name, s_file_stat, opts.u);
		}
		else
			append(fls, arr.files[i].name, s_file_stat, opts.u);
		i++;
	}
}

void	split_print(t_dir fls, t_opt opts, t_dir dir, int need_dir_name)
{
	int i;

	i = 0;
	if (fls.cur > 0)
	{
		fls.is_arg = 1;
		ls_files(fls, opts, 0);
	}
	if (fls.cur > 0 && dir.cur > 0)
		ft_printf("\n");
	while (i < dir.cur)
	{
		if (i)
			ft_printf("\n");
		ft_ls(dir.files[i].name, opts, need_dir_name);
		i++;
	}
}

void	pre_ls(t_dir arr, t_opt opts, int need_dir_name)
{
	int			i;
	t_dir		fls;
	t_dir		dir;

	i = 0;
	dir_init(&fls);
	dir_init(&dir);
	split_args(arr, &fls, &dir, opts);
	if (opts.t && opts.sort)
	{
		sort_dates(dir.files, dir.cur, opts);
		sort_dates(fls.files, fls.cur, opts);
	}
	else if (opts.sort)
	{
		sort_files(dir.files, dir.cur, opts.r);
		sort_files(fls.files, fls.cur, opts.r);
	}
	split_print(fls, opts, dir, need_dir_name);
	free_filenames(&fls);
	free_filenames(&dir);
	free(fls.files);
	free(dir.files);
}
