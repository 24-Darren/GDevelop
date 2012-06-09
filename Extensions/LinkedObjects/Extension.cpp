/**

Game Develop - LinkedObjects Extension
Copyright (c) 2008-2012 Florian Rival (Florian.Rival@gmail.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.

*/

#include "GDL/ExtensionBase.h"
#include "ObjectsLinksManager.h"
#include "GDL/Version.h"
#include <boost/version.hpp>
#include <iostream>

/**
 * \brief This class declares information about the extension.
 */
class Extension : public ExtensionBase
{
    public:

        /**
         * Constructor of an extension declares everything the extension contains : Objects, actions, conditions and expressions.
         */
        Extension()
        {
            DECLARE_THE_EXTENSION("LinkedObjects",
                                  _("Associations d'objets"),
                                  _("Extension permettant d'associer virtuellement des objets entre eux et de les retrouver ensuite."),
                                  "Compil Games",
                                  "zlib/libpng License ( Open Source )")

            #if defined(GD_IDE_ONLY)

            DECLARE_ACTION("LinkObjects",
                           _("Lier deux objets"),
                           _("Lier deux objets ensemble, pour pouvoir retrouver l'un � partir de l'autre."),
                           _("Lier _PARAM3_ et _PARAM4_"),
                           _("Associations d'objets"),
                           "Extensions/LinkedObjectsicon24.png",
                           "Extensions/LinkedObjectsicon16.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "3");
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "4");
                instrInfo.AddParameter("object", _("Objet 1"), "", false);
                instrInfo.AddParameter("object", _("Objet 2"), "", false);

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::LinkedObjects::LinkObjects").SetIncludeFile("LinkedObjects/LinkedObjectsTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("RemoveLinkBetween",
                           _("D�lier deux objets"),
                           _("D�lier deux objets."),
                           _("D�lier _PARAM3_ et _PARAM4_"),
                           _("Associations d'objets"),
                           "Extensions/LinkedObjectsicon24.png",
                           "Extensions/LinkedObjectsicon16.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "3");
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "4");
                instrInfo.AddParameter("object", _("Objet 1"), "", false);
                instrInfo.AddParameter("object", _("Objet 2"), "", false);

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::LinkedObjects::RemoveLinkBetween").SetIncludeFile("LinkedObjects/LinkedObjectsTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("RemoveAllLinksOf",
                           _("D�lier tous les objets d'un objet"),
                           _("D�lier tous les objets d'un objet."),
                           _("D�lier tous les objets li�s � _PARAM2_"),
                           _("Associations d'objets"),
                           "Extensions/LinkedObjectsicon24.png",
                           "Extensions/LinkedObjectsicon16.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "2");
                instrInfo.AddParameter("object", _("Objet"), "", false);

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::LinkedObjects::RemoveAllLinksOf").SetIncludeFile("LinkedObjects/LinkedObjectsTools.h");

            DECLARE_END_ACTION()

            DECLARE_CONDITION("PickObjectsLinkedTo",
                           _("Prendre en compte des objets li�s"),
                           _("Prends en compte des objets li�s � un objet pour les prochaines conditions et actions.\nLa condition renvoie faux si aucun objet n'a �t� pris en compte."),
                           _("Prendre en compte tous les objets \"_PARAM5_\" li�s � _PARAM3_"),
                           _("Associations d'objets"),
                           "Extensions/LinkedObjectsicon24.png",
                           "Extensions/LinkedObjectsicon16.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameterWithoutPicking", "5");
                instrInfo.AddCodeOnlyParameter("inlineCode", "0"); //For backward compatibility
                instrInfo.AddParameter("object", _("Objet"), "", false);
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "3");
                instrInfo.AddParameter("object", _("Objets li�s � prendre en compte"), "", false);

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::LinkedObjects::PickObjectsLinkedTo").SetIncludeFile("LinkedObjects/LinkedObjectsTools.h");

            DECLARE_END_CONDITION()

            DECLARE_ACTION("PickObjectsLinkedTo",
                           _("Prendre en compte des objets li�s"),
                           _("Prends en compte des objets li�s � un objet pour les prochaines actions."),
                           _("Prendre en compte tous les objets \"_PARAM5_\" li�s � _PARAM3_"),
                           _("Associations d'objets"),
                           "Extensions/LinkedObjectsicon24.png",
                           "Extensions/LinkedObjectsicon16.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameterWithoutPicking", "5");
                instrInfo.AddCodeOnlyParameter("inlineCode", "0"); //For backward compatibility
                instrInfo.AddParameter("object", _("Objet"), "", false);
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "3");
                instrInfo.AddParameter("object", _("Objets li�s � prendre en compte"), "", false);

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::LinkedObjects::PickObjectsLinkedTo").SetIncludeFile("LinkedObjects/LinkedObjectsTools.h");

