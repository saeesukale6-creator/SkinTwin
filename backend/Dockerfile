
FROM gcc:14

WORKDIR /app

COPY httplib.h .
COPY server.cpp .

RUN g++ server.cpp -o server -std=c++17 -pthread

EXPOSE 10000

CMD ["./server"]

