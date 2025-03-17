CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRC = main.cpp

ifeq ($(OS),Windows_NT)
    OUT = HollowSunSaveEditor.exe
else
    OUT = HollowSunSaveEditor
endif

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
ifeq ($(OS),Windows_NT)
	del $(OUT)
else
	rm -f $(OUT)
endif

