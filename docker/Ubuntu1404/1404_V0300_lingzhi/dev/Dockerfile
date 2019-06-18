FROM ubuntu:1404_V0200

COPY docker-prepare.sh /bin/docker-prepare.sh

RUN chmod 755 /bin/docker-prepare.sh

ENTRYPOINT ["docker-prepare.sh"]
