#ifndef MAINSODUKO_VISUAL_H
#define MAINSODUKO_VISUAL_H

#include <QMainWindow>
#include <sudoku.h>

namespace Ui {
class MainSoduko_visual;
}

class MainSoduko_visual : public QMainWindow, Sudoku, Jogada
{
    Q_OBJECT
public:
    explicit MainSoduko_visual(QWidget *parent = nullptr);
    ~MainSoduko_visual();

    void exibirCelulaAtual(int i,int j, int valor);

    void exibirCelulaInicial(int i, int j, int valor);

    void exibirCelulaAndamento(int Ntab_testados,int Ntab_gerados, int Ntab_analisar);

private slots:
    void on_tabela_atual_cellClicked(int row, int column);

    void on_botao_jogar_clicked();

    void on_caixa_de_valor_valueChanged(int arg1);

    void on_actionReiniciar_triggered();

    void on_Novo_triggered();

    void on_Preencher_imediato_triggered();

    void on_Resolver_triggered();

    void on_Sair_triggered();

    void on_Botao_cont_clicked();

private:
    Ui::MainSoduko_visual *ui;
    Jogada jogar;
    Sudoku  tabe_inic,tabe_atual;
};

#endif // MAINSODUKO_VISUAL_H
