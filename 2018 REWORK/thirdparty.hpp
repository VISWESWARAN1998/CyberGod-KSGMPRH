#ifndef THIRDPARTY_HPP
#define THIRDPARTY_HPP

#include <QDialog>

namespace Ui {
class ThirdParty;
}

class ThirdParty : public QDialog
{
    Q_OBJECT

public:
    explicit ThirdParty(QWidget *parent = 0);
    ~ThirdParty();

private:
    Ui::ThirdParty *ui;
};

#endif // THIRDPARTY_HPP
