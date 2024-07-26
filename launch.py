import subprocess
import sys

bldcfg = sys.argv[1]

subprocess.run(["bin/{}/windows/AuroraStory/AuroraStory.exe".format(bldcfg)])