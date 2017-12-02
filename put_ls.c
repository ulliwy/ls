/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/20 11:42:01 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_link(char *name)
{
	char			*linkname;

	linkname = (char *)malloc(1000);
	ft_bzero(linkname, 1000);
	readlink(name, linkname, 1000);
	ft_printf(" -> %s", linkname);
	free(linkname);
}

void	print_dev_info(t_dir fls, struct stat s_file_stat, int i, char *name)
{
	int 			maj;
	int 			min;
	int 			nbytes;
	int 			len;

	ft_printf(" %*d", ft_numlen(fls.info.links), s_file_stat.st_nlink);
	print_username(s_file_stat, fls.info.username);
	print_groupname(s_file_stat, fls.info.group);
	maj = ft_numlen(fls.info.maj);
	min = ft_numlen(fls.info.min);
	nbytes = ft_numlen(fls.info.nbytes);
	if (fls.info.maj + fls.info.min)
		len = maj + min + 2 > nbytes ? maj + min : nbytes;
	else
		len = nbytes;
	if (S_ISCHR(s_file_stat.st_mode) || S_ISBLK(s_file_stat.st_mode))
		ft_printf("  %*d, %*d", len - min, major(s_file_stat.st_rdev), min,
			minor(s_file_stat.st_rdev));
	else
		ft_printf("  %*d", len + (fls.info.maj + fls.info.min ? 2 : 0),
			s_file_stat.st_size);
	print_time(s_file_stat);
	ft_printf(" %s", fls.files[i].name);
	if (S_ISLNK(s_file_stat.st_mode))
		print_link(name);
}

void	long_output(t_dir fls, char *dir_name)
{
	char			*name;
	int 			i;
	struct stat		s_file_stat;

	i = 0;
	if (fls.cur > 0 && !(fls.is_arg))
		ft_printf("total %d\n", fls.blk);
	while (i < fls.cur)
	{
		if (dir_name)
			name = create_path(dir_name, fls.files[i].name);
		else
			name = fls.files[i].name;
		if (lstat(name, &s_file_stat) < 0)
			return (put_file_error(fls.files[i].name));
		print_mode(s_file_stat);
		print_perm(s_file_stat);
		print_extattr(name);
		print_dev_info(fls, s_file_stat, i, name);
		if (dir_name)
			free(name);
		i++;
		ft_putchar('\n');
	}	
}

void	regular_output(t_dir fls)
{
	int i;

	i = 0;
	while (i < fls.cur)
	{
		ft_printf("%s\n", fls.files[i].name);
		i++;
	}
}

int		ls_files(t_dir fls, t_opt opts, char *dir_name)
{
	if (!opts.l)
		regular_output(fls);
	else
		long_output(fls, dir_name);	
	return (1);
}
