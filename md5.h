/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:36:38 by notraore          #+#    #+#             */
/*   Updated: 2019/05/15 16:35:16 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"
# define ABS(x) ((x < 0) ? (-x) : (x))

union
{
	unsigned			w;
	unsigned char		b[4];
}						wbunion;

union
{
	unsigned			w[16];
	char				b[64];
}						mm;

typedef unsigned		digest[4];
typedef unsigned int	(*dgstfctn)(unsigned a[]);
typedef struct s_mdf	t_mdf;

struct					s_mdf
{
	digest				h0;
	dgstfctn			ff[4];
	short				mo[4];
	short				om[4];
	short				rot0[4];
	short				rot1[4];
	short				rot2[4];
	short				rot3[4];
	short				*rots[4];
	unsigned			kspace[64];
	unsigned			*k;
	digest				h;
	digest				abcd;
	dgstfctn			fctn;
	short				m;
	short				o;
	short				g;
	unsigned			f;
	short				*rotn;
	int					os;
	int					grp;
	int					grps;
	int					q;
	int					p;
	int					i;
	int					j;
	unsigned char		*msg2;

};

/*
**digest.c
*/
unsigned				f_zero(unsigned abcd[]);
unsigned				f_one(unsigned abcd[]);
unsigned				f_two(unsigned abcd[]);
unsigned				f_three(unsigned abcd[]);

/*
** utils.c
*/
double					my_pow(double x, int y);
unsigned				*calc(unsigned *ks);
unsigned				rol(unsigned v, short amt);
void					init_mdf(t_mdf *targ);

#endif
