default:
	g++ huffmanEncoding.cpp -o encode.o -std=c++11
	g++ huffmanDecoding.cpp -o decode.o -std=c++11

encode:
	./encode.o
	@echo "Char codes are written into 'encoding.txt'"
	@echo "Encoded output is written into file 'encodedOutput.txt'"

decode:
	./decode.o
	@echo "Decoded output is written into file 'decodedOutput.txt'"

clean:
	rm encode.o decode.o encodedOutput.txt decodedOutput.txt encoding.txt