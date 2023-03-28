/* ************************************************************************** */
/*		                                                                      */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:06:55 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/11/25 14:07:21 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/stat.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h> 
# include "libft/libft.h"
# include <string.h>
# include <signal.h>
# include <sys/types.h>

# define PROMPT ">minishell "
# define _XOPEN_SOURCE 700

//type 0 = output, type 1 = input, type 2 = output_append, type 3 = here_doc

/*parsing*/

# define COMMANDE 1
# define FLAG 2
# define ARG 3
# define PIPE 4
# define RED_OUT 5 
# define RED_IN 6
# define RED_OUT_APP 7
# define RED_HERE_DOC 8
# define DOLLAR 9

typedef struct s_redir
{
	char			*file;
	int				type;
	struct s_redir	*next;
}				t_redir;

typedef struct s_simple_command
{
	int						args_num;
	char					**args;
	char					*cmd;
	char					**env;
	int						last_ret;
	int						infile;
	int						outfile;
	int						badfd;
	int						pos;
	int						err;
	t_redir					*redir;
	struct s_simple_command	*next;
	struct s_simple_command	*previous;
}				t_simple_command;

typedef struct s_token
{
	int		size;
	int		type;
	char	*value;
	int		fl_q;
	int		nbr_spaces;
	int		subst;
	int		fl_space;
}				t_token;

/*binaries/main_bin.c*/

int					stat_management(char *bin, int mode);
int					get_stat(char *str);
void				execution(t_simple_command *c_table, char **env);
void				ft_bin_nofork(t_simple_command *c_table, char **env);
void				ft_exec_bin(t_simple_command *c_table, char **env);

/*binaries/path_utils.c*/

int					cant_exec(char *file, char *message, int vexit);
void				ft_add_path(t_simple_command *c_table, char **path);
char				**ft_get_paths(char **envp);
char				*ft_add_slash(char *res);
char				*ft_rm_path(char *str);

/*builtin/cd_utils.c*/

void				add_pwds(t_simple_command *c_table, char *oldpwd,
						char *newpwd);
int					cd_path(t_simple_command *c_table, char **path, char *temp);

/*builtin/cd.c*/
void				cd_noarg(t_simple_command *c_table);
int					cd_get_dash(t_simple_command *c_table);
void				cd_curpath(t_simple_command *c_table);
void				cd_classic(t_simple_command *c_table);
void				ft_bi_cd(t_simple_command *c_table);

/*builtin/echo.c*/
int					is_nonewl(char *str, char c);
void				ft_bi_echo(t_simple_command *c_table);

/*builtin/env.c*/
void				ft_bi_env(t_simple_command *c_table);

/*builtin/exit.c*/

int					check_number(char *str);
void				exit_too_long(t_simple_command *c_table);
int					ft_exitreturn(char *str);
void				ft_bi_exit(t_simple_command *c_table);

/*builtin/export_utils.c*/
void				ft_cp_env(char **sorted, char **env);
int					is_valid_export(char *str);
void				ft_export_replace(char *str, char *full,
						t_simple_command **c_table, int i);
void				ft_export_addone(char *str, char *full,
						t_simple_command **c_table);
void				ft_export_add(char *toadd, t_simple_command **c_table);

/*builtin/export.c*/
void				ft_sort_sorted(char **tab);
void				print_expformat(const char *str);
void				ft_export_noarg(t_simple_command *c_table);
void				ft_export_arg(t_simple_command **c_table);
void				ft_bi_export(t_simple_command **c_table);

/*builtin/pwd.c*/
void				ft_bi_pwd(t_simple_command *c_table);

/*builtin/unset.c*/
int					ft_strccmp(char *s1, char *s2, char c);
int					is_in_env(char *str, char **env);
void				ft_remove_from_env(char *str, char ***env);
void				ft_bi_unset(t_simple_command **c_table);

/*builtin/utils.c*/
char				*make_pwd(char *prefix);
int					ft_isbuiltin(char *str);
void				start_builtin(t_simple_command **c_table);
void				ft_split_builtin(t_simple_command **c_table);

/*env/env_init.c*/
char				*ft_add_shlvl(char *env);
char				**ft_empty_env(void);
char				**ft_copy_env(char **env);
void				free_tab_pipes(pid_t *tab, int *pipes);
void				no_path(t_simple_command *c_table, int ret);

