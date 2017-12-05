/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/20 11:42:01 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_username_length(struct stat f_stat)
{
	struct passwd *pswd;

	pswd = getpwuid(f_stat.st_uid);
	if (pswd->pw_name)
		return (ft_strlen(pswd->pw_name));
	else
		return (ft_numlen(f_stat.st_uid));
}

int		get_group_length(struct stat f_stat)
{
	struct group *grp;

	grp = getgrgid(f_stat.st_gid);
	if (grp->gr_name)
		return (ft_strlen(grp->gr_name));
	else
		return (ft_numlen(f_stat.st_gid));
}

int		ft_numlen(int n)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	dev_info(struct stat f_stat, t_dir *arr)
{
	int		maj;
	int		min;

	maj = major(f_stat.st_rdev);
	min = minor(f_stat.st_rdev);
	if (maj > (arr->info).maj)
		(arr->info).maj = maj;
	if (min > (arr->info).min)
		(arr->info).min = min;
}

void	update_info(struct stat f_stat, t_dir *arr)
{
	int		u_len;
	int		g_len;

	if (f_stat.st_nlink > (arr->info).links)
		(arr->info).links = f_stat.st_nlink;
	u_len = get_username_length(f_stat);
	if (u_len > (arr->info).username)
		(arr->info).username = u_len;
	g_len = get_group_length(f_stat);
	if (g_len > (arr->info).group)
		(arr->info).group = g_len;
	if (f_stat.st_size > (arr->info).nbytes)
		(arr->info).nbytes = f_stat.st_size;
	if (S_ISCHR(f_stat.st_mode) || S_ISBLK(f_stat.st_mode))
		dev_info(f_stat, arr);
	if (f_stat.st_size > (arr->info).nbytes)
		(arr->info).nbytes = f_stat.st_size;
	arr->blk += f_stat.st_blocks;
}
