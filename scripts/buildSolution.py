import os
import subprocess
import sys

root_directory = os.getcwd()
bldcfg = sys.argv[1]

# Create executables
subprocess.run(["MSBuild", "AuroraStory.sln", "/p:Configuration={}".format(bldcfg)])