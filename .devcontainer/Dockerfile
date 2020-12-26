FROM ubuntu:latest

RUN apt update && export DEBIAN_FRONTEND=noninteractive \
    && /bin/bash \
    && apt -y install git \
    && apt -y install clang clangd clang-tidy clang-format clang-tools lldb \
    && apt -y install cmake \
    && apt -y install doxygen \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# echo "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-11 main" >> /etc/apt/sources.list.d/docker.list
# echo "deb-src http://apt.llvm.org/focal/ llvm-toolchain-focal-11 main" >> /etc/apt/sources.list.d/docker.list