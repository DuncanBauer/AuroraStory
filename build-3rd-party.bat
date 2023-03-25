:: :: Compile spdlog with CMake
:: cd AuroraMapleLib/vendor/spdlog
:: if not exist build\ (
::     mkdir build
:: )
:: cd build
:: cmake ..
:: cmake --build . --target ALL_BUILD --config Debug
:: cmake --build . --target ALL_BUILD --config Release
:: cd ../../../../



:: :: Compile yaml-cpp with CMake
cd MapleServer/vendor/yaml-cpp
if not exist build\ (
    mkdir build
)
cd build
cmake ..
cmake --build . --target ALL_BUILD --config Debug
cmake --build . --target ALL_BUILD --config Release
cd ../../../../




:: Compile lz4 with MSBuild for Windows | Other platforms to come later
cd MapleLib/vendor/lz4/build/VS2022/liblz4

MSBuild liblz4.vcxproj /p:Configuration=Debug /p:Platform=x64
MSBuild liblz4.vcxproj /p:Configuration=Release /p:Platform=x64

cd ../../../../../../