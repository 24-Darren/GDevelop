/**

Game Develop - A Star Automatism Extension
Copyright (c) 2010-2012 Florian Rival (Florian.Rival@gmail.com)

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
#include "AStarAutomatism.h"
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
            DECLARE_THE_EXTENSION("AStarAutomatism",
                                  _("Automatisme de recherche de chemin ( Pathfinding A* )"),
                                  _("Automatisme permettant de d�placer les objets en �vitant les obstacles."),
                                  "Compil Games",
                                  "zlib/libpng License ( Open Source )")

                DECLARE_AUTOMATISM("AStarAutomatism",
                          _("Recherche de chemin"),
                          _("AStar"),
                          _("Automatisme permettant de d�placer les objets en �vitant les obstacles."),
                          "",
                          "Extensions/AStaricon.png",
                          AStarAutomatism,
                          SceneAStarDatas)

                    #if defined(GD_IDE_ONLY)

                    automatismInfo.SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_AUTOMATISM_ACTION("SetDestination",
                                   _("D�placement vers une position"),
                                   _("D�place l'objet vers une position"),
                                   _("D�placer _PARAM0_ vers _PARAM3_;_PARAM4_"),
                                   _("D�placement"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddCodeOnlyParameter("currentScene", "");
                        instrInfo.AddParameter("expression", _("Position X de la destination"), "", false);
                        instrInfo.AddParameter("expression", _("Position Y de la destination"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("MoveTo").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("SetSpeed",
                                   _("Vitesse"),
                                   _("Change la vitesse de d�placement sur le chemin"),
                                   _("Faire _PARAM3__PARAM2_ � la vitesse de _PARAM0_ sur le chemin"),
                                   _("D�placement"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Vitesse"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetSpeed").SetAssociatedGetter("GetSpeed").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("Speed",
                                   _("Vitesse"),
                                   _("Teste la vitesse de d�placement sur le chemin"),
                                   _("La vitesse de d�placement de _PARAM0_ est _PARAM3_ � _PARAM2_"),
                                   _("D�placement"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Vitesse"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetSpeed").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");


                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetCost",
                                   _("Difficult� de passage"),
                                   _("Change la difficult� de passage au dessus de l'objet. 9 est un obstacle infranchissable."),
                                   _("Faire _PARAM3__PARAM2_ � la difficult� de passage au dessus de _PARAM0_"),
                                   _("Obstacles"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Difficult� ( 0 � 9 )"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetCost").SetAssociatedGetter("GetCost").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("Cost",
                                   _("Difficult� de passage"),
                                   _("Teste la difficult� de passage au dessus de l'objet"),
                                   _("La difficult� de passage au dessus de _PARAM0_ est _PARAM3_ � _PARAM2_"),
                                   _("Obstacles"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Difficult�"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetCost").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");


                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_CONDITION("PathFound",
                                   _("Chemin trouv�"),
                                   _("Renvoi vrai si un chemin a �t� trouv�"),
                                   _("Un chemin a �t� trouv� pour _PARAM0_"),
                                   _("D�placement"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("PathFound").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_CONDITION("DestinationReached",
                                   _("Destination atteinte"),
                                   _("Renvoi vrai si la destination de l'objet a �t� atteinte"),
                                   _("_PARAM0_ a atteint sa destination"),
                                   _("D�placement"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("DestinationReached").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()
                    DECLARE_AUTOMATISM_ACTION("SetGridWidth",
                                   _("Largeur de la grille virtuelle"),
                                   _("Change la largeur des cellules de la grille virtuelle."),
                                   _("Faire _PARAM4__PARAM3_ � la largeur des cellules de la grille virtuelle"),
                                   _("Param�trage global"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddCodeOnlyParameter("currentScene", "");
                        instrInfo.AddParameter("expression", _("Largeur ( pixels )"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetGridWidth").SetAssociatedGetter("GetGridWidth").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");


                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("GridWidth",
                                   _("Largeur de la grille virtuelle"),
                                   _("Teste la largeur des cellules de la grille virtuelle."),
                                   _("La largeur des cellules de la grille virtuelle est _PARAM4_ � _PARAM3_"),
                                   _("Param�trage global"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddCodeOnlyParameter("currentScene", "");
                        instrInfo.AddParameter("expression", _("Largeur ( pixels )"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetGridWidth").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()
                    DECLARE_AUTOMATISM_ACTION("SetGridHeight",
                                   _("Hauteur de la grille virtuelle"),
                                   _("Change la hauteur des cellules de la grille virtuelle."),
                                   _("Faire _PARAM4__PARAM3_ � la hauteur des cellules de la grille virtuelle"),
                                   _("Param�trage global"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddCodeOnlyParameter("currentScene", "");
                        instrInfo.AddParameter("expression", _("Hauteur ( pixels )"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetGridHeight").SetAssociatedGetter("GetGridHeight").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("GridHeight",
                                   _("Hauteur de la grille virtuelle"),
                                   _("Teste la hauteur des cellules de la grille virtuelle."),
                                   _("La hauteur des cellules de la grille virtuelle est _PARAM4_ � _PARAM3_"),
                                   _("Param�trage global"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddCodeOnlyParameter("currentScene", "");
                        instrInfo.AddParameter("expression", _("Hauteur ( pixels )"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetGridHeight").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("EnterSegment",
                                   _("Changer la position sur le chemin"),
                                   _("Change l'�tat d'avancement de l'objet sur le chemin calcul�."),
                                   _("Faire _PARAM3__PARAM2_ � l'�tat de l'avancement de l'objet sur le chemin calcul�"),
                                   _("Avanc�"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Valeur"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("EnterSegment").SetAssociatedGetter("GetCurrentSegment").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("LeftBorder",
                                   _("Bordure gauche"),
                                   _("Teste la taille, en cases virtuelles, de la bordure gauche de l'objet."),
                                   _("La bordure gauche de _PARAM0_ est _PARAM3_ � _PARAM2_"),
                                   _("Param�trage"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Largeur ( en cases virtuelles )"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_CONDITION("RightBorder",
                                   _("Bordure droite"),
                                   _("Teste la taille, en cases virtuelles, de la bordure droite de l'objet."),
                                   _("La bordure droite de _PARAM0_ est _PARAM3_ � _PARAM2_"),
                                   _("Param�trage"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Largeur ( en cases virtuelles )"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_CONDITION("TopBorder",
                                   _("Bordure haute"),
                                   _("Teste la taille, en cases virtuelles, de la bordure haute de l'objet."),
                                   _("La bordure haute de _PARAM0_ est _PARAM3_ � _PARAM2_"),
                                   _("Param�trage"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Largeur ( en cases virtuelles )"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_CONDITION("BottomBorder",
                                   _("Bordure basse"),
                                   _("Teste la taille, en cases virtuelles, de la bordure basse de l'objet."),
                                   _("La bordure basse de _PARAM0_ est _PARAM3_ � _PARAM2_"),
                                   _("Param�trage"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Largeur ( en cases virtuelles )"), "", false);
                        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetLeftBorder",
                                   _("Bordure gauche"),
                                   _("Change la taille, en cases virtuelles, de la bordure gauche de l'objet."),
                                   _("Faire _PARAM3__PARAM2_ � taille de la bordure gauche de _PARAM0_"),
                                   _("Param�trage"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Largeur ( Cases virtuelles )"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetLeftBorder").SetAssociatedGetter("GetLeftBorder").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("SetRightBorder",
                                   _("Bordure droite"),
                                   _("Change la taille, en cases virtuelles, de la bordure droite de l'objet."),
                                   _("Faire _PARAM3__PARAM2_ � taille de la bordure droite de _PARAM0_"),
                                   _("Param�trage"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Largeur ( Cases virtuelles )"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetRightBorder").SetAssociatedGetter("GetRightBorder").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");


                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("SetTopBorder",
                                   _("Bordure haute"),
                                   _("Change la taille, en cases virtuelles, de la bordure haute de l'objet."),
                                   _("Faire _PARAM3__PARAM2_ � taille de la bordure haute de _PARAM0_"),
                                   _("Param�trage"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Largeur ( Cases virtuelles )"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetTopBorder").SetAssociatedGetter("GetTopBorder").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");


                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("SetBottomBorder",
                                   _("Bordure basse"),
                                   _("Change la taille, en cases virtuelles, de la bordure basse de l'objet."),
                                   _("Faire _PARAM3__PARAM2_ � taille de la bordure basse de _PARAM0_"),
                                   _("Param�trage"),
                                   "Extensions/AStaricon24.png",
                                   "Extensions/AStaricon16.png");

                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);
                        instrInfo.AddParameter("expression", _("Largeur ( Cases virtuelles )"), "", false);
                        instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);

                        instrInfo.cppCallingInformation.SetFunctionName("SetBottomBorder").SetAssociatedGetter("GetBottomBorder").SetManipulatedType("number").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_EXPRESSION("Speed", _("Vitesse de d�placement"), _("Vitesse de d�placement sur le chemin"), _("D�placement"), "Extensions/AStaricon16.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetSpeed").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");

                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("Cost", _("Difficult� de passage"), _("Difficult� de passage au dessus de l'objet"), _("Obstacles"), "Extensions/AStaricon16.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetCost").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("LastNodeX", _("Position X du dernier point de passage"), _("Position X du dernier point de passage"), _("D�placement"), "Extensions/AStaricon16.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetLastNodeX").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("LastNodeY", _("Position Y du dernier point de passage"), _("Position Y du dernier point de passage"), _("D�placement"), "Extensions/AStaricon16.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetLastNodeY").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("NextNodeX", _("Position X du prochain point de passage"), _("Position X du prochain point de passage"), _("D�placement"), "Extensions/AStaricon16.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetNextNodeX").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("NextNodeY", _("Position Y du prochain point de passage"), _("Position Y du prochain point de passage"), _("D�placement"), "Extensions/AStaricon16.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetNextNodeY").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("DestinationX", _("Position X de la destination"), _("Position X de la destination"), _("D�placement"), "Extensions/AStaricon16.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetDestinationX").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("DestinationY", _("Position Y de la destination"), _("Position Y de la destination"), _("D�placement"), "Extensions/AStaricon16.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetDestinationY").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("GridWidth", _("Largeur de la grille virtuelle"), _("Largeur de la grille virtuelle"), _("Param�trage global"), "Extensions/AStaricon16.png")
                        instrInfo.AddCodeOnlyParameter("currentScene", "");
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetGridWidth").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("GridHeight", _("Hauteur de la grille virtuelle"), _("Hauteur de la grille virtuelle"), _("Param�trage global"), "Extensions/AStaricon16.png")
                        instrInfo.AddCodeOnlyParameter("currentScene", "");
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetGridHeight").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("LeftBorder", _("Bordure gauche"), _("Bordure gauche"), _("Param�trage"), "Extensions/AStaricon16.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetLeftBorder").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()
                    DECLARE_AUTOMATISM_EXPRESSION("RightBorder", _("Bordure droite"), _("Bordure droite"), _("Param�trage"), "Extensions/AStaricon16.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetRightBorder").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()
                    DECLARE_AUTOMATISM_EXPRESSION("TopBorder", _("Bordure haute"), _("Bordure haute"), _("Param�trage"), "Extensions/AStaricon16.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetTopBorder").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
                    DECLARE_END_AUTOMATISM_EXPRESSION()
                    DECLARE_AUTOMATISM_EXPRESSION("BottomBorder", _("Bordure basse"), _("Bordure basse"), _("Param�trage"), "Extensions/AStaricon16.png")
                        instrInfo.AddParameter("object", _("Objet"), "", false);
                        instrInfo.AddParameter("automatism", _("Automatisme"), "AStarAutomatism", false);

                        instrInfo.cppCallingInformation.SetFunctionName("GetBottomBorder").SetIncludeFile("AStarAutomatism/AStarAutomatism.h");
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
