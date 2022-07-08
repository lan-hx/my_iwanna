# my_iwanna

浙江大学2022短学期C++项目管理及工程实践课程作业

小组：i wanna be the guy复刻

## 编译指南：

如有任何问题，可参见github CI文件：.github/workflows/cmake.yml

1. master分支（不带测试）：

cmake编译时需指定QT库文件所在位置，设置QT_PREFIX_DIR变量。

例：
``` cmake
cmake -G Ninja -B build -DQT_PREFIX_DIR=C:/Qt/5.15.2/mingw81_64
cd build
cmake --build . --target iwanna
```

2. test分支（带测试，编译速度极慢，因为要编译gtest库）：

需要增加指定vcpkg包管理器路径，或者自己设定工具链。

例：
``` cmake
cmake -G Ninja -B build -DQT_PREFIX_DIR=C:/Qt/5.15.2/mingw81_64 -DVCPKG_DIR=vcpkg -DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic
cd build
cmake --build . --target iwanna_test
```

其中triplet根据编译器自行指定，msvc建议使用`x64-windows`
