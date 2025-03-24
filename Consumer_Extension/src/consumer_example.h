#ifndef CONSUMER_EXAMPLE_H
#define CONSUMER_EXAMPLE_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {

class ConsumerExample : public Node {
    GDCLASS(ConsumerExample, Node)

private:
    Ref<RefCounted> _provider; // We use RefCounted as the base type, not the specific ProviderExample

protected:
    static void _bind_methods();

public:
    void set_provider(const Ref<RefCounted>& provider);
    Ref<RefCounted> get_provider() const;
    
    // Process value: doubles using provider then subtracts 5
    int process_value(int value) const;
    
    ConsumerExample();
};

}  // namespace godot
#endif // CONSUMER_EXAMPLE_H