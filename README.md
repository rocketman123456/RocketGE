# RocketGE

Following Hazel Video Series

If you want to run this program
run `git clone https://github.com/microsoft/vcpkg.git` to instaall vcpkg
install spdlog, glfw, yaml-cpp and eigen3 through vcpkg
change VCPKG_ROOT in CMakeLists.txt
and every thing should be fine

macos
`cmake -DCMAKE_TOOLCHAIN_FILE=/Users/developer/Program/vcpkg/scripts/buildsystems/vcpkg.cmake ..`
