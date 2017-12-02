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
			if (r ? ft_strcmp(arr[i].name, arr[j].name) > 0 :
				ft_strcmp(arr[i].name, arr[j].name) < 0)
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

void		sort_dates(t_file *arr, int n, t_opt opts)
{
	return (merge_sort(arr, 0, n - 1, opts.r));
}
