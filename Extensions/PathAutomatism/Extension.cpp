/**

Game Develop - Path Automatism Extension
Copyright (c) 2010-2011 Florian Rival (Florian.Rival@gmail.com)

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
/**
 * Contributors to the extension:
 * Victor Levasseur ( Created Path automatism editor and enhanced extension )
 */

#include "GDL/ExtensionBase.h"
#include "GDL/Version.h"
#include "PathAutomatism.h"
#include <boost/version.hpp>

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
            DECLARE_THE_EXTENSION("PathAutomatism",
                                  _("Automatisme Chemin"),
                                  _("Automatisme permettant de d�placer les objets sur un chemin pr�d�fini"),
                                  "Compil Games",
                                  "zlib/libpng License ( Open Source )")

                DECLARE_AUTOMATISM("PathAutomatism",
                          _("Chemin"),
                          _("Path"),
                          _("Automatisme permettant de d�placer les objets sur un chemin pr�d�fini."),
                          "",
                          "res/path32.png",
                          PathAutomatism,
                          ScenePathDatas)

                    #if defined(GD_IDE_ONLY)

                    automatismInfo.SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_AUTOMATISM_ACTION("SetReverseAtEnd",
                                   _("D�/Activer les allers-retours"),
                                   _("Active ou d�sactive les aller retours"),
                                   _("Activer les allers-retours de _PARAM0_ : _PARAM2_"),
                                   _("Options"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("yesorno", _("Activer"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetReverseAtEnd").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("SetStopAtEnd",
                                   _("D�/Activer l'arr�t � la fin du chemin"),
                                   _("Active ou d�sactive l'arr�t de l'objet � la fin du chemin."),
                                   _("Activer l'arr�t de _PARAM0_ � la fin du chemin : _PARAM2_"),
                                   _("Options"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("yesorno", _("Activer"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetStopAtEnd").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("ReverseAtEnd",
                                   _("Allers-retours"),
                                   _("Renvoie vrai si l'objet effectue des allers-retours"),
                                   _("_PARAM0_ effectue des allers retours"),
                                   _("Options"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("ReverseAtEnd").SetIncludeFile("PathAutomatism/PathAutomatism.h");
                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_CONDITION("StopAtEnd",
                                   _("Arr�t � la fin du chemin"),
                                   _("Renvoie vrai si l'objet s'arr�te � la fin de son chemin."),
                                   _("_PARAM0_ s'arr�te � la fin du chemin"),
                                   _("Options"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("StopAtEnd").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("Reverse",
                                   _("Inverse le sens du mouvement sur le chemin"),
                                   _("Inverse le sens du mouvement sur le chemin."),
                                   _("Inverser le sens du mouvement de l'objet _PARAM0_ sur son chemin"),
                                   _("Mouvement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("Reverse").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("GetSegment",
                                   _("Num�ro du segment sur le chemin"),
                                   _("Renvoie vrai si le num�ro du segment sur le chemin v�rifie bien le test."),
                                   _("_PARAM0_ est sur le segment _PARAM3__PARAM2_"),
                                   _("Position"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe de comparaison"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetCurrentSegment").SetManipulatedType("number").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("EnterSegment",
                                   _("Placer sur un segment du chemin"),
                                   _("Place l'objet sur un segment du chemin."),
                                   _("Placer _PARAM0_ sur le segment _PARAM3__PARAM2_"),
                                   _("Position"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetCurrentSegment").SetAssociatedGetter("GetCurrentSegment").SetManipulatedType("number").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_EXPRESSION("Segment", _("Segment en cours"), _("N� du segment en cours"), _("Position"), "res/actions/window.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetCurrentSegment").SetIncludeFile("PathAutomatism/PathAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_CONDITION("GetPosition",
                                   _("Position de l'objet sur le segment"),
                                   _("Renvoie vrai si la position de l'objet sur le segment v�rifie bien le test.\nValeur comprise entre 0 et 1."),
                                   _("_PARAM0_ est positionn� � _PARAM3__PARAM2_ du segment actuel"),
                                   _("Position"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe de comparaison"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetPositionOnSegment").SetManipulatedType("number").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetPosition",
                                   _("Placer � une position du segment actuel"),
                                   _("Place l'objet � un endroit pr�cis du segment actuel."),
                                   _("Placer _PARAM0_ � _PARAM3__PARAM2_ sur le segment actuel"),
                                   _("Position"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetPositionOnSegment").SetAssociatedGetter("GetPositionOnSegment").SetManipulatedType("number").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_EXPRESSION("Position", _("Position sur segment"), _("Position sur le segment (entre 0 et 1)"), _("Position"), "res/actions/window.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetPositionOnSegment").SetIncludeFile("PathAutomatism/PathAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_CONDITION("GetPathName",
                                   _("Nom du chemin"),
                                   _("Renvoie vrai si le nom du chemion v�rifie bien le test.."),
                                   _("Le nom du chemin actuel de _PARAM0_ est _PARAM3__PARAM2_"),
                                   _("Chemin"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("string", _("Nom"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe de comparaison"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetCurrentPathName").SetManipulatedType("string").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetPathName",
                                   _("Changer de chemin"),
                                   _("Change le chemin utilis� par le chemin."),
                                   _("Mettre _PARAM2_ en tant que chemin � parcourir de _PARAM0_"),
                                   _("Chemin"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("string", _("Nom"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("ChangeCurrentPath").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_STR_EXPRESSION("CurrentPathName", _("Nom du chemin actuel"), _("Nom du chemin actuel"), _("Chemin"), "res/actions/window.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetCurrentPathName").SetIncludeFile("PathAutomatism/PathAutomatism.h");
                    DECLARE_END_AUTOMATISM_STR_EXPRESSION()

                    DECLARE_AUTOMATISM_CONDITION("GetOffsetX",
                                   _("Position X du chemin"),
                                   _("Renvoie vrai si la position X du chemin v�rifie bien le test."),
                                   _("La position X du chemin de _PARAM0_ est _PARAM3__PARAM2_"),
                                   _("Position du chemin"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe de comparaison"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetOffsetX").SetManipulatedType("number").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetOffsetX",
                                   _("Modifier la position X du chemin"),
                                   _("Place le chemin � un endroit pr�cis sur l'axe X."),
                                   _("Mettre la position X du chemin de _PARAM0_ � _PARAM3__PARAM2_"),
                                   _("Position du chemin"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetOffsetX").SetAssociatedGetter("GetOffsetX").SetManipulatedType("number").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_EXPRESSION("PathX", _("Position X du chemin"), _("Position X du chemin"), _("Position du chemin"), "res/actions/window.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetOffsetX").SetIncludeFile("PathAutomatism/PathAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_CONDITION("GetOffsetY",
                                   _("Position Y du chemin"),
                                   _("Renvoie vrai si la position Y du chemin v�rifie bien le test."),
                                   _("La position Y du chemin de _PARAM0_ est _PARAM3__PARAM2_"),
                                   _("Position du chemin"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe de comparaison"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetOffsetY").SetManipulatedType("number").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetOffsetY",
                                   _("Modifier la position Y du chemin"),
                                   _("Place le chemin � un endroit pr�cis sur l'axe Y."),
                                   _("Mettre la position Y du chemin de _PARAM0_ � _PARAM3__PARAM2_"),
                                   _("Position du chemin"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetOffsetY").SetAssociatedGetter("GetOffsetY").SetManipulatedType("number").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_EXPRESSION("PathY", _("Position Y du chemin"), _("Position Y du chemin"), _("Position du chemin"), "res/actions/window.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetOffsetY").SetIncludeFile("PathAutomatism/PathAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_CONDITION("GetFollowAngle",
                                   _("Rotation automatique"),
                                   _("Renvoie vrai l'objet est tourn�e automatiquement sur le chemin."),
                                   _("_PARAM0_ est tourn� automatiquement en fonction du chemin"),
                                   _("Options"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("FollowAngle").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetFollowAngle",
                                   _("D�/Activer la rotation automatique"),
                                   _("Active ou d�sactive la rotation automatique de l'objet sur le chemin."),
                                   _("Activer la rotation automatique de _PARAM0_ ? _PARAM2_"),
                                   _("Options"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("yesorno", _("Activer ?"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetFollowAngle").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("GetAngleOffset",
                                   _("D�calage d'angle"),
                                   _("Renvoie vrai si le d�calage d'angle (de la rotation automatique) v�rifie la condition."),
                                   _("Le d�calage d'angle de _PARAM0_ sur le chemin est _PARAM3__PARAM2_"),
                                   _("Options"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe de comparaison"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetAngleOffset").SetManipulatedType("number").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetAngleOffset",
                                   _("Modifier le d�calage d'angle"),
                                   _("Modifie le d�calage d'angle de la rotation automatique."),
                                   _("Mettre le d�calage d'angle de l'objet _PARAM0_ sur le chemin � _PARAM3__PARAM2_"),
                                   _("Options"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetAngleOffset").SetAssociatedGetter("GetAngleOffset").SetManipulatedType("number").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_EXPRESSION("AngleOffset", _("D�calage d'angle"), _("D�calage d'angle de l'objet sur le chemin"), _("Options"), "res/actions/window.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetAngleOffset").SetIncludeFile("PathAutomatism/PathAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_CONDITION("GetSpeed",
                                   _("Vitesse"),
                                   _("Renvoie vrai si la vitesse v�rifie bien le test."),
                                   _("La vitesse de _PARAM0_ sur le chemin est _PARAM3__PARAM2_"),
                                   _("Mouvement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe de comparaison"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetSpeed").SetManipulatedType("number").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetSpeed",
                                   _("Modifier la vitesse"),
                                   _("Modifie la vitesse de l'objet sur le chemin."),
                                   _("Mettre la vitesse de l'objet _PARAM0_ sur le chemin � _PARAM3__PARAM2_"),
                                   _("Mouvement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetSpeed").SetAssociatedGetter("GetSpeed").SetManipulatedType("number").SetIncludeFile("PathAutomatism/PathAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_EXPRESSION("Speed", _("Vitesse"), _("Vitesse de l'objet sur le chemin"), _("Mouvement"), "res/actions/window.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "PathAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetSpeed").SetIncludeFile("PathAutomatism/PathAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    #endif

                DECLARE_END_AUTOMATISM();

            CompleteCompilationInformation();
        };
        virtual ~Extension() {};

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
