NAME_EXE	=	server

SRC_EXE         =       main.cc \
                        road.cc \
												csvparser.cc \
												graph.cc
												# dijkstra.cc \

OBJ_EXE         =       $(SRC_EXE:.cc=.o)

CXX             =        g++ -std=c++11

all             :       $(NAME_EXE)

$(NAME_EXE)     :       $(OBJ_EXE) $(OBJ_CORE)
												$(CXX) -o $(NAME_EXE) $(OBJ_EXE) $(LDFLAGS)

clean           :
												rm -f $(OBJ_EXE)

fclean   :									clean
												rm -f $(NAME_EXE)

re              :       fclean all

.PHONY          :       all clean fclean re
