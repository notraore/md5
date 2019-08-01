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

#define SI0(a) (ROTR(a, 28) ^ ROTR(a, 34) ^ ROTR(a, 39))
#define SI1(e) (ROTR(e, 14) ^ ROTR(e, 18) ^ ROTR(e, 41))
#define SUM0(x) (ROTR(x, 1) ^ ROTR(x, 8) ^ (x >> 7))
#define SUM1(x) (ROTR(x, 19) ^ ROTR(x, 61) ^ (x >> 6))

static uint64_t const k[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538, 
	0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe, 
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab, 
	0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725, 
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 
	0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b, 
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218, 
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 
	0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec, 
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c, 
	0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6, 
	0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817 };

void				rev_endian32(uint32_t *src, const size_t len)
{
	unsigned char		*data;
	uint32_t			n;
	size_t				i;

	i = 0;
	while (i < len)
	{
		n = src[i];
		data = (unsigned char *)&src[i++];
		data[0] = ((n >> 24) & 0xff);
		data[1] = ((n >> 16) & 0xff);
		data[2] = ((n >> 8) & 0xff);
		data[3] = (n & 0xff);
	}
}

void				rev_endian64(uint64_t *src, const size_t len)
{
	unsigned char		*data;
	uint64_t			n;
	size_t				i;

	i = 0;
	while (i < len)
	{
		n = src[i];
		data = (unsigned char *)&src[i++];
		data[0] = ((n >> 56) & 0xff);
		data[1] = ((n >> 48) & 0xff);
		data[2] = ((n >> 40) & 0xff);
		data[3] = ((n >> 32) & 0xff);
		data[4] = ((n >> 24) & 0xff);
		data[5] = ((n >> 16) & 0xff);
		data[6] = ((n >> 8) & 0xff);
		data[7] = (n & 0xff);
	}
}

void				init_sha256(t_sha512 *tar)
{
	tar->shastate[0] = 0x6a09e667f3bcc908;
	tar->shastate[1] = 0xbb67ae8584caa73b;
	tar->shastate[2] = 0x3c6ef372fe94f82b;
	tar->shastate[3] = 0xa54ff53a5f1d36f1;

	tar->shastate[4] = 0x510e527fade682d1;
	tar->shastate[5] = 0x9b05688c2b3e6c1f;
	tar->shastate[6] = 0x1f83d9abfb41bd6b;
	tar->shastate[7] = 0x5be0cd19137e2179;

	tar->count[0] = 0;
	tar->count[1] = 0;
}

static uint32_t			*padding(t_sha512 *tar)
{
	static uint32_t state[8];
	uint32_t		tmp1;
	uint32_t		tmp2;
	int				i;

	i = 0;
	ft_memcpy(state, tar->shastate, sizeof(state));
	while (i < 64)
	{
		tmp1 = state[7] + SI1(state[4]) + CH(state[4], state[5], state[6])
			+ k[i] + ((uint32_t *)tar->buff)[i];
		tmp2 = SI0(state[0]) + MA(state[0], state[1], state[2]);
		state[7] = state[6];
		state[6] = state[5];
		state[5] = state[4];
		state[4] = state[3] + tmp1;
		state[3] = state[2];
		state[2] = state[1];
		state[1] = state[0];
		state[0] = tmp1 + tmp2;
		i++;
	}
	return (state);
}

void		update(t_sha512 *tar)
{
	uint32_t		*pad_rest;
	uint32_t		*buffer;
	size_t			i;

	i = 16;
	buffer = (uint32_t *)tar->buff;
	rev_endian32(buffer, 16);
	while (i < 64)
	{
		buffer[i] = buffer[i - 16] + SUM0(buffer[i - 15]) + buffer[i - 7]
		+ SUM1(buffer[i - 2]);
		i++;
	}
	pad_rest = padding(tar);
	tar->shastate[0] += pad_rest[0];
	tar->shastate[1] += pad_rest[1];
	tar->shastate[2] += pad_rest[2];
	tar->shastate[3] += pad_rest[3];
	tar->shastate[4] += pad_rest[4];
	tar->shastate[5] += pad_rest[5];
	tar->shastate[6] += pad_rest[6];
	tar->shastate[7] += pad_rest[7];
	ft_memset(tar->buff, 0, 64);

}

void			digest_sha256(t_sha512 *tar, unsigned char const *msg, size_t len)
{
	uint32_t		bits;

	while (len)
	{
		bits = tar->count[0] >> 3;
		if (bits + len < 64)
		{
			ft_memcpy(tar->buff + bits, msg, len);
			tar->count[0] += len << 3;
			return ;
		}
		ft_memcpy(tar->buff + bits, msg, 64 - bits);
		tar->count[0] = 0;
		++tar->count[1];
		update(tar);
		msg += 64 - bits;
		len -= 64 - bits;
	}
}

void			digest_sha256_suite(t_sha512 *tar, unsigned char *hash)
{
	uint32_t		bits;
	uint64_t		size;
	size_t			i;

	i = 0;
	bits = tar->count[0] >> 3;
	tar->buff[bits] = 0x80;
	if (bits + sizeof(uint32_t) > 64)
		update(tar);
	size = ((size_t)tar->count[1] << 9) + tar->count[0];
	rev_endian64(&size, 1);
	ft_memcpy(tar->buff + (64 - sizeof(uint64_t)), &size, sizeof(uint64_t));
	update(tar);
	while (i < 128)
	{
		hash[i] = ((unsigned char *)tar->shastate)[i];
		++i;
	}
	rev_endian32((uint32_t *)hash, 8);
}

void			print_hash(unsigned char *hash, int count)
{
	int						g;
	size_t					i;
	const unsigned char		*pc;

	pc = hash;
	i = 0;
	while (i < count)
	{
		g = (*(pc + i) >> 4) & 0xf;
		g += g >= 10 ? 'a' - 10 : '0';
		ft_putchar(g);
		g = *(pc + i) & 0xf;
		g += g >= 10 ? 'a' - 10 : '0';
		ft_putchar(g);
		i++;
	}
	ft_putchar('\n');
}

void			printstr_sha256(t_sha512 *tar, unsigned const char *msg)
{
	unsigned char hash[128];

	init_sha256(tar);
	digest_sha256(tar, msg, ft_strlen((char *)msg));
	digest_sha256_suite(tar, hash);
	print_hash(hash, 128);
}

void			printstr_md5(t_md5 *md5, unsigned const char *msg)
{
	unsigned char hash[128];

	init_md5(md5);
	digest(md5, msg, ft_strlen((char *)msg));
	digest_suite(md5, hash, 128);
	print_hash(hash, 128);
}
