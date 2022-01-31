#ifndef MAPEDITBAR_H
#define MAPEDITBAR_H

#include "map.h"

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QVBoxLayout>


class MapEditBar : public QWidget
{
  Q_OBJECT
  /**
   * tlacitka:
   * Vratit k reseni - vrati se k solutionsettingbaru ->(emit na main window)
   * Vytvorit novou mapu dle boxiku (neni asi treba constr, ale nejaka metoda)
   * Combobox
   * - zde dat jaky typ zmeny chceme (oddelat typ zmeny z solutionpaintdevice)
   * 2 zapsatelne boxy, povolujici jen cela cisla -> velikost prazdne mapy
   **/
public:
  explicit MapEditBar(QWidget *parent = nullptr);
  void set_combo_box_val(const QString &str);

protected:
  void combo_box_changed(QString str);

  QVBoxLayout *m_layout;

  QPushButton *m_ret_button;
  QComboBox *m_tile_type;
signals:
  void change_tile_type(Map::TileType);
  void ret_button_clicked();
};

#endif // MAPEDITBAR_H
