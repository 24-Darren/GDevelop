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
                                  _("Linked objects"),
                                  _("Extension allowing to virtually link two objects."),
                                  "Compil Games",
                                  "zlib/libpng License ( Open Source )")

            #if defined(GD_IDE_ONLY)

            DECLARE_ACTION("LinkObjects",
                           _("Link two objects"),
                           _("Link two objects together, so as to be able to get one from the other."),
                           _("Link _PARAM3_ and _PARAM4_"),
                           _("Linked objects"),
                           "Extensions/LinkedObjectsicon24.png",
                           "Extensions/LinkedObjectsicon16.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "3");
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "4");
                instrInfo.AddParameter("object", _("Object 1"), "", false);
                instrInfo.AddParameter("object", _("Object 2"), "", false);

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::LinkedObjects::LinkObjects").SetIncludeFile("LinkedObjects/LinkedObjectsTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("RemoveLinkBetween",
                           _("Unlink two objects"),
                           _("Unlink two objects."),
                           _("Unlink _PARAM3_ and _PARAM4_"),
                           _("Linked objects"),
                           "Extensions/LinkedObjectsicon24.png",
                           "Extensions/LinkedObjectsicon16.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "3");
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "4");
                instrInfo.AddParameter("object", _("Object 1"), "", false);
                instrInfo.AddParameter("object", _("Object 2"), "", false);

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::LinkedObjects::RemoveLinkBetween").SetIncludeFile("LinkedObjects/LinkedObjectsTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("RemoveAllLinksOf",
                           _("Unlink all objects from an object"),
                           _("Unlink all objects from an object."),
                           _("Unlink all objects from _PARAM2_"),
                           _("Linked objects"),
                           "Extensions/LinkedObjectsicon24.png",
                           "Extensions/LinkedObjectsicon16.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "2");
                instrInfo.AddParameter("object", _("Object"), "", false);

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::LinkedObjects::RemoveAllLinksOf").SetIncludeFile("LinkedObjects/LinkedObjectsTools.h");

            DECLARE_END_ACTION()

            DECLARE_CONDITION("PickObjectsLinkedTo",
                           _("Take into account linked objects"),
                           _("Take some objects linked to the object into account for next conditions and actions.\nThe condition will return false if no object was taken into account."),
                           _("Take into account all \"_PARAM5_\" linked to _PARAM3_"),
                           _("Linked objects"),
                           "Extensions/LinkedObjectsicon24.png",
                           "Extensions/LinkedObjectsicon16.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameterWithoutPicking", "5");
                instrInfo.AddCodeOnlyParameter("inlineCode", "0"); //For backward compatibility
                instrInfo.AddParameter("object", _("Object"), "", false);
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "3");
                instrInfo.AddParameter("object", _("Linked objects to be taken in account"), "", false);

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::LinkedObjects::PickObjectsLinkedTo").SetIncludeFile("LinkedObjects/LinkedObjectsTools.h");

            DECLARE_END_CONDITION()

            DECLARE_ACTION("PickObjectsLinkedTo",
                           _("Take into account linked objects"),
                           _("Take objects linked to the object into account for next actions."),
                           _("Take into account all \"_PARAM5_\" linked to _PARAM3_"),
                           _("Linked objects"),
                           "Extensions/LinkedObjectsicon24.png",
                           "Extensions/LinkedObjectsicon16.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameterWithoutPicking", "5");
                instrInfo.AddCodeOnlyParameter("inlineCode", "0"); //For backward compatibility
                instrInfo.AddParameter("object", _("Object"), "", false);
                instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "3");
                instrInfo.AddParameter("object", _("Linked objects to be taken in account"), "", false);

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

