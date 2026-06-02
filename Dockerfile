FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .


RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build

RUN cd build && ctest -C Release --output-on-failure

CMD ["./build/RoguelikeEngine"]