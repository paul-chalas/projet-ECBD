#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QString>
#include <charger_csv.h>

class MaFenetre : public QMainWindow
{
    Q_OBJECT // Macro Obligatoire

public slots :
    void setQuitter();
    void predire();

public :
    MaFenetre(QWidget *parent = 0);
    void initComboBox(int i, QComboBox* box);
    int determinerFreq(string maladie);
    int determinerConf();
private :
    QLabel *m_lnom, *m_lprenom, *m_lab, *m_lpredire;
    QPushButton *m_bou, *m_predire;
    QComboBox *m_fievre, *m_douleur, *m_toux;
    QLineEdit *m_nom, *m_prenom;
    QTableWidget *m_info;
    QString couleur;

    CVString m_vet; //vecteur d'entete
    CMatString m_mat; //Matrice de données
};

#endif // MAFENETRE_H
