#include "consumer_example.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/array.hpp>

using namespace godot;

void ConsumerExample::_bind_methods() {
    // Register methods
    ClassDB::bind_method(D_METHOD("set_provider", "provider"), &ConsumerExample::set_provider);
    ClassDB::bind_method(D_METHOD("get_provider"), &ConsumerExample::get_provider);
    ClassDB::bind_method(D_METHOD("process_value", "value"), &ConsumerExample::process_value);

    // Register property
    ClassDB::add_property(
        "ConsumerExample",
        PropertyInfo(Variant::OBJECT, "provider", PROPERTY_HINT_RESOURCE_TYPE, "ProviderExample"),
        "set_provider",
        "get_provider"
    );
}

ConsumerExample::ConsumerExample() {
    // Initialize member variables correctly
    _provider = Ref<RefCounted>();
}

void ConsumerExample::set_provider(const Ref<RefCounted>& provider) {
    _provider = provider;
}

Ref<RefCounted> ConsumerExample::get_provider() const {
    return _provider;
}

int ConsumerExample::process_value(int value) const {
    if (_provider.is_null()) {
        UtilityFunctions::printerr("Provider not set!");
        return value; // Return original value if no provider
    }
    
    // Check if the provider has the necessary methods
    if (!_provider->has_method("set_value") || !_provider->has_method("double_value")) {
        UtilityFunctions::printerr("Provider does not have required methods!");
        return value;
    }
    
    // Call set_value on provider using call() method
    _provider->call("set_value", value);
    
    // Call double_value on provider
    Variant result = _provider->call("double_value");
    
    // Get result and subtract 5
    int doubled = result;
    return doubled - 5;
}