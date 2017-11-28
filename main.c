/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/20 11:42:01 by iprokofy         ###   ########.fr       */
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

// void	print_parameters(t_opt opts)
// {
// 	printf("options: \n");
// 	printf("   R: %d\n", opts.R);
// 	printf("   a: %d\n", opts.a);
// 	printf("   l: %d\n", opts.l);
// 	printf("   r: %d\n", opts.r);
// 	printf("   t: %d\n", opts.t);
// }

void	dir_init(t_dir *arr)
{
	arr->cur = 0;
	arr->max = MAX_LEN;
	arr->blk = 0;
	arr->files = (t_file *)malloc((sizeof(t_file)) * arr->max);
	(arr->info).links = 0;
	(arr->info).username = 0;
	(arr->info).group = 0;
	(arr->info).nbytes = 0;
	(arr->info).maj = 0;
	(arr->info).min = 0;
}

void	print_names(t_dir *arr)
{
	int i = 0;

	if (!arr)
		return ;

	printf("cur: %d\n", arr->cur);
	while (i < arr->cur)
	{
		printf("%s\n", arr->files[i].name);
		i++;
	}
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

void	print_username(struct stat f_stat, int len)
{
	struct passwd	*pswd;

	pswd = getpwuid(f_stat.st_uid);
	if (pswd->pw_name)
		ft_printf(" %-*s", len, pswd->pw_name);
	else
		ft_printf(" %-*ld", len, f_stat.st_uid);
}

void	print_groupname(struct stat f_stat, int len)
{
	struct group *grp;

	grp = getgrgid(f_stat.st_gid);
	if (grp->gr_name)
		ft_printf("  %-*s", len, grp->gr_name);
	else
		ft_printf("  %-*ld", len, f_stat.st_gid);
}

void	print_extattr(char *path)
{
	ssize_t	buflen;

	buflen = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (buflen <= 0)
		ft_putchar(' ');
	else if (buflen > 0)
		ft_putchar('@');
}

int 	ft_numlen(int n)
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

// void	print_size_dev(struct stat f_stat, t_info info)
// {
// 	// if (S_ISCHR(f_stat.st_mode) || S_ISBLK(f_stat.st_mode))
// 	// 	ft_printf("--");
// 	// else
// 	// 	ft_printf("  %*d", info.)
		

// }

void	print_time(struct stat f_stat)
{
	// Sat Dec  6 23:34:35 2014
	char	*tstmp;
	time_t	t;

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

void	long_output(t_dir fls, char *dir_name)
{
	char			*name;
	int 			i;
	struct stat		s_file_stat;
	int 			len;
	int 			maj;
	int 			min;
	int 			nbytes;
	char			*linkname;
	ssize_t			r;

	i = 0;
	// printf("------------------------\n");
	// printf("links: %d\n", fls.info.links);
	// printf("username: %d\n", fls.info.username);
	// printf("group: %d\n", fls.info.group);
	// printf("nbytes: %d\n", fls.info.nbytes);
	// printf("maj: %d\n", fls.info.maj);
	// printf("min: %d\n", fls.info.min);
	// printf("------------------------\n");
	ft_printf("total %d\n", fls.blk);
	while (i < fls.cur)
	{
		if (dir_name)
			name = create_path(dir_name, fls.files[i].name);
		else
			name = fls.files[i].name;
		if (lstat(name, &s_file_stat) < 0)
		{
			ft_putstr("ft_ls: ");
			perror(fls.files[i].name);
			return ;
		}
		print_mode(s_file_stat);
		print_perm(s_file_stat);
		print_extattr(name);
		ft_printf(" %*d", ft_numlen(fls.info.links), s_file_stat.st_nlink);
		print_username(s_file_stat, fls.info.username);
		print_groupname(s_file_stat, fls.info.group);
		//print_size_dev(s_file_stat, fls.info);
		maj = ft_numlen(fls.info.maj);
		min = ft_numlen(fls.info.min);
		nbytes = ft_numlen(fls.info.nbytes);
		if (fls.info.maj + fls.info.min)
			len = maj + min + 2 > nbytes ? maj + min : nbytes;
		else
			len = nbytes;
		if (S_ISCHR(s_file_stat.st_mode) || S_ISBLK(s_file_stat.st_mode))
			ft_printf("  %*d, %*d", len - min, major(s_file_stat.st_rdev), min, minor(s_file_stat.st_rdev));
		else
			ft_printf("  %*d", len + (fls.info.maj + fls.info.min ? 2 : 0), s_file_stat.st_size);
		print_time(s_file_stat);
		ft_printf(" %s", fls.files[i].name);
		if (S_ISLNK(s_file_stat.st_mode))
		{
			linkname = (char *)malloc(s_file_stat.st_size + 1);
			r = readlink(name, linkname, s_file_stat.st_size + 1);
			ft_printf(" -> %s", linkname);
			free(linkname);
		}
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
	// rows = fls.cur / N_COL + (fls.cur % N_COL ? 1 : 0);
	// while (i < rows)
	// {
	// 	j = 0;
	// 	if (i)
	// 		ft_printf("\n");
	// 	while (j < N_COL && i + j * rows + offset < fls.cur)
	// 	{
	// 		if (fls.files[i + j * rows][0] == '.')
	// 		{
	// 			if (hidden)
	// 				ft_printf("%-*.15s", COL_SIZE, fls.files[i + j * rows + offset]);
	// 			else
	// 				offset++;
	// 		}
	// 		else
	// 			ft_printf("%-*.15s", COL_SIZE, fls.files[i + j * rows + offset]);
	// 		j++;
	// 	}
	// 	i++;
	// }
}


int		ls_files(t_dir fls, t_opt opts, char *dir_name, int need_dir_name)
{
	if (need_dir_name)
		ft_printf("%s:\n", dir_name);
	if (!opts.l)
		regular_output(fls);
	else
		long_output(fls, dir_name);	
	return (1);
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

void	append(t_dir *arr, char *name, long mtime)
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
	arr->files[arr->cur].mtime = mtime;
	arr->cur++;
}

int 	get_username_length(struct stat f_stat)
{
	struct passwd *pswd;

	pswd = getpwuid(f_stat.st_uid);
	if (pswd->pw_name)
		return (ft_strlen(pswd->pw_name));
	else
		return (ft_numlen(f_stat.st_uid));
}

int 	get_group_length(struct stat f_stat)
{
	struct group *grp;

	grp = getgrgid(f_stat.st_gid);
	if (grp->gr_name)
		return (ft_strlen(grp->gr_name));
	else
		return (ft_numlen(f_stat.st_gid));
}

void	update_info(struct stat f_stat, t_dir *arr)
{
	int		u_len;
	int		g_len;
	int 	maj;
	int 	min;

	//printf("nlink: %d\n", f_stat.st_nlink);

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
	{
		maj = major(f_stat.st_rdev);
		min = minor(f_stat.st_rdev);
		if (maj > (arr->info).maj)
			(arr->info).maj = maj;
		if (min > (arr->info).min)
			(arr->info).min = min;
	}
	if (f_stat.st_size > (arr->info).nbytes)
		(arr->info).nbytes = f_stat.st_size;
	arr->blk += f_stat.st_blocks;
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

void	ft_ls(char *d, t_opt opts, int need_dir_name)
{
	DIR 			*dir;
	struct dirent 	*dp;
	t_dir 			items;
	struct stat		s_file_stat;
	int 			i;
	char			*name;

	dir_init(&items);
	if (!(dir = opendir(d)))
	{
		ft_putstr("ft_ls: ");
		perror(d);
		return ;
	}
	//printf("DIR: %s\n", d);
	while ((dp = readdir(dir)))
	{
		//ft_printf("->%d:  %s\n", lstat(dp->d_name, &s_file_stat), dp->d_name);
		name = create_path(d, dp->d_name);
		lstat(name, &s_file_stat);
		if (dp->d_name[0] == '.')
		{
			if (opts.a)
			{
				append(&items, dp->d_name, s_file_stat.st_mtime);
				update_info(s_file_stat, &items);
			}
		}
		else
		{

		 	append(&items, dp->d_name, s_file_stat.st_mtime);
		 	update_info(s_file_stat, &items);
		}
		free(name);
	}
	// printf("------------------------\n");
	// printf("links: %d\n", items.info.links);
	// printf("username: %d\n", items.info.username);
	// printf("group: %d\n", items.info.group);
	// printf("nbytes: %d\n", items.info.nbytes);
	// printf("maj: %d\n", items.info.maj);
	// printf("min: %d\n", items.info.min);
	// printf("------------------------\n");
	// sort_files(items.files, items.cur, opts);
	//print_names(&items);
	sort_files(items.files, items.cur, opts);
	ls_files(items, opts, d, need_dir_name);
	i = 0;
	if (opts.R)
	{
		while (i < items.cur)
		{

			name = create_path(d, items.files[i].name);
			if (!lstat(name, &s_file_stat) && S_ISDIR(s_file_stat.st_mode)
					&& ft_strcmp(items.files[i].name, ".")
					&& ft_strcmp(items.files[i].name, ".."))
			{
				ft_printf("\n");
				ft_ls(name, opts, 1);
			}
			free(name);
			i++;
		}
	}
	if (dir)
		closedir(dir);
	free_filenames(&items);
	free(items.files);
}

int 	pre_ls(t_dir arr, t_opt opts, int need_dir_name)
{
	int			i;
	struct stat	s_file_stat;
	t_dir		fls;
	t_dir		dir;
	
	i = 0;
	dir_init(&fls);
	dir_init(&dir);
	while (i < arr.cur)
	{
		if (lstat(arr.files[i].name, &s_file_stat) < 0)
		{
			ft_putstr("ft_ls: ");
			perror(arr.files[i].name);
		}
		else if (S_ISDIR(s_file_stat.st_mode))
		{
			append(&dir, arr.files[i].name, s_file_stat.st_mtime);
			update_info(s_file_stat, &dir);
		}
		else
		{
			append(&fls, arr.files[i].name, s_file_stat.st_mtime);
			update_info(s_file_stat, &fls);
		}
		i++;
	}
	sort_files(fls.files, fls.cur, opts);
	if (fls.cur > 0)
		ls_files(fls, opts, 0, 0);
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

int		main(int argc, char **argv)
{
	t_dir	args;
	t_opt	opts;
	int		i;
	int 	is_op;
	int 	parsed_opt;

	dir_init(&args);
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
			append(&args, argv[i], 0);
		}
		i++;
	}
	if (!args.cur || opts.cur_dir)
		append(&args, ".", 0);
	pre_ls(args, opts, args.cur > 1 ? 1 : 0);
	free_filenames(&args);
	free(args.files);
	return (0);
}
