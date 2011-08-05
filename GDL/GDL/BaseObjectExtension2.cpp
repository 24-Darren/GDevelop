#include "GDL/BaseObjectExtension.h"

void BaseObjectExtension::DeclareExtensionSecondPart()
{
    DECLARE_ACTION("Create",
                   _("Cr�er un objet"),
                   _("Cr�er un objet � la position sp�cifi�e"),
                   _("Cr�er l'objet _PARAM0_ � la position _PARAM1_;_PARAM2_"),
                   _("Objets"),
                   "res/actions/create24.png",
                   "res/actions/create.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameterWithoutPickingThem", "3");
        instrInfo.AddCodeOnlyParameter("listOfAlreadyPickedObjects", "");
        instrInfo.AddParameter("object", _("Objet � cr�er"), "", false);
        instrInfo.AddParameter("expression", _("Position X"), "", false);
        instrInfo.AddParameter("expression", _("Position Y"), "", false);
        instrInfo.AddParameter("layer", _("Calque ( calque de base si vide )"), "", true).SetDefaultValue("\"\"");

        instrInfo.cppCallingInformation.SetFunctionName("CreateObjectOnScene").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("CreateByName",
                   _("Cr�er un objet de partir son nom"),
                   _("Cr�er un objet � la position sp�cifi�e"),
                   _("Cr�er l'objet ayant le nom _PARAM0_ � la position _PARAM1_;_PARAM2_"),
                   _("Objets"),
                   "res/actions/create24.png",
                   "res/actions/create.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddCodeOnlyParameter("mapOfAllObjectLists", "");
        instrInfo.AddCodeOnlyParameter("listOfAlreadyPickedObjects", "");
        instrInfo.AddParameter("string", _("Texte repr�sentant le nom de l'objet � cr�er"), "", false);
        instrInfo.AddParameter("expression", _("Position X"), "", false);
        instrInfo.AddParameter("expression", _("Position Y"), "", false);
        instrInfo.AddParameter("layer", _("Calque ( calque de base si vide )"), "", true).SetDefaultValue("\"\"");

        instrInfo.cppCallingInformation.SetFunctionName("CreateObjectOnScene").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("AjoutObjConcern",
                   _("Prendre en compte des objets"),
                   _("Prend en compte tous les objets ainsi nomm�s de la sc�ne."),
                   _("Prendre en compte tous les _PARAM3_"),
                   _("Objets"),
                   "res/actions/add24.png",
                   "res/actions/add.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameterWithoutPickingThem", "3");
        instrInfo.AddCodeOnlyParameter("listOfAlreadyPickedObjects", "");
        instrInfo.AddParameter("object", _("Objet"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("PickAllObjects").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("AjoutHasard",
                   _("Prendre un objet au hasard"),
                   _("Prend un seul objet ayant ce nom parmi tous ceux de la sc�ne"),
                   _("Prendre un _PARAM0_ au hasard"),
                   _("Objets"),
                   "res/actions/ajouthasard24.png",
                   "res/actions/ajouthasard.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "3");
        instrInfo.AddCodeOnlyParameter("listOfAlreadyPickedObjects", "");
        instrInfo.AddParameter("object", _("Objet"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("PickRandomObject").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("MoveObjects",
                   _("Effectuer le d�placement des objets"),
                   _("Fait bouger les objets en fonction des forces qui leurs sont attribu�s.\nGame Develop appelle par d�faut cette action � la fin de la liste des �v�nements.\nVous pouvez l'appeler et utiliser ensuite les actions de centrage de cam�ra/positionnement d'objets d'interfaces par exemple."),
                   _("Effectuer le d�placement des objets"),
                   _("D�placement"),
                   "res/actions/doMove24.png",
                   "res/actions/doMove.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");

        instrInfo.cppCallingInformation.SetFunctionName("MoveObjects").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_ACTION()

    DECLARE_CONDITION("SeDirige",
                   _("Un objet se dirige vers un autre"),
                   _("Teste si l'objet se dirige vers un autre.\nL'objet 1 doit �tre en mouvement."),
                   _("_PARAM0_ se dirige vers _PARAM1_"),
                   _("D�placement"),
                   "res/conditions/sedirige24.png",
                   "res/conditions/sedirige.png");

        instrInfo.AddParameter("object", _("Objet"), "", false);
        instrInfo.AddParameter("object", _("Objet 2"), "", false);
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "0");
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "1");
        instrInfo.AddParameter("expression", _("Angle de tol�rance"), "", false);
        instrInfo.AddCodeOnlyParameter("conditionInverted", "");

        instrInfo.cppCallingInformation.SetFunctionName("MovesToward").SetIncludeFile("GDL/ObjectTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("Distance",
                   _("Distance entre deux objets"),
                   _("Teste si la distance entre les deux objets correspond au test effectu�"),
                   _("La distance entre les objets _PARAM0_ et _PARAM1_ est _PARAM3_ � _PARAM2_"),
                   _("Position"),
                   "res/conditions/distance24.png",
                   "res/conditions/distance.png");

        instrInfo.AddParameter("object", _("Objet"), "", false);
        instrInfo.AddParameter("object", _("Objet 2"), "", false);
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "0");
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "1");
        instrInfo.AddParameter("expression", _("Distance"), "", false);
        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);
        instrInfo.AddCodeOnlyParameter("conditionInverted", "");

        instrInfo.cppCallingInformation.SetFunctionName("DistanceBetweenObjects").SetIncludeFile("GDL/ObjectTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("AjoutObjConcern",
                   _("Prendre en compte des objets"),
                   _("Prend en compte tous les objets ainsi nomm�s de la sc�ne."),
                   _("Prendre en compte tous les _PARAM3_"),
                   _("Objets"),
                   "res/conditions/add24.png",
                   "res/conditions/add.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameterWithoutPickingThem", "3");
        instrInfo.AddCodeOnlyParameter("listOfAlreadyPickedObjects", "");
        instrInfo.AddParameter("object", _("Objet"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("PickAllObjects").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("AjoutHasard",
                   _("Prendre un objet au hasard"),
                   _("Prend un seul objet ayant ce nom parmi tous ceux de la sc�ne"),
                   _("Prendre un _PARAM0_ au hasard"),
                   _("Objets"),
                   "res/conditions/ajouthasard24.png",
                   "res/conditions/ajouthasard.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "3");
        instrInfo.AddCodeOnlyParameter("listOfAlreadyPickedObjects", "");
        instrInfo.AddParameter("object", _("Objet"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("PickRandomObject").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("NbObjet",
                   _("Nombre d'objets"),
                   _("Teste le nombre d'objet concern�s."),
                   _("Le nombre de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                   _("Objets"),
                   "res/conditions/nbObjet24.png",
                   "res/conditions/nbObjet.png");

        instrInfo.AddParameter("object", _("Objet"), "", false);
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "0");
        instrInfo.AddParameter("expression", _("Valeur � tester"), "", false);
        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("PickedObjectsCount").SetManipulatedType("number").SetIncludeFile("GDL/ObjectTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CollisionNP", //"CollisionNP" cames from an old condition to test collision between two sprites non precisely.
                   _("Collision"),
                   _("Teste la collision entre deux objets en utilisant leurs masques de collisions.\nNotez que certains objets peuvent ne pas avoir de masque de collisions.\nD'autres, comme les Sprites, proposent des conditions de collisions plus pr�cises."),
                   _("_PARAM0_ est en collision avec _PARAM1_ ( Masques de collisions )"),
                   _("Collision"),
                   "res/conditions/collision24.png",
                   "res/conditions/collision.png");

        instrInfo.AddParameter("object", _("Objet"), "", false);
        instrInfo.AddParameter("object", _("Objet"), "", false);
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "0");
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "1");
        instrInfo.AddCodeOnlyParameter("conditionInverted", "");

        instrInfo.cppCallingInformation.SetFunctionName("HitBoxesCollision").SetIncludeFile("GDL/ObjectTools.h");

    DECLARE_END_CONDITION()

    DECLARE_EXPRESSION("Count", _("Nombre d'objets"), _("Compte le nombre d'objets indiqu� actuellement concern�s"), _("Objets"), "res/conditions/nbObjet.png")
        instrInfo.AddParameter("object", _("Objet"), "", false);
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "0");

        instrInfo.cppCallingInformation.SetFunctionName("PickedObjectsCount").SetIncludeFile("GDL/ObjectTools.h");
    DECLARE_END_EXPRESSION()
}
