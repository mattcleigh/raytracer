project('raytracer_project', 'cpp', default_options: ['cpp_std=c++20'])

# Extra include directories
inc_dir = include_directories('../libs/json/include')

# Define executable name and source files
main_executable = 'main'
source_files = [
    'csrc/camera.cpp',
    'csrc/factory.cpp',
    'csrc/float3.cpp',
    'csrc/main.cpp',
    'csrc/materials.cpp',
    'csrc/random.cpp',
    'csrc/scene.cpp',
]

# Create an executable
executable(main_executable, source_files, include_directories: inc_dir)
