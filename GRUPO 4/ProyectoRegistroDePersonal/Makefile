CXX = g++
CXXFLAGS = -g -fdiagnostics-color=always
TARGET = main.exe
SOURCES = main.cpp Menus.cpp Fecha.cpp Persona.cpp GestorPersonas.cpp MenuEmpleado.cpp Empleado.cpp ArbolRadix.cpp Validaciones.cpp ListaCircularDoble.cpp extras.cpp Bibliotecas/EasyBMP.cpp BigO.cpp
OBJECTS = $(patsubst %.cpp,obj/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: %.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f obj/*.o $(TARGET)