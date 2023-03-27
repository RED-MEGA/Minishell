/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:22:05 by reben-ha          #+#    #+#             */
/*   Updated: 2023/03/27 02:33:20 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../01.Main/minishell.h"

void	syntax_error(char *token)
{
	return (ft_printf(2,
		"%sMinishell : syntax error near unexpected `%s'%s\n",
		RED, token, RESET),
		exit(258));
}

t_tree	*bracket_handle(t_list **lst)
{
	t_tree	*tree;

	(*lst) = (*lst)->next;
	tree = or_and(lst);
	(*lst) = (*lst)->next;
	if (*lst)
		skip_space(lst);
	return (tree);
}

t_tree	*pipeline(t_list **lst)
{
	t_tree	*tree;

	tree = create_command(lst);
	while (*lst
			&& (*lst)->type == TK_PIPE)
	{
		ft_treeswap_root(&tree, create_operator(lst), LEFT);
		tree->right = create_command(lst);
	}
	return (tree);
}

t_tree	*or_and(t_list **lst)
{
	t_tree	*tree;

	tree = pipeline(lst);
	while ((*lst)
			&& ((*lst)->type == TK_OR
			|| (*lst)->type == TK_AND))
	{
		ft_treeswap_root(&tree, create_operator(lst), LEFT);
		tree->right = pipeline(lst);
	}
	return (tree);
}

t_tree	*mk_tree(t_list *lst)
{
	t_tree	*tree;

	tree = NULL;
	return (or_and(&lst));
}