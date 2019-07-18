FROM debian:9.9-slim

RUN echo "Installing build dependencies" && \
    apt-get -y update && \
    apt-get -y install  wget \
                        make \
                        gcc \
                        g++ \
                        cmake \
                        zlib1g \
                        zlib1g-dev \
                        libffi-dev \
                        && \
    echo "Installing python" && \
    mkdir -p /tmp/python && \
    cd /tmp/python && \
    wget https://www.python.org/ftp/python/3.7.3/Python-3.7.3.tgz && \
    tar xzf Python-3.7.3.tgz && \
    cd Python-3.7.3 && \
    ./configure --enable-optimizations --enable-shared && \
    make install && \
    echo "Clearing python cache" && \
    rm -rf /tmp/python && \
    echo "Clearing apt-get cache" && \
    apt-get -y purge wget zlib1g-dev libffi-dev && \
    apt-get -y autoremove && \
    apt-get -y clean && \
    rm -rf /var/lib/apt

RUN useradd -ms /bin/bash builder

WORKDIR /home/builder

VOLUME /home/builder/code
VOLUME /home/builder/build

USER builder

CMD /bin/bash