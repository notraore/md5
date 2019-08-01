/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:52:36 by notraore          #+#    #+#             */
/*   Updated: 2019/08/01 18:52:37 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void				init_sha256(t_sha256 *sha)
{
	sha->shastate[0] = 0x6a09e667;
	sha->shastate[1] = 0xbb67ae85;
	sha->shastate[2] = 0x3c6ef372;
	sha->shastate[3] = 0xa54ff53a;
	sha->shastate[4] = 0x510e527f;
	sha->shastate[5] = 0x9b05688c;
	sha->shastate[6] = 0x1f83d9ab;
	sha->shastate[7] = 0x5be0cd19;
	sha->count[0] = 0;
	sha->count[1] = 0;
}

static uint32_t		*padding(t_sha256 *sha)
{
	static uint32_t state[8];
	uint32_t		tmp1;
	uint32_t		tmp2;
	int				i;

	i = 0;
	ft_memcpy(state, sha->shastate, sizeof(state));
	while (i < 64)
	{
		tmp1 = state[7] + SIGMA1(state[4]) + CH(state[4], state[5], state[6])
			+ k[i] + ((uint32_t *)sha->buff)[i];
		tmp2 = SIGMA0(state[0]) + MA(state[0], state[1], state[2]);
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
