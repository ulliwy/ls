/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/20 11:42:01 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_mode(struct stat f_stat)
{
	if (S_ISLNK(f_stat.st_mode))
		ft_putchar('l');
	else if (S_ISDIR(f_stat.st_mode))
		ft_putchar('d');
	else if (S_ISREG(f_stat.st_mode))
		ft_putchar('-');
	else if (S_ISFIFO(f_stat.st_mode))
		ft_putchar('p');
	else if (S_ISSOCK(f_stat.st_mode))
		ft_putchar('s');
	else if (S_ISCHR(f_stat.st_mode))
		ft_putchar('c');
	else if (S_ISBLK(f_stat.st_mode))
		ft_putchar('b');	
}

void	print_extattr(char *path)
{
	ssize_t	buflen;
	acl_t 	acl;

	buflen = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (buflen > 0)
		ft_putchar('@');
	else if (acl)
	{
		ft_putchar('+');
		acl_free(acl);
	}
	else
		ft_putchar(' ');
}

void	print_perm_own(struct stat f_stat)
{
	f_stat.st_mode & S_IROTH ? ft_putchar('r') : ft_putchar('-');
	f_stat.st_mode & S_IWOTH ? ft_putchar('w') : ft_putchar('-');
	if (!(f_stat.st_mode & S_IXOTH) && f_stat.st_mode & S_ISVTX)
		ft_putchar('T');
	else if (f_stat.st_mode & S_ISVTX && f_stat.st_mode & S_IXOTH)
		ft_putchar('t');
	else if (f_stat.st_mode & S_IXOTH)
		ft_putchar('x');
	else
		ft_putchar('-');
}

void	print_perm(struct stat f_stat)
{
	f_stat.st_mode & S_IRUSR ? ft_putchar('r') : ft_putchar('-');
	f_stat.st_mode & S_IWUSR ? ft_putchar('w') : ft_putchar('-');
	if (!(f_stat.st_mode & S_IXUSR) && f_stat.st_mode & S_ISUID)
		ft_putchar('S');
	else if (f_stat.st_mode & S_IXUSR && f_stat.st_mode & S_ISUID)
		ft_putchar('s');
	else if (f_stat.st_mode & S_IXUSR)
		ft_putchar('x');
	else
		ft_putchar('-');
	f_stat.st_mode & S_IRGRP ? ft_putchar('r') : ft_putchar('-');
	f_stat.st_mode & S_IWGRP ? ft_putchar('w') : ft_putchar('-');
	if (!(f_stat.st_mode & S_IXGRP) && f_stat.st_mode & S_ISGID)
		ft_putchar('S');
	else if (f_stat.st_mode & S_IXGRP && f_stat.st_mode & S_ISGID)
		ft_putchar('s');
	else if (f_stat.st_mode & S_IXGRP)
		ft_putchar('x');
	else
		ft_putchar('-');
	print_perm_own(f_stat);
}
