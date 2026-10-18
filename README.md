
### Project structure

Each platform have its **own folder** in the src. Put your platform's code and platform-specific modules inside that folder.

A platform folder should contain:
- A **platform-specific main file** containing the logic for that platform.
- A module representing the **complete platform**, built from `GenericPlatform` plus any additional platform-specific modules.
- A separate folder for each module used by that platform, with that module's `.h` and `.cpp` files.

##### Every module needs a `begin()` function

Each module must provide a `begin()` function to initialize itself and construct/initialize its submodules as needed.

Typical pattern:

```cpp
void ExampleModule::begin() {
    subModuleA.begin();
    subModuleB.begin();
}
```

Call each submodule's `begin()` from the parent module's `begin()` so initialization flows from the top-level platform down through its components.

##### Keep a separate `main` file for each platform

Every platform must have its **own main file** containing all logic specific to that platform, such as its setup sequence, control loop, and coordination of its modules.

Keep Platform A's main file under `src/PlatformA/`, Platform B's under `src/PlatformB/`, and so on.

### Do not copy your platform's main file directly into `src/`

Instead:

1. Keep your platform's main file in that platform's folder.
2. Before building, identify the platform you want to build.
3. Replace the active `src/main.cpp` with the chosen platform's main file (copy it or move it into place).
4. Check whether other main files under `src/` would also be compiled. If they are obsolete or duplicate active entry points, exclude them from the build or delete them only if no longer needed. Keep the platform-specific copies in their platform folders.



## Questions and guidance

When you have a question about code structure or implementation:

1. First check the existing `GenericPlatform` code for the project's established structure and conventions.
2. If the answer is unclear, ask **Max** for guidance before introducing a different architecture or changing shared code.
