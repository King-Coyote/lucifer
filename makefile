CC := g++
LD := g++

CXXFLAGS := -g `Magick++-config --cxxflags --cppflags`
LDFLAGS := -g `Magick++-config --cxxflags --cppflags` `Magick++-config --ldflags --libs` -fopenmp

SRC_DIR := objects basic_types random
BUILD_DIR := $(addprefix build/,$(SRC_DIR))

SRC := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
INCLUDES := $(addprefix -I,$(SRC_DIR))
OBJ := $(patsubst %.cpp,build/%.o,$(SRC))

vpath %.cpp $(SRC_DIR)

.PHONY: clean

define make-goal
$1/%.o: %.cpp
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $$< -o $$@
endef

lucifer: main.cpp $(OBJ)
	$(LD) $(INCLUDES) $^ -o $@ $(LDFLAGS)

#test: src/dummy_main.cpp $(OBJ)
#	$(LD) $(INCLUDES) $^ -o $@ $(LDFLAGS)

clean:
	rm $(OBJ)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))


