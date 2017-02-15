/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/15 21:15:38 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	parse(t_lst *env, char *line)
{
	char	**args;

	args = NULL;
	args = ft_strsplit(line, ' ');
	if (args && args[0])
	{
		if (ft_strcmp(args[0], "exit") == 0)
			ft_builtin_exit(env, args[0], args + 1);
		if (ft_strcmp(args[0], "env") == 0)
			ft_builtin_env(env, args[0], &args[1]);
		if (ft_strcmp(args[0], "setenv") == 0)
			ft_builtin_setenv(env, args[0], args + 1);
		if (ft_strcmp(args[0], "unsetenv") == 0)
			ft_builtin_unsetenv(env, args[0], &args[1]);
		if (ft_strcmp(args[0], "echo") == 0)
			ft_builtin_echo(env, args[0], args + 1);
		if (ft_strcmp(args[0], "cd") == 0)
			ft_builtin_cd(env, args[0], args + 1);
		ft_tabdel(args);
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_buf	*buf;
	t_word	*lst;
	t_lst	*env;

	lst = NULL;
	env = NULL;
	env = ft_env_to_list(envp, env);
	signal(SIGWINCH, get_sigwinch);
	signal(SIGINT, get_sigint);
	if (!(buf = init_buf()))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	init_curs();
	while (read_line(buf) > ERR_EXIT)
	{
		close_termios();
		if (is_line_ended(buf) >= 0)
		{
			parse(env, buf->final_line);
/*
			char n;
			X('\n');
			n = lex_buf(buf, &lst);
			if (n < 0)
				return (-1);
			else if (n > 0)
			{
				X(n);
			}
			else
			{
				PUT2("\n\n____________\n\n");
			t_word *tmp = lst;
			while (tmp)
			{
				PUT2("s : ");
				PUT2(tmp->s);
				PUT2(", token : ");
				E(tmp->flag);
				X('\n');
				tmp = tmp->next;
			}
				PUT2("____________\n\n");
			}
//			parse();
*/			ft_strdel(&(buf->final_line));
			destroy_word(&lst);
			lst = NULL;
		}
		ft_bzero(buf->line, (size_t)(sizeof(char) * BUFF_SIZE));
		buf->size = 0;
		clean_pos_curs();
	}
	close_termios();
	free_buf(buf);
	return (0);
}
