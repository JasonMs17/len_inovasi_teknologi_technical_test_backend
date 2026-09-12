# Stage 1: Build binary
FROM alpine:3.19 AS builder

RUN apk add --no-cache g++ cmake make

WORKDIR /app
COPY . .

RUN mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF .. && \
    make -j$(nproc) leniot_backend

# Stage 2: Minimal runtime image
FROM alpine:3.19

RUN apk add --no-cache libstdc++

WORKDIR /app
COPY --from=builder /app/build/src/leniot_backend /app/leniot_backend

EXPOSE 8080/udp 9001/udp 9002/udp

ENTRYPOINT ["/app/leniot_backend"]
