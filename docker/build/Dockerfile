FROM debian:bullseye-slim

WORKDIR /home/

RUN apt-get update -y && \
	apt-get install -y gcc clang build-essential vim make valgrind libreadline-dev 

RUN apt-get clean && \
	rm -rf /var/lib/apt/lists/*
	
CMD ["bash"]
