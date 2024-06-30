project('raytracer_project', 'cpp', default_options: ['cpp_std=c++20'])

# Extra include directories
inc_dir = include_directories('libs/json/include')

# Define executable name and source files
main_executable = 'main'
source_files = [
    'raytracer/main.cpp',
    'raytracer/vec3.cpp',
    'raytracer/scene.cpp',
    'raytracer/camera.cpp',
    'raytracer/materials.cpp',
    'raytracer/random.cpp',
]

# Create an executable
executable(main_executable, source_files, include_directories: inc_dir)
