# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM gcc:latest

# Install required packages
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    cmake \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Install vcpkg (optional, if you want to manage dependencies with vcpkg)
RUN git clone https://github.com/microsoft/vcpkg.git /vcpkg \
&& cd /vcpkg \
&& ./bootstrap-vcpkg.sh

# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . /usr/src/AuroraStory
WORKDIR /usr/src/AuroraStory

# Clone the required GitHub dependencies
RUN git submodule add https://github.com/chriskohlhoff/asio.git vendor/asio \
    && git submodule add https://github.com/trusch/libbcrypt.git vendor/bcrypt \
    && git submodule add https://github.com/trusch/libbcrypt.git vendor/mongo-c-driver \
    && git submodule add https://github.com/gabime/spdlog.git vendor/mongo-cxx-driver \
    && git submodule add https://github.com/gabime/spdlog.git vendor/spdlog \
    && git submodule add https://github.com/jbeder/yaml-cpp.git vendor/yaml-cpp

# This command compiles your app using GCC, adjust for your source code
RUN g++ -o AuroraStory main.cpp

# This command runs your application, comment out this line to compile only
CMD ["./AuroraStory"]

LABEL Name=aurorastory Version=0.0.1
