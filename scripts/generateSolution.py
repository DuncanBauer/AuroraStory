import platform
import subprocess

# Create vs2022 solution
if platform.system() == "Windows":
    subprocess.run(["vendor/premake5.exe", "vs2022"])