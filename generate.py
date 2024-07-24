import os
import subprocess
import sys

root_directory = os.getcwd()
bldcfg = sys.argv[1]

print("Building Spdlog")
subprocess.call("python3 scripts/buildSpdlog.py {}".format(bldcfg), shell=True)

print("Generating AuroraStory solution")
subprocess.call("python3 scripts/generateSolution.py", shell=True)

print("Building AuroraStory solution")
subprocess.call("python3 scripts/buildSolution.py {}".format(bldcfg), shell=True)