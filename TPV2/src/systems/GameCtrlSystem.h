#pragma once
#include "../ecs/System.h"
#include <string>
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"

class GameCtrlSystem : public ecs::System {
public:
	__SYSID_DECL__(ecs::_hdlr_GAMECTRL)

	GameCtrlSystem();
	~GameCtrlSystem();

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego está parado no hacer nada, en otro caso mover los asteroides como
	// en la práctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
	// de los 10 al principio de cada ronda).
	void update() override;

	Uint8 winner_; // 0 - None, 1 - Asteroids, 2- Fighter
	Uint8 state_ = 0; // El estado actual del juego (en lugar del componente State)

private:
	// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighter, y si no hay más vidas avisar que ha acabado el juego (y quien
	// es el ganador).
	void onCollision_FighterAsteroid();

	// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
	// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
	void onAsteroidsExtinction();

	void startRound();
	void startGame();

	enum State {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER, // game over
		WIN // win
	};
};

