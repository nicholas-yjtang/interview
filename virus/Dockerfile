FROM ubuntu:20.04
RUN apt update && DEBIAN_FRONTEND=noninteractive TZ=Etc/UTC apt install -y build-essential cmake pkg-config liblog4cxx-dev libgtest-dev
RUN mkdir -p /opt/virus
WORKDIR /opt/virus
COPY CMakeLists.txt main.cpp test.cpp transmission.cpp transmission.h WardFactory.cpp WardFactory.h run.sh /opt/virus/
COPY conf conf
RUN cmake .
RUN make
RUN chmod a+x run.sh
ENTRYPOINT ["/opt/virus/run.sh"]