/*exit/exit.c*/
int					check_exec(int mode, t_simple_command *c_table);
void				ft_del_heredoc(int index);
void				ft_free_2dstr(char **str);
int					ft_proper_free(t_simple_command *c_table, char **env);
int					check_tty(void);

/*exit/malloc_error.c*/
void				free_alltok(t_token *tab, int size);
void				ft_check_nullarg(t_simple_command *lst,
						t_token *arr_tok, int size);
char				*add_arr_zer(char *arr, int i);

/*file/file_open.c*/
void				ft_add_input(char *file, t_simple_command *c_table);
void				ft_add_output(char *file, t_simple_command *c_table);
void				ft_add_append(char *file, t_simple_command *c_table);
void				ft_add_heredoc(char *delim, t_simple_command *c_table);
void				ft_open_files(t_simple_command *c_table, t_redir *list);

/*file/file_utils.c*/
void				ft_write_wfolder(t_redir *wrong,
						t_simple_command *c_table);
void				ft_file_error(t_simple_command *c_table);
int					ft_isfolder(char *file, int ret);
void				write_heredoc(char *delim, int ret, char **env);
char				*add_index_file(char *str, int pos);

/*file/stream_utils.c*/
int					save_stdin(void);
void				stdin_getback(int saved);
char				*add_index_file(char *str, int pos);
void				ft_close_prev(t_simple_command *c_table);

/*file/heredoc_utils.c*/
int					sizetochar(char *str, char c);
int					skip_expand(char *str);
char				*get_exp(char *str);
char				*expended(char *str, char **env);
void				write_exp_heredoc(char *str, char **env, int fd);

/*pipe/pipe_utils.c*/
int					onec_exec(t_simple_command *c_table);
pid_t				*init_childs(int nbr_sent);
int					*init_pipes(int nbr_sent, pid_t *childs);
void				dup_fds(int *pipefd, int i,
						t_simple_command *c_table, int size);
void				launch_exec(t_simple_command *c_table, pid_t *childs,
						int *pipefd, int size);
/*pipe/pipe.c*/
int					ft_lstcmd(t_simple_command *list);
void				close_pipes(int *tab, int size);
int					ft_pipe(t_simple_command *c_table);
int					free_one_memb(t_simple_command *c_table, pid_t *tab,
						int *pipes, int ret);
void				ft_add_prev(t_simple_command *c_table);

/*utils.c*/
int					exit_free_val(char *cmd, int ret, char **env);
int					soft_quit(char **temp_env, int ret);
int					ft_2dlen(char **tab);
int					check_files(t_simple_command *c_table);
void				launch_start(char *cmd, int nbr_tok, char ***env, int *ret);

/*readline.c*/

int					ft_check_space(char *str);
int					syntax_error(t_token *arr_token, int size, char *error);
int					check_syntax(t_token *arr_tok, int nbr_tokens);
t_simple_command	*get_first(t_simple_command *memb);

/*signals/sig_handlers.c*/

void				inthandler(int sig);
void				quithandler(int sig);
void				inthandler2(int sig);
void				quithandler2(int sig);
void				inthandler3(int sig);

/*signals/set_signals.c*/
int					sig_val(int ret);
void				set_signals(void);
void				set_signals2(void);
void				set_signals3(void);
void				segvhandler2(int sig);

/*parsing/lexer/ft_split_tokens.c*/
int					what_is_len(char *str, int fl_q);
void				make_str_body(char *arr, char *str, int *i, int len);
int					make_str_check(char *arr, char **str, int *i, int fl_q);
char				*make_str(char *str, int fl_q);

t_token				*ft_split_tokens(char *str, int nbr_tokens);

/*parsing/lexer/what_is_len.c*/
int					what_is_len_s_quotes(char *str);
int					what_is_len_double_quotes(char *str);
int					what_is_len_simple(char *str);
int					what_is_len_dollar(char *str);
int					what_is_len_redir(char *str);

/*parsing/lexer/make_str_quotes.c*/
void				make_str_s_quotes(char *str, t_token *my_arr,
						int *i, int *y);
void				check_str_double_quote(char *str, t_token *my_arr,
						int *i, int *y);
void				make_str_double_quote_filled(char *str, t_token *my_arr,
						int *i, int *y);
void				make_str_double_quote(char *str, t_token *my_arr,
						int *i, int *y);
