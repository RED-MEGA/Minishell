/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:47:27 by ebennamr          #+#    #+#             */
/*   Updated: 2023/03/09 16:07:56 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdarg.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# include "readline/readline.h"
# include "readline/history.h"

# include "const.h"
# include "libft/libft.h"

enum e_token
{
	TK_WORD,
	TK_SINGLE_QUOTE,
	TK_DOUBLE_QUOTE,
	TK_PIPE,
	TK_HERE_DOC,
	TK_RD_INPUT,
	TK_RD_OUTPUT,
	TK_RD_OUTPUT_APPEND,
	TK_AND,
	TK_OR,
	TK_OPEN_BRACE,
	TK_CLOSE_BRACE,
	TK_WT_SPACE,
	TK_OPEN_QUOTE
};

typedef struct s_public
{

	unsigned int	exit_status;
	char			**env;
	char			**exp_list;
	char			*path;
	int				isdef_env;
}					t_public;

t_public g_pub;

typedef struct s_struct
{
	int		i;
	int		j;
}			t_loc;

t_loc	ini_loc();
/* ==============> Tokenizer <============== */
/* ==============> /lexer/ <============== */
int	check_quote(t_list *tokens);
int check_brace(t_list *tokens);

	typedef struct s_token
{
	int		type;
	char	*value;
}			t_token;

void	add_token(t_list **list, int type, char *value);
void	skip_wt_sapce(t_list **list, char *line, int *i);
void	skip_quote(t_list **list, char *line, int *i, char qoute);
void	skip_word(t_list **list, char *line, int *i);
t_list	**create_token_list(t_list **head, char *line);


/* ==============> /minishell/ <============== */
int		indexofchar(char *line, char c);
char	**mat_join(char **s1, char **s2);
int		ft_strcmp(char *str1, char *str2);

	/* ==============> /utils/pwd <============== */
char *get_pwd(void);
char	*get_prompt(char *pwd);
char	*wildcard_exp(char *word);
t_list	*get_ls(void);

/* ==============> /utils/env/ <============== */
void	load_env(char *_path, char **env);
void	export_to_env(char *key, char *value, int option);
void	unset_var(char *key);
char	*expand_env(char *key);
void	add_to_env(char *content) ;
void	set_shlvl();
void	fill_key_value_opt(char *arg, char **key, char **value, int *opt);
void export_args(char **args);
void	export_to_explist(char *arg);
void	add_to_export(char *content);
void	unset_from_exp(char *key);
/* ==============> /utils/unset <============== */
void unset_cmd(char **args);
/* ==============> /utils/export <============== */
void	sort_mat(char **arr);
void	export();
int		valid_arg(char *arg);
/* ==============> /utils/export_utils <============== */
int		check_var(char *var);
void	print_export(char *var);

/* ==============> built-in <============== */
/* ==============> /built-in/ <============== */
void	echo_b(char *command_line);
void	exit_b(char *command_line);
/* ==============> Parser <============== */
/* ==============> /parser/ <============== */
typedef struct s_tree
{
	t_list			*lst;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

t_tree	*ft_treenew(t_list *lst);
t_tree	*ft_treelast(t_tree *tree, int option);
void	ft_treeadd_back(t_tree **tree, t_tree *new, int option);
void	ft_treeswap_root(t_tree **current_root, t_tree *new_root, int option);
void	ft_treeclear(t_tree **tree);

t_tree	*parser(t_list *lst);
void	test();

t_tree	*create_command(t_list *lst, int *i);
t_tree	*create_operator(t_list *lst, int *i);
t_tree	*create_redirect(t_list *lst, int *i);

#endif
