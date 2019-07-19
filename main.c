/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:30:46 by notraore          #+#    #+#             */
/*   Updated: 2019/05/15 15:30:46 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

int				main(int argc, char **argv)
{
	// char		*line;
	// t_mdf		target;
	// unsigned	*ret;
	// char		*msg;

	// ft_bzero(&target, sizeof(t_mdf));
	// init_mdf(&target);
	// get_next_line(0, &line);
	// msg = ft_strjoin(line, "\n");
	// ret = mdf(msg, strlen(msg), &target);
	// while (target.i < 4)
	// {
	// 	wbunion.w = ret[target.i];
	// 	while (target.j < 4)
	// 	{
	// 		printf("%02x", wbunion.b[target.j]);
	// 		target.j++;
	// 	}
	// 	target.i++;
	// 	target.j = 0;
	// }
	// printf("\n");
	t_sha256 sha;
	if (argc == 2)
		printstr_sha256(&sha, argv[1]);
	return (0);
}
