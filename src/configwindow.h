/*
 * Qt-ponies - ponies on the desktop
 * Copyright (C) 2012 mysha
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QStandardItemModel>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QSettings>
#include <QAction>
#include <QActionGroup>

#include <memory>
#include <iostream>

#include "pony.h"

namespace Ui {
    class ConfigWindow;
}

class ConfigWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = 0);
    ~ConfigWindow();


    std::list<std::shared_ptr<Pony>> ponies;
    QTimer timer;

    template <typename T>
    T getSetting(const QString& name) { return QSettings ("config.ini",QSettings::IniFormat).value(name).value<T>(); }


public slots:
    void remove_pony();
    void remove_pony_all();

private slots:
    void remove_pony_activelist();
    void newpony_list_changed(QModelIndex item);
    void add_pony();
    void update_active_list();
    void toggle_window(QSystemTrayIcon::ActivationReason reason);
    void save_settings();
    void load_settings();

private:
    Ui::ConfigWindow *ui;
    QSignalMapper *signal_mapper;
    QStandardItemModel *list_model;
    QStandardItemModel *active_list_model;
    QSystemTrayIcon tray_icon;
    QMenu tray_menu;
    QActionGroup *action_group;
    QAction *action_addponies;
    QAction *action_activeponies;
    QAction *action_configuration;

};

#endif // CONFIGWINDOW_H
