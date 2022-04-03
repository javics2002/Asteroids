#pragma once
#include "../ecs/System.h"
class FighterGunSystem : public ecs::System {
public:
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego no est� parado y el jugador pulsa SDLK_S, enviar un mensaje
	// correspondiente con la caracter�sticas f�sicas de la bala (como en la
	// pr�ctica 1). Recuerda que se puede disparar s�lo una bala cada 0.25sec.
	void update() override;

private:
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
	// Indica si el sistema est� activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no est� activo)
	bool active_;
};

