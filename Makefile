CPPFLAGS=-g 

mkpass_source=randcharacter.cpp pass.cpp mkpass.cpp
mkpass_objs=$(mkpass_source:%.cpp=%.o)

mkpass: $(mkpass_objs)
	g++ $(CPPFLAGS) $(mkpass_objs) -o mkpass

%.o: %.c
	g++ -c $(CPPFLAGS) $< -o $@
	
.PHONY clean:
	rm -rf *.o 2>/dev/null
	rm -rf mkpass 2>/dev/null
