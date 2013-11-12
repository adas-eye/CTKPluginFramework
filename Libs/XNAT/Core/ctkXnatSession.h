/*=============================================================================

  Plugin: org.commontk.xnat

  Copyright (c) University College London,
    Centre for Medical Image Computing

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

#ifndef CTKXNATSESSION_H
#define CTKXNATSESSION_H

#include "ctkXNATCoreExport.h"

#include <QScopedPointer>
#include <QString>

#include <QObject>
#include <QVariantMap>
#include <QUuid>

class ctkXnatSessionPrivate;

class ctkXnatDataModel;
class ctkXnatExperiment;
class ctkXnatFile;
class ctkXnatLoginProfile;
class ctkXnatObject;
class ctkXnatProject;
class ctkXnatReconstruction;
class ctkXnatReconstructionFolder;
class ctkXnatReconstructionResource;
class ctkXnatRoot;
class ctkXnatScan;
class ctkXnatScanFolder;
class ctkXnatScanResource;
class ctkXnatSubject;

class CTK_XNAT_CORE_EXPORT ctkXnatSession
{

public:

  //********
  // Add ctkXnatLoginProfile argument
  ctkXnatSession(const ctkXnatLoginProfile& loginProfile);
  ~ctkXnatSession();

  // **********
  // Remove ?
  // For Qt singal/slots; should go into the constructor or private impl.
  void createConnections();

  /**
   * @brief Get the current login profile for this session object.
   * @return A copy of the currently used login profile.
   */
  ctkXnatLoginProfile loginProfile() const;

  /**
   * @brief Get XNAT server url.
   *
   * The url is the one specified by the login profile.
   *
   * @return The XNAT server url.
   */
  QUrl url() const;

  /**
   * @brief Get the user name for this XNAT session.
   *
   * The user name is the one specified by the login profile.
   *
   * @return The XNAT session user name.
   */
  QString userName() const;

  /**
   * @brief Get the password for this XNAT session.
   *
   * The password is the one specified by the login profile.
   *
   * @return The XNAT session password.
   */
  QString password() const;

  ctkXnatDataModel* dataModel() const;

  // **********
  // Should these methods still be moved to the subclasses?
  void fetch(ctkXnatDataModel* server);
  void fetch(ctkXnatProject* project);
  void fetch(ctkXnatSubject* subject);
  void fetch(ctkXnatExperiment* experiment);
  void fetch(ctkXnatScanFolder* scanFolder);
  void fetch(ctkXnatScan* scan);
  void fetch(ctkXnatScanResource* scanResource);
  void fetch(ctkXnatReconstructionFolder* reconstructionFolder);
  void fetch(ctkXnatReconstruction* reconstruction);
  void fetch(ctkXnatReconstructionResource* reconstructionResource);

  bool exists(const ctkXnatObject* object);

  void save(ctkXnatObject* object);
  void remove(ctkXnatObject* object);

  void download(ctkXnatFile* file, const QString& fileName);

//  void downloadScanFiles(ctkXnatExperiment* experiment, const QString& zipFileName);
//  void downloadReconstructionFiles(ctkXnatExperiment* experiment, const QString& zipFileName);

//  void download(ctkXnatScan* scan, const QString& zipFileName);

  void download(ctkXnatScanResource* scanResource, const QString& zipFileName);
  void download(ctkXnatReconstructionResource* reconstructionResource, const QString& zipFileName);

//  void downloadReconstruction(ctkXnatReconstruction* reconstruction, const QString& zipFilename);

//  void downloadReconstructionResourceFiles(ctkXnatReconstructionResource* reconstructionResource, const QString& zipFilename);

//  void download(ctkXnatReconstructionResourceFile* reconstructionResourceFile, const QString& zipFileName);

public slots:
  void processResult(QUuid queryId, QList<QVariantMap> parameters);
  void progress(QUuid queryId, double progress);

protected:
  QScopedPointer<ctkXnatSessionPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(ctkXnatSession)
  Q_DISABLE_COPY(ctkXnatSession)
};

#endif
