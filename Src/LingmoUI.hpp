/*
 * (C) Copyright 2024 Elysia. All Rights Reserved.
 * Description: LingmoUI.hpp
 * Author: Elysia <c.elysia@foxmail.com>
 * Date: 24-7-17
 * Modify Record:
 */
#ifndef LINGMOUI_HPP
#define LINGMOUI_HPP

#include <QObject>
#include <QQmlEngine>
#include <QQmlEngineExtensionPlugin>

#include "singleton.hpp"

/**
 * @brief The LingmoUI class
 */
class LingmoUI : public QQmlExtensionPlugin {
  Q_OBJECT

 public:
  SINGLETON(LingmoUI)

  Q_DECL_EXPORT void registerTypes(QQmlEngine *engine);

  void registerTypes(const char *uri) const;

  void initializeEngine(QQmlEngine *engine, [[maybe_unused]] const char *uri);

 private:
  const int _major = 2;
  const int _minor = 0;
  const char *_uri = "LingmoUI";
};

#endif  // LINGMOUI_HPP
