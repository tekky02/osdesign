// authorinfo.hh
// created by tekky on 2021.3.9.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QMONITOR_AUTHORINFO_HH__
#define __QMONITOR_AUTHORINFO_HH__

#include <QLabel>
#include <QWidget>

class AuthorInfo : public QWidget {
  Q_OBJECT

public:
  explicit AuthorInfo(QWidget *parent = nullptr);
  ~AuthorInfo();

private:
  QLabel *about_;
};

#endif // __QMONITOR_AUTHORINFO_HH__