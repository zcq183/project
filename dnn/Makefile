all: dnn
INC=/usr/local/include/opencv4 -I /usr/local/include/opencv4/opencv
LIB=/usr/local/lib
LIBS=-lopencv_highgui  -lopencv_video   -lopencv_videoio  -lopencv_dnn  -lopencv_imgproc -lopencv_core -lopencv_dnn -lopencv_imgcodecs
CFLAGS= -std=c++11
CC=g++
dnn:tf.cpp
	g++ -g -o $@ $< -I $(INC) -L $(LIB) $(LIBS)  -std=c++11

clean:
	rm dnn_call
