#include "AboutDialog.h"

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

AboutDialog::AboutDialog(QWidget* parent) :
    QDialog(parent)
{
	QLabel* aboutText = new QLabel("This application was developed by Alex Fish in 2023.", this);
	
	QPushButton* okButton = new QPushButton("OK",this);
	okButton->setDefault(true);
	okButton->setIcon(QIcon());
	connect(okButton, &QPushButton::clicked, this, &AboutDialog::close);
	
	QGridLayout* layout = new QGridLayout();
	layout->setSizeConstraint(QLayout::SetFixedSize);
	layout->addWidget(aboutText,1,1,Qt::AlignCenter);
	layout->addWidget(okButton,2,1,Qt::AlignCenter);	

	setLayout(layout);
	setWindowTitle("About");
}

AboutDialog::~AboutDialog()
{
} 
