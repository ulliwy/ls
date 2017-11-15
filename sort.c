/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 11:29:49 by iprokofy          #+#    #+#             */
/*   Updated: 2017/11/15 11:41:54 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_names(char **arr, int n)
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
			if (ft_strcmp(arr[i], arr[j]) < 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (0);
}
