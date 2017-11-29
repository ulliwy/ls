/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 11:29:49 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/20 11:42:02 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_files(t_file *arr, int n, int r)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			if (r ? ft_strcmp(arr[i].name, arr[j].name) > 0 : ft_strcmp(arr[i].name, arr[j].name) < 0)
			{
				tmp = arr[i].name;
				arr[i].name = arr[j].name;
				arr[j].name = tmp;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	set_half(t_file *arr, int start, t_file t1[], int k)
{
	int i;

	i = 0;
	while (i < k)
	{
		t1[i] = arr[start + i];
		i++;
	}
}

void	merge(t_file *arr, int l, int r, int rev)
{
	int 	i;
	int		j;
	int		k;
    t_file 	t1[l + (r - l) / 2 - l + 1];
    t_file 	t2[r - l + (r - l) / 2];	

    set_half(arr, l, t1, l + (r - l) / 2 - l + 1);
	set_half(arr, l + (r - l) / 2 + 1, t2, r - l + (r - l) / 2);
	i = 0;
	j = 0;
	k = l;
	while ((i < (l + (r - l) / 2) - l + 1) && (j < r - (l + (r - l) / 2)))
	{
		if (rev ? t1[i].mtime < t2[j].mtime : t1[i].mtime > t2[j].mtime)
			arr[k++] = t1[i++];
		else if (t1[i].mtime == t2[j].mtime)
		{
			if (ft_strcmp(t1[i].name, t2[j].name) <= 0)
				arr[k++] = t1[i++];
			else
				arr[k++] = t2[j++];
		}
		else
			arr[k++] = t2[j++];
	}
	while (i < (l + (r - l) / 2) - l + 1)
		arr[k++] = t1[i++];
	while (j < r - (l + (r - l) / 2))
		arr[k++] = t2[j++];
}

void		merge_sort(t_file *arr, int l, int r, int rev)
{
	int 	m;

	if (l < r)
	{
		m = l + (r - l) / 2;
		merge_sort(arr, l, m, rev);
		merge_sort(arr, m + 1, r, rev);
		merge(arr, l, r, rev);
	}
}

void		sort_dates(t_file *arr, int n, t_opt opts)
{
	return (merge_sort(arr, 0, n - 1, opts.r));
}