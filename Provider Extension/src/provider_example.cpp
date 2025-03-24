#include "provider_example.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void ProviderExample::_bind_methods() {
    // Register methods
    ClassDB::bind_method(D_METHOD("set_value", "value"), &ProviderExample::set_value);
    ClassDB::bind_method(D_METHOD("get_value"), &ProviderExample::get_value);
    ClassDB::bind_method(D_METHOD("double_value"), &ProviderExample::double_value);

    // Register property
    ClassDB::add_property(
        "ProviderExample",
        PropertyInfo(Variant::INT, "value"),
        "set_value",
        "get_value"
    );
}

ProviderExample::ProviderExample() {
    // Initialize member variables
    _value = 0;
}

void ProviderExample::set_value(int p_value) {
    _value = p_value;
}

int ProviderExample::get_value() const {
    return _value;
}

int ProviderExample::double_value() const {
    return _value * 2;
}