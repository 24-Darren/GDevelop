/**

Game Develop - Primitive Drawing Extension
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
#include "GDL/Version.h"
#include "DrawerObject.h"
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
            DECLARE_THE_EXTENSION("PrimitiveDrawing",
                          _("Dessin primitif"),
                          _("Extension permettant de dessiner directement des formes et de manipuler des images."),
                          "Compil Games",
                          "zlib/libpng License ( Open Source )")

            //Declaration of all objects available
            DECLARE_OBJECT("Drawer",
                           _("Dessinateur manuel"),
                           _("Objet permettant de dessiner � l'�cran"),
                           "Extensions/primitivedrawingicon.png",
                           &CreateDrawerObject,
                           &DestroyDrawerObject,
                           "DrawerObject");

                #if defined(GD_IDE_ONLY)
                DrawerObject::LoadEdittimeIcon();
                objInfos.SetIncludeFile("PrimitiveDrawing/DrawerObject.h");

                DECLARE_OBJECT_ACTION("Rectangle",
                               _("Rectangle"),
                               _("Dessine un rectangle � l'�cran"),
                               _("Dessiner de _PARAM1_;_PARAM2_ � _PARAM3_;_PARAM4_ un rectangle avec _PARAM0_"),
                               _("Dessin"),
                               "res/actions/rectangle24.png",
                               "res/actions/rectangle.png");

                    instrInfo.AddParameter("object", _("Objet dessinateur"), "Drawer", false);
                    instrInfo.AddParameter("expression", _("Position X du point haut gauche"), "", false);
                    instrInfo.AddParameter("expression", _("Position Y du point haut gauche"), "", false);
                    instrInfo.AddParameter("expression", _("Position X du point bas droit"), "", false);
                    instrInfo.AddParameter("expression", _("Position Y du point bas droit"), "", false);


                    instrInfo.cppCallingInformation.SetFunctionName("DrawRectangle").SetIncludeFile("PrimitiveDrawing/DrawerObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_ACTION("Circle",
                               _("Cercle"),
                               _("Dessine un cercle � l'�cran"),
                               _("Dessiner en _PARAM1_;_PARAM2_ un cercle de rayon _PARAM3_ avec _PARAM0_"),
                               _("Dessin"),
                               "res/actions/circle24.png",
                               "res/actions/circle.png");

                    instrInfo.AddParameter("object", _("Objet dessinateur"), "Drawer", false);
                    instrInfo.AddParameter("expression", _("Position X du centre"), "", false);
                    instrInfo.AddParameter("expression", _("Position Y du centre"), "", false);
                    instrInfo.AddParameter("expression", _("Rayon en pixels"), "", false);


                    instrInfo.cppCallingInformation.SetFunctionName("DrawCircle").SetIncludeFile("PrimitiveDrawing/DrawerObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_ACTION("Line",
                               _("Ligne"),
                               _("Dessine une ligne � l'�cran"),
                               _("Dessiner de _PARAM1_;_PARAM2_ � _PARAM3_;_PARAM4_ une ligne ( �paisseur  : _PARAM5_) avec _PARAM0_"),
                               _("Dessin"),
                               "res/actions/line24.png",
                               "res/actions/line.png");

                    instrInfo.AddParameter("object", _("Objet dessinateur"), "Drawer", false);
                    instrInfo.AddParameter("expression", _("Position X du point de d�part"), "", false);
                    instrInfo.AddParameter("expression", _("Position Y du point de d�part"), "", false);
                    instrInfo.AddParameter("expression", _("Position X du point d'arriv�e"), "", false);
                    instrInfo.AddParameter("expression", _("Position Y du point d'arriv�e"), "", false);
                    instrInfo.AddParameter("expression", _("Epaisseur en pixels"), "", false);


                    instrInfo.cppCallingInformation.SetFunctionName("DrawLine").SetIncludeFile("PrimitiveDrawing/DrawerObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_ACTION("FillColor",
                               _("Couleur de remplissage"),
                               _("Change la couleur de remplissage pour le dessin."),
                               _("Changer la couleur de remplissage de _PARAM0_ en _PARAM1_"),
                               _("Param�trage"),
                               "res/actions/text24.png",
                               "res/actions/text.png");

                    instrInfo.AddParameter("object", _("Objet dessinateur"), "Drawer", false);
                    instrInfo.AddParameter("color", _("Couleur de remplissage"), "", false);


                    instrInfo.cppCallingInformation.SetFunctionName("SetFillColor").SetIncludeFile("PrimitiveDrawing/DrawerObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_ACTION("OutlineColor",
                               _("Couleur du contour"),
                               _("Change la couleur du contour des futurs dessins."),
                               _("Changer la couleur du contour de _PARAM0_ en _PARAM1_"),
                               _("Param�trage"),
                               "res/actions/color24.png",
                               "res/actions/color.png");

                    instrInfo.AddParameter("object", _("Objet"), "Drawer", false);
                    instrInfo.AddParameter("color", _("Couleur"), "", false);


                    instrInfo.cppCallingInformation.SetFunctionName("SetOutlineColor").SetIncludeFile("PrimitiveDrawing/DrawerObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_ACTION("OutlineSize",
                               _("Taille du contour"),
                               _("Modifie la taille du contour des futurs dessins."),
                               _("Faire _PARAM2__PARAM1_ � la taille du contour de _PARAM0_"),
                               _("Param�trage"),
                               "res/actions/outlineSize24.png",
                               "res/actions/outlineSize.png");

                    instrInfo.AddParameter("object", _("Objet"), "Drawer", false);
                    instrInfo.AddParameter("expression", _("Taille en pixels"), "", false);
                    instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);


                    instrInfo.cppCallingInformation.SetFunctionName("SetOutlineSize").SetManipulatedType("number").SetAssociatedGetter("GetOutlineSize").SetIncludeFile("PrimitiveDrawing/DrawerObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("OutlineSize",
                               _("Taille du contour"),
                               _("Teste la taille du contour."),
                               _("La taille du contour de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                               _("Param�trage"),
                               "res/conditions/outlineSize24.png",
                               "res/conditions/outlineSize.png");

                    instrInfo.AddParameter("object", _("Objet"), "Drawer", false);
                    instrInfo.AddParameter("expression", _("Taille � tester"), "", false);
                    instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);


                    instrInfo.cppCallingInformation.SetFunctionName("GetOutlineSize").SetManipulatedType("number").SetIncludeFile("PrimitiveDrawing/DrawerObject.h");

                DECLARE_END_OBJECT_CONDITION()

                DECLARE_OBJECT_ACTION("FillOpacity",
                               _("Opacit� du remplissage"),
                               _("Modifie la transparence du remplissage des futurs dessins."),
                               _("Faire _PARAM2__PARAM1_ � l'opacit� du remplissage de _PARAM0_"),
                               _("Param�trage"),
                               "res/actions/opacity24.png",
                               "res/actions/opacity.png");

                    instrInfo.AddParameter("object", _("Objet"), "Drawer", false);
                    instrInfo.AddParameter("expression", _("Valeur"), "", false);
                    instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);


                    instrInfo.cppCallingInformation.SetFunctionName("SetFillOpacity").SetManipulatedType("number").SetAssociatedGetter("GetFillOpacity").SetIncludeFile("PrimitiveDrawing/DrawerObject.h");


                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("FillOpacity",
                               _("Opacit� du remplissage"),
                               _("Teste la valeur de l'opacit� du remplissage."),
                               _("L'opacit� du remplissage de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                               _("Param�trage"),
                               "res/conditions/opacity24.png",
                               "res/conditions/opacity.png");

                    instrInfo.AddParameter("object", _("Objet"), "Drawer", false);
                    instrInfo.AddParameter("expression", _("Valeur � tester"), "", false);
                    instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);


                    instrInfo.cppCallingInformation.SetFunctionName("GetFillOpacity").SetManipulatedType("number").SetIncludeFile("PrimitiveDrawing/DrawerObject.h");

                DECLARE_END_OBJECT_CONDITION()

                DECLARE_OBJECT_ACTION("OutlineOpacity",
                               _("Opacit� du contour"),
                               _("Modifie l'opacit� du contour des futurs dessins."),
                               _("Faire _PARAM2__PARAM1_ � l'opacit� du contour de _PARAM0_"),
                               _("Param�trage"),
                               "res/actions/opacity24.png",
                               "res/actions/opacity.png");

                    instrInfo.AddParameter("object", _("Objet"), "Drawer", false);
                    instrInfo.AddParameter("expression", _("Valeur"), "", false);
                    instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);


                    instrInfo.cppCallingInformation.SetFunctionName("SetOutlineOpacity").SetManipulatedType("number").SetAssociatedGetter("GetOutlineOpacity").SetIncludeFile("PrimitiveDrawing/DrawerObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("OutlineOpacity",
                               _("Opacit� du contour"),
                               _("Teste la valeur de l'opacit� du contour."),
                               _("L'opacit� du contour de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                               _("Param�trage"),
                               "res/conditions/opacity24.png",
                               "res/conditions/opacity.png");

                    instrInfo.AddParameter("object", _("Objet"), "Drawer", false);
                    instrInfo.AddParameter("expression", _("Valeur � tester"), "", false);
                    instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);


                    instrInfo.cppCallingInformation.SetFunctionName("GetOutlineOpacity").SetManipulatedType("number").SetIncludeFile("PrimitiveDrawing/DrawerObject.h");

                DECLARE_END_OBJECT_CONDITION()

            #endif

            DECLARE_END_OBJECT()

            #if defined(GD_IDE_ONLY)

            DECLARE_ACTION("CopyImageOnAnother",
                           _("Copier une image sur une autre"),
                           _("Copie une image sur une autre.\nNotez qu'il est pr�f�rable que l'image source reste charg�e en m�moire si l'op�ration est r�p�t�e."),
                           _("Copier l'image _PARAM1_ sur _PARAM0_ � l'emplacement _PARAM2_;_PARAM3_"),
                           _("Images"),
                           "res/copy24.png",
                           "res/copyicon.png");

                instrInfo.AddParameter("string", _("Nom de l'image � modifier"), "", false);
                instrInfo.AddParameter("string", _("Nom de l'image source"), "", false);
                instrInfo.AddParameter("expression", _("Position X"), "", false);
                instrInfo.AddParameter("expression", _("Position Y"), "", false);
                instrInfo.AddParameter("yesorno", _("Utiliser la transparence de la source ( non si vide )"), "",false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::PrimitiveDrawingTools::CopyImageOnAnother").SetIncludeFile("PrimitiveDrawing/PrimitiveDrawingTools.h");


            DECLARE_END_ACTION()

            DECLARE_ACTION("CaptureScreen",
                           _("Capturer l'�cran"),
                           _("Effectue une copie de l'�cran et l'enregistre dans le fichier indiqu� et/ou\ndans l'image de la banque d'images indiqu�e."),
                           _("Faire une copie de l'�cran ( L'enregistrer dans le fichier _PARAM1_ et/ou dans l'image _PARAM2_ )"),
                           _("Images"),
                           "res/imageicon24.png",
                           "res/imageicon.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddParameter("string", _("Nom du fichier sous lequel enregistrer la capture"), "", true).SetDefaultValue("");
                instrInfo.AddParameter("string", _("Nom de l'image sous laquelle enregistrer la capture"), "", true).SetDefaultValue("");

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::PrimitiveDrawingTools::CaptureScreen").SetIncludeFile("PrimitiveDrawing/PrimitiveDrawingTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("CreateSFMLTexture",
                           _("Cr�er une image en m�moire"),
                           _("Cr�� une image en m�moire, stock�e dans la banque d'images du jeu.\nVous pouvez par exemple ensuite ouvrir une image depuis le disque et la stocker dedans"),
                           _("Cr�er une image nomm�e _PARAM1_ en m�moire ( Largeur : _PARAM2_, Hauteur : _PARAM3_, Couleur : _PARAM4_ )"),
                           _("Images"),
                           "res/imageicon24.png",
                           "res/imageicon.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddParameter("string", _("Nom de l'image"), "", false);
                instrInfo.AddParameter("expression", _("Largeur"), "", true);
                instrInfo.AddParameter("expression", _("Hauteur"), "", true);
                instrInfo.AddParameter("color", _("Couleur initiale"), "", true).SetDefaultValue("0;0;0");

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::PrimitiveDrawingTools::CreateSFMLTexture").SetIncludeFile("PrimitiveDrawing/PrimitiveDrawingTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("OpenSFMLTextureFromFile",
                           _("Ouvrir une image depuis un fichier"),
                           _("Charge en m�moire une image depuis un fichier."),
                           _("Charger en m�moire le fichier _PARAM1_ dans l'image _PARAM2_"),
                           _("Images"),
                           "res/imageicon24.png",
                           "res/imageicon.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddParameter("file", _("Nom du ficher"), "", false);
                instrInfo.AddParameter("string", _("Nom de l'image"), "", false);

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::PrimitiveDrawingTools::OpenSFMLTextureFromFile").SetIncludeFile("PrimitiveDrawing/PrimitiveDrawingTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("SaveSFMLTextureToFile",
                           _("Enregistrer une image dans un fichier"),
                           _("Enregistre une image dans un fichier."),
                           _("Sauver l'image _PARAM2_ dans le fichier _PARAM1_"),
                           _("Images"),
                           "res/imageicon24.png",
                           "res/imageicon.png");

                instrInfo.AddCodeOnlyParameter("currentScene", "");
                instrInfo.AddParameter("file", _("Nom du ficher"), "", false);
                instrInfo.AddParameter("string", _("Nom de l'image"), "", false);

                instrInfo.cppCallingInformation.SetFunctionName("GDpriv::PrimitiveDrawingTools::SaveSFMLTextureToFile").SetIncludeFile("PrimitiveDrawing/PrimitiveDrawingTools.h");

            DECLARE_END_ACTION()

            #endif


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
