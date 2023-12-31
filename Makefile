CFLAGS=-Wall -O3 -g -Wextra -Wno-unused-parameter -Wno-psabi
CXXFLAGS=$(CFLAGS)
OBJECTS=Background.o Widget.o Device.o main.o 
BINARIES=main 
DEPS = Background.hpp Widget.hpp Device.hpp

# Where our library resides. You mostly only need to change the
# RGB_LIB_DISTRIBUTION, this is where the library is checked out.
RGB_LIB_DISTRIBUTION=/home/admin/rgb/rpi-rgb-led-matrix
JSON_INCDIR=/home/admin/rgb/json/single_include
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread -lsfml-graphics


all : $(BINARIES)


main : $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

# All the binaries that have the same name as the object file.q
% : %.o $(RGB_LIBRARY)
	$(CXX) $< -o $@ $(LDFLAGS) 


%.o : %.cc $(DEPS)
	$(CXX) -I$(RGB_INCDIR) -I$(JSON_INCDIR) $(CXXFLAGS) -c -o $@ $< 

clean:
	rm -f $(OBJECTS) $(BINARIES)

FORCE:
.PHONY: FORCE
