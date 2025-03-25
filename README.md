# Consumer-Provider GDExtension Example

This repository demonstrates how to create two separate GDExtensions in Godot 4 that work together through a provider-consumer relationship, without needing direct compile-time dependencies.

## Overview

In this example:

- **Provider GDExtension**: Implements a simple class that can store and double a value
- **Consumer GDExtension**: References the Provider to process values (doubles them and subtracts 5)

This shows how GDExtensions can be compiled separately but work together at runtime - a powerful pattern for creating modular C++ components in Godot.

## Key Lessons Learned

1. **Separate Compilation Works**: GDExtensions can be compiled independently without including each other's headers.

2. **Runtime Dependency Resolution**: Dependencies between GDExtensions are established at runtime in Godot, not at compile time.

3. **Using Generic Base Classes**: Using `RefCounted` instead of specific class types allows for flexible interface design.

4. **Dynamic Method Calls**: Use Godot's `call()` method with `Array` parameters to dynamically invoke methods on objects from other extensions.

5. **No Comments in .gdextension Files**: We discovered that comments in `.gdextension` files (at least those using `#`) can cause Godot to fail to find the DLL files. **Avoid comments in .gdextension files**.

6. **Entry Symbol Naming**: Make sure the entry symbol in your `.gdextension` file matches the function name in your C++ code exactly.

7. **File Structure**: The relative paths in the `.gdextension` file must match the actual file structure.

## Repository Structure

```
/Provider Extension/
  /src/                           # Provider source files
    provider_example.h            # Header for Provider class
    provider_example.cpp          # Implementation of Provider class
    register_types.h              # Header for registering Provider with Godot
    register_types.cpp            # Implementation for registering Provider with Godot
  /godot-cpp/                     # Godot C++ bindings (submodule)
  /demo/                          # Demo project to test the Provider
    /bin/
      provider_example.gdextension # GDExtension definition file
      /windows/                   # Compiled binaries for Windows
        libProviderExample.windows.template_debug.x86_64.dll

/Consumer Extension/
  /src/                           # Consumer source files
    consumer_example.h            # Header for Consumer class
    consumer_example.cpp          # Implementation of Consumer class  
    register_types.h              # Header for registering Consumer with Godot
    register_types.cpp            # Implementation for registering Consumer with Godot
  /godot-cpp/                     # Godot C++ bindings (submodule)
  /demo/                          # Demo project to test the Consumer
    /bin/
      consumer_example.gdextension # GDExtension definition file with dependency on Provider
      /windows/                   # Compiled binaries for Windows
        libConsumerExample.windows.template_debug.x86_64.dll

/Godot Project/                   # The actual Godot project using both extensions
  /gdextension/                   # Directory for GDExtensions
    provider_example.gdextension  # Copy of the Provider's .gdextension file
    consumer_example.gdextension  # Copy of the Consumer's .gdextension file
    /windows/                     # Directory for Windows binaries
      libProviderExample.windows.template_debug.x86_64.dll
      libConsumerExample.windows.template_debug.x86_64.dll
```

## Example Usage

```gdscript
extends Node

func _ready():
    # Check if both extensions loaded properly
    if ClassDB.class_exists("ProviderExample") and ClassDB.class_exists("ConsumerExample"):
        # Create a provider instance
        var provider = ProviderExample.new()
        
        # Create a consumer instance
        var consumer = ConsumerExample.new()
        add_child(consumer)
        
        # Set the provider on the consumer
        consumer.provider = provider
        
        # Process a value using the consumer
        # This will double the value (5 * 2 = 10) then subtract 5 (10 - 5 = 5)
        var result = consumer.process_value(5)
        print("Result: ", result)  # Should print 5
    else:
        push_error("Failed to load one or both extensions!")
```

## Creating Your Own Provider-Consumer Extensions

1. Set up each GDExtension project separately, following the structure above.

2. In the consumer's `.gdextension` file, specify the dependency:
   ```
   [dependencies]
   provider_example = "*"  # Any version
   ```

3. In the consumer, use the generic `RefCounted` type instead of specific provider types:
   ```cpp
   private:
       Ref<RefCounted> _provider; // Generic reference
   ```

4. Use dynamic method calls to interact with the provider:
   ```cpp
   Array args;
   args.push_back(value);
   _provider->call("set_value", args);
   
   Variant result = _provider->call("double_value");
   ```

## Common Issues and Solutions

1. **Symbol Not Found**: Make sure the entry_symbol in your `.gdextension` file matches your C++ function name.

2. **DLL Not Found**: Double-check paths in the `.gdextension` file against your file structure.

3. **Unresolved External Symbols**: Ensure you've implemented all methods declared in your headers.

4. **Missing Dependencies**: Ensure both extensions are properly placed in the Godot project.

5. **Comments Breaking .gdextension**: Do not include comments in `.gdextension` files as they can interfere with Godot's ability to find the DLL files.

## Extending Further

This simple example demonstrates the concept of GDExtension dependencies. You can apply this pattern to create more complex relationships such as:

- Multiple specialized consumers of a common data provider
- Layered extensions where one extension enhances another
- Plugin systems where core functionality can be extended

Each component remains separately compiled and modular, making your project easier to maintain and extend.
