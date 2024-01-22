CPPFLAGS := -std=c++20
SOURCES := src/cpp/ParseError.cpp src/cpp/LexError.cpp src/cpp/ErrorScan.cpp src/cpp/TableHead.cpp src/cpp/Scanner.cpp src/cpp/Parser.cpp src/cpp/main.cpp 
TARGET := simple-database

$(TARGET) : $(SOURCES)
	g++ $(SOURCES) $(CPPFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

install:
	sudo cp $(TARGET) /usr/local/bin/