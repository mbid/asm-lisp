#include "compile_type.hpp"

#include "error/compile_type_error.hpp"

#include <llvm/IR/DerivedTypes.h>

#include <boost/variant.hpp>

#include <string>
#include <algorithm>

using std::size_t;
using std::string;
using std::stoul;
using std::out_of_range;
using std::invalid_argument;
using std::distance;

using boost::blank;

using namespace symbol_shortcuts;
using namespace compile_type_error;

type_symbol compile_int(list_symbol::const_iterator begin, list_symbol::const_iterator end, compilation_context& context)
{
    if(distance(begin, end) != 1)
        fatal<id("int_invalid_argument_number")>(blank());

    const lit_symbol& bit_width_lit = begin->cast_else<lit_symbol>([&]()
    {
        fatal<id("int_invalid_argument_symbol")>(begin->source());
    });

    unsigned long width;
    try
    {
        size_t index_after;
        string as_str{bit_width_lit.begin(), bit_width_lit.end()};
        width = stoul(as_str, &index_after);
        if(index_after != as_str.size())
            throw invalid_argument{""};
        if(width == 0 || width > 1024) // TODO: be less conservative
            throw out_of_range{""};
    }
    catch(const invalid_argument&)
    {
        fatal<id("int_invalid_argument_literal")>(bit_width_lit.source());
    }
    catch(const out_of_range&)
    {
        fatal<id("int_out_of_range_bit_width")>(bit_width_lit.source());
    }

    llvm::IntegerType* llvm_type = llvm::IntegerType::get(context.llvm(), width);
    return type{llvm_type};
}

type_symbol compile_struct(list_symbol::const_iterator begin, list_symbol::const_iterator end,
        compilation_context& context);