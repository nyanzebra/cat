#pragma once

#include "ast_visitors.hpp"
#include "operators.hpp"


#include "ast/ast_arm.hpp"
#include "ast/ast_expression.hpp"
#include "ast/ast_meta_class.hpp"
#include "ast/ast_program.hpp"
#include "ast/ast_type.hpp"
#include "ast/ast_assembly.hpp"
#include "ast/ast_function.hpp"
#include "ast/ast_meta_interface.hpp"
#include "ast/ast_range.hpp"
#include "ast/ast_unary_operator.hpp"
#include "ast/ast_binary_operator.hpp"
#include "ast/ast_function_call.hpp"
#include "ast/ast_node.hpp"
#include "ast/ast_sequence.hpp"
#include "ast/ast_variable.hpp"
#include "ast/ast_block.hpp"
#include "ast/ast_function_prototype.hpp"
#include "ast/ast_pattern.hpp"
#include "ast/ast_template.hpp"

#include "ast/modifiers.hpp"

#include "utility/enum.hpp"

namespace syntax {

// flows
class ast_while_loop;
class ast_for_loop;
class ast_if_block;
class ast_else_block;

class ast_module;


} // namespace syntax
