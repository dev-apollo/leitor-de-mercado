#include "mercado.hpp"

int main()
{
    exibirLista("produtos.txt", compararProdutos(getProdutosEstoque("produtos.txt"), getProdutosLista("lista.txt")));
}