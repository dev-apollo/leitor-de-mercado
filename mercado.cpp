#include "mercado.hpp"

vector<ProdutoEstoque> getProdutosEstoque(string endereco){
    ifstream arquivo(endereco);
    vector<ProdutoEstoque> produtosEstoque;
    if(!arquivo.is_open()){
        cout<<"Erro ao abrir o arquivo."<<endl;
    }
    string linha;
    while(getline(arquivo, linha)){
        istringstream iss(linha);
        string token;
        vector<string> produtoAtual;
        while(getline(iss, token, ',')){
            produtoAtual.push_back(token);
        }
        ProdutoEstoque produtoCompleto = { produtoAtual[0], stod(produtoAtual[1]), stoi(produtoAtual[2]), produtoAtual[3] };
        produtosEstoque.push_back(produtoCompleto);
    }
    arquivo.close();
    return produtosEstoque;
}

vector<ProdutoLista> getProdutosLista(string endereco){
    ifstream arquivo(endereco);
    vector<ProdutoLista> produtosLista;
    if(!arquivo.is_open()){
        cout<<"Erro ao abrir o arquivo."<<endl;
    }
    string linha;
    while(getline(arquivo, linha)){
        istringstream iss(linha);
        string token;
        vector<string> produtoAtual;
        while(getline(iss, token, ',')){
            produtoAtual.push_back(token);
        }
        ProdutoLista produtoCompleto = { produtoAtual[0], stoi(produtoAtual[1]) };
        produtosLista.push_back(produtoCompleto);
    }
    arquivo.close();
    return produtosLista;
    
}

vector<ProdutoEstoque> compararProdutos(vector<ProdutoEstoque> produtosEstoque, vector<ProdutoLista> produtosLista){
    vector<ProdutoEstoque> produtosComprados;
    for(ProdutoLista pl: produtosLista){
        int cont = 0;
        for(ProdutoEstoque pe: produtosEstoque){
            if(pl.nome == pe.nome){
                int quantidade;
                if(pl.quantidade > pe.quantidade){
                    quantidade = pe.quantidade;
                }else{
                    quantidade = pl.quantidade;
                }
                ProdutoEstoque produtoDisponivel = { pe.nome, pe.preco, quantidade, pe.categoria };
                produtosComprados.push_back(produtoDisponivel);
                break;
            }else{
                cont++;
            }
        }
        if(cont >= produtosEstoque.size()){
            ProdutoEstoque produtoIndisponivel = { pl.nome, 0, pl.quantidade, "" };
            produtosComprados.push_back(produtoIndisponivel);
        }
    }
    return produtosComprados;
}

void descontarProdutosEstoque(string endereco, vector<ProdutoEstoque> produtosComprados){
    ofstream arquivo(endereco, ios::app);
    if(!arquivo.is_open()){
        cout<<"Erro ao abrir o arquivo."<<endl;
    }
    vector<ProdutoEstoque> produtosParaDescontar = getProdutosEstoque(endereco);
    limparArquivo(endereco);
    for(ProdutoEstoque pd: produtosParaDescontar){
        for(ProdutoEstoque pc: produtosComprados){
            if(pd.nome == pc.nome){
                pd.quantidade-=pc.quantidade;
                break;
            }
        }
        arquivo<<pd.nome<<","<<pd.preco<<","<<pd.quantidade<<","<<pd.categoria<<endl;
    }
    arquivo.close();
}

void exibirLista(string endereco, vector<ProdutoEstoque> produtosComprados){
    double total = 0;
    for(ProdutoEstoque p: produtosComprados){
        if(p.preco <= 0 || p.quantidade <= 0){
            cout<<p.nome<<" - Indisponivel"<<endl;
        }else{
            cout<<p.quantidade<<" "<<p.nome<<" - "<<p.preco*p.quantidade<<endl;
            total+=p.preco*p.quantidade;
        }
    }
    cout<<"Valor da Compra: R$ "<<total<<endl;
    descontarProdutosEstoque(endereco, produtosComprados);
}

void limparArquivo(string endereco){
    ofstream arquivo(endereco);
    if(!arquivo.is_open()){
        cout<<"Erro ao abrir o arquivo."<<endl;
    }
    arquivo<<"";
    arquivo.close();
}