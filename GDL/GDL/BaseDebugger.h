#if defined(GDE)
/**
 * Game Develop
 *    Editor
 *
 *  Par Florian "4ian" Rival
 *
 */
/**
 *
 *  Classe de base pour cr�er un debugger.
 *  Il suffit de d�river de cette classe et
 *  d'impl�menter la fonction UpdateGUI() qui
 *  sera appel�e � intervalle r�gulier.
 */

#ifndef BASEDEBUGGER_H
#define BASEDEBUGGER_H
#include <SFML/System.hpp>

class GD_API BaseDebugger
{
    public:
        BaseDebugger();
        virtual ~BaseDebugger();

        void Update();

    protected:
    private:
        virtual void UpdateGUI() = 0;

        sf::Clock timeInterval;
};

#endif // BASEDEBUGGER_H
#endif
