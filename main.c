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

void			mdf_allocation(const char *msg, int msglen, t_mdf *targ)
{
	targ->grps = 1 + (msglen + 8) / 64;
	targ->msg2 = malloc(64 * targ->grps);
	if (!targ->msg2)
		ft_kill("Message malloc failed.");
	memcpy(targ->msg2, msg, msglen);
	targ->msg2[msglen] = (unsigned char)0x80;
	targ->q = msglen + 1;
	while (targ->q < 64 * targ->grps)
	{
		targ->msg2[targ->q] = 0;
		targ->q++;
	}
	wbunion.w = 8 * msglen;
	targ->q -= 8;
	memcpy(targ->msg2 + targ->q, &wbunion.w, 4);
}

void			mdf_loop(t_mdf *targ, short *rots[4])
{
	while (targ->p < 4)
	{
		targ->fctn = targ->ff[targ->p];
		targ->rotn = rots[targ->p];
		targ->m = targ->mo[targ->p];
		targ->o = targ->om[targ->p];
		targ->q = 0;
		while (targ->q < 16)
		{
			targ->g = (targ->m * targ->q + targ->o) % 16;
			targ->f = targ->abcd[1] + rol(targ->abcd[0] +
			targ->fctn(targ->abcd) + targ->k[targ->q + 16 * targ->p] +
			mm.w[targ->g], targ->rotn[targ->q % 4]);
			targ->abcd[0] = targ->abcd[3];
			targ->abcd[3] = targ->abcd[2];
			targ->abcd[2] = targ->abcd[1];
			targ->abcd[1] = targ->f;
			targ->q++;
		}
		targ->p++;
	}
}

void			mdf_digest_msg(t_mdf *targ, short *rots[4])
{
	while (targ->grp < targ->grps)
	{
		memcpy(mm.b, targ->msg2 + targ->os, 64);
		targ->q = 0;
		while (targ->q < 4)
		{
			targ->abcd[targ->q] = targ->h[targ->q];
			targ->q++;
		}
		targ->p = 0;
		mdf_loop(targ, rots);
		targ->p = 0;
		while (targ->p < 4)
		{
			targ->h[targ->p] += targ->abcd[targ->p];
			targ->p++;
		}
		targ->os += 64;
		targ->grp++;
	}
}

unsigned		*mdf(const char *msg, int msglen, t_mdf *targ)
{
	static short rot0[4] = {7, 12, 17, 22};
	static short rot1[4] = {5, 9, 14, 20};
	static short rot2[4] = {4, 11, 16, 23};
	static short rot3[4] = {6, 10, 15, 21};
	static short *rots[4] = {rot0, rot1, rot2, rot3};

	if (targ->k == NULL)
		targ->k = calc(targ->kspace);
	while (targ->q < 4)
	{
		targ->h[targ->q] = targ->h0[targ->q];
		targ->q++;
	}
	mdf_allocation(msg, msglen, targ);
	mdf_digest_msg(targ, rots);
	if (targ->msg2)
		free(targ->msg2);
	return (targ->h);
}

int				main(void)
{
	char		*line;
	t_mdf		target;
	unsigned	*ret;
	char		*msg;

	ft_bzero(&target, sizeof(t_mdf));
	init_mdf(&target);
	get_next_line(0, &line);
	msg = ft_strjoin(line, "\n");
	ret = mdf(msg, strlen(msg), &target);
	while (target.i < 4)
	{
		wbunion.w = ret[target.i];
		while (target.j < 4)
		{
			printf("%02x", wbunion.b[target.j]);
			target.j++;
		}
		target.i++;
		target.j = 0;
	}
	printf("\n");
	return (0);
}
