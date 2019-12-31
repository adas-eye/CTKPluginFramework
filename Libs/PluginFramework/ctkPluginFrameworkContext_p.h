/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#ifndef CTKPLUGINFRAMEWORKCONTEXT_P_H
#define CTKPLUGINFRAMEWORKCONTEXT_P_H

#include <QDebug>
#include <QMutex>
#include <QDir>

#include "ctkPluginFrameworkFactory.h"
#include "ctkPluginFramework.h"
#include "ctkPluginStorage_p.h"
#include "ctkPlugins_p.h"
#include "ctkPluginFrameworkListeners_p.h"
#include "ctkPluginFrameworkDebug_p.h"


class ctkPlugin;
class ctkPluginStorage;
class ctkServices;

/**
 * \ingroup PluginFramework
 * 插件框架上下文
 */
class ctkPluginFrameworkContext
{

public:

  /**
   * All plugins in this framework. 包含了所有插件
   */
  ctkPlugins* plugins;

  /**
   * All listeners in this framework. 此框架中的所有侦听器
   */
  ctkPluginFrameworkListeners listeners;

  /**
   * All registered services in this framework. 此框架中的所有注册服务
   */
  ctkServices* services;

  /**
   * System plugin 系统插件
   */
  QSharedPointer<ctkPluginFramework> systemPlugin;

  /**
   * ctkPlugin storage  ctkPlugin存储
   */
  ctkPluginStorage* storage;

  /**
   * Private Plugin data storage 私有插件数据存储
   */
  QDir dataStorage;

  /**
   * First framework init  首次框架初始化状态
   */
  bool firstInit;

  /**
   * Framework id.  当前框架的id
   */
  int id;

  /**
   * global lock. 全局锁
   */
  static QMutex globalFwLock;

  /**
   * Id to use for next instance of plugin framework. 用于插件框架的下一个实例的Id。
   */
  static int globalId;

  ctkProperties& props;

  /**
   * Debug handle.
   */
  ctkPluginFrameworkDebug debug;

  /**
   * Contruct a framework context
   *
   */
  ctkPluginFrameworkContext();

  ~ctkPluginFrameworkContext();


  /**
   * Initialize the framework
   *
   */
  void init();


  /**
   * Undo as much as possible of what init() does.
   *
   */
  void uninit();


  /**
   *
   */
  int getId() const;

  /**
   * Get private plugin data storage file handle
   */
  QFileInfo getDataStorage(long id);

  /**
   * Check that the plugin belongs to this framework instance.
   *
   */
  void checkOurPlugin(ctkPlugin* plugin) const;


  /**
   * Check that the plugin specified can resolve all its
   * Require-ctkPlugin constraints.
   *
   * @param plugin ctkPlugin to check, must be in INSTALLED state
   *
   * @throws ctkPluginException 解析插件
   */
  void resolvePlugin(ctkPluginPrivate* plugin);


  /**
   * Log message for debugging framework
   *
   */
  QDebug log() const;

private:

  QSet<ctkPluginPrivate*> tempResolved;

  bool initialized;

  /**
   * Delete framework directory if it exists.
   *
   */
  void deleteFWDir();

  void checkRequirePlugin(ctkPluginPrivate* plugin);

  void initProperties();
};


#endif // CTKPLUGINFRAMEWORKCONTEXT_P_H
