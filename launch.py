import subprocess
import sys

bldcfg = sys.argv[1]

subprocess.run(["bin/{}/windows/AuroraStory.exe".format(bldcfg)])