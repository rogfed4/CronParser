parse: 
	g++ -std=c++11 -o parse main.cpp src/*

tests:
	g++ -std=c++11 -o tests test/* src/*
	./tests
	

clean:
	del parse.exe
	del tests.exe
	del example.exe

example:
	g++ -std=c++11 -o example main.cpp src/*
	.\\example "10 */0 12 8 0 /user/bin"


# find some complex examples below
# run:
# 	.example "6,52-25/3,27-38/3,70/2,2/66 0 21-35/2 7-3/2,*,9-4/2,3 5-2/2,1-7/2 /usr/bin/find"
# 	.example "*/15 0 1,12 2 3-6 /use"
#   .example "1 12/2-1 * * * /user/bin"
#   .exmaple "- * * * * /user/bin"
#   .exmaple "32,72 * * * * /user/bin"
#   .example "* 12-36 * * * /user/bin"
#   .example "* * 10-15,40 * * /user/bin"
#   .example "* * * 12-13 * /user/bin"
#   .example "* * * * * * * *ASD"
#   .example "0 0 31 4 * /user/bin"
#   .example "10 2 12 8 0 /user/bin" 
#   .example "10 */A 12 8 0 /user/bin"
#   .example "10 ! 12 8 0 /user/bin"
#   .example "10 */-1 12 8 0 /user/bin"

