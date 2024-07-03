CXX=clang++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion -g
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Demo.cpp KnightCard.cpp VictoryCard.cpp Monopoly.cpp YearOfPlentyCard.cpp Player.cpp Board.cpp Tile.cpp Vertex.cpp Edge.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))
TEST_SOURCES=Test.cpp
TEST_OBJECTS=$(subst .cpp,.o,$(TEST_SOURCES))

run: demo
	./$^

demo: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: $(TEST_OBJECTS) $(filter-out Demo.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) -o test $^

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test

