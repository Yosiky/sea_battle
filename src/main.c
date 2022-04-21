/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:45:45 by eestelle          #+#    #+#             */
/*   Updated: 2022/04/21 19:15:14 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sea_battle.h"
#include <stdio.h>

void	help(void)
{
	write(2, "Error: ./sea_battle [NAME FILE]\n", 33);
}

void	print(char arr[10][10], int fd)
{
	char out[13] = "|..........|\n";

	write(fd, "+----------+\n", 13); 
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
			if (arr[i][j])
				out[j + 1] = 'o';
			else
				out[j + 1] = '.';
		write(fd, out, 13);
	}
	write(fd, "+----------+\n", 13); 
}

void	init(char arr[10][10])
{
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			arr[i][j] = 0;
}

uint32_t	generate_ship(int l)
{
	uint32_t	z = rand() & 1;
	uint32_t	x = rand() % (z == 0 ? 10 - l : 10);
	uint32_t	y = rand() % (z == 1 ? 10 - l : 10);

	printf("x = %d, y = %d, z = %d\n", x, y, z);
	printf("xyz = %d\n", ((x << 16) + (y << 8) + (z & 1)));
	return ((x << 16) + (y << 8) + (z & 1));
}

int		check(char arr[10][10], int l, uint32_t xyz)
{
	int	x = (xyz & 0x00ff0000) >> 16;
	int	y = (xyz & 0x0000ff00) >> 8;
	int	z = xyz & 1;

	printf("xyz = %d\n", xyz);
	printf("x = %d, y = %d, z = %d\n", x, y, z);
	if (z)
	{
		for (int i = l + 1; i >= 0; --i)
		{
			if (y + i == 10 || y + i == -1)
				continue ;
			for (int j = -1; j < 2; ++j)
			{
				if (x + j == 10 || x + j == -1)
					continue ;
				if (arr[y + i][x + j])
					return (1);
			}
		}
		for (int i = l - 1; i >= 0; --i)
			arr[y + i][x] = 1;
	}
	else
	{
		for (int i = l + 1; i >= 0; --i)
		{
			if (x + i == 10 || x + i == -1)
				continue ;
			for (int j = -1; j < 2; ++j)
			{
				if (y + j == 10 || y + j == -1)
					continue ;
				if (arr[y + j][x + i])
					return (1);
			}
		}
		for (int i = l - 1; i >= 0; --i)
			arr[y][x + i] = 1;
	}
	return (0);
}

void	generate(char arr[10][10])
{
	char	flag;

	while (check(arr, 4, generate_ship(4))) ;
	/*for (int i = 0; i < 2; ++i)
		while (check(arr, 3, generate_ship(3))) ;
	for (int i = 0; i < 3; ++i)
		while (check(arr, 2, generate_ship(2))) ;
	for (int i = 0; i < 4; ++i)
		while (check(arr, 1, generate_ship(1))) ;
*/
}

int	main(int argc, char **argv)
{
	char	arr[10][10];
	int		fd;

	srand(time(NULL));	
	init(arr);
	if (argc <= 2)
	{
		if (argc == 2)
			fd = open(argv[1], O_CREAT | O_WRONLY);
		else
			fd = 1;
		generate(arr);
		print(arr, fd);
	}
	else
		help();
	return (0);
}
