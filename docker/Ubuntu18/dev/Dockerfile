FROM ubuntu:18.04

COPY docker-prepare.sh /bin/docker-prepare.sh
COPY isudo /bin/isudo

RUN echo "dash dash/sh boolean false"| debconf-set-selections \
    && DEBIAN_FRONTEND=noninteractive dpkg-reconfigure dash \
    && mkdir -p /home/yang \
    && cp /root/.bashrc /home/yang \
    && cp /root/.profile /home/yang \
    && chmod 755 /bin/docker-prepare.sh \
    && chown root:root /bin/isudo && chmod 755 /bin/isudo && chmod +s /bin/isudo

ENTRYPOINT ["docker-prepare.sh"]
