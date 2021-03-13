// authorinfo.cc.
// created by tekky on 2021.3.9.
// Copyright © 2021 tekky. All rights reserved.

#include "qmonitor/authorinfo.hh"

#include <QGridLayout>
#include <QLabel>

#include "resources.h"

AuthorInfo::AuthorInfo(QWidget *parent) : QWidget{parent} {
  auto layout = new QGridLayout(this);
  about_ = new QLabel(tk::resources::About);
  layout->addWidget(about_);
}

AuthorInfo::~AuthorInfo() {}