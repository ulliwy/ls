/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:30:34 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/20 11:42:01 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_max_blk_length(t_dir fls, int *i)
{
	int		max;
	int		cur_l;

	max = 0;
	while (*i < fls.cur)
	{
		cur_l = ft_strlen(fls.files[*i].name);
		if (cur_l > max)
			max = cur_l;
		(*i)++;
	}
	max = max / 8 + 1;
	return (max);
}

void	print_row(t_dir fls, int start, int blk)
{
	int i;
	int cur;

	i = 0;
	cur = start;
	while (i < fls.cols && cur < fls.cur)
	{
		ft_printf("%-*s", blk, fls.files[cur].name);
		cur = cur + fls.rows;
		i++;
	}
	ft_printf("\n");
}

void	column_output(t_dir fls)
{
	int				blk_length;
	struct winsize	ws;
	int				n_files;
	int				i;

	n_files = 0;
	blk_length = get_max_blk_length(fls, &n_files);
	if ((fls.cols = ioctl(0, TIOCGWINSZ, &ws)) != 0)
		return (regular_output(fls));
	fls.cols = (ws.ws_col / 8) / blk_length;
	i = 0;
	fls.rows = fls.cur / fls.cols + (fls.cur % fls.cols ? 1 : 0);
	while (i < fls.rows)
	{
		print_row(fls, i, blk_length * 8);
		i++;
	}
}
