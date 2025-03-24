#ifndef PROVIDER_EXAMPLE_H
#define PROVIDER_EXAMPLE_H

#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {

class ProviderExample : public RefCounted {
    GDCLASS(ProviderExample, RefCounted)

private:
    int _value;

protected:
    static void _bind_methods();

public:
    void set_value(int p_value);
    int get_value() const;
    int double_value() const;

    ProviderExample();
};

}  // namespace godot
#endif // PROVIDER_EXAMPLE_H