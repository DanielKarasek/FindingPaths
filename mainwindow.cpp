#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "solutionpaintdevice.h"
#include "solutionsettingbar.h"
#include "mapeditbar.h"
#include "mediator.h"
#include "map.h"

#include <QHBoxLayout>

#include <iostream>

MainWindow::MainWindow(Mediator &mediator,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_map_edit_bar = new MapEditBar();
  m_solution_set_bar = new SolutionSettingBar();

  m_solution_paint_dev = new SolutionPaintDevice(this->size().width()-100);

  m_solution_set_bar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  m_map_edit_bar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  m_solution_paint_dev->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  mediator.attach_solution_paint_dev(m_solution_paint_dev);
  QObject::connect(m_solution_set_bar, &SolutionSettingBar::start_clicked, &mediator, &Mediator::start_solve);
  QObject::connect(m_solution_set_bar, &SolutionSettingBar::reset_clicked, &mediator, &Mediator::reset_solve);
  QObject::connect(m_solution_set_bar, &SolutionSettingBar::pause_clicked, &mediator, &Mediator::toggle_pause_flag);
  QObject::connect(m_solution_set_bar, &SolutionSettingBar::change_step_time, &mediator, &Mediator::change_step_time);

  QObject::connect(m_solution_set_bar, &SolutionSettingBar::map_edit_clicked, this, &MainWindow::show_map_edit_bar);
  QObject::connect(m_solution_set_bar, &SolutionSettingBar::map_edit_clicked, &mediator, &Mediator::reset_solve);
  QObject::connect(m_solution_set_bar, &SolutionSettingBar::combo_box_changed, &mediator, &Mediator::set_method);


  QObject::connect(m_map_edit_bar, &MapEditBar::change_tile_type, m_solution_paint_dev, &SolutionPaintDevice::set_modification_tile_type);
  QObject::connect(m_map_edit_bar, &MapEditBar::ret_button_clicked, this, &MainWindow::show_solution_bar);
  m_layout = new QHBoxLayout();
  m_layout->addWidget(m_solution_paint_dev);
  m_layout->addWidget(m_solution_set_bar);
  m_layout->addWidget(m_map_edit_bar);
  this->centralWidget()->setLayout(m_layout);
  show_solution_bar();
}

MainWindow::~MainWindow()
{
  delete ui;
}



void MainWindow::show_solution_bar()
{
  m_solution_set_bar->setVisible(true);
  m_map_edit_bar->setVisible(false);

  m_solution_paint_dev->set_modification(false);
}
void MainWindow::show_map_edit_bar()
{
  m_solution_set_bar->setVisible(false);
  m_map_edit_bar->setVisible(true);

  m_solution_paint_dev->set_modification(true);
  m_solution_paint_dev->set_modification_tile_type(Map::empty);
  m_map_edit_bar->set_combo_box_val("empty");
}

//SolutionSettingBar *solution_set_bar;
//MapEditBar *map_edit_bar;
