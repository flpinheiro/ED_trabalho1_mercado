CXX = g++
CXXFLAGS = -Wall -g

main: Edmercado.o Cliente.o Carrinho.o Estoque.o util.o
	$(CXX) $(CXXFLAGS) -o EDmercado Edmercado.o Cliente.o Carrinho.o Estoque.o util.o

clean: 
	rm Edmercado.o Cliente.o Carrinho.o Estoque.o util.o