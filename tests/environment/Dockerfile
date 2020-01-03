FROM debian:buster-slim AS apt_provider

FROM toliak/mtasa-python

USER 0

# Because toliak/mtasa-python breaks apt-get
COPY --from=apt_provider /var/lib/apt /var/lib/apt

RUN apt-get -y update && \
    apt-get -y install procps && \
    apt-get -y autoremove && \
    apt-get -y clean && \
    rm -rf /var/lib/apt

COPY entrypoint.sh /home/mtasa/entrypoint.sh

USER mtasa
CMD ./entrypoint.sh