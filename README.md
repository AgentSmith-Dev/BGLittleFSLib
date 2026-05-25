Baiscally a C++ Wrapper for LittleFS

# Requirements
Needs github repro littlefs from Arm

# To implement hardware related filesystem

- derive your own class from `clAGS_LittleFS`
- Overwrite pure virtual functions: `iRead(), iProg(), iErase(), iSync`
