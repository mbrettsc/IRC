all:
	c++ client.cpp -o client
	c++ server.cpp -o server

clean:
	rm -rf server client

re: clean all