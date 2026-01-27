/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:27:37 by tseche            #+#    #+#             */
/*   Updated: 2026/01/27 16:36:00 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

//--------------------[TOKEN]----------------------------
typedef enum e_token_type
{
	SQUOTETYPE, // \'
	DQUOTETYPE, // \"
	PIPETYPE,   // |
	SUPTYPE,    // >
	INFTYPE,    // <
	DSUPTYPE,   // >>
	DINFTYPE,   // <<
	LPARENTYPE, // (
	RPARENTYPE, // )
	AMPERTYPE,  // &&
	VERBARTYPE, // ||
	DOLLARTYPE, //	$
	WORDTYPE,   // [.]+
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	kind;
}					t_token;

//--------------------[AST]----------------------------

typedef enum e_ast_type
{
	HEREDOC, // <<
	IN,      // <
	PIPE,    // |
	OUT,     // > | >>
	AND,     // &&
	OR,      // ||
	NORMAL,
}					t_ast_type;

// typedef struct s_node
// {
// 	struct s_node	kind;
// 	struct s_ast	*next;

// 	union
// 	{
// 		char		*del;
// 		char		*input;

// 		struct
// 		{
// 			char	*output;
// 			bool	override;
// 		};
// 		struct
// 		{
// 			char	*name;
// 			char	**args;
// 		};
// 	};
// }					t_node;

typedef struct s_ast
{
	t_ast_type		kind;
	struct s_ast	*next;
}					t_ast;

typedef struct s_ast_pipe
{
	t_ast_type kind; // PIPE | '|'
	struct s_ast	*next;
}					t_ast_pipe;

typedef struct s_ast_and
{
	t_ast_type kind; // AND | '&&'
	struct s_ast	*next;
}					t_ast_and;

typedef struct s_ast_or
{
	t_ast_type kind; // OR | '||'
	struct s_ast	*next;
}					t_ast_or;

typedef struct s_ast_heredoc
{
	t_ast_type kind; // HEREDOC | '<<'
	struct s_ast	*next;
	char			*del;
}					t_ast_heredoc;

typedef struct s_ast_in
{
	t_ast_type kind; // IN | '<'
	struct s_ast	*next;
	char			*input;
}					t_ast_in;

typedef struct s_ast_out
{
	t_ast_type kind; // OUT | ('>' | '>>')
	struct s_ast	*next;
	char			*output;
	bool			overwrite;
}					t_ast_out;

typedef struct s_ast_normal
{
	t_ast_type kind; // NORMAL | anything other
	struct s_ast	*next;
	char			*name;
	char			**args;
}					t_ast_normal;

#endif
