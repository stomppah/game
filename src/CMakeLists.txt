add_executable(game
    main.cpp
    window.cpp
)

target_compile_features(game PUBLIC cxx_std_23)
target_compile_definitions(game PUBLIC -DNOMINMAX)
target_compile_options(game PUBLIC /W4 /WX)