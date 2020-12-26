##
# docker build --force-rm --no-cache -t networkservice-image ci/
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
        lcov \
        net-tools \
        python-pip \
        python-setuptools \
        python-wheel \
        python3-pip \
        python3-setuptools \
        python3-wheel \
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
    echo deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-10 main >> /etc/apt/sources.list && \
    echo deb-src http://apt.llvm.org/bionic/ llvm-toolchain-bionic-10 main >> /etc/apt/sources.list && \
    wget --no-check-certificate -O - https://apt.kitware.com/keys/kitware-archive-latest.asc|apt-key add - && \
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

# Install gcovr (See https://gcovr.com/en/stable/guide.html)
RUN pip3 install gcovr

# Install cpp-coveralls
RUN pip install --system cpp-coveralls

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

# Install googletest and googlemock
ARG GTEST_VERSION=1.10.0
ARG GTEST_DOWNLOAD_URL=https://github.com/google/googletest/archive
ARG GTEST_INSTALL_DIR=/opt

RUN wget --no-check-certificate ${GTEST_DOWNLOAD_URL}/release-${GTEST_VERSION}.tar.gz -O - \
    | tar xzC ${GTEST_INSTALL_DIR}
RUN mkdir -p ${GTEST_INSTALL_DIR}/googletest-release-${GTEST_VERSION}/build \
    && cd ${GTEST_INSTALL_DIR}/googletest-release-${GTEST_VERSION}/build \
    && cmake .. \
    && make && make install \
    && cd ${GTEST_INSTALL_DIR} && rm -rf googletest-release-${GTEST_VERSION}

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