void				make_str_dq_cons(char *arr, char *str, int *i, int len);

/*parsing/lexer/make_str_simple_dollar_redir.c*/
void				make_str_dollar_filled(char *str, t_token *my_arr,
						int *i, int *y);
void				make_str_dollar(char *str, t_token *my_arr, int *i, int *y);
void				make_str_simple(char *str, t_token *my_arr, int *i, int *y);
void				make_str_redir(char *str, t_token *my_arr, int *i, int *y);
void				make_str_body_two(char *str, char *arr, int *i, int fl_q);

/*parsing/lexer/nbr_tokens.c*/

void				nbr_words_dollar_body(char const *str, int *i);
int					nbr_words_dollar(char const *str, int *i);
int					nbr_words_redir(char const *str, int *i);
int					nbr_words_simple(char const *str, int *i);
int					nbr_words(char const *str);

/*parsing/lexer/nbr_words_quotes.c*/
int					nbr_words_s_quotes(char const *str, int *i);
int					mouve_index(char const *str, int *i);
int					nbr_words_double_quotes(char const *str, int *i);
int					in_charset(char letter);
int					what_is_len_redir(char *str);

/*parsing/lexer/what_is_len.c*/
int					what_is_len_s_quotes(char *str);
int					what_is_len_double_quotes(char *str);
int					what_is_len_simple(char *str);
int					what_is_len_dollar_var(char *str);
int					what_is_len_dollar(char *str);

/*parsing/lexer/which_type_is_it.c*/

int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					which_type(t_token *my_arr);
void				typification(t_token *my_arr, int nbr_token);
void				fill_size_tokens(t_token *my_arr, int nbr_tokens);

/*parsing/parser/preparsing.c*/
t_simple_command	*new_elem(t_token *arr_tok, int index,
						char **env, int ret);
void				add_env_in_elem(t_simple_command *lst_command, char **env);
t_simple_command	*creation_list_command(t_token *arr_tok, int arr_len,
						char **env, int last_ret);
void				ft_free_arrtok(t_token *tab, int size);

/*parsing/parser/tools_parser.c*/

void				ft_free_3dtab(char **tab);
void				ft_free_redir(t_redir **list);
char				*ft_exp_dol(char *str, int mode, char **env, int ret);
char				*ft_var_only(char *str);
/*parsing/parser/fill_args_parser.c*/

int					ft_count_args(t_token *arr_tok, int index, int len);
void				ft_fill_args_var_not_exist(char	**args, int *i);
void				ft_fill_args_join(char **args, char *temp, int *i, int *j);
char				**ft_fill_args_finita(char **args, int i);
char				**ft_fill_args(t_token *arr_tok, int index,
						char **env, int ret);

/*parsing/parser/fill_args_parser_check.c*/
int					ft_fill_args_check_var_not_exist(t_token *arr_tok, int ind);
int					ft_fill_args_check_expand(t_token *arr_tok, int ind);
int					ft_fill_args_check_spaces(t_token *arr_tok, int ind);

/*parsing/parser/do_var_existe.c*/
int					do_var_existe(t_token **arr_tok, int len,
						char **env, int index);

/*parsing/parser/fill_redir_parser.c*/
int					is_there_red(t_token *arr_tok, int index,
						int len, char **env);
void				new_redir(t_token *arr_tok, t_redir **start);
t_redir				*ft_fill_redir(t_token *arr_tok, int index,
						char **env, int ret);
int					is_expandable(char *str, int red, int quote, char **env);

/*parsing/parser_print.c*/
void				print_args(t_simple_command *start);
void				print_redir(t_simple_command *c);
void				ft_print_sentences(t_simple_command *start);

/*parsing/parser/fill_redir_utils.c*/
int					is_good_redir(t_token *tok, int ind, char **env);
int					is_there_red(t_token *tok, int ind, int len, char **env);
char				*call_expand(t_token *tok, int ind, char **env, int ret);
void				free_endred(t_token *tok, int ind, int i);

/*parsing/parser/verif_parsing.c*/

int					is_redir(t_token arr_tok);
int					is_text(t_token arr_tok);
int					nbr_pipe(t_token *arr_tok, int len);
int					skip_topipe(t_token *arr_tok, int index, int len);
int					ft_2dlen(char **tab);

#endif