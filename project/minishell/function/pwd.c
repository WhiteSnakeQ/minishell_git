/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init_obj.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: kreys <kirrill20030@gmail.com>			 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/12/11 00:14:32 by kreys			 #+#	#+#			 */
/*   Updated: 2023/12/11 12:46:32 by kreys			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	pwd(char **strs, t_prj *prj, int fd)
{
	if (!strs)
		return ;
	ft_printf(fd, "%s\n", prj->our_path);
	prj->exit = 0;
	return ;
}
