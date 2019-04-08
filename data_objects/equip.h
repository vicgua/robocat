#ifndef EQUIP_H
#define EQUIP_H

#include <QObject>
#include <QString>

class Equip
{
    Q_GADGET
    Q_PROPERTY(QString nomEquip MEMBER m_nomEquip WRITE setNomEquip RESET resetNomEquip)
    Q_PROPERTY(QString nomEquipOriginal MEMBER m_nomEquipOriginal CONSTANT)
public:
    explicit Equip(QString nomEquip) {
        m_nomEquip = nomEquip;
        m_nomEquipOriginal = nomEquip;
    }

    QString nomEquip() const {
        return m_nomEquip;
    }
    void setNomEquip(const QString &nomEquip) {
        if (nomEquip.isEmpty()) {
            throw "Nom equip no pot estar buit";
        }
        m_nomEquip = nomEquip;
    }
    void resetNomEquip() {
        m_nomEquip = m_nomEquipOriginal;
    }

    QString nomEquipOriginal() const {
        return m_nomEquipOriginal;
    }

    bool operator<(const Equip &other) const {
        return m_nomEquip < other.m_nomEquip;
    }

    bool operator==(const Equip &other) const {
        return m_nomEquip == other.m_nomEquip;
    }

private:
    QString m_nomEquip;
    QString m_nomEquipOriginal;
};

#endif // EQUIP_H
