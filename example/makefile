OUTPUT    = example.exe
CXX       = g++
CXX_FLAGS = -std=c++20 -Ofast -I../include -Wall -Wextra -Werror -Wpedantic -Wconversion -Wshadow -Woverflow
LD_FLAGS  = -s

all:
	$(CXX) $(CXX_FLAGS) main.cpp $(LD_FLAGS) -o $(OUTPUT)
	./example.exe
	strings example.exe | egrep -i 'very|obvious|string|that|would|be|noticable' # code 1 == nothing found