            DECLARE_END_ACTION()

            #endif

            CompleteCompilationInformation();
        };
        virtual ~Extension() {};

        /**
         * The extension must be aware of objects deletion
         */
        virtual bool ToBeNotifiedOnObjectDeletion() { return true; }

        /**
         * Be sure to remove all links when an object is deleted
         */
        virtual void ObjectDeletedFromScene(RuntimeScene & scene, Object * object)
        {
            GDpriv::LinkedObjects::ObjectsLinksManager::managers[&scene].RemoveAllLinksOf(object);
        }

        /**
         * Initialize manager of linked objects of scene
         */
        virtual void SceneLoaded(RuntimeScene & scene)
        {
            GDpriv::LinkedObjects::ObjectsLinksManager::managers[&scene].ClearAll();
        }

        /**
         * Destroy manager of linked objects of scene
         */
        virtual void SceneUnloaded(RuntimeScene & scene)
        {
            GDpriv::LinkedObjects::ObjectsLinksManager::managers.erase(&scene);
        }

    protected:
    private:

        /**
         * This function is called by Game Develop so
         * as to complete information about how the extension was compiled ( which libs... )
         * -- Do not need to be modified. --
         */
        void CompleteCompilationInformation()
        {
            #if defined(GD_IDE_ONLY)
            compilationInfo.runtimeOnly = false;
            #else
            compilationInfo.runtimeOnly = true;
            #endif

            #if defined(__GNUC__)
            compilationInfo.gccMajorVersion = __GNUC__;
            compilationInfo.gccMinorVersion = __GNUC_MINOR__;
            compilationInfo.gccPatchLevel = __GNUC_PATCHLEVEL__;
            #endif

            compilationInfo.boostVersion = BOOST_VERSION;

            compilationInfo.sfmlMajorVersion = 2;
            compilationInfo.sfmlMinorVersion = 0;

            #if defined(GD_IDE_ONLY)
            compilationInfo.wxWidgetsMajorVersion = wxMAJOR_VERSION;
            compilationInfo.wxWidgetsMinorVersion = wxMINOR_VERSION;
            compilationInfo.wxWidgetsReleaseNumber = wxRELEASE_NUMBER;
            compilationInfo.wxWidgetsSubReleaseNumber = wxSUBRELEASE_NUMBER;
            #endif

            compilationInfo.gdlVersion = RC_FILEVERSION_STRING;
            compilationInfo.sizeOfpInt = sizeof(int*);

            compilationInfo.informationCompleted = true;
        }
};

/**
 * Used by Game Develop to create the extension class
 * -- Do not need to be modified. --
 */
extern "C" ExtensionBase * GD_EXTENSION_API CreateGDExtension() {
    return new Extension;
}

/**
 * Used by Game Develop to destroy the extension class
 * -- Do not need to be modified. --
 */
extern "C" void GD_EXTENSION_API DestroyGDExtension(ExtensionBase * p) {
    delete p;
}
