# SSH Client

This is a simple SSH client that uses the libssh library.

## Dependencies

- CMake (version 3.0.0 or later)
- libssh (version 0.8.6 or later)
- A C++11 compiler

## Building the Code

To build the code, follow these steps:

1. Install the required dependencies.
   - On Windows: Use [vcpkg](https://github.com/microsoft/vcpkg) to install libssh. Set `CMAKE_TOOLCHAIN_FILE` and `VCPKG_TARGET_TRIPLET` appropriately.
   - On Linux: Use your package manager to install libssh and its development headers.

2. Create a build directory and navigate into it:
   
   ```
   mkdir build
   cd build
   ```

3. Configure the build with CMake:

   ```
   cmake ..
   ```

   If you need to specify a specific version or installation path for libssh, you can use the following options:

   ```
   cmake .. -DLibSSH_ROOT=/path/to/libssh
   ```

4. Build the code:

   ```
   cmake --build .
   ```

5. Run the `ssh-client` binary:

   ```
   ./ssh-client
   ```

## Notes

- This example is for demonstration purposes only, and should not be used for production environments.
- Always use secure methods of storing sensitive data like passwords. The example uses hard-coded values for the sake of simplicity, but in practice, you should avoid hard-coding passwords in your code.