#pragma once
#include "../ecs/System.h"

class RenderSystem : public ecs::System {
public:
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
		// Inicializar el sistema, etc.
	void initSystem() override;
		// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
		// - Dibujar las vidas (siempre).
		// - Dibujar los mensajes correspondiente: si el juego está parado, etc (como en
		// la práctica 1)
	void update() override;

private:
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_. Otra posibilidad es simplemente consultar el valor de
	// winner_ y state_ directamente a GameCtrlSystem (en este caso no hacen falta
	// los siguientes métodos y atributos)
	void onRoundStart();
	void onRoundOver();
	void onGameStart();
	void onGameOver();
	uint8_t winner_; // 0 - None, 1 - Asteroid, 2- Fighter
	uint8_t state_; // El estado actual de juego (como en GameCtrlSystem)
};
