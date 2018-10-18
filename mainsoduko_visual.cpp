#include "mainsoduko_visual.h"
#include "ui_mainsoduko_visual.h"
#include <sudoku.h>

MainSoduko_visual::MainSoduko_visual(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainSoduko_visual),
    jogar(0, 0, 0),
    tabe_inic("sudoku.txt"), tabe_atual(tabe_inic)
{
    QLabel *prov_atual;
    QLabel *prov_inici;
    ui->setupUi(this);
    ui->Botao_cont->hide();
    ui->tabela_inicial->QTableWidget::setEnabled(false);
    ui->tabela_atual->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tabela_atual->setTabKeyNavigation(false);
    for(unsigned i=0; i<9; i++)
    {
        for(unsigned j=0; j <9; j++)
        {
            prov_atual = new QLabel;
            prov_atual->setAlignment(Qt::AlignCenter);
            prov_atual->setGeometry(0,0,30,30);
            if(tabe_atual.at(i,j) == 0 )
            {
                prov_atual->setText("");
                ui->linha->setText("A");
                ui->botao_jogar->setEnabled(false);
                ui->coluna->setNum(1);
            }
            else prov_atual->setNum(int(tabe_atual.at(i,j)));
            if(i ==0 & j== 0)prov_atual->setStyleSheet("background: lightyellow");

            else{
                if(((i<3 || i> 5) && j%6>2) || (j<3 || j> 5) && i%6>2)
                {
                    prov_atual->setStyleSheet("background:lightcyan");
                }
                else
                {
                    prov_atual->setStyleSheet("background:white");
                }
            }
            ui->tabela_atual->setCellWidget(i,j,prov_atual);
            prov_inici = new QLabel;
            prov_inici->setAlignment(Qt::AlignCenter);
            prov_inici->setGeometry(0,0,30,30);
            if(tabe_inic.at(i,j) == 0 )
            {
                prov_inici->setText("");
            }
            else prov_inici->setNum(int(tabe_inic.at(i,j)));
                if(((i<3 || i> 5) && j%6>2) || (j<3 || j> 5) && i%6>2)
                {
                    prov_inici->setStyleSheet("background:lightcyan");
                }
                else
                {
                    prov_inici->setStyleSheet("background:white");
                }
                ui->tabela_inicial->setCellWidget(i,j,prov_inici);
        }
        ui->caixa_de_valor->setRange(0,9);
        ui->caixa_de_valor->setWrapping(true);
        ui->caixa_de_valor->setSpecialValueText("Apagar");
    }
}

MainSoduko_visual::~MainSoduko_visual()
{
    delete ui;
}

void MainSoduko_visual::on_tabela_atual_cellClicked(int row, int column)
{
   QLabel *prov_atual = (QLabel*)(ui->tabela_atual->cellWidget(jogar.linha(),jogar.coluna()));
   if(((jogar.linha()<3 || jogar.linha()> 5) && jogar.coluna()%6>2) || (jogar.coluna()<3 || jogar.coluna()> 5) && jogar.linha()%6>2)
   {
        prov_atual->setStyleSheet("background:lightcyan");
   }
   else
   {
        prov_atual->setStyleSheet("background:white");
   }
   jogar.setCell(row,column);
   prov_atual = (QLabel*)(ui->tabela_atual->cellWidget(jogar.linha(),jogar.coluna()));
   prov_atual->setStyleSheet("background: lightyellow");
   ui->linha->setText(QString(jogar.linha()+'A'));
   ui->coluna->setNum(jogar.coluna()+1);
   on_caixa_de_valor_valueChanged(jogar.valor());
}

void MainSoduko_visual::on_botao_jogar_clicked()
{
    if(jogar.valor() ==0)
    {
        tabe_atual.apagar_jogada(jogar,tabe_inic);
    }
    else tabe_atual.fazer_jogada(jogar);
    tabe_atual.exibir();
    MainSoduko_visual::on_caixa_de_valor_valueChanged(jogar.valor());
}

void MainSoduko_visual::on_caixa_de_valor_valueChanged(int arg1)
{
    jogar.setValue(arg1);
    if(tabe_atual.jogada_valida(jogar) || tabe_atual.apagamento_valido(jogar,tabe_inic))
    {
        ui->botao_jogar->setEnabled(true);
    }
    else ui->botao_jogar->setEnabled(false);
}

void MainSoduko_visual::on_actionReiniciar_triggered()
{
    tabe_atual = tabe_inic;
    tabe_atual.exibir();
}

void MainSoduko_visual::exibirCelulaAtual(int i,int j, int valor)
{
     QLabel *prov = (QLabel*)(ui->tabela_atual->cellWidget(i,j));
     if(valor ==0) prov->setText("");
     else prov->setNum(valor);
}

void MainSoduko_visual::exibirCelulaInicial(int i, int j, int valor)
{
    QLabel *prov = (QLabel*)(ui->tabela_inicial->cellWidget(i,j));
    if(valor ==0) prov->setText("");
    else prov->setNum(valor);
}

void MainSoduko_visual::exibirCelulaAndamento(int Ntab_testados,int Ntab_gerados,int  Ntab_analisar)
{
    ui->statusBar->showMessage(QString("TABULEIROS: %1 testados, %2 gerados, %3 analisado" ).arg(Ntab_testados).arg(Ntab_gerados).arg(Ntab_analisar));
}

void MainSoduko_visual::on_Novo_triggered()
{
    tabe_inic.gerar();
    tabe_inic.exibir_origem();
    tabe_atual = tabe_inic;
    tabe_atual.exibir();
}

void MainSoduko_visual::on_Preencher_imediato_triggered()
{
    int num = tabe_atual.resolver_casas_faceis();
    tabe_atual.exibir();
    if(num>0) ui->statusBar->showMessage(QString::number(num) + QString(" casas preenchidas"));
    else if(num<0 && num>-81) ui->statusBar->showMessage(QString("TABULEIRO INSOLÚVEL! ")+ ((-num==1) ? QString("%1 casa preenchida.").arg(-num) : QString("%1 casas preeenchidas.").arg(-num)));
    else if(num <-81) ui->statusBar->showMessage(QString("TABELEIRO INSOLÚVEL!"));
    ui->Botao_cont->show();
    ui->Botao_cont->setEnabled(true);
    ui->botao_jogar->setEnabled(false);
    ui->caixa_de_valor->setEnabled(false);
}

void MainSoduko_visual::on_Resolver_triggered()
{
    tabe_atual.resolver(true);
    ui->Botao_cont->show();
    ui->Botao_cont->setEnabled(true);
    ui->botao_jogar->setEnabled(false);
    ui->caixa_de_valor->setEnabled(false);
}

void MainSoduko_visual::on_Sair_triggered()
{
    QCoreApplication::quit();
}

void MainSoduko_visual::on_Botao_cont_clicked()
{
    ui->botao_jogar->setEnabled(true);
    ui->caixa_de_valor->setEnabled(true);
    ui->Botao_cont->setEnabled(false);
    ui->statusBar->clearMessage();
    ui->statusBar->setEnabled(false);
    ui->Botao_cont->hide();
}
