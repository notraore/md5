/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:30:46 by notraore          #+#    #+#             */
/*   Updated: 2019/05/15 15:30:46 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

#define SIGMA0(a) (ROTR(a, 2) ^ ROTR(a, 13) ^ ROTR(a, 22))
#define SIGMA1(e) (ROTR(e, 6) ^ ROTR(e, 11) ^ ROTR(e, 25))
#define SIG0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3))
#define SIG1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10))

void		update(t_sha256 *sha)
{
	uint32_t		*pad_rest;
	uint32_t		*buffer;
	size_t			i;

	i = 16;
	buffer = (uint32_t *)sha->buff;
	rev_endian32(buffer, 16);
	while (i < 64)
	{
		buffer[i] = buffer[i - 16] + SIG0(buffer[i - 15]) + buffer[i - 7]
		+ SIG1(buffer[i - 2]);
		i++;
	}
	pad_rest = padding(sha);
	sha->shastate[0] += pad_rest[0];
	sha->shastate[1] += pad_rest[1];
	sha->shastate[2] += pad_rest[2];
	sha->shastate[3] += pad_rest[3];
	sha->shastate[4] += pad_rest[4];
	sha->shastate[5] += pad_rest[5];
	sha->shastate[6] += pad_rest[6];
	sha->shastate[7] += pad_rest[7];
	ft_memset(sha->buff, 0, 64);
}

void		digest_sha256(t_sha256 *s, unsigned char const *msg, size_t len)
{
	uint32_t		bits;

	while (len)
	{
		bits = s->count[0] >> 3;
		if (bits + len < 64)
		{
			ft_memcpy(s->buff + bits, msg, len);
			s->count[0] += len << 3;
			return ;
		}
		ft_memcpy(s->buff + bits, msg, 64 - bits);
		s->count[0] = 0;
		++s->count[1];
		update(s);
		msg += 64 - bits;
		len -= 64 - bits;
	}
}

void		digest_sha256_suite(t_sha256 *sha, unsigned char *hash)
{
	uint32_t		bits;
	uint64_t		size;
	size_t			i;

	i = 0;
	bits = sha->count[0] >> 3;
	sha->buff[bits] = 0x80;
	if (bits + sizeof(uint32_t) > 64)
		update(sha);
	size = ((size_t)sha->count[1] << 9) + sha->count[0];
	rev_endian64(&size, 1);
	ft_memcpy(sha->buff + (64 - sizeof(uint64_t)), &size, sizeof(uint64_t));
	update(sha);
	while (i < 32)
	{
		hash[i] = ((unsigned char *)sha->shastate)[i];
		++i;
	}
	rev_endian32((uint32_t *)hash, 8);
}
