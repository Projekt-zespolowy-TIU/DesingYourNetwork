#include "RaportDialog.h"
#include "ui_RaportDialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QFile>
#include <QDir>
#include <QTextStream>


#include "IPstructs.h"

using namespace core;

RaportDialog::RaportDialog(Networkv4 network, std::vector<std::shared_ptr<Subnet>> subnets,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RaportDialog)
{
    ui->setupUi(this);

    this->network = network;
    this->subnets = subnets;

    displayNetworkRaport();
}

RaportDialog::~RaportDialog()
{
    delete ui;
}

void RaportDialog::displayNetworkRaport()
{
    ui->raportScrollContent->setLayout(raportLayout);

    raportText->setFrameStyle(0);

    raportText->append("Network \n");
    raportText->append("Address: " + network.Ip->asStringDec());
    raportText->append(network.Ip->asStringBin());
    raportText->append("Mask " + network.NetMask->asStringDec());
    raportText->append(network.NetMask->asStringBin());
    raportText->append("Host capacity: " + QString::number(network.hostsCapacity()));

    raportLayout->addWidget(raportText);

    for(int i = 0; i < static_cast<int>(subnets.size()); i++)
    {
        raportText->append("\nSubnet " + QString::number(1 + i) + "\n");
        raportText->append("Address: " + subnets.at(i)->Ip->asStringDec());
        raportText->append(subnets.at(i)->Ip->asStringBin());
        raportText->append("Mask " + subnets.at(i)->NetMask->asStringDec());
        raportText->append(subnets.at(i)->NetMask->asStringBin());
        raportText->append("Hosts: " + QString::number(subnets.at(i)->HostNumber) + "/" + QString::number(subnets.at(i)->hostsCapacity()));
    }
}

void RaportDialog::on_saveButton_clicked()
{
    QString dir = QCoreApplication::applicationDirPath();
    QString filename = dir.append("/raport.txt");
    QFile file(filename);
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream(&file);
        stream << raportText->toPlainText() << endl;
    }
}