add_executable(game
    main.cpp
)

target_compile_features(game PUBLIC cxx_std_23)
target_compile_options(game PUBLIC /W4 /WX)