/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/20 11:42:01 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_file_error(char *d)
{
	ft_putstr("ls: ");
	perror(d);
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

void	read_dir(char *d, t_dir *items, t_opt opts)
{
	DIR 			*dir;
	char			*name;
	struct stat		s_file_stat;
	struct dirent 	*dp;

	if (!(dir = opendir(d)))
		return (put_file_error(d));
	while ((dp = readdir(dir)))
	{
		name = create_path(d, dp->d_name);
		lstat(name, &s_file_stat);
		if (dp->d_name[0] == '.')
		{
			if (opts.a)
				append(items, dp->d_name, s_file_stat, opts.u);
		}
		else
		 	append(items, dp->d_name, s_file_stat, opts.u);
		free(name);
	}
	if (dir)
		closedir(dir);
}

void	recursive_search(char *d, t_dir *items, t_opt opts)
{
	int 	i;
	char	*name;
	struct stat		s_file_stat;

	i = 0;
	if (opts.R)
		while (i < items->cur)
		{
			name = create_path(d, (items->files[i]).name);
			if (!lstat(name, &s_file_stat) && S_ISDIR(s_file_stat.st_mode)
					&& ft_strcmp(items->files[i].name, ".")
					&& ft_strcmp(items->files[i].name, ".."))
			{
				ft_printf("\n");
				ft_ls(name, opts, 1);
			}
			free(name);
			i++;
		}
}

void	ft_ls(char *d, t_opt opts, int need_dir_name)
{
	t_dir 			items;

	if (need_dir_name)
		ft_printf("%s:\n", d);
	dir_init(&items);
	read_dir(d, &items, opts);
	if (opts.t && opts.sort)
		sort_dates(items.files, items.cur, opts);
	else if (opts.sort)
		sort_files(items.files, items.cur, opts.r);
	ls_files(items, opts, d);
	recursive_search(d, &items, opts);
	free_filenames(&items);
	free(items.files);
}
