/**
 * 
 * ASA 2021/2022 - IST
 * Projeto 2
 * 
 * 99218 - Francisco Augusto
 * 95908 - Rita Costa
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int node1, node2, num_nodes, num_connect, num1, num2;
long unsigned int size_comuns, ler, numero;
vector<vector<int>> _descendants;
long **_ancestors;
vector<int> comuns, _ancestrais_comuns_maisprx, _ancestors1, _ancestors2, para_ler,_verify;
bool comum;

/**
 * @brief verification_aux - função auxiliar a direct_verification
 * @param  int v 
 * @return int 
 */
int verification_aux(int v){
    _verify[v] = 2;
    for(long unsigned int w = 0; w < _descendants[v].size(); w++){
        if (_verify[_descendants[v][w]] == 0){
            _verify[_descendants[v][w]] = verification_aux(_descendants[v][w]);
            if(_verify[_descendants[v][w]] == -1){
                return -1;
            }
        }
        if (_verify[_descendants[v][w]] == 2){
            return -1;
        }
    }
    return 1;
}


/**
 * @brief verification - função que permite determinar se 
 * um grafo apresenta loops ou não
 * @param vector<vector<int>> _adj 
 * @return int 
 */
int verification(int v){
    for(long unsigned int v = 0; v < _verify.size(); v++){
        if (_verify[v] == 0){
            _verify[v] = verification_aux(v);
            if(_verify[v] == -1){
                return -1;
            }
        }
    }
    return 0;
}


/**
 * @brief verification - função que permite determinar se 
 * um grafo apresenta loops ou não
 * @param vector<int> G 
 * @param vector<vector<int>> _adj 
 * @return int 
 */
void common_ancestors(){
    ler =  _ancestors[node1 -1][2];
    for(long unsigned int i = 0; i < ler; i++){
        para_ler.push_back(_ancestors[node1 -1][i]);
    }
    _ancestors1.push_back(node1);
    while(para_ler.size()!=0){
        ler = _ancestors[para_ler.back()][2];
        numero = para_ler.back();
        para_ler.pop_back();
        for(long unsigned int i = 0; i < ler; i++){
            para_ler.push_back(_ancestors[numero][i]);
        }
        _ancestors1.push_back(numero +1);
    }
    ler =  _ancestors[node2 -1][2];
    for(long unsigned int i = 0; i < ler; i++){
        para_ler.push_back(_ancestors[node2 -1][i]);
    }
    _ancestors2.push_back(node2);
    while(para_ler.size()!=0){
        ler = _ancestors[para_ler.back()][2];
        numero = para_ler.back();
        para_ler.pop_back();
        for(long unsigned int i = 0; i < ler; i++){
            para_ler.push_back(_ancestors[numero][i]);
        }
        _ancestors2.push_back(numero +1);
    }
    for(long unsigned int i = 0; i< _ancestors1.size(); i++){
        comum = false;
        for(long unsigned int j = 0; j< _ancestors2.size(); j++){
            if(_ancestors1[i] == _ancestors2[j]){
                comum = true;
            }
        }
        if(comum){
            comuns.push_back(_ancestors1[i]);
        }
    }
}


/**
 * Main do programa
 * @return int 
 */
int main(){ 
    if(scanf("%d", &node1)!= 1){
        printf("Failed to read\n");
    }
    if(scanf("%d", &node2)!=1){
        printf("Failed to read\n");
    }
    if(scanf("%d", &num_nodes)!=1){
        printf("Failed to read\n");
    }
    if(scanf("%d", &num_connect)!=1){
        printf("Failed to read\n");
    }
    bool remove;
    _ancestors = new long*[num_nodes];
    for(int i= 0; i < num_nodes; i++){
        _descendants.push_back(vector<int>(0));
        _ancestors[i] = new long[3];
        _ancestors[i][2] = 0;
        _verify.push_back(0);
    }
    for (int i = 0; i < num_connect; i++){
        if(scanf("%d", &num1)!=1){
            printf("Failed to read\n");
        }
        if(scanf("%d", &num2)!=1){
            printf("Failed to read\n");
        }
        _descendants[num1-1].push_back(num2-1);
        if(_ancestors[num2 -1][2] == 2){
            printf("0\n");
            return 0;
        }
        _ancestors[num2 -1][_ancestors[num2 -1][2]] = num1 -1;
        _ancestors[num2 -1][2] =_ancestors[num2 -1][2] + 1;
    }
    int verify = verification(num_nodes);
    if(verify == -1){
        printf("0\n");
        return 0;
    }
    else{
        common_ancestors();
        size_comuns = comuns.size();
        for(long unsigned int i= 0; i < size_comuns; i++){
            remove = false;
            for(long unsigned int j = 0; j< _descendants[comuns[i]-1].size(); j++){
                for(long unsigned int k= 0; k< size_comuns; k++){
                    if(comuns[k]-1 == _descendants[comuns[i]-1][j]){
                        remove = true;
                        break;
                    }
                }
            }
            if(!remove){
                _ancestrais_comuns_maisprx.push_back(comuns[i]);
            }
        }
        if(_ancestrais_comuns_maisprx.size() == 0){
            printf("-\n");
        }
        else{
            sort(_ancestrais_comuns_maisprx.begin(), _ancestrais_comuns_maisprx.end());
            _ancestrais_comuns_maisprx.erase( unique( _ancestrais_comuns_maisprx.begin(), _ancestrais_comuns_maisprx.end() ), _ancestrais_comuns_maisprx.end() );
        for(long unsigned int i = 0; i<_ancestrais_comuns_maisprx.size();i++){
            printf("%d ", _ancestrais_comuns_maisprx[i]);
        }
        printf("\n");
        }
    }
    return 0;
}