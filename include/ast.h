/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:27:37 by tseche            #+#    #+#             */
/*   Updated: 2026/03/09 10:28:31 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_data	t_data;

//--------------------[TOKEN]----------------------------
typedef enum e_token_type
{
	PIPETYPE,// |
	SUPTYPE,// >
	INFTYPE,// <
	DSUPTYPE,// >>
	DINFTYPE,// <<
	LPARENTYPE,// (
	RPARENTYPE,// )
	AMPERTYPE,// &&
	VERBARTYPE,// ||
	WORDTYPE,// [.]+
	UNKNOWN,
	ERROR,
	eof
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	kind;
}					t_token;

typedef struct s_src_info
{
	char	*src;
	size_t	i;
	size_t	len;
}				t_src_info;

//--------------------[LEXER]--------------------------

t_token	lexer(t_src_info *txt);
bool	expect(t_src_info *txt, t_token_type type);
t_token	advance(t_src_info *txt);
size_t	len_quoted(char *src, char q);
int		is_start_word(char c);
int		len_word(char *src);
void	report_parsing_error(char c, char *s);

//--------------------[AST]----------------------------

typedef enum e_ast_type
{
	HEREDOC,// <<
	IN,// <
	PIPE,// |
	OUT,// > | >>
	AND,// &&
	OR,// ||
	SUBSHELL,
	CMD,
	END
}					t_ast_type;

typedef struct s_ast
{
	t_ast_type		kind;
	struct s_ast	*next;
}					t_ast;

typedef struct s_ast_subshell
{
	t_ast_type		kind; // SUBSHELL | '( )'
	struct s_ast	*next;
	t_ast			**inter;
}					t_ast_subshell;

typedef struct s_ast_pipe
{
	t_ast_type		kind; // PIPE | '|'
	struct s_ast	*next;
}					t_ast_pipe;

typedef struct s_ast_and
{
	t_ast_type		kind; // AND | '&&'
	struct s_ast	*next;
}					t_ast_and;

typedef struct s_ast_or
{
	t_ast_type		kind; // OR | '||'
	struct s_ast	*next;
}					t_ast_or;

typedef struct s_ast_heredoc
{
	t_ast_type		kind; // HEREDOC | '<<'
	struct s_ast	*next;
	char			*del;
}					t_ast_heredoc;

typedef struct s_ast_in
{
	t_ast_type		kind; // IN | '<'
	struct s_ast	*next;
	char			*input;
}					t_ast_in;

typedef struct s_ast_out
{
	t_ast_type		kind; // OUT | ('>' | '>>')
	struct s_ast	*next;
	char			*output;
	bool			overwrite;
}					t_ast_out;

typedef struct s_ast_cmd
{
	t_ast_type		kind; // NORMAL | anything other
	struct s_ast	*next;
	char			*name;
	char			**args;
}					t_ast_cmd;

//------------------[LOOKUP]----------------

typedef t_ast *(*		t_look_handler)(
	t_src_info		*txt,
	t_ast_type		type,
	t_data			*shell
);
typedef struct s_lookup
{
	t_ast_type		type;
	t_look_handler	fn;
}				t_lookup;

void	gen_lookup(t_lookup *lookup);

//------------------[PARSER]----------------

t_ast	*parse_args_cmd(t_ast_cmd *node, t_src_info *txt);
t_ast	**parse(char *src, t_data *shell);
t_ast	*parse_expr(t_lookup *lookup, t_src_info *txt, t_data *shell);
t_ast	*parse_output(t_src_info *txt, t_ast_type kind, t_data *shell);
t_ast	*parse_ord(t_src_info *txt, t_ast_type kind, t_data *shell);
t_ast	*parse_heredoc(t_src_info *txt, t_ast_type kind, t_data *shell);
t_ast	*parse_input(t_src_info *txt, t_ast_type kind, t_data *shell);
t_ast	*parse_cmd(t_src_info *txt, t_ast_type kind, t_data *shell);
t_ast	*parse_subshell(t_src_info *txt, t_ast_type kind, t_data *shell);
t_ast	**check_last(t_ast **node, t_ast *next, t_src_info *txt);

#endif
