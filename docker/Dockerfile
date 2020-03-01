FROM ubuntu:16.04
RUN apt-get update -y && apt-get install -y gcc
RUN apt-get install -y ffmpeg
RUN apt-get install -y wget
RUN apt-get install -y xz-utils
RUN apt-get install -y build-essential
RUN apt-get install -y libcairo2-dev
RUN apt-get install -y libgtk-3-dev
RUN apt-get install -y libxml2-dev
RUN apt-get install -y libavcodec-dev
RUN apt-get install -y libavutil-dev
RUN apt-get install -y libavformat-dev
RUN apt-get install -y libfreetype6-dev

# get the duktape source code
RUN wget https://duktape.org/duktape-2.5.0.tar.xz
RUN tar xvf duktape-2.5.0.tar.xz
