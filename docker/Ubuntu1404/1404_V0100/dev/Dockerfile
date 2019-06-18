FROM ubuntu:14.04

COPY docker-prepare.sh /bin/docker-prepare.sh
COPY isudo /bin/isudo

RUN buildDeps='gcc g++ dos2unix make vim ack-grep unzip zip lib32ncurses5 lib32z1 tree python python3 git tig subversion wget curl bc' \
    && apt-get update \
    && apt-get install -y $buildDeps \
    && echo "dash dash/sh boolean false"| debconf-set-selections \
    && DEBIAN_FRONTEND=noninteractive dpkg-reconfigure dash \
    && echo "set ts=4\nset expandtab\nset autoindent" >> /etc/vim/vimrc \
    && svn info http://svn.apache.org/repos/asf/ \
    && mkdir -p /home/yang \
    && cp /root/.bashrc /home/yang \
    && cp /root/.profile /home/yang \
    && cp /root/.subversion /home/yang -a \
    && chmod 755 /bin/docker-prepare.sh \
    && chown root:root /bin/isudo && chmod 755 /bin/isudo && chmod +s /bin/isudo


ENTRYPOINT ["docker-prepare.sh"]

