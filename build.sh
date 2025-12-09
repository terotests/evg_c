#!/bin/bash
docker build -t evg-video docker

# docker run -it -v (pwd)/project:/project evg-video /bin/bash
# docker run -it -v $(pwd)/project:/project evg-video gcc -o /project/bin/main /project/src/main.c
# docker run -it -v $(pwd)/project:/project evg-video /project/bin/main