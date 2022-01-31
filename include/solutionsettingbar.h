#ifndef SOLUTIONSETTINGBAR_H
#define SOLUTIONSETTINGBAR_H

#include "valuelabeledslider.h"

#include <QObject>
#include <QWidget>

#include <QPushButton>
#include <QComboBox>

#include <QVBoxLayout>
#include <QString>
#include <string>

class SolutionSettingBar : public QWidget
{
  Q_OBJECT
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
public:
  explicit SolutionSettingBar(QWidget *parent = nullptr);
  //  void connect_start_button_click(const QObject *receiver, PointerToMemberFunction method)

protected:
  void toggle_pause();

  QPushButton *m_start_button;
  QPushButton *m_reset_button;
  QPushButton *m_pause_button;
  QPushButton *m_map_edit_button;
  QPushButton *m_change_step_time;
  QComboBox *m_method_combobox;

  ValueLabeledSlider *m_slider;


  QVBoxLayout *m_layout;

  QString m_pause_text[2]{"pause", "unpause"};
  bool m_pause_flag{false};
signals:
  void start_clicked();
  void reset_clicked();
  void pause_clicked();
  void map_edit_clicked();
  void combo_box_changed(const std::string &str);
  void change_step_time(int ms);
};

#endif // SOLUTIONSETTINGBAR_H
