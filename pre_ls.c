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

int 	pre_ls(t_dir arr, t_opt opts, int need_dir_name)
{
	int			i;
	struct stat	s_file_stat;
	struct stat	s_file_stat_link;
	t_dir		fls;
	t_dir		dir;
	char		*linkname;
	
	i = 0;
	dir_init(&fls);
	dir_init(&dir);
	while (i < arr.cur)
	{
		if (lstat(arr.files[i].name, &s_file_stat) < 0)
		{
			ft_putstr("ls: ");
			if (arr.files[i].name[0])
				perror(arr.files[i].name);
			else
				perror("fts_open");
		}
		else if (S_ISDIR(s_file_stat.st_mode))
		{
			append(&dir, arr.files[i].name, s_file_stat.st_mtime);
			update_info(s_file_stat, &dir);
		}
		else if (S_ISLNK(s_file_stat.st_mode) && !(opts.l))
		{
			linkname = (char *)malloc(s_file_stat.st_size + 1);
			readlink(arr.files[i].name, linkname, s_file_stat.st_size + 1);
			lstat(linkname, &s_file_stat_link);
			if (S_ISDIR(s_file_stat_link.st_mode))
			{
				append(&dir, arr.files[i].name, s_file_stat_link.st_mtime);
				update_info(s_file_stat_link, &dir);
			}
			else
			{
				append(&fls, arr.files[i].name, s_file_stat.st_mtime);
				update_info(s_file_stat, &fls);
			}
			free(linkname);
		}
		else
		{
			append(&fls, arr.files[i].name, s_file_stat.st_mtime);
			update_info(s_file_stat, &fls);
		}
		i++;
	}
	//print_names(&dir);
	//printf("-------\n");
	//print_names(&fls);
	if (opts.t)
	{
		sort_dates(dir.files, dir.cur, opts);
		sort_dates(fls.files, fls.cur, opts);
	}
	else
	{
		sort_files(dir.files, dir.cur, opts.r);
		sort_files(fls.files, fls.cur, opts.r);
	}
	if (fls.cur > 0)
	{
		fls.is_arg = 1;
		ls_files(fls, opts, 0);
	}
	i = 0;
	if (fls.cur > 0 && dir.cur > 0)
		ft_printf("\n");
	while (i < dir.cur)
	{
		if (i)
			ft_printf("\n");
		ft_ls(dir.files[i].name, opts, need_dir_name);
		i++;
	}
	// need_dir_name = 1;
	free_filenames(&fls);
	free_filenames(&dir);
	free(fls.files);
	free(dir.files);
	return (0);
}