#ifndef SUPPORTPROJECT_HPP
#define SUPPORTPROJECT_HPP

#include <QDialog>

namespace Ui {
class SupportProject;
}

class SupportProject : public QDialog
{
    Q_OBJECT

public:
    explicit SupportProject(QWidget *parent = 0);
    ~SupportProject();

private:
    Ui::SupportProject *ui;
};

#endif // SUPPORTPROJECT_HPP
