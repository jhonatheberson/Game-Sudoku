#include <mainsoduko_visual.h>
#include <sudoku.h>

extern MainSoduko_visual *pt_w;

void Sudoku::exibir() const
{
    for(int i=0; i<9; i++) for(int j=0; j<9; j++)
    {
        pt_w -> exibirCelulaAtual(i,j, this->at(i,j));
    }
}

/// Exibir o conteudo do tabuleiro inicial
void Sudoku::exibir_origem() const
{
    for(int i=0; i<9; i++) for(int j=0; j<9; j++)
    {
        pt_w -> exibirCelulaInicial(i,j, this->at(i,j));
    }

}

/// Exibe os numeros de tabuleiros gerados, testados e a analisar
void Sudoku::exibir_andamento(unsigned Ntab_testados, unsigned Ntab_gerados, unsigned Ntab_analisar) const
{
    pt_w -> exibirCelulaAndamento(Ntab_testados,Ntab_gerados, Ntab_analisar);
}
