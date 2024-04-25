FROM ubuntu:latest
RUN apt-get update -y \
  && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
     build-essential bison flex time curl gdb cmake git nano \
     ca-certificates \
  && rm -rf /var/lib/apt/lists/* && update-ca-certificates

#
# lemon parser generator in /usr/local/lemon & /usr/local/bin/lemon
#
#   https://sqlite.org/src/doc/trunk/doc/lemon.html
#
#   src/template file is in /usr/local/lemon/{lemon.c,lempar.c}
#   executable is symlinked in /usr/local/bin/lemon
#
RUN mkdir -p /usr/local/lemon
WORKDIR /usr/local/lemon
RUN curl -L -o lemon.c 'https://sqlite.org/src/raw/file?name=tool/lemon.c&ci=trunk'
RUN curl -L -o lempar.c 'https://sqlite.org/src/raw/file?name=tool/lempar.c&ci=trunk'
RUN gcc -o lemon lemon.c
RUN ln -s /usr/local/lemon/lemon /usr/local/bin/lemon

#
# reflex https://github.com/Genivia/RE-flex modern (utf-8/unicode) lexer
#
RUN mkdir -p /usr/local/reflex
WORKDIR /usr/local/reflex
RUN curl -L -o reflex.tar.gz https://github.com/Genivia/RE-flex/archive/refs/tags/v3.2.11.tar.gz
RUN tar --strip-components=1 -xf reflex.tar.gz
RUN ./clean.sh && ./build.sh && ./allinstall.sh

RUN echo  export PATH='"'/app:/app/bin:/app/bin/$(uname -s)-$(uname -m):'${PATH}''"' >> /root/.bashrc

WORKDIR /app
EXPOSE 8000

ENTRYPOINT ["/bin/bash","-i","-c","\"$@\"","--"]

