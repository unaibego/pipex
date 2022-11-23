/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prueba.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:01:38 by ubegona           #+#    #+#             */
/*   Updated: 2022/11/23 14:04:34 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdio.h"
#include "sys/wait.h"
#include "stdlib.h"

int	main()
{
	printf("%d", access("/sbin/ping", 0));
}