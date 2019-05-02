#ifndef CLASSIFICATSDIALOG_H
#define CLASSIFICATSDIALOG_H

#include <QDialog>
#include <QMap>
#include <QPair>
#include <QString>
#include <QFormLayout>
#include <QVBoxLayout>

class ClassificatsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ClassificatsDialog(QWidget *parent = nullptr);
    ~ClassificatsDialog();

    QMap<QString, int> numClassificats() const;

public slots:
    void setCategories(const QMap<QString, int> &cats);
private:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
};

#endif // CLASSIFICATSDIALOG_H
