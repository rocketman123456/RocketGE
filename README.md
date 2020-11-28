# RocketGE

Following Hazel Video Series

If you want to run this program
run `git clone https://github.com/microsoft/vcpkg.git` to instaall vcpkg
install spdlog, glfw, yaml-cpp and eigen3 through vcpkg
change VCPKG_ROOT in CMakeLists.txt
and every thing should be fine

macos
`cmake -DCMAKE_TOOLCHAIN_FILE=/Users/developer/Program/vcpkg/scripts/buildsystems/vcpkg.cmake ..`

1。输入管理模块，用来获取用户输入

2。策略模块，用来执行策略

3。场景管理模块，用来管理场景和更新场景

4。渲染模块，用来执行渲染和画面输出

5。音频音效模块，用来管理声音，混音和播放

6。网络通信模块，用来管理网络通信

7。文件I/O模块，用来管理资源的加载和参数的保存回复

8。内存管理模块，用来调度管理内存上的资源

9。驱动模块，用来根据时间，事件等驱动其它模块

10。辅助模块，用来执行调试，log输出等辅助功能

11。应用程序模块，用来抽象处理配置文件，特定平台的通知，创建窗口等需要与特定平台对接的部分