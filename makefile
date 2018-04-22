CC := g++
LD := g++

CXXFLAGS := -g -O3 -msse4.1 -std=c++11 `Magick++-config --cxxflags --cppflags`
LDFLAGS := -g `Magick++-config --cxxflags --cppflags` `Magick++-config --ldflags --libs` -fopenmp -lprofiler -ljsoncpp

SRC_DIR := objects basic_types random
BUILD_DIR := $(addprefix build/,$(SRC_DIR))

SRC := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
INCLUDES := $(addprefix -I,$(SRC_DIR)) -Ijson
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

# NOTE: STANDARD FOR BENCHMARKING IS 20 SAMPLES AT 600x480 RESOLUTION, 1 OBJECT (SPHERE, 0.2 RADIUS) and 6 walls!
# in sequential version, this gave ~20.1s for a standard render.
# in optimised, vectorised, hydrolysed version it took ~16-17s. See gperftools readout for difference in RenderVec operations sampling!
