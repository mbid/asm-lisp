#ifndef COMPILE_MACRO_ERROR_HPP_
#define COMPILE_MACRO_ERROR_HPP_

#include "error_utils.hpp"
#include "compile_exception.hpp"

namespace compile_macro_error
{

constexpr std::pair<conststr, conststr> dictionary[] =
{
    {"invalid_argument_number", ""},
    {"invalid_param_list", ""},
    {"invalid_return_type", ""},
    {"invalid_body", ""},
    {"invalid_parameter_declaration", ""},
    {"invalid_parameter_declaration_node_number", ""},
    {"invalid_parameter_name", ""},
    {"invalid_parameter_type", ""},
    {"duplicate_parameter_name", ""},
    {"invalid_block_list", ""},
    {"empty_body", ""},
    {"duplicate_variable_name", ""},
    {"duplicate_block_name", ""},
    {"invalid_block_definition", ""},
    {"invalid_block_definition_argument_number", ""},
    {"empty_instruction", ""},
    {"invalid_instruction_constructor", ""},
    {"unknown_instruction_constructor", ""},
    {"instruction_constructor_invalid_argument_number", "invalid number of arguments to instruction constructor \'{0}\': expected {1}, got {2}"},
    {"invalid_instruction_type_parameter", ""},
    {"invalid_number_type", ""},
    {"invalid_comparison_kind", ""},
    {"unknown_comparison_kind", ""},
    {"invalid_block_name", ""},
    {"invalid_block_body", ""},
    {"empty_statement", ""},
    {"let_invalid_argument_number", ""},
    {"invalid_variable_name", ""},
    {"invalid_statement", ""},
    {"missing_variable_name", ""},
    {"missing_instruction", ""},
    {"locally_duplicate_variable_name", ""},
    {"invalid_instruction_call_argument_number", "invalid number of arguments for instruction '{0}': expected '{1}', got '{2}'"},
    {"variable_undefined", ""},
    {"variable_type_mismatch", ""},
    {"invalid_literal_for_type", ""},
    {"invalid_integer_constant", ""},
    {"out_of_range_integer_constant", ""},
    {"invalid_value", ""},
    {"condbr_invalid_block_name", ""},
    {"block_not_found", ""},
    {"branch_to_entry_block", ""}
};

constexpr std::size_t id(conststr str)
{
    return id(str, dictionary);
}

template<std::size_t error_id, class Location, class... ParamTypes>
[[ noreturn ]] void fatal(Location location, ParamTypes&&... params)
{
    static_assert(error_id < size(dictionary), "invalid error id");
    static_assert(error_id != std::numeric_limits<std::size_t>::max(), "invalid error id");
    throw compile_exception{error_kind::COMPILE_MACRO, error_id, location, std::forward<ParamTypes>(params)...};
}

}

#endif

