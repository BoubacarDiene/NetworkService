##
# docker build -t networkservice-image ci/
# docker run --privileged -it -u $(id -u) --rm -v $(pwd):/workdir networkservice-image:latest
##

# Download base image
FROM ubuntu:18.04

# Define labels (maintainer and description)
LABEL maintainer="Boubacar DIENE <boubacar.diene@gmail.com>"
LABEL description="Docker image to build NetworkService project"

# Install required packages from ubuntu repository
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        cppcheck \
        ctags \
        doxygen \
        ebtables \
        gdb \
        git \
        gnupg2 \
        graphviz \
        iptables \
        net-tools \
        python-pip \
        python-setuptools \
        python-wheel \
        strace \
        tree \
        unzip \
        valgrind \
        vim \
        wget && \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Install additional packages from other repositories
# - LLVM Clang's tools and libraries (See https://apt.llvm.org/)
# - cmake (See https://apt.kitware.com/)
USER root

RUN wget --no-check-certificate -O - https://apt.llvm.org/llvm-snapshot.gpg.key|apt-key add - && \
    wget --no-check-certificate -O - https://apt.kitware.com/keys/kitware-archive-latest.asc|apt-key add - && \
    echo deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-10 main >> /etc/apt/sources.list && \
    echo deb-src http://apt.llvm.org/bionic/ llvm-toolchain-bionic-10 main >> /etc/apt/sources.list && \
    echo deb https://apt.kitware.com/ubuntu/ bionic main >> /etc/apt/sources.list

RUN apt-get update && apt-get install -y --no-install-recommends \
    clang-10 \
    clang-format-10 \
    clang-tidy-10 \
    cmake \
    libclang-10-dev \
    llvm-10-dev && \
apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN ln -s /usr/bin/clang-format-10 /usr/bin/clang-format && \
    ln -s /usr/bin/clang-tidy-10 /usr/bin/clang-tidy

# Install cmake_format (See https://github.com/cheshirekow/cmake_format)
RUN pip install cmake_format

# IWYU (Include What You Use)
# Example: ${IWYU_VERSION##*_} = ${clang_10##*_} = 10
ARG IWYU_VERSION=clang_10
ARG IWYU_DOWNLOAD_URL=https://github.com/include-what-you-use/include-what-you-use/archive/
ARG IWYU_INSTALL_DIR=/opt
ARG IWYU_BUILD_DIR=include-what-you-use/build

RUN wget --no-check-certificate ${IWYU_DOWNLOAD_URL}/${IWYU_VERSION}.zip -P ${IWYU_INSTALL_DIR} && \
    cd ${IWYU_INSTALL_DIR} && unzip ${IWYU_VERSION}.zip && rm ${IWYU_VERSION}.zip && \
    mkdir -p include-what-you-use-${IWYU_VERSION}/build && \
    cd include-what-you-use-${IWYU_VERSION}/build && \
    cmake .. -DCMAKE_PREFIX_PATH=/usr/lib/llvm-${IWYU_VERSION##*_} && make && \
    ln -s /opt/include-what-you-use-${IWYU_VERSION}/build/bin/include-what-you-use /usr/bin/iwyu

# Install CLI11 (Command line parser for >= C++11)
ARG CLI11_VERSION=1.9.0
ARG CLI11_DOWNLOAD_URL=https://github.com/CLIUtils/CLI11/releases/download
ARG CLI11_INSTALL_DIR=/usr/local/include

RUN wget --no-check-certificate ${CLI11_DOWNLOAD_URL}/v${CLI11_VERSION}/CLI11.hpp \
    -P ${CLI11_INSTALL_DIR}

# Install nlohmann/json
ARG JSON_VERSION=3.7.3
ARG JSON_DOWNLOAD_URL=https://github.com/nlohmann/json/releases/download
ARG JSON_INSTALL_DIR=/usr/local/include

RUN wget --no-check-certificate ${JSON_DOWNLOAD_URL}/v${JSON_VERSION}/json.hpp \
    -P ${JSON_INSTALL_DIR}

# Add user
ENV USERNAME networkservice-usr
ENV HOMEDIR /home/${USERNAME}

RUN useradd -ms /bin/bash ${USERNAME}
USER ${USERNAME}
WORKDIR /workdir

# Install vim plugins
RUN mkdir -p ${HOMEDIR}/.vim/autoload ${HOMEDIR}/.vim/bundle \
    && wget https://tpo.pe/pathogen.vim -P ${HOMEDIR}/.vim/autoload/ \
    && cd ${HOMEDIR}/.vim/bundle \
    && git clone https://github.com/ctrlpvim/ctrlp.vim.git \
    && git clone https://github.com/preservim/nerdtree.git \
    && git clone https://github.com/kana/vim-operator-user.git \
    && git clone https://github.com/rhysd/vim-clang-format.git \
    && git clone git://github.com/pboettch/vim-cmake-syntax.git

COPY .vimrc ${HOMEDIR}/

# Entry point
ENTRYPOINT ["/bin/bash"]
