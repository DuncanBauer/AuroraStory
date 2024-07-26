import os
import subprocess
import sys

root_directory = os.getcwd()
bldcfg = sys.argv[1]

# Move to yaml-cpp build directory
os.chdir("vendor/yaml-cpp")
if not os.path.exists("build"):
    os.mkdir("build")
os.chdir("build")

# Build yaml-cpp libraries
subprocess.run(["cmake", "-DYAML_BUILD_SHARED_LIBS=OFF", "-DCMAKE_BUILD_TYPE={}".format(bldcfg), ".."])
subprocess.run(["cmake", "--build", ".", "--config", "{}".format(bldcfg)])

# Return to root directory
os.chdir(root_directory)