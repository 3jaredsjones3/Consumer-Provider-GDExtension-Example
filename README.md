# Godot 4 Compute Shader GDExtension Template

A minimal template for implementing compute shaders in a GDExtension for Godot 4.

This repository serves as both a template and a reference for developers looking to implement GPU compute functionality in their Godot 4 projects using GDExtension. It demonstrates how to properly initialize a compute shader, process data with it, and retrieve the results back in GDScript.

## Features

- Minimal implementation of a compute shader in GDExtension
- Support for both built-in and external shader files
- Compute mode selector to switch between approaches
- Detailed error reporting and debugging
- Example of how to process array data with the GPU

## Requirements

- Godot 4.x (tested with Godot 4.4 stable)
- C++ compiler compatible with your platform
- GPU with Vulkan support
- SCons build system

## Project Structure

- `src/` - C++ source files
  - `basic_compute_example.h` - Header with class definitions
  - `basic_compute_example.cpp` - Implementation of the compute shader functionality
  - `register_types.cpp/h` - Registration of GDExtension types
- `compute.glsl` - Example compute shader file
- `gdextension/` - GDExtension configuration files
- `testing_basic_compute.gd` - GDScript test file

## Using as a Template

This repository is designed to be used as a template for your own compute shader GDExtension projects. Here's how to get started:

### Creating a New Repository from This Template

1. Click the "Use this template" button at the top of the GitHub repository page
2. Choose a name for your new repository
3. Clone your new repository locally

### Customizing the Template for Your Project

1. Rename the class in the source files from `BasicComputeExample` to your preferred name
2. Update the shader code to implement your specific computation needs
3. Modify the GDExtension registration to use your new class names
4. Update the `.gdextension` file to reflect your project name
5. Adjust the build files as needed for your specific project requirements

### Key Files to Modify

- `src/basic_compute_example.h` and `.cpp` → Rename and customize
- `src/register_types.cpp` and `.h` → Update with your class name
- `basic_compute_example.gdextension` → Rename and update entry point
- `compute.glsl` → Replace with your shader code
- `SConstruct` → Update library name and build parameters

## Setup and Build

1. Clone this repository and its submodules:
   ```
   git clone --recursive https://github.com/yourusername/godot-compute-shader-gdextension.git
   ```

2. If you didn't clone with `--recursive`, initialize and update the godot-cpp submodule:
   ```
   git submodule update --init --recursive
   ```

3. Build the GDExtension:
   ```
   scons target=template_debug
   ```
   or for release:
   ```
   scons target=template_release
   ```

4. The compiled library will be placed in the `bin/` directory.

## Usage

1. Import the GDExtension folder into your Godot project
2. Create an instance of the `BasicComputeExample` class in your GDScript:

```gdscript
var compute_example = BasicComputeExample.new()

# Choose compute mode (0 = built-in, 1 = external shader file)
compute_example.set_compute_mode(0) # Using built-in shader

# Initialize the shader
var success = compute_example.initialize_shader()
if not success:
    print("Shader initialization failed!")
    return

# Process data with compute shader
var input_data = PackedFloat32Array([1.0, 2.0, 3.0, 4.0, 5.0])
var input_bytes = PackedByteArray()
input_bytes.resize(input_data.size() * 4)  # 4 bytes per float

for i in range(input_data.size()):
    input_bytes.encode_float(i * 4, input_data[i])

var output_bytes = compute_example.process_data(input_bytes)

# Convert results back to floats
var output_data = PackedFloat32Array()
output_data.resize(output_bytes.size() / 4)

for i in range(output_data.size()):
    output_data[i] = output_bytes.decode_float(i * 4)

print("Result:", output_data)
```

## Common Pitfalls and Troubleshooting

### IMPORTANT: GLSL Syntax for GDExtension Compute Shaders

When creating compute shaders for use with GDExtension and the RenderingDevice API, there are crucial syntax differences compared to Godot's built-in shader system:

1. **DO NOT use the `#[compute]` directive**. This is specific to Godot's shader preprocessing system and will cause compilation errors when used with RenderingDevice.

2. **The `#version 450` statement must be the first line** of your GLSL shader file.

#### Incorrect (Will Not Work):
```glsl
#[compute]
#version 450

layout(local_size_x = 64, local_size_y = 1, local_size_z = 1) in;
// Rest of shader...
```

#### Correct (Will Work):
```glsl
#version 450

layout(local_size_x = 64, local_size_y = 1, local_size_z = 1) in;
// Rest of shader...
```

### Other Common Issues:

1. **Shader initialization fails**: Ensure your GPU supports Vulkan and compute shaders.

2. **Compute pipeline creation errors**: Check the shader syntax carefully and make sure all bindings are correct.

3. **Buffer size issues**: Make sure your buffer sizes are correctly calculated, especially with vector types.

4. **Type conversion errors**: Pay attention to the explicit type casting in C++, especially when working with RenderingDevice API.

5. **No changes to data**: Ensure that your compute shader is actually modifying the data and the buffer access is correct.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- The Godot Engine community
- Contributors to the Godot GDExtension system
- Anyone who provides feedback and improvements to this example

## Template Benefits

Using this template for your compute shader projects provides several advantages:

1. **Correct structure from the start**: Avoid common setup pitfalls with GDExtension
2. **Working compute shader implementation**: Start with a functioning shader pipeline
3. **Error handling**: The template includes robust error reporting and handling
4. **Best practices**: Follow established patterns for GDExtension development
5. **Save development time**: Focus on your specific computation logic rather than boilerplate

## Template Limitations

Be aware of these limitations when using this template:

1. **Basic implementation only**: The template provides minimal functionality to keep it clean and understandable
2. **Single compute shader**: You may need to extend the design for multiple shaders
3. **Simple data types**: The example only handles basic float arrays
4. **No texture support**: If you need texture input/output, you'll need to extend the implementation

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the project
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request
