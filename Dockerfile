FROM python:3.7.6-slim-buster

RUN useradd -ms /bin/bash builder
WORKDIR /home/builder

# Prepare compilation environment
RUN apt-get -y update && \
    apt-get -y install gcc g++ cmake make && \
    apt-get -y autoremove && \
    apt-get -y clean && \
    rm -rf /var/lib/apt

ARG BUILD_ARGS
COPY --chown=builder:builder . .

USER builder
VOLUME /home/builder/build
CMD ./entrypoint.sh $BUILD_ARGS
