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
:: cd AuroraMapleLib/vendor/yaml-cpp
:: if not exist build\ (
::     mkdir build
:: )
:: cd build
:: cmake ..
:: cmake --build . --target ALL_BUILD --config Debug
:: cmake --build . --target ALL_BUILD --config Release
:: cd ../../../../



:: Compile CryptoPP with MSBuild for Windows | Other platforms to come later
cd MapleLib/vendor/cryptopp
if not exist x64\Output\Debug (
    MSBuild cryptlib.vcxproj /p:Configuration=Debug /p:Platform=x64
)
if not exist x64\Output\Release (
    MSBuild cryptlib.vcxproj /p:Configuration=Release /p:Platform=x64
)
cd ../../../