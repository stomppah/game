This is an implementation of OpenGL from scratch following Nathan Baggs' stream "int main(){} to game".

I update the code at least once weekly as I progress through the live streams.

This is more of a practice environment for me to learn C++, so don't expect any fantastic features :)

## Testing

When running tests for this project, you need to specify the build configuration using the `-C` flag with CTest:

```
cd build
ctest -C Debug
```

Without specifying a configuration, CTest will fail with an error like "Test not available without configuration". Always use the `-C` flag followed by the desired configuration (Debug, Release, MinSizeRel, or RelWithDebInfo).

![image](/Screenshot%202025-04-04%20225217.png)
