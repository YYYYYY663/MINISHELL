/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymizukam <ymizukam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:48:09 by ymizukam          #+#    #+#             */
/*   Updated: 2025/01/05 02:48:01 by ymizukam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include "libft.h"
# include "lmap.h"


char	*var_get(char *key, t_info *info);
int	    var_dispacher(t_list **lst, t_info *info);




#endif