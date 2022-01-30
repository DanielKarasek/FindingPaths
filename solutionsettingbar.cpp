#include "solutionsettingbar.h"

#include "valuelabeledslider.h"

#include <QPushButton>
#include <QComboBox>

#include <QVBoxLayout>

/**
* tlacitka:
* Start - zacne resit od nuly (jen emit na mediator)
* Reset - vrati nas na nulu, ale nezacne automaticky (jen emit na mediator)
* Pause - pauzne unpauzne (zmena textu, emit na mediator)
* uprava mapy (emit na mediator a mainwindow - domyslet propojeni z main window)
* KAZDEMU TLACITKU PRIDAT EMIT (pokud se emitne tak -> volat svuj slot
*                               ktery to emitne ven + inner veci)
* hybatko
* Velikost casoveho kroku - vydedit slider, a nastavit vystupni hodnotu
*                           na 10-2000 nebo takove nejake rozmezi + mozna pridat text(najit stack overflow)
*                         - hodi emit smerem na mediator(tady bylo nejake to jak se to meni hodnekrat za sec, bacha)
**/

SolutionSettingBar::SolutionSettingBar(QWidget *parent)
  : QWidget{parent}
{
  m_start_button = new QPushButton("Start", this);
  m_reset_button = new QPushButton("Reset", this);
  m_pause_button = new QPushButton("Pause", this);
  m_change_step_time = new QPushButton("apply step time", this);

  m_map_edit_button = new QPushButton("Edit Map", this);

  m_slider = new ValueLabeledSlider(10, 5000, Qt::Horizontal, this);
  m_slider->setValue(1000);

  m_method_combobox = new QComboBox(this);
  m_method_combobox->addItem("alphastar");
  m_method_combobox->addItem("BFS");
  m_method_combobox->addItem("DFS");


  QObject::connect(m_start_button, &QPushButton::clicked, this, [this](){emit start_clicked();});
  QObject::connect(m_reset_button, &QPushButton::clicked, this, [this](){emit reset_clicked();});
  QObject::connect(m_pause_button, &QPushButton::clicked, this, [this](){toggle_pause();emit pause_clicked();});
  QObject::connect(m_map_edit_button, &QPushButton::clicked, this, [this](){emit map_edit_clicked();});
  QObject::connect(m_change_step_time, &QPushButton::clicked, this, [this](){emit change_step_time(m_slider->value());});
  QObject::connect(m_method_combobox, &QComboBox::currentTextChanged, this, [this](){emit combo_box_changed(m_method_combobox->currentText().toStdString());});

  m_slider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  m_layout = new QVBoxLayout;
  m_layout->setAlignment(Qt::AlignTop);
  m_layout->addWidget(m_start_button);
  m_layout->addWidget(m_reset_button);
  m_layout->addWidget(m_pause_button);
  m_layout->addWidget(m_slider);
  m_layout->addWidget(m_change_step_time);
  m_layout->addStretch(20);
  m_layout->addWidget(m_method_combobox);
  m_layout->addStretch(10000);


  m_layout->addWidget(m_map_edit_button);
  this->setLayout(m_layout);
}


void SolutionSettingBar::toggle_pause()
{
  m_pause_flag = !m_pause_flag;
  m_pause_button->setText(m_pause_text[m_pause_flag]);
}


