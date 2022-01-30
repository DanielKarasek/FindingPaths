#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "solutionsettingbar.h"
#include "mapeditbar.h"
#include "solutionpaintdevice.h"
#include "mediator.h"

#include <QHBoxLayout>
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(Mediator &mediator, QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void show_solution_bar();
  void show_map_edit_bar();

protected:
  SolutionSettingBar *m_solution_set_bar;
  MapEditBar *m_map_edit_bar;
  SolutionPaintDevice *m_solution_paint_dev;

  QHBoxLayout *m_layout;

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
