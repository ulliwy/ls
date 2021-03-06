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

void	print_time(struct stat f_stat, t_opt opts)
{
	char	*tstmp;
	time_t	t;
	long	cur;

	if (opts.u)
		cur = f_stat.st_atime;
	else if (opts.uu)
		cur = f_stat.st_birthtimespec.tv_sec;
	else
		cur = f_stat.st_mtime;
	tstmp = ctime(&cur);
	ft_putchar(' ');
	write(1, tstmp + 4, 4);
	write(1, tstmp + 8, 3);
	t = time(NULL);
	if ((cur - t > 15770000) || (cur - t < -15770000))
		write(1, tstmp + 19, 5);
	else
		write(1, tstmp + 11, 5);
}

void	put_uinfo(t_dir fls, struct stat s_file_stat, char *name, t_opt opts)
{
	print_mode(s_file_stat);
	print_perm(s_file_stat);
	print_extattr(name);
	ft_printf(" %*d", ft_numlen(fls.info.links), s_file_stat.st_nlink);
	if (!opts.g)
		print_username(s_file_stat, fls.info.username);
	print_groupname(s_file_stat, fls.info.group);
}

void	print_link(char *name)
{
	char			*linkname;

	linkname = (char *)malloc(1000);
	ft_bzero(linkname, 1000);
	readlink(name, linkname, 1000);
	ft_printf(" -> %s", linkname);
	free(linkname);
}
