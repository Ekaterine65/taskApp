FROM ubuntu

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get install qtbase6-dev qtchooser qt6-qmake qtbase6-dev-tools -y
RUN apt-get install build-essential -y

WORKDIR /root/
RUN mkdir server
WORKDIR /root/server/
COPY *.cpp /root/server/
COPY *.h /root/server/
COPY *.pro /root/server/
COPY *.user /root/server/

RUN qmake6 echoServer.pro
RUN make

ENTRYPOINT ["./echoServer"]
