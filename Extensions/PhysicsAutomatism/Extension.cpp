/** \author

Game Develop - Physic Automatism Extension
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

#include "GDL/ExtensionBase.h"
#include "GDL/Version.h"
#include "PhysicsAutomatism.h"
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
            DECLARE_THE_EXTENSION("PhysicsAutomatism",
                                  _("Automatisme Moteur physique"),
                                  _("Automatisme permettant de d�placer les objets comme si ils �taient soumis aux lois de la physique."),
                                  "Compil Games",
                                  "zlib/libpng License ( Open Source )")

                DECLARE_AUTOMATISM("PhysicsAutomatism",
                          _("Moteur physique"),
                          _("Physics"),
                          _("Automatisme permettant de d�placer les objets comme si ils �taient soumis aux lois de la physique."),
                          "",
                          "res/physics32.png",
                          PhysicsAutomatism,
                          ScenePhysicsDatas)

                    DECLARE_AUTOMATISM_ACTION("SetStatic",
                                   _("Rendre l'objet statique"),
                                   _("Rend l'objet statique physiquement"),
                                   _("Rendre _PARAM0_ statique"),
                                   _("Mouvement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActSetStatic);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("SetDynamic",
                                   _("Rendre l'objet dynamique"),
                                   _("Rend l'objet dynamique ( affect� par les forces et les autres objets )."),
                                   _("Rendre _PARAM0_ dynamique"),
                                   _("Mouvement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActSetDynamic);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("IsDynamic",
                                   _("L'objet est dynamique"),
                                   _("Teste si l'objet est dynamique ( affect� par les forces et les autres objets )."),
                                   _("_PARAM0_ est dynamique"),
                                   _("Mouvement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::CondIsDynamic);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetFixedRotation",
                                   _("Fixer la rotation"),
                                   _("Emp�che l'objet de tourner."),
                                   _("Fixer la rotation de _PARAM0_"),
                                   _("Rotation"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActSetFixedRotation);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("AddRevoluteJoint",
                                   _("Ajouter une charni�re"),
                                   _("Ajoute une charni�re autour de laquelle l'objet va tourner.\nLa distance entre la charni�re et l'objet restera identique � quand l'action sera appel�e."),
                                   _("Ajouter une charni�re � _PARAM0_ � la position _PARAM2_;_PARAM3_"),
                                   _("Joints"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActAddRevoluteJoint);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Position X de la charni�re"), false, "")
                        DECLARE_PARAMETER("expression", _("Position Y de la charni�re"), false, "")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("AddRevoluteJointBetweenObjects",
                                   _("Ajouter une charni�re entre deux objets"),
                                   _("Ajoute une charni�re autour de laquelle l'objet va tourner. "),
                                   _("Ajouter une charni�re entre _PARAM0_ et _PARAM2_"),
                                   _("Joints"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActAddRevoluteJointBetweenObjects);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("object", _("Objet"), true, "")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("ActAddGearJointBetweenObjects",
                                   _("Ajouter une liaison engrenage entre deux objets"),
                                   _("Ajoute une liaison engrenage autour de laquelle l'objet va tourner. "),
                                   _("Ajouter une liaison engrenage entre _PARAM0_ et _PARAM2_"),
                                   _("Joints"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActAddGearJointBetweenObjects);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("object", _("Objet"), true, "")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("SetFreeRotation",
                                   _("Rendre la rotation libre"),
                                   _("Permet � l'objet de tourner."),
                                   _("Permettre � _PARAM0_ de tourner"),
                                   _("Rotation"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActSetFreeRotation);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("IsFixedRotation",
                                   _("Rotation fix�e"),
                                   _("Teste si l'objet a sa rotation fix�e."),
                                   _("_PARAM0_ a sa rotation fix�e"),
                                   _("Rotation"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::CondIsFixedRotation);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetAsBullet",
                                   _("Consid�rer comme un projectile"),
                                   _("Consid�rer l'objet comme un projectile, afin de garantir une meilleure gestion des collisions."),
                                   _("Consid�rer _PARAM0_ comme un projectile"),
                                   _("Autre"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActSetAsBullet);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("DontSetAsBullet",
                                   _("Ne pas consid�rer comme un projectile"),
                                   _("Ne pas consid�rer l'objet comme un projectile, afin d'utiliser une gestion standard des collisions."),
                                   _("Ne pas consid�rer _PARAM0_ comme un projectile"),
                                   _("Autre"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActDontSetAsBullet);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("IsBullet",
                                   _("L'objet est consid�r�e comme un projectile"),
                                   _("Teste si l'objet est consid�r� comme un projectile."),
                                   _("_PARAM0_ est consid�r� comme un projectile"),
                                   _("Autre"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::CondIsBullet);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("ApplyForce",
                                   _("Appliquer une force"),
                                   _("Applique une force � l'objet."),
                                   _("Appliquer � _PARAM0_ une force _PARAM2_;_PARAM3_"),
                                   _("D�placement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActApplyForce);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Composante X"), false, "")
                        DECLARE_PARAMETER("expression", _("Composante Y"), false, "")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("ApplyForceUsingPolarCoordinates",
                                   _("Appliquer une force ( angle )"),
                                   _("Applique une force � l'objet, en utilisant un angle et une longueur comme coordonn�es de cette force."),
                                   _("Appliquer � _PARAM0_ une force d'angle _PARAM2_ et de longueur _PARAM3_"),
                                   _("D�placement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActApplyForceUsingPolarCoordinates);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Angle"), false, "")
                        DECLARE_PARAMETER("expression", _("Longueur"), false, "")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("ApplyForceTowardPosition",
                                   _("Appliquer une force vers une position"),
                                   _("Applique une force, dirig�e vers une position, � l'objet."),
                                   _("Appliquer � _PARAM0_ une force vers la position _PARAM2_;_PARAM3_ de longeur _PARAM4_"),
                                   _("D�placement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActApplyForceTowardPosition);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Position X"), false, "")
                        DECLARE_PARAMETER("expression", _("Position Y"), false, "")
                        DECLARE_PARAMETER("expression", _("Longueur de la force"), false, "")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("ApplyTorque",
                                   _("Appliquer un moment (rotation)"),
                                   _("Applique un moment (rotation) � l'objet."),
                                   _("Appliquer � _PARAM0_ un moment de valeur _PARAM2_"),
                                   _("Rotation"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActApplyTorque);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Valeur du moment"), false, "")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("SetLinearVelocity",
                                   _("Vitesse lin�aire"),
                                   _("Modifie la vitesse de l'objet."),
                                   _("Mettre la vitesse lin�aire de _PARAM0_ � _PARAM2_;_PARAM3_"),
                                   _("D�placement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActLinearVelocity);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Coordonn�e X"), false, "")
                        DECLARE_PARAMETER("expression", _("Coordonn�e Y"), false, "")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("LinearVelocityX",
                                   _("Vitesse lin�aire en X"),
                                   _("Teste la vitesse lin�aire en X de l'objet."),
                                   _("La vitesse lin�aire en X de _PARAM0_ est _PARAM3_ � _PARAM2_"),
                                   _("D�placement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::CondLinearVelocityX);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
                        DECLARE_PARAMETER("signe", _("Signe de la comparaison"), false, "")

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_CONDITION("LinearVelocityY",
                                   _("Vitesse lin�aire en Y"),
                                   _("Teste la vitesse lin�aire en Y de l'objet."),
                                   _("La vitesse lin�aire en Y de _PARAM0_ est _PARAM3_ � _PARAM2_"),
                                   _("D�placement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::CondLinearVelocityY);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
                        DECLARE_PARAMETER("signe", _("Signe de la comparaison"), false, "")

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetAngularVelocity",
                                   _("Vitesse angulaire ( de rotation )"),
                                   _("Modifie la vitesse angulaire de l'objet."),
                                   _("Mettre la vitesse angulaire de _PARAM0_ � _PARAM2_"),
                                   _("Rotation"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActAngularVelocity);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Nouvelle valeur"), false, "")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("AngularVelocity",
                                   _("Vitesse angulaire ( de rotation )"),
                                   _("Teste la vitesse angulaire ( Vitesse de rotation ) de l'objet."),
                                   _("La vitesse angulaire de _PARAM0_ est _PARAM3_ � _PARAM2_"),
                                   _("Rotation"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::CondAngularVelocity);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
                        DECLARE_PARAMETER("signe", _("Signe de la comparaison"), false, "")

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_CONDITION("LinearDamping",
                                   _("Amortissement lin�aire"),
                                   _("Teste l'amortissement lin�aire de l'objet."),
                                   _("L'amortissement lin�aire de _PARAM0_ est _PARAM3_ � _PARAM2_"),
                                   _("D�placement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::CondLinearDamping);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
                        DECLARE_PARAMETER("signe", _("Signe de la comparaison"), false, "")

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_CONDITION("CollisionWith",
                                   _("Collision"),
                                   _("Teste si deux objets sont en contact.\nAttention ! Seul les objets sp�cifi�s en premier, si ils sont en collision avec un des autres objets, seront pris en compte pour les prochaines conditions et actions."),
                                   _("_PARAM0_ est en collision avec un _PARAM2_"),
                                   _("Collision"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::CondCollisionWith);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("object", _("Objet"), true, "")

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetLinearDamping",
                                   _("Amortissement lin�aire"),
                                   _("Modifie l'amortissement lin�aire de l'objet."),
                                   _("Mettre l'amortissement lin�aire de _PARAM0_ � _PARAM2_"),
                                   _("D�placement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActLinearDamping);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Valeur"), false, "")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_CONDITION("AngularDamping",
                                   _("Amortissement angulaire"),
                                   _("Teste l'amortissement angulaire de l'objet."),
                                   _("L'amortissement angulaire de _PARAM0_ est _PARAM3_ � _PARAM2_"),
                                   _("D�placement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::CondAngularDamping);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
                        DECLARE_PARAMETER("signe", _("Signe de la comparaison"), false, "")

                    DECLARE_END_AUTOMATISM_CONDITION()

                    DECLARE_AUTOMATISM_ACTION("SetAngularDamping",
                                   _("Amortissement angulaire"),
                                   _("Modifie l'amortissement angulaire de l'objet."),
                                   _("Mettre l'amortissement angulaire de _PARAM0_ � _PARAM2_"),
                                   _("D�placement"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActAngularDamping);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Valeur"), false, "")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_ACTION("SetGravity",
                                   _("Gravit�"),
                                   _("Modifie la force de gravit�"),
                                   _("Mettre la force de gravit� � _PARAM2_;_PARAM3_"),
                                   _("Options globales"),
                                   "res/actions/window24.png",
                                   "res/actions/window.png",
                                   &PhysicsAutomatism::ActSetGravity);

                        DECLARE_PARAMETER("object", _("Objet"), true, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                        DECLARE_PARAMETER("expression", _("Coordonn�e X"), false, "")
                        DECLARE_PARAMETER("expression", _("Coordonn�e Y"), false, "")

                    DECLARE_END_AUTOMATISM_ACTION()

                    DECLARE_AUTOMATISM_EXPRESSION("LinearVelocityX", _("Vitesse lin�aire en X"), _("Vitesse lin�aire en X"), _("D�placement"), "res/actions/scaleHeight.png", &PhysicsAutomatism::ExpLinearVelocityX)
                        DECLARE_PARAMETER("object", _("Objet"), false, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("LinearVelocityY", _("Vitesse lin�aire en Y"), _("Vitesse lin�aire en Y"), _("D�placement"), "res/actions/scaleHeight.png", &PhysicsAutomatism::ExpLinearVelocityY)
                        DECLARE_PARAMETER("object", _("Objet"), false, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("AngularVelocity", _("Vitesse angulaire"), _("Vitesse angulaire ( de rotation )"), _("Rotation"), "res/actions/scaleHeight.png", &PhysicsAutomatism::ExpAngularVelocity)
                        DECLARE_PARAMETER("object", _("Objet"), false, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("LinearDamping", _("Amortissement lin�aire"), _("Amortissement lin�aire"), _("D�placement"), "res/actions/scaleHeight.png", &PhysicsAutomatism::ExpLinearDamping)
                        DECLARE_PARAMETER("object", _("Objet"), false, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                    DECLARE_END_AUTOMATISM_EXPRESSION()

                    DECLARE_AUTOMATISM_EXPRESSION("LinearDamping", _("Amortissement angulaire"), _("Amortissement angulaire"), _("Rotation"), "res/actions/scaleHeight.png", &PhysicsAutomatism::ExpAngularDamping)
                        DECLARE_PARAMETER("object", _("Objet"), false, "")
                        DECLARE_PARAMETER("automatism", _("Automatisme"), false, "PhysicsAutomatism")
                    DECLARE_END_AUTOMATISM_EXPRESSION()

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
