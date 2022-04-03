#pragma once
#include "../ecs/System.h"

class RenderSystem : public ecs::System {
public:
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
		// Inicializar el sistema, etc.
	void initSystem() override;
		// - Dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
		// - Dibujar las vidas (siempre).
		// - Dibujar los mensajes correspondiente: si el juego est� parado, etc (como en
		// la pr�ctica 1)
	void update() override;

private:
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_. Otra posibilidad es simplemente consultar el valor de
	// winner_ y state_ directamente a GameCtrlSystem (en este caso no hacen falta
	// los siguientes m�todos y atributos)
	void onRoundStart();
	void onRoundOver();
	void onGameStart();
	void onGameOver();
	uint8_t winner_; // 0 - None, 1 - Asteroid, 2- Fighter
	uint8_t state_; // El estado actual de juego (como en GameCtrlSystem)
};
