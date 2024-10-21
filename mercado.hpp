#ifndef MERCADO_HPP
#define MERCADO_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct ProdutoEstoque{
    string nome;
    double preco;
    int quantidade;
    string categoria;
};

struct ProdutoLista{
    string nome;
    int quantidade;
};

vector<ProdutoEstoque> getProdutosEstoque(string endereco);
vector<ProdutoLista> getProdutosLista(string endereco);
vector<ProdutoEstoque> compararProdutos(vector<ProdutoEstoque> produtosEstoque, vector<ProdutoLista> produtosLista);
void descontarProdutosEstoque(string endereco, vector<ProdutoEstoque> produtos);
void exibirLista(string endereco, vector<ProdutoEstoque> produtos);
void limparArquivo(string endereco);
#endif