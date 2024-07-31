# Use an official Ubuntu image as the base
FROM gcc:latest AS builder

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && apt-get install -y \
    cmake \
    git \
    libssl-dev \
    lua5.3 \
    liblua5.3-dev \
    openssl \
    uuid-dev \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Install Premake5
RUN wget https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-linux.tar.gz \
    && tar -xzf premake-5.0.0-beta2-linux.tar.gz \
    && cp premake5 /usr/local/bin/premake5 \
    && rm -rf premake5 \
    && rm -rf example.so \
    && rm -rf libluasocket.so \
    && rm -rf premake-5.0.0-beta2-linux.tar.gz

# Install LuaCPP
RUN wget https://github.com/jordanvrtanoski/luacpp/archive/refs/tags/v0.2.0.tar.gz \
    && tar -xzf v0.2.0.tar.gz \
    && cd luacpp-0.2.0/Source \
    && mkdir build && cd build \
    && cmake ../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_SHARED_LIBS=OFF \
    && cmake --build . --config Debug \
    && make && make install \
    && cd ../../../ \
    && rm -rf luacpp-0.2.0 \
    && rm v0.2.0.tar.gz

# Install Mongo-C-Driver
RUN wget https://github.com/mongodb/mongo-c-driver/releases/download/1.27.4/mongo-c-driver-1.27.4.tar.gz \
    && tar -xzf mongo-c-driver-1.27.4.tar.gz \
    && cd mongo-c-driver-1.27.4/build \
    && cmake ../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_SHARED_LIBS=OFF \
    && cmake --build . --config Debug \
    && make && make install \
    && cd ../../ \
    && rm -rf mongo-c-driver-1.27.4 \
    && rm mongo-c-driver-1.27.4.tar.gz

# Install Mongo-CXX-Driver
RUN wget https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.10.2/mongo-cxx-driver-r3.10.2.tar.gz \
    && tar -xzf mongo-cxx-driver-r3.10.2.tar.gz \
    && cd mongo-cxx-driver-r3.10.2/build \
    && cmake ../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_CXX_STANDARD=20 -DBUILD_SHARED_LIBS=OFF \
    && cmake --build . --config Debug \
    && make && make install \
    && cd ../../ \
    && rm -rf mongo-cxx-driver-r3.10.2 \
    && rm mongo-cxx-driver-r3.10.2.tar.gz

# Install Spdlog
RUN wget https://github.com/gabime/spdlog/archive/refs/tags/v1.14.1.tar.gz \
    && tar -xzf v1.14.1.tar.gz \
    && cd spdlog-1.14.1 \
    && mkdir build && cd build \
    && cmake ../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr/local \
    && cmake --build . --config Debug \
    && make && make install \
    && cd ../../ \
    && rm -rf spdlog-1.14.1 \
    && rm v1.14.1.tar.gz

# Install Yaml-cpp
RUN wget https://github.com/jbeder/yaml-cpp/archive/refs/tags/0.8.0.tar.gz \
    && tar -xzf 0.8.0.tar.gz \
    && cd yaml-cpp-0.8.0 \
    && mkdir build && cd build \
    && cmake ../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr/local \
    && cmake --build . --config Debug \
    && make && make install \
    && cd ../../ \
    && rm -rf yaml-cpp-0.8.0 \
    && rm 0.8.0.tar.gz

# Install Bcrypt
RUN git clone --depth 1 https://github.com/trusch/libbcrypt.git bcrypt \
  && cp -r bcrypt/include usr/local \
  && cd bcrypt \
  && mkdir build && cd build \
  && cmake ../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr/local \
  && cmake --build . --config Debug \
  && make && make install \
  && cd ../../ \
  && rm -rf bcrypt

# Install ASIO
RUN git clone --depth 1 https://github.com/chriskohlhoff/asio.git asio \
  && cp -r asio/asio/include usr/local/include/asio \
  && rm -rf asio


  # Create a minimal image for running AuroraStory
FROM gcc:latest
# FROM ubuntu:20.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    make \
    python3 \
    vim

# Expose Login Server port
EXPOSE 8484

# Expose 20 Channel Server ports, could be more if more than one world
EXPOSE 7575-7594

# Expose MongoDB connection port
EXPOSE 27017

# These commands copy your files into the specified directory in the image
# and set that as the working location
WORKDIR /aurorastory
COPY . .

# Copy the compiled assets that we need to run from the builder image
COPY --from=builder /usr/local/include /usr/local/include
COPY --from=builder /usr/local/lib /usr/local/lib
COPY --from=builder /usr/local/bin/premake5 /aurorastory/premake5

COPY --from=builder /usr/include/lua5.3 /usr/include/lua5.3
COPY --from=builder /usr/lib/x86_64-linux-gnu/liblua5.3.a /usr/local/lib/liblua5.3.a
COPY --from=builder /usr/lib/x86_64-linux-gnu/liblua5.3-c++.a /usr/local/lib/liblua5.3-c++.a
COPY --from=builder /usr/lib/x86_64-linux-gnu/liblua5.3.so /usr/local/lib/liblua5.3.so
COPY --from=builder /usr/lib/x86_64-linux-gnu/liblua5.3-c++.so /usr/local/lib/liblua5.3-c++.so

# Ensure premake5 is executable
RUN chmod +x premake5

# This command generates a makefile using premake5
RUN ./premake5 gmake2
# RUN make

# This command runs your application, comment out this line to compile only
# CMD ["./AuroraStory"]