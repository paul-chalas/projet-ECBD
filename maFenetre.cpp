#include "maFenetre.h"
#include "charger_csv.h"
#include "vector"

MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(800,600);

    m_predire = new QPushButton("Predire", this);
    m_predire->setGeometry(50,200,80,40);

    m_bou = new QPushButton("Quitter", this);
    m_bou->setGeometry(670,200,80,40);

    read_csv (m_mat, m_vet, "/home/c16024036/Téléchargements/build-tp_ecbd-Desktop-Debug/data.csv");

    m_fievre = new QComboBox(this);
    m_douleur = new QComboBox(this);
    m_toux = new QComboBox(this);

    initComboBox(0, m_fievre);
    initComboBox(1, m_douleur);
    initComboBox(2, m_toux);

    m_lnom = new QLabel("Nom :",this);
    m_lnom->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_lnom->move(400, 20);

    m_lprenom = new QLabel("Prenom :",this);
    m_lprenom->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_lprenom->move(400, 60);

    m_nom = new QLineEdit(this);
    m_nom->setGeometry(500,20,250,30);

    m_prenom = new QLineEdit(this);
    m_prenom->setGeometry(500,60,250,30);

    m_info = new QTableWidget(this);
    m_info->setGeometry(200,300,430,290);
    m_info->setRowCount(m_mat.size());
    m_info->setColumnCount(m_vet.size());

    QStringList tableHeader;
    for (unsigned i = 0; i < m_vet.size(); i++){
        tableHeader.append(QString::fromUtf8((m_vet[i].c_str())));
    }
    m_info->setHorizontalHeaderLabels(tableHeader);

    for (unsigned i = 0; i < m_mat.size(); i++){
        for (unsigned j = 0; j < m_mat[i].size(); j++){
            m_info->setItem(i, j, new QTableWidgetItem(QString::fromUtf8((m_mat[i][j].c_str()))));
        }
    }
    m_info->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_lpredire = new QLabel("", this);
    m_lpredire->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_lpredire->setGeometry(20,20,200,30);



    connect(m_bou, SIGNAL(clicked()), this, SLOT(setQuitter()));
    connect(m_predire, SIGNAL(clicked()), this, SLOT(predire()));
    //connect(m_fievre, SIGNAL(currentIndexChanged(const QString &)),this, SLOT(determinerConf()));
}

void MaFenetre::setQuitter()
{
    exit(0);
}

void MaFenetre::predire()
{
    cout << "prédiction !" << endl;

    QStringList maladies;
    for (unsigned j = 0; j < m_mat.size(); j++)
        maladies.append(QString::fromUtf8((m_mat[j][3].c_str())));
    maladies.removeDuplicates();

    vector<float> scores;

    for (int i = 0; i < maladies.size(); ++i){
        scores.push_back(determinerFreq(maladies.at(i).toStdString()));
    }

    float maxScore = 0;
    int indice = 0;
    for (unsigned i = 0; i < scores.size() ; ++i){
        if (scores[i] > maxScore){
            maxScore = scores[i];
            indice = i;
        }
    }
    if (maxScore == 0){
        m_lpredire->setText("Impossible de savoir :'(");
    } else {
        m_lpredire->setText(maladies.at(indice));
    }

}

float MaFenetre::determinerFreq(string maladie)
{
    float freq = 0;
    for (unsigned i = 0; i < m_mat.size(); i++){
        if (m_mat[i][3] == maladie){
            freq++;
        }
    }

    float freqFievre = 0;
    float freqDouleur = 0;
    float freqToux = 0;


    if (m_fievre->currentText().toStdString() == "NULL"){
        freqFievre = 1;
    } else{
        for (unsigned i = 0; i < m_mat.size(); i++){
            if (m_mat[i][3] == maladie && m_mat[i][0] == m_fievre->currentText().toStdString()){
                freqFievre++;
            }
        }
        freqFievre = freqFievre/freq;
    }

    if (m_douleur->currentText().toStdString() == "NULL"){
        freqDouleur = 1;
    } else{
        for (unsigned i = 0; i < m_mat.size(); i++){
            if (m_mat[i][3] == maladie && m_mat[i][1] == m_douleur->currentText().toStdString()){
                freqDouleur++;
            }
        }
        freqDouleur = freqDouleur/freq;
    }

    if (m_toux->currentText().toStdString() == "NULL"){
        freqToux = 1;
    } else{
        for (unsigned i = 0; i < m_mat.size(); i++){
            if (m_mat[i][3] == maladie && m_mat[i][2] == m_toux->currentText().toStdString()){
                freqToux++;
            }
        }
        freqToux = freqToux/freq;
    }

    freq = freq/m_mat.size();

    float score = freq * freqFievre * freqDouleur * freqToux;

    cout << "Score de " << maladie << " : " << score << endl;

    return (score);
}


void MaFenetre::initComboBox(int i, QComboBox* box)
{
    QString qs = QString::fromUtf8(m_vet[i].c_str());
    m_lab = new QLabel (qs, this);
    m_lab->setFont(QFont("Arial",12,QFont::Bold,true));
    m_lab->move(320 + (100*i),125);

    box->setGeometry(300 + (100*i),150,100,30);
    QStringList tmp;
    for (unsigned j = 0; j < m_mat.size(); j++)
        tmp.append(QString::fromUtf8((m_mat[j][i].c_str())));
    tmp.removeDuplicates();
    box->addItem("NULL");
    box->addItems(tmp);
}
