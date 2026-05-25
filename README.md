Basically a C++ Wrapper for LittleFS

# Requirements
[Needs github repro littlefs from Arm](https://github.com/littlefs-project/littlefs.git).
Your project needs to add `ltfs_util.c` and `lfs.c`

# To implement hardware related filesystem

- derive your own class from `clAGS_LittleFS`
- Overwrite pure virtual functions: `iRead(), iProg(), iErase(), iSync`
