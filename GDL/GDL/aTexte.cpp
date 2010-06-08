
#include <vector>
#include <string>
#include <SFML/System.hpp>
#include "GDL/Object.h"
#include <cmath>
#include "GDL/aTexte.h"
#include "GDL/Event.h"
#include <iostream>
#include <sstream>
#include "GDL/Chercher.h"
#include "GDL/CommonTools.h"
#include "GDL/Force.h"
#include <iostream>
#include "GDL/Access.h"
#include "GDL/RuntimeScene.h"



////////////////////////////////////////////////////////////
/// Ecrit du texte
///
/// Type : EcrireTexte
/// Param�tre 1 : Texte
/// Param�tre 2 : X
/// Param�tre 3 : Y
/// Param�tre 4 : Couleur
/// Param�tre 5 : Taille
/// Param�tre 6 : Police
/// Param�tre 7 : Calque
////////////////////////////////////////////////////////////
bool ActEcrireTexte( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    Text texte;
    texte.text.SetString(action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned) );
    texte.text.SetPosition(action.GetParameter( 1 ).GetAsMathExpressionResult(scene, objectsConcerned), action.GetParameter( 2 ).GetAsMathExpressionResult(scene, objectsConcerned));

    vector < string > colors = SpliterStringToVector <string> (action.GetParameter(3).GetAsTextExpressionResult(scene, objectsConcerned), ';');

    if ( colors.size() > 2 )
    {
        texte.text.SetColor(sf::Color(
                                ToInt(colors[0]),
                                ToInt(colors[1]),
                                ToInt(colors[2]) ));
    }

    texte.text.SetCharacterSize(action.GetParameter(4).GetAsMathExpressionResult(scene, objectsConcerned));

    texte.fontName = action.GetParameter(5).GetPlainString();

    //Compatibilit� Game Develop 1.0.4529
    if ( action.GetParameters().size() >= 7 )
        texte.layer = action.GetParameter(6).GetPlainString();

    scene.textes.push_back(texte);

    return true;
}

#undef PARAM
