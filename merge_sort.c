/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 11:29:49 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/20 11:42:02 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_halves(t_file *arr, t_file t1[], t_file t2[], t_merge merge)
{
	int i;

	i = 0;
	while (i < merge.m - merge.l + 1)
	{
		t1[i] = arr[merge.l + i];
		i++;
	}
	i = 0;
	while (i < merge.r - merge.m)
	{
		t2[i] = arr[merge.m + 1 + i];
		i++;
	}
}

void	create_merge(t_file *arr, t_file t1[], t_file t2[], t_merge merge)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((i < merge.m - merge.l + 1) && (j < merge.r - merge.m))
	{
		if (merge.rev ? t1[i].mtime < t2[j].mtime : t1[i].mtime > t2[j].mtime)
			arr[merge.k++] = t1[i++];
		else if (t1[i].mtime == t2[j].mtime)
		{
			if (merge.rev ? ft_strcmp(t1[i].name, t2[j].name) > 0 :
				ft_strcmp(t1[i].name, t2[j].name) <= 0)
				arr[merge.k++] = t1[i++];
			else
				arr[merge.k++] = t2[j++];
		}
		else
			arr[merge.k++] = t2[j++];
	}
	while (i < merge.m - merge.l + 1)
		arr[merge.k++] = t1[i++];
	while (j < merge.r - merge.m)
		arr[merge.k++] = t2[j++];
}

void	merge(t_file *arr, int l, int r, int rev)
{
	t_merge		merge;
	t_file		t1[l + (r - l) / 2 - l + 1];
	t_file		t2[r - l + (r - l) / 2];

	merge.l = l;
	merge.r = r;
	merge.m = l + (r - l) / 2;
	merge.k = l;
	merge.rev = rev;
	set_halves(arr, t1, t2, merge);
	create_merge(arr, t1, t2, merge);
}

void	merge_sort(t_file *arr, int l, int r, int rev)
{
	int		m;

	if (l < r)
	{
		m = l + (r - l) / 2;
		merge_sort(arr, l, m, rev);
		merge_sort(arr, m + 1, r, rev);
		merge(arr, l, r, rev);
	}
}
