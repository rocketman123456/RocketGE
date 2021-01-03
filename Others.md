# RocketGE<br>
If you want to run this program, run `git clone https://github.com/microsoft/vcpkg.git` to install vcpkg, then install required libraries through vcpkg, and change VCPKG_ROOT in CMakeLists.txt.<br>
macos<br>
```
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/developer/Program/vcpkg/scripts/buildsystems/vcpkg.cmake ..
```
linux<br>
```
cmake -DCMAKE_TOOLCHAIN_FILE=/home/developer/Program/vcpkg/scripts/buildsystems/vcpkg.cmake ..
```
Mainly Following Hazel Video Series and 从零开始手敲次世代游戏引擎 <br>
## Main Loop <br>
1。输入管理模块，用来获取用户输入 <br>
2。策略模块，用来执行策略 <br>
3。场景管理模块，用来管理场景和更新场景 <br>
4。渲染模块，用来执行渲染和画面输出 <br>
5。音频音效模块，用来管理声音，混音和播放 <br>
6。网络通信模块，用来管理网络通信 <br>
7。文件I/O模块，用来管理资源的加载和参数的保存回复 <br>
8。内存管理模块，用来调度管理内存上的资源 <br>
9。驱动模块，用来根据时间，事件等驱动其它模块 <br>
10。辅助模块，用来执行调试，log输出等辅助功能 <br>
11。应用程序模块，用来抽象处理配置文件，特定平台的通知，创建窗口等需要与特定平台对接的部分 <br>

## Game Engine Work flow <br>

1.我们首先需要一个建立一个跨平台的模块，它能够在不同的操作系统+图形API环境当中，为我们创建这个基本的上下文。（可能是窗口，可能是全屏FrameBuffer，也可能是Off Screen Buffer）<br>
2.然后，我们需要对平台的硬件能力进行查询和遍历，找到平台硬件（这里特指GPU）所能够支持的画布格式，并且将1所创建的上下文的FrameBuffer格式指定为这个格式，GPU才能够在上面作画。<br>
3.CPU使用平台所支持的图形API创建绘图所需要的各种Heap/Buffer/View，生成资源描述子（RootSignature或者Descriptor），将各种资源的元数据（Meta Data)填入描述子，并传递给GPU <br>
4.CPU根据场景描述信息进行顶点数据/索引/贴图/Shader等的加载，并将其展开在GPU所能看到的（也就是在描述子里面登记过的）Buffer当中
帧循环开始 <br>
5.CPU读取用户输入（在之前的文章当中还未涉及），并更新用户可操作场景物体的位置和状态 <br>
6.CPU执行游戏逻辑（包括动画、AI），并更新对应物体的位置和状态 <br>
7.CPU进行物体的裁剪，找出需要绘制的物体（可见的物体）<br>
8.CPU将可见物体的位置和状态翻译成为常量，并把常量上传到GPU可见的常量缓冲区 <br>
9.CPU生成记录GPU绘图指令的Buffer （CommandList），并记录绘图指令 <br>
10.CPU创建Fence，以及相关的Event，进行CPU和GPU之间的同步 <br>
11.CPU提交记录了绘图指令的Buffer（CommandList），然后等待GPU完成绘制（通过观察Fence）<br>
12.CPU提交绘制结果，要求显示（Flip或者Present）<br>
13.帧循环结束 <br>

## Entity-Component-System<br>
一个实体只包含了一个ID值和一个组件集合。实体并不包含任何可执行的代码。组件集合也不必和实体ID值存储在一起。但应该设计使组件集合的访问效率尽可能高。虽然，每个实体使用不同的ID值不是必须的，但这样做有下面这些优点：<br>
1.实体可以直接使用ID值引用，避免使用指针。<br
2.方便进行持久化，避免读取数据时，重建指针。<br>
3.数据可以在内存中更加自由地存放。<br>
4.实体ID经过设计可以跨网络使用。<br>
上面的部分优点也可以通过智能指针达到。<br>
## Resources <br>
```
Online Tools
https://code2flow.com/app

C++
http://en.cppreference.com/w/
http://www.cplusplus.com/
http://www.learncpp.com/
https://isocpp.org/wiki/faq/
https://www.youtube.com/user/CppCon/featured
https://sourceforge.net/p/predef/wiki/OperatingSystems/
https://godbolt.org/
https://cppinsights.io/
http://graphics.stanford.edu/~seander/bithacks.html
https://github.com/AnthonyCalandra/modern-cpp-features

C#
https://youtu.be/FID9sDXmCoQ

Graphics Theoretics
https://paroj.github.io/gltut/index.html

Graphics Debugging
https://renderdoc.org/
https://gpuopen.com/compute-product/codexl/
https://gpuopen.com/archive/gpu-perfstudio/

OpenGL
http://docs.gl/
https://www.khronos.org/opengl/wiki/
http://www.opengl-tutorial.org/
https://learnopengl.com/
http://ogldev.atspace.co.uk/
http://nehe.gamedev.net/
https://open.gl/

DirectX
http://www.rastertek.com/
http://www.directxtutorial.com/
https://msdn.microsoft.com/en-us/library/windows/desktop/dn899121(v=vs.85).aspx
https://digitalerr0r.wordpress.com/2015/08/19/quickstart-directx-12-programming/
https://www.3dgep.com/

Vulkan
https://vulkan-tutorial.com/
https://www.khronos.org/registry/vulkan/specs/1.2/html/vkspec.html

Metal
https://www.youtube.com/watch?v=PcA-VAybgIQ&list=PLEXt1-oJUa4BVgjZt9tK2MhV_DW7PVDsg

Game Engines
https://google.github.io/filament/Filament.md.html

Math
https://www.youtube.com/playlist?list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab
https://www.youtube.com/playlist?list=PL7wAPgl1JVvUEb0dIygHzO4698tmcwLk9
https://ocw.mit.edu/courses/mathematics/18-06-linear-algebra-spring-2010/index.htm
http://www.euclideanspace.com/
https://eater.net/quaternions
https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/
E-Books
https://github.com/EbookFoundation/free-programming-books/blob/master/free-programming-books.md
https://www.packtpub.com/packt/offers/free-learning

General
https://github.com/mr-mig/every-programmer-should-know
https://ideone.com/
https://code.sololearn.com/

Programming Patterns
https://gafferongames.com/post/fix_your_timestep/
https://dewitters.com/dewitters-gameloop/
http://gameprogrammingpatterns.com/
https://refactoring.guru/design-patterns/catalog

Game Design
https://vitalzigns.itch.io/gdd
https://www.youtube.com/user/McBacon1337

Free Assets
https://hdrihaven.com/
https://texturehaven.com/
https://3dmodelhaven.com/
https://www.wildtextures.com/
https://www.textures.com/
https://poly.google.com/
https://kenney.nl/

Rich Presences
Visual Studio (2017): https://marketplace.visualstudio.com/items?itemName=swanzana.discord-rpc-vs
Visual Studio (2019): https://marketplace.visualstudio.com/items?itemName=VisualDevelopment.drpcvs2019
Visual Studio Code: https://marketplace.visualstudio.com/items?itemName=icrawl.discord-vscode
```