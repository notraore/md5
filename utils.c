/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:36:21 by notraore          #+#    #+#             */
/*   Updated: 2019/05/15 15:36:22 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

double			my_pow(double x, int y)
{
	int		i;
	double	value;

	i = 0;
	value = 1;
	if (y == 0)
		return (1.0f);
	else if (x == 0)
		return (0.0f);
	while (i < ABS(y))
	{
		value *= x;
		i++;
	}
	if (y < 0)
		return (1.0f / value);
	else
		return (value);
}

unsigned		*calc(unsigned *ks)
{
	int		i;
	double	s;
	double	pwr;

	i = 0;
	pwr = pow(2, 32);
	while (i < 64)
	{
		s = fabs(sin(1 + i));
		ks[i] = (unsigned)(s * pwr);
		i++;
	}
	return (ks);
}

unsigned		rol(unsigned v, short amt)
{
	unsigned msk;

	msk = (1 << amt) - 1;
	return (((v >> (32 - amt)) & msk) | ((v << amt) & ~msk));
}



void			init_mdf(t_mdf *targ)
{
	targ->h0[0] = 0x67452301;
	targ->h0[1] = 0xEFCDAB89;
	targ->h0[2] = 0x98BADCFE;
	targ->h0[3] = 0x10325476;

	targ->ff[0] = &f_zero;
	targ->ff[1] = &f_one;
	targ->ff[2] = &f_two;
	targ->ff[3] = &f_three;
	targ->mo[0] = 1;
	targ->mo[1] = 5;
	targ->mo[2] = 3;
	targ->mo[3] = 7;
	targ->om[0] = 0;
	targ->om[1] = 1;
	targ->om[2] = 5;
	targ->om[3] = 0;
	targ->os = 0;
	targ->grps = 0;
	targ->grp = 0;
	targ->grps = 0;
	targ->p = 0;
}
