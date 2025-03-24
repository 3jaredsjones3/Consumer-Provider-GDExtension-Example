#ifndef PROVIDER_REGISTER_TYPES_H
#define PROVIDER_REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void initialize_provider_example_module(ModuleInitializationLevel p_level);
void uninitialize_provider_example_module(ModuleInitializationLevel p_level);

#endif // PROVIDER_REGISTER_TYPES_H