#include "classificatsdialog.h"
#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>

ClassificatsDialog::ClassificatsDialog(QWidget *parent) :
    QDialog(parent),
    verticalLayout(new QVBoxLayout),
    formLayout(new QFormLayout)
{
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    QLabel *categoriaLabel = new QLabel("Categoria");
    categoriaLabel->setFont(font);
    QLabel *classificatsLabel = new QLabel("Classificats");
    classificatsLabel->setFont(font);
    formLayout->addRow(categoriaLabel, classificatsLabel);
    verticalLayout->addLayout(formLayout);
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    verticalLayout->addWidget(buttonBox);
    setLayout(verticalLayout);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &ClassificatsDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ClassificatsDialog::reject);
}

ClassificatsDialog::~ClassificatsDialog()
{
    delete formLayout;
}

QMap<QString, int> ClassificatsDialog::numClassificats() const
{
    QMap<QString, int> n_classificats;
    for (int i = 1; i < formLayout->rowCount(); ++i) {
        QWidget *labelWidget =
                formLayout->itemAt(i, QFormLayout::LabelRole)->widget();
        QWidget *spinBoxWidget =
                formLayout->itemAt(i, QFormLayout::FieldRole)->widget();
        //QString cat = dynamic_cast<QLabel*>(labelWidget)->text();
        QString cat = labelWidget->property("text").toString();
        //int num = dynamic_cast<QSpinBox*>(spinBoxWidget)->value();
        int num = spinBoxWidget->property("value").toInt();
        if (num > 0) {
            n_classificats[cat] = num;
        }
    }
    return n_classificats;
}

void ClassificatsDialog::setCategories(const QMap<QString, int> &cats)
{
    QMapIterator<QString, int> it(cats);
    while (it.hasNext()) {
        it.next();
        QLabel *nomCatLabel = new QLabel(it.key());
        QSpinBox *classificats = new QSpinBox;
        classificats->setMinimum(0);
        classificats->setMaximum(it.value());
        formLayout->addRow(nomCatLabel, classificats);
    }
}
