default:
	g++ src/glad.c src/shaderClass.cpp src/VAO.cpp src/VBO.cpp src/EBO.cpp main.cpp -lGL -lglfw -o bin/utsKGV
