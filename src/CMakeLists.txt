add_executable(game
    exception.cpp
    main.cpp
    material.cpp
    mesh.cpp
    shader.cpp
    window.cpp
)

target_include_directories(game PUBLIC ${PROJECT_SOURCE_DIR}/third-party/opengl)
target_compile_features(game PUBLIC cxx_std_23)
target_compile_definitions(game PUBLIC -DNOMINMAX)
target_compile_options(game PUBLIC /W4 /WX )# /Debug /Od /Z7
