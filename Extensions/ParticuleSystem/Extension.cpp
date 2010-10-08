/**

Game Develop - Particle System Extension
Copyright (c) 2010 Florian Rival (Florian.Rival@gmail.com)

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
#include "GDL/Version.h"
#include "ParticleEmitterObject.h"
#include <boost/version.hpp>

/**
 * This class declare information about the extension.
 */
class Extension : public ExtensionBase
{
    public:

        /**
         * Constructor of an extension declares everything the extension contains : Objects, actions, conditions and expressions.
         */
        Extension()
        {
            DECLARE_THE_EXTENSION("ParticleEmitterObject",
                                  _("Syst�me de particules"),
                                  _("Extension permettant d'afficher un grand nombre de petites particules."),
                                  "Compil Games",
                                  "zlib/libpng License ( Open Source )")

            //Declaration of all objects available
            DECLARE_OBJECT("ParticleEmitter",
                           _("Emetteur de particules"),
                           _("Objet affichant un texte"),
                           "Extensions/particleSystemicon.png",
                           &CreateParticleEmitterObject,
                           &DestroyParticleEmitterObject);

                DECLARE_OBJECT_ACTION("ChangeColor",
                               _("Changer la couleur d'un objet texte"),
                               _("Change la couleur du texte. Par d�faut, la couleur est le blanc."),
                               _("Changer la couleur de _PARAM0_ en _PARAM1_"),
                               _("Effets"),
                               "res/actions/color24.png",
                               "res/actions/color.png",
                               &ParticleEmitterObject::ActChangeColor);

                    DECLARE_PARAMETER("object", _("Objet"), true, "ParticleEmitter")
                    DECLARE_PARAMETER("color", _("Couleur"), false, "")
                    MAIN_OBJECTS_IN_PARAMETER(0)

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_ACTION("Opacity",
                               _("R�gler l'opacit� d'un objet"),
                               _("Modifie la transparence d'un objet texte."),
                               _("Faire _PARAM2__PARAM1_ � l'opacit� de _PARAM0_"),
                               _("Visibilit�"),
                               "res/actions/opacity24.png",
                               "res/actions/opacity.png",
                               &ParticleEmitterObject::ActOpacity);

                    DECLARE_PARAMETER("object", _("Objet"), true, "ParticleEmitter")
                    DECLARE_PARAMETER("expression", _("Valeur"), false, "")
                    DECLARE_PARAMETER("signe", _("Signe de la modification"), false, "")
                    MAIN_OBJECTS_IN_PARAMETER(0)

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("Opacity",
                               _("Opacit� d'un objet"),
                               _("Teste la valeur de l'opacit� ( transparence ) d'un objet texte."),
                               _("L'opacit� de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                               _("Visibilit�"),
                               "res/conditions/opacity24.png",
                               "res/conditions/opacity.png",
                               &ParticleEmitterObject::CondOpacity);

                    DECLARE_PARAMETER("object", _("Objet"), true, "ParticleEmitter")
                    DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
                    DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
                    MAIN_OBJECTS_IN_PARAMETER(0)

                DECLARE_END_OBJECT_CONDITION()


                DECLARE_OBJECT_ACTION("Angle",
                               _("R�gler l'angle d'un objet texte"),
                               _("Modifie l'angle d'un objet texte."),
                               _("Faire _PARAM2__PARAM1_ � l'angle de _PARAM0_"),
                               _("Rotation"),
                               "res/actions/rotate24.png",
                               "res/actions/rotate.png",
                               &ParticleEmitterObject::ActAngle);

                    DECLARE_PARAMETER("object", _("Objet"), true, "ParticleEmitter")
                    DECLARE_PARAMETER("expression", _("Valeur"), false, "")
                    DECLARE_PARAMETER("signe", _("Signe de la modification"), false, "")
                    MAIN_OBJECTS_IN_PARAMETER(0)

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("Angle",
                               _("Angle d'un objet texte"),
                               _("Teste la valeur de l'angle d'un objet texte."),
                               _("L'angle de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                               _("Rotation"),
                               "res/conditions/rotate24.png",
                               "res/conditions/rotate.png",
                               &ParticleEmitterObject::CondAngle);

                    DECLARE_PARAMETER("object", _("Objet"), true, "ParticleEmitter")
                    DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
                    DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
                    MAIN_OBJECTS_IN_PARAMETER(0)

                DECLARE_END_OBJECT_CONDITION()

                DECLARE_OBJECT_EXPRESSION("Opacity", _("Opacit�"), _("Opacit�"), _("Opacit�"), "res/actions/opacity.png", &ParticleEmitterObject::ExpOpacity)
                    DECLARE_PARAMETER("object", _("Objet"), true, "ParticleEmitter")
                DECLARE_END_OBJECT_EXPRESSION()

                DECLARE_OBJECT_EXPRESSION("Angle", _("Angle"), _("Angle"), _("Rotation"), "res/actions/rotate.png", &ParticleEmitterObject::ExpAngle)
                    DECLARE_PARAMETER("object", _("Objet"), true, "ParticleEmitter")
                DECLARE_END_OBJECT_EXPRESSION()

            DECLARE_END_OBJECT()

            CompleteCompilationInformation();
        };
        virtual ~Extension() {};

    protected:
    private:

        /**
         * This function is called by Game Develop so
         * as to complete information about how the extension was compiled ( which libs... )
         * -- Do not need to be modified. --
         */
        void CompleteCompilationInformation()
        {
            #if defined(GDE)
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

            #if defined(GDE)
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
extern "C" ExtensionBase * CreateGDExtension() {
    return new Extension;
}

/**
 * Used by Game Develop to destroy the extension class
 * -- Do not need to be modified. --
 */
extern "C" void DestroyGDExtension(ExtensionBase * p) {
    delete p;
}
