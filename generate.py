import os
import subprocess
import sys

root_directory = os.getcwd()
bldcfg = sys.argv[1]

print("Building bcrypt")
subprocess.call("python3 scripts/buildBcrypt.py {}".format(bldcfg), shell=True)

print("Building rpclib")
subprocess.call("python3 scripts/buildRpclib.py {}".format(bldcfg), shell=True)

print("Building Spdlog")
subprocess.call("python3 scripts/buildSpdlog.py {}".format(bldcfg), shell=True)

print("Building Yaml-Cpp")
subprocess.call("python3 scripts/buildYamlCpp.py {}".format(bldcfg), shell=True)

print("Generating AuroraStory solution")
subprocess.call("python3 scripts/generateSolution.py", shell=True)

print("Building AuroraStory solution")
subprocess.call("python3 scripts/buildSolution.py {}".format(bldcfg), shell=True)