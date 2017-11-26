#pragma once

#include "entity/entity.hpp"
#include "entity/class_entity.hpp"
#include "entity/interface_entity.hpp"
#include "entity/function_entity.hpp"
#include "entity/type_entity.hpp"
#include "entity/entity_modifiers.hpp"
#include "entity/variable_entity.hpp"

/*

Let's have sizeof(template) be a compile time check that returns number of args.
Let's have template[] be a compile time check that return type at index
templates should be able to take (template, typename, or integer_type)

*/

namespace cat {

type_entity_ptr make_auto_type() { return type_entity_ptr(new type_entity("auto", type::kAUTO)); }
type_entity_ptr make_void_type() { return type_entity_ptr(new type_entity("void", type::kVOID)); }
type_entity_ptr make_bool_type() { return type_entity_ptr(new type_entity("bool", type::kBOOL)); }
type_entity_ptr make_char_type() { return type_entity_ptr(new type_entity("char", type::kCHAR)); }
type_entity_ptr make_byte_type() { return type_entity_ptr(new type_entity("byte", type::kBYTE)); }
type_entity_ptr make_int8_type() { return type_entity_ptr(new type_entity("int8", type::kINT8)); }
type_entity_ptr make_int16_type() { return type_entity_ptr(new type_entity("int16", type::kINT16)); }
type_entity_ptr make_int32_type() { return type_entity_ptr(new type_entity("int32", type::kINT32)); }
type_entity_ptr make_int64_type() { return type_entity_ptr(new type_entity("int64", type::kINT64)); }
type_entity_ptr make_uint8_type() { return type_entity_ptr(new type_entity("uint8", type::kUINT8)); }
type_entity_ptr make_uint16_type() { return type_entity_ptr(new type_entity("uint16", type::kUINT16)); }
type_entity_ptr make_uint32_type() { return type_entity_ptr(new type_entity("uint32", type::kUINT32)); }
type_entity_ptr make_uint64_type() { return type_entity_ptr(new type_entity("uint64", type::kUINT64)); }
type_entity_ptr make_flt32_type() { return type_entity_ptr(new type_entity("flt32", type::kFLT32)); }
type_entity_ptr make_flt64_type() { return type_entity_ptr(new type_entity("flt64", type::kFLT64)); }
type_entity_ptr make_class_type(const std::string& name, const std::string& global_name) { return type_entity_ptr(new type_entity(name, global_name, type::kCLASS)); }
type_entity_ptr make_interface_type(const std::string& name, const std::string& global_name) { return type_entity_ptr(new type_entity(name, global_name, type::kINTERFACE)); }
type_entity_ptr make_nullptr_type() { return type_entity_ptr(new type_entity("nullptr", type::kAUTO)); }
type_entity_ptr make_function_type(const function_signature& signature) { return type_entity_ptr(new type_entity(signature)); }

}
