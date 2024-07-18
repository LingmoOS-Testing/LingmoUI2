/*
 * (C) Copyright 2024 Elysia. All Rights Reserved.
 * Description: LingmoApp.hpp
 * Author: Elysia <c.elysia@foxmail.com>
 * Date: 24-7-18
 * Modify Record:
 */
#ifndef LINGMOAPP_HPP
#define LINGMOAPP_HPP

#include <QObject>
#include <QQmlEngine>
#include <QTranslator>

#include "singleton.hpp"
#include "stdafx.hpp"

/**
 * @brief The LingmoApp class.
 */
class LingmoApp : public QObject {
  Q_OBJECT
  Q_PROPERTY_AUTO(bool, useSystemAppBar)
  Q_PROPERTY_AUTO(QString, windowIcon)
  Q_PROPERTY_AUTO(QLocale, locale)
  Q_PROPERTY_AUTO_P(QObject *, launcher)
  QML_NAMED_ELEMENT(LingmoApp)
  QML_SINGLETON

 private:
  explicit LingmoApp(QObject *parent = nullptr);

  ~LingmoApp() override;

 public:
  SINGLETON(LingmoApp)

  inline static LingmoApp *create(QQmlEngine *, QJSEngine *) {
    return LingmoApp::getInstance();
  }

  /**
   * @brief init - function to init the App
   * @param launcher
   * @param locale
   */
  Q_INVOKABLE void init(QObject *launcher, QLocale locale = QLocale::system());

 private:
  QQmlEngine *_engine{};
  QTranslator *_translator = nullptr;
};

#endif  // LINGMOAPP_HPP
