/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_user_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/20 11:42:01 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_username(struct stat f_stat, int len)
{
	struct passwd	*pswd;

	pswd = getpwuid(f_stat.st_uid);
	if (pswd->pw_name)
		ft_printf(" %-*s ", len, pswd->pw_name);
	else
		ft_printf(" %-*ld ", len, f_stat.st_uid);
}

void	print_groupname(struct stat f_stat, int len)
{
	struct group *grp;

	grp = getgrgid(f_stat.st_gid);
	if (grp->gr_name)
		ft_printf(" %-*s", len, grp->gr_name);
	else
		ft_printf(" %-*ld", len, f_stat.st_gid);
}

void	print_time(struct stat f_stat, int atime)
{
	char	*tstmp;
	time_t	t;

	if (atime)
		tstmp = ctime(&f_stat.st_atime);
	else
		tstmp = ctime(&f_stat.st_mtime);
	ft_putchar(' ');
	write(1, tstmp + 4, 4);
	write(1, tstmp + 8, 3);
	t = time(NULL);
	if ((f_stat.st_mtime - t > 15770000) || (f_stat.st_mtime - t < -15770000))
		write(1, tstmp + 19, 5);
	else
		write(1, tstmp + 11, 5);
}